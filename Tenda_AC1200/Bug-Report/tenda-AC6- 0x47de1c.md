# Vulnerability Report

Vendor: Tenda

Product: AC1200 Smart Dual-Band WiFi Router

Version: US_AC6V2.0RTL_V15.03.06.51_multi_TDE01(Download Link:https://www.tendacn.com/download/detail-3794.html)


Type: Buffer Overflow


## Vulnerability description

We found a buffer overflow vulnerability in AC1200 with firmware which was released recently, allows remote attackers to destory the execution memory from a crafted request. This can cause a denial of service or impact code execution.

**Remote Command Execution**

In `httpd` binary:

In the function 0x47de1c (readUsb), the `mountpoint` and `filename` are copied to `mntFileName` through sprntf, but there is no length check for these two variables, which will cause the buffer to be destroyed.

![5](https://user-images.githubusercontent.com/112852902/191786536-c306fd3a-3962-42f6-a526-bd09ac96b3b9.png)
