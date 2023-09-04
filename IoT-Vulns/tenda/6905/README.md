# Tenda FH1203 Vulnerability

This vulnerability lies in the `form_fast_setting_wifi_set` function which influences the latest version of Tenda FH1203. (The latest version is [V2.0.1.6](https://down.tenda.com.cn/uploadfile/FH1203/fh1203_kfw_V2.0.1.6_cn_svn1134.zip))

## Vulnerability Description

There is a **stack-based buffer overflow** vulnerability in function `form_fast_setting_wifi_set`.

In function `form_fast_setting_wifi_set` it reads user provided parameter `ssid` into `src`, this variable is passed into function `strcpy` without any length check, which may overflow the stack-based buffer `v7` and `v8`.

![Vulnerability Function](./vuln.png)

## Timeline

* 2023-07-10: CVE ID assigned (CVE-2023-37700)
