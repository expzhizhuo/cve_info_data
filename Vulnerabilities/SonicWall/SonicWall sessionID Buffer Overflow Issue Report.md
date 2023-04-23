# SonicWall sessionID Buffer Overflow Issue Report

## Timeline

- 2021.6.3          Found this issue
- 2021.6.7          Report to SonicWall
- 2021.8.28        CNVD-2021-55354
- 2022.1.10        CVE-2021-20048



## Product information

### The products and/or hardware versions affected

So far, confirmed in SonicWall TZ350(6.5.4.7-83n).

We believe there are much more models suffered from this vulnerability.

<img src="SonicWall sessionID Buffer Overflow Issue Report/image-20220208202841110.png" alt="image-20220208202841110" style="zoom:50%;" />

### Operating system

TZ350: SonicOS Enhanced 6.5.4.0-17n

### Software and/or hardware configuration

Default

## Vulnerability information

There is a buffer overflow vulnerability when handling "sessionID" in SonicWall TZ350.

### Threat model

An attacker can intercept the traffic between router and Internet. That is, an attacker can perform a man-in-the-middle attack on the router. The attacker has the ability to downgrade SSL attacks. (May not be necessary)

### Detailed description of the vulnerability

The location of the vulnerability in SonicWall TZ350(6.5.4.7-83n) firmware is 0x8046E468.

Here is a snapshot around 0x8046E468 which is inside function `sub_8046E1B8`. As we can see, in function `sub_8046E1B8`, it malloc a buffer to store HTTP response and `v8` and `v9` are points to this buffer. `v10` is points to `&v9[255]`.

<img src="SonicWall sessionID Buffer Overflow Issue Report/image-20220208202913075.png" alt="image-20220208202913075" style="zoom:50%;" />

Then, when handling `sessionID`, it use `strcpy` copy `v10` to `dest` without a length check. `dest` is a buff from caller. When the value in a malicious response is too long, it leads a buffer overflow.

<img src="SonicWall sessionID Buffer Overflow Issue Report/image-20220208202940027.png" alt="image-20220208202940027" style="zoom:50%;" />