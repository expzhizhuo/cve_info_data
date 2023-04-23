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


Then `pcVar2` is copied into `name` by strcpy. However the length of `pcVar2` is not checked. The buffer for `name` is 64 bytes. The original `recv_buf` length is 4096 bytes, so the length of `pcVar2` may be greater than 64 bytes. This results in a buffer overflow.

![2](https://user-images.githubusercontent.com/112852902/191786318-3be08be8-cec2-4e20-b161-c6b54df56c4f.png)
