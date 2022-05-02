### Affected device

production: EX300_v2   
version: V4.0.3c.140_B20210429  

production: A720R  

version:V4.1.5cu.470_B20200911

### Vulnerability description

A denial-of-service vulnerability was found in  totolink EX300_v2, ver V4.0.3c.140_B20210429 and A720R ,ver V4.1.5cu.470_B20200911 in web server.
A successful exploit allow an adjacent  attacker to exhaust storage space, leading to a DoS condition.

`ExportSettings.sh` will append some data to /var/config.dat file, if send requests  to `http://[target]/ExportSettings.sh` a lot of times,  `config.dat` will exhaust the space of device and result in a DoS condition.

- ExportSettings.sh

```sh
#!/bin/sh
eval `flash get HARDWARE_MODEL`
dateStr=`date  '+%Y%m%d'`
filename=\"Config-$HARDWARE_MODEL-$dateStr.dat\"
eval `flash get CSID`
echo $CSID >>/var/config.dat   # here

echo "Pragma: no-cache\n"
echo "Cache-control: no-cache\n"
echo "Content-type: application/octet-stream"
echo "Content-Transfer-Encoding: binary"                        #  "\n" make Un*x happy
echo "Content-Disposition: attachment; filename=$filename"
echo ""

cat /var/config.dat 2>/dev/null
```



