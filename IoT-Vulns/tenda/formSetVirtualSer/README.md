# Tenda Router Vulnerability on formSetVirtualSer function

This vulnerability lies in the `formSetVirtualSer` function in `httpd` binary on certain Tenda devices.

## Vulnerability Description

* Binary Path: /bin/httpd
* Entry Url: /SetVirtualServerCfg
* Affected Versions
    * AC10 V1.0 V15.03.06.23
    * AC1206 V15.03.06.23
    * AC8 v4 V16.03.34.06
    * AC6 V2.0 V15.03.06.23
    * AC7 V1.0 V15.03.06.44
    * AC5 V1.0 V15.03.06.28
    * AC9 V3.0 V15.03.06.42_multi
    * AC10 v4.0 V16.03.10.13

    
There is a **stack-based buffer overflow** vulnerability in function `formSetVirtualSer`. An attacker can set `list` field in requests to launch a denial-of-service or remote-code-execution attack.

![Vulnerability Function1](./vuln1.png)

![Vulnerability Function2](./vuln2.png)

![Vulnerability Function3](./vuln3.png)

In function `formSetVirtualSer` it reads user provided parameter `list` into `buf`, this variable is passed into function `save_virtualser_data`. In this function, the vulnerable variable is passed into function `sscanf` without any length check, which may overflow the stack-based buffer `lan_ip` and `protocol`.

## Timeline
