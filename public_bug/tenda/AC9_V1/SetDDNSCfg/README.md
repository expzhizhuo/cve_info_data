# Tenda AC9 V1 stack buffer overflow vulnerability

## Overview

- Manufacturer's website: <https://www.tenda.com.cn/>
- Firmware download: <https://www.tenda.com.cn/product/download/AC9.html>

## Vulnerability information

A stack buffer overflow vulnerability has been found in Tenda AC9 V1. If exploited, the vulnerability allows attackers to perform a DoS attack or execute arbitary code.

## Affected version(s)

We have verified this vulnerability in the following version(s):

- V15.03.05.19_multi

![](pic/version.png)

Figure shows the v1 latest firmware ：V15.03.05.19_multi，and V1 and v3 are different hardware.

## Reproduce the vulnerability

First, we login to the shell of the device through telnet and view the `/tmp` directory and the process number of the netctrl program to check that the device is working as expected.

![](pic/reproduce_1.png)

We then use burp suite to send the constructed payload to `/goform/SetDDNSCfg` with the parameter `ddnsDomain` set to 1000 characters.

![](pic/reproduce_2.png)

Then we can find that the netctrl program crashes and there is a coredump file for netctrl generated in the `/tmp` directory. We can also notice that the netctrl program is not restarted after the crash.

![](pic/reproduce_3.png)

## Vulnerability details

The vulnerability exists in function `sub_13724`(I don't know what the exact function name is, it's a function related to handling ddns configurations) in `/bin/netctrl` program, and the source point which sets the relevant configurations is located in function `formSetSysToolDDNS` of the `httpd` program.

First the value of `ddnsDomain` is stored persistently for key `adv.ddns1.domain` in `httpd` program.

![](pic/code_1.png)

Then in function `sub_13724` of `/bin/netctrl`, the previously stored very long string is copied into array `nptr` by function `GetValue` , causing the local variable `i` to be **overwritten** to a large value. And variable `i` is then used to calculate index to array `a1`. Certainly, the calculated index is pretty large so when the program tries to access the invalid address, it crashes.

![](pic/code_2.png)

This analysis above can be verified if we further debug the generated coredump file. We can notice that the local variable `i` is overwritten to `0x62616168`. If we construct a payload that sets a appropriate value for `i` to avoid the program crashes but also overwrites the return address of the function `sub_13724`, we could hijick the control flow to anywhere we want, as well as execute arbitrary code.

![](pic/debug_1.png)

## CVE-ID

unsigned
