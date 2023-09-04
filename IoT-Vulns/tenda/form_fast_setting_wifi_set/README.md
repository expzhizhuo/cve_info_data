# Tenda Router Vulnerability on form_fast_setting_wifi_set function

This vulnerability lies in the `form_fast_setting_wifi_set` function in `httpd` binary on certain Tenda devices.

## Vulnerability Description

* Binary Path: /bin/httpd
* Entry Url: /fast_setting_wifi_set
* Affected Versions
    * F1203 V2.0.1.6
    * FH1203 V2.0.1.6
    * FH1205 V2.0.0.7(775)
    
There is a **stack-based buffer overflow** vulnerability in function `form_fast_setting_wifi_set`. An attacker can set `ssid` field in requests to launch a denial-of-service or remote-code-execution attack.

![Vulnerability Function](./vuln.png)

In function `form_fast_setting_wifi_set` it reads user provided parameter `ssid` into `pcVar1`, this variable is passed into function `strcpy` without any length check, which may overflow the stack-based buffer `acStack_d7` and `acStack_97`.

## Timeline
