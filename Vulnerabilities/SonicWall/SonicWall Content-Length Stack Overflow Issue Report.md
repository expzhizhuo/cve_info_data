# SonicWall Content-Length Stack Overflow Issue Report

## Timeline

- 2021.5.20        Found this issue
- 2021.5.26        Report to SonicWall
- 2021.8.28        CNVD-2021-55355
- 2022.1.10        CVE-2021-20046



## Product information

### The products and/or hardware versions affected

So far, confirmed in SonicWall TZ350(6.5.4.7-83n), SOHO(5.9.2.13-7o).

We believe there are much more models suffered from this vulnerability.

### Operating system

TZ350: SonicOS Enhanced 6.5.4.0-17n

SOHO: Unknown

### Software and/or hardware configuration

Default

## Vulnerability information

There is a stack overflow vulnerability when handling "Content-Length" in SonicWall TZ350, and the same problem is also found in SonicWall SOHO.

### Threat model

An attacker can intercept the traffic between router and Internet. That is, an attacker can perform a man-in-the-middle attack on the router. The attacker has the ability to downgrade SSL attacks. (May not be necessary)

### Detailed description of the vulnerability

The location of the vulnerability in SonicWall TZ350(6.5.4.7-83n) firmware is 0x810B0F18.

Here is a snapshot around 0x810B0F18 which is inside function `sub_810B0A30`. As we can see, after get a HTTP response from `sub_80AAE718` and store the response in buffer `v6`. Then it call `sub_810B09D0` to handler field "Content-Length" in HTTP response.

<img src="SonicWall Content-Length Stack Overflow Issue Report/image-20220208202441171.png" alt="image-20220208202441171" style="zoom:50%;" />

In function `sub_810B09D0`, it call `sub_810B0908` to get the value of "Content-Length" and provide a stack buffer `v5` to hold the value.

<img src="SonicWall Content-Length Stack Overflow Issue Report/image-20220208202407108.png" alt="image-20220208202407108" style="zoom:50%;" />

However, in function `sub_810B0908`, it use `strcpy` to copy the value of "Content-Length" to stack buffer which only has 32 bytes length. When the value in a malicious response is more than 32 bytes, it leads a stack overflow.

<img src="SonicWall Content-Length Stack Overflow Issue Report/image-20220208202339493.png" alt="image-20220208202339493" style="zoom:50%;" />