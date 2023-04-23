# CVE-ID

[CVE-2022-32054](https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2022-32054 "https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2022-32054")

# Information

**Vendor of the products:**    Tenda

**Reported by:**    WangJincheng(<wjcwinmt@outlook.com>) & ShaLetian(<ltsha@njupt.edu.cn>)

**Affected products:**    Tenda AC10 V1.0

**Vendor's website:**    [https://www.tenda.com.cn/profile/contact.html](https://www.tenda.com.cn/profile/contact.html "https://www.tenda.com.cn/profile/contact.html")

**Affected firmware version:**    US_AC10V1.0RTL_V15.03.06.26_multi_TD01

**Firmware download address:**    [https://www.tenda.com.cn/download/detail-2939.html](https://www.tenda.com.cn/download/detail-2939.html "https://www.tenda.com.cn/download/detail-2939.html")

# Overview

`Tenda AC10` has a remote code execution vulnerability. Attackers can inject evil command into parameter `lanIp` which will be passed as a part of an argument to `doSystemCmd` and execute arbitrary commands to control the Router.

# Vulnerability details

The vulnerability is detected at `/bin/httpd`.

In the `TendaTelnet` function, the function called `GetValue` gets the value of the key `lan.ip` and then stores it to a local variable called `lan_ip`. Then, the variable `lan_ip` and the string `telnetd -b %s &` is passed as an argument to `doSystemCmd`.

![image](https://github.com/winmt/CVE/blob/main/Tenda%20AC10/pic/1.jpg)

We found that we can set the value of the key `lan.ip` by calling function `fromAdvSetLanip`. The variable `lan_ip` here is got from parameter `lanIp` sent by `POST` request and it will be set as the value of the key `lan.ip` with function `SetValue`.

![image](https://github.com/winmt/CVE/blob/main/Tenda%20AC10/pic/2.jpg)

Above all, attackers can inject evil command into parameter `lanIp` which will be passed as a part of an argument to `doSystemCmd` and execute arbitrary commands to control the Router.

# Exploit vulnerability

Scan ports before exploit the vulnerability.

![image](https://github.com/winmt/CVE/blob/main/Tenda%20AC10/pic/4.jpg)

We use `HackBar` to send data **`lanIp=192.168.0.1;telnetd -l /bin/sh;`** by `POST` request to the URL **`http://192.168.0.1/goform/AdvSetLanip`**.

![image](https://github.com/winmt/CVE/blob/main/Tenda%20AC10/pic/3.jpg)

Then, we scan ports again and dectect that the port `23` which represents `Telnet service` has been opened.

![image](https://github.com/winmt/CVE/blob/main/Tenda%20AC10/pic/5.jpg)

We telnet into the router through port `23` and control it successfully.

![image](https://github.com/winmt/CVE/blob/main/Tenda%20AC10/pic/6.jpg)
