# D-Link DIR845L contains Static Default Credential Vulnerability

## overview

- type: static default credential vulnerability 

- supplier: D-Link (https://www.dlink.com)

- product: D-Link DIR845L

- firmware download:  https://ftp.dlink.de/dir/dir-845l/archive/driver_software/DIR-845L_fw_reva_100b20_ALL_de_20121123.zip

- affect version: D-Link DIR845L v1.00-v1.03 

## Description

### 1. Vulnerability Details

A vulnerability in the Telnet service of D-Link DAP1522 could allow an unauthenticated, remote attacker to take full control of the device . The vulnerability exists because a system account has a default and static password. An attacker could exploit this vulnerability by using this default account to connect to the affected system. A successful exploit could allow the attacker to gain full control of an affected device. 

In /etc/init0.d/S80telnetd.sh 

![image-20220817001614610](readme.assets/image-20220817001614610.png)

### 2. Recurring loopholes and POC

To reproduce the vulnerability, the following steps can be followed: 

Start frimware through QEMU system or other methods (real device) 

use the default username and password to login telnet 

![image-20220817001657667](readme.assets/image-20220817001657667.png)