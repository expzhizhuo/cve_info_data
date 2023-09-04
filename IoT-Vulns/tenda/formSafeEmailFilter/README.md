# Tenda F1202, PA202, PW201A, FH1202 Vulnerability

This vulnerability lies in the `/SafeEmailFilter` page on certain Tenda devices.

## Vulnerability Description

* Binary Path: /bin/httpd or /usr/sbin/tenda_httpd
* Entry Url: /SafeEmailFilter
* Affected Versions
    * F1202 V1.2.0.9
    * PA202 V1.1.2.5
    * PW201A V1.1.2.5
    * FH1202 V1.2.0.9
    
There is a **stack-based buffer overflow** vulnerability in page `SafeEmailFilter`. An attacker can set `page` field in requests to launch a denial-of-service or remote-code-execution attack.

![Vulnerability Function](./vuln.png)

In the vulnerability function it reads user provided parameter `page` into `uVar1`, this variable is passed into function `sprintf` without any length check, which may overflow the stack-based buffer `acStack_118`.

## Timeline

