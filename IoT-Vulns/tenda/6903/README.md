# Tenda FH1203 Vulnerability

This vulnerability lies in the `fromAddressNat` function which influences the latest version of Tenda FH1203. (The latest version is [V2.0.1.6](https://down.tenda.com.cn/uploadfile/FH1203/fh1203_kfw_V2.0.1.6_cn_svn1134.zip))

## Vulnerability Description

There is a **stack-based buffer overflow** vulnerability in function `fromAddressNat`.

In function `fromAddressNat` it reads user provided parameter `entrys` and `mitInterface` into `Var` and `v2`, these variables are passed into function `sprintf` without any length check, which may overflow the stack-based buffer `v6`.

![Vulnerability Function](./vuln.png)

## Timeline

* 2023-07-10: CVE ID assigned (CVE-2023-37706)
