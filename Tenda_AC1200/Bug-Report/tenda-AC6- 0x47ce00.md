# Vulnerability Report

Vendor: Tenda

Product: AC1200 Smart Dual-Band WiFi Router

Version: US_AC6V2.0RTL_V15.03.06.51_multi_TDE01(Download Link:https://www.tendacn.com/download/detail-3794.html)


Type: Buffer Overflow


## Vulnerability description

We found a buffer overflow vulnerability in AC1200 with firmware which was released recently, allows remote attackers to destory the execution memory from a crafted request. This can cause a denial of service or impact code execution.

**Remote Command Execution**

In `httpd` binary:

In function `0x47ce00`, `name` is allocated a buffer of 0x1000 bytes for storing a variable. This value is passed to the 0x47bd44 (rtl_hw_add_list) function for processing.


In 0x47bd44, the `name` is copied to `new` through strcpy. The buffer size allocated by `new` is 0x488. There is no length check for that before copying. This can lead to buffer overflows.
![3](https://user-images.githubusercontent.com/112852902/191786432-4503a74b-0d54-4e54-a922-400ed9d56327.png)

![4](https://user-images.githubusercontent.com/112852902/191786444-3707a53d-e758-4eb4-8735-1aee92383626.png)
