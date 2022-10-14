# Vulnerability Report

Vendor: Tenda

Product: AC1200 Smart Dual-Band WiFi Router

Version: US_AC6V2.0RTL_V15.03.06.51_multi_TDE01(Download Link:https://www.tendacn.com/download/detail-3794.html)


Type: Buffer Overflow


## Vulnerability description

We found a buffer overflow vulnerability in AC1200 with firmware which was released recently, allows remote attackers to destory the execution memory from a crafted request. This can cause a denial of service or impact code execution.

**Remote Command Execution**

In `httpd` binary:

In function 0x4a12cc, the value of `_src` is obtained through websGerVar.

![6](https://user-images.githubusercontent.com/112852902/191786727-2d819c1a-cb5d-43ed-a141-b267dc5b2b97.png)


The `_src` is copied to `info.urls` via strcpy. However, the length of `_src` is not checked, the buffer of `info` is 0x254 bytes. This can lead to buffer overflows.

![7](https://user-images.githubusercontent.com/112852902/191786760-70bc58c8-bcc0-4a1f-9131-4cd56fc8c6ee.png)
![8](https://user-images.githubusercontent.com/112852902/191786763-f6cfecea-6b9d-4ace-99a8-722f298543f8.png)
