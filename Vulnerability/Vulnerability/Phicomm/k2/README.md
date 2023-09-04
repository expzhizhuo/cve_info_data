# Phicomm k2 V22.6.529.216 Command Injection vulnerability 

## Firmware information

- Vendor: Phicomm
- Version: k2 V22.6.529.216

![image-20230808111624610](./img/image-20230808111624610.png)

## Affected version

I have verified that **Phicomm k2 V22.6.529.216** products have Command Injection vulnerability, and other series products have not been verified for the time being.

## Vulnerability details

`shadowsocksr.lua`

![image-20230807173247944](./img/image-20230807173247944.png)

It is easy to find that the function concatenates the executed command with the content entered by the user, and directly invokes the luci.sys.call function to execute, resulting in command injection vulnerability.

Similarly, we can find the following functions with similar vulnerabilities.

`timerbooter.lua`

![image-20230807173817369](./img/image-20230807173817369.png)

`wifireboot.lua`

![image-20230807173915293](./img/image-20230807173915293.png)



## Poc

`shadowsocksr.lua`

![image-20230808110020289](./img/image-20230808110020289.png)



`timerbooter.lua`

![image-20230808103054030](./img/image-20230808103054030.png)



`wifireboot.lua`

![image-20230808104134800](./img/image-20230808104134800.png)