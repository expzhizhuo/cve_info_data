# D-link 882 DIR882A1_FW130B06 has a commend injection vulnerability

## Overview

- **Type**: command injection vulnerability
- **Vendor**: Dlink (http://www.dlink.com.cn/)
- **Products**: WiFi Router D-Link 882 DIR882A1_FW130B06
- **Firmware download address:** http://www.dlinktw.com/techsupport/ProductInfo.aspx?m=DIR-882

## Description

### 1.Product Information:

![image-20220308211351254](images/image-20220308211351254.png)



### 2.Vulnerability details

D-link 882 DIR882A1_FW130B06 can start telnet without auth.

![image-20220308210756290](images/image-20220308210756290.png)

After we start telnet and use `admin`  with admin password add `@twsz2018`, we can login telnet. And the Router will return a  constrained shell like this.

![image-20220308213334152](images/image-20220308213334152.png)

![image-20220308210842276](images/image-20220308210842276.png)

Use `/usr/bin/cli` , But in this binary there is a commend injection vulnerability, we can make commend like this `ping 1.1.1.1 & ps` to bypass.

![image-20220308213823655](images/image-20220308213823655.png)

![image-20220308210918955](images/image-20220308210918955.png)



### 3.Recurring vulnerabilities and POC

In order to reproduce the vulnerability, the following steps can be followed:

1. Boot the firmware by qemu-system or other ways (real machine)
2. Telnet router
3. Execute commend

