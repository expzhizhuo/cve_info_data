# Vulnerability Report

Vendor: TP-Link

Product: AC1900 Wireless Gigabit Access Point

Version: AP500(US)_V1_180320(Beta)(Download Link:https://www.tp-link.com/us/support/download/ap500/#Firmware)


Type: Buffer Overflow


## Vulnerability description

We found a buffer overflow vulnerability in AC1900 with firmware which was released recently, allows remote attackers to destory the execution memory from a crafted request. This can cause a denial of service or impact code execution.

**Remote Command Execution**

In `wl` binary:

There is a stack overflow vulnerability caused by strncpy. Details as follow：

In function 0x32384, the length of `_nptr_00` is not limited.


![9](https://user-images.githubusercontent.com/112852902/191786850-d049e346-e528-491c-a9ff-44b4ac378a5f.png)

The buffer size of the destination (`acStack88`) is 32 bytes.

![10](https://user-images.githubusercontent.com/112852902/191786857-5bede81d-7cff-4de2-9d32-daca8329aef6.png)


If the length of `_nptr_00` is greater than 40 bytes, it will cause stack overflow.
![11](https://user-images.githubusercontent.com/112852902/191786875-8ad1f9d3-56cc-41a0-9fde-9c1f289e66c1.png)


