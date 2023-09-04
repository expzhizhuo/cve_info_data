# Tenda FH1203 Vulnerability

This vulnerability lies in the `addWifiMacFilter` function which influences the latest version of Tenda FH1203. (The latest version is [V2.0.1.6](https://down.tenda.com.cn/uploadfile/FH1203/fh1203_kfw_V2.0.1.6_cn_svn1134.zip))

## Vulnerability Description

There is a **stack-based buffer overflow** vulnerability in function `addWifiMacFilter`.

In function `addWifiMacFilter` it reads user provided parameter `deviceId` into `Var`, and `deviceMac` into `v4`, and these variables are passed into function `sprintf` without any length check, which may overflow the stack-based buffer `v8`.

![Vulnerability Function](./vuln.png)

## Timeline

* 2023-07-10: CVE ID assigned (CVE-2023-37701)
