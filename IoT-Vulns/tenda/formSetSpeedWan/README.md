# Tenda Router Vulnerability on formSetSpeedWan function

This vulnerability lies in the `formSetSpeedWan` function in `httpd` binary on certain Tenda devices.

## Vulnerability Description

* Binary Path: /bin/httpd
* Entry Url: /SetSpeedWan
* Affected Versions
    * AC10 V1.0 V15.03.06.23
    * AC1206 V15.03.06.23
    * AC6 V2.0 V15.03.06.23
    * AC7 V1.0 V15.03.06.44
    * F1203 V2.0.1.6
    * AC5 V1.0 V15.03.06.28
    * FH1203 V2.0.1.6
    * AC9 V3.0 V15.03.06.42_multi
    * FH1205 V2.0.0.7(775)
    
There is a **stack-based buffer overflow** vulnerability in function `formSetSpeedWan`. An attacker can set `speed_dir` field in requests to launch a denial-of-service or remote-code-execution attack.

![Vulnerability Function1](./vuln1.png)

![Vulnerability Function2](./vuln2.png)

![Vulnerability Function3](./vuln3.png)

In function `formSetSpeedWan` it reads user provided parameter `speed_dir` into `__nptr`, this variable is passed into function `sprintf` without any length check, which may overflow the stack-based buffer `ref_buf`.

## Timeline
