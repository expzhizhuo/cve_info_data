# Vulnerability Report

Vendor: Tenda

Product: AC1200 Smart Dual-Band WiFi Router

Version: US_AC6V2.0RTL_V15.03.06.51_multi_TDE01(Download Link:https://www.tendacn.com/download/detail-3794.html)


Type: Buffer Overflow


## Vulnerability description

We found a buffer overflow vulnerability in AC1200 with firmware which was released recently, allows remote attackers to destory the execution memory from a crafted request. This can cause a denial of service or impact code execution.

**Remote Command Execution**

In `httpd` binary:

In function `0x47c5dc`, take the content before ';' of `recv_buf` to `pcVar2` through strchr. If the content is not empty, then take the content after the 'set' and store it in `pcVar2`.


Then use strchr to take the content after '=' of  `pcVar2`  and store it in `pvalue`. But the length of `pvalue` is not checked and copied into `value` by strcpy. The length of `value` is 1024 bytes. The original `recv_buf` length is 4096 bytes, so the length of the `pvalue` may be greater than 1024 bytes. This results in a buffer overflow.
![1](https://user-images.githubusercontent.com/112852902/191786210-9d10fcf9-91db-40ee-8ead-d9a1e4e0f497.png)
