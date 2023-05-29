# CVE-2023-28771-PoC
PoC for CVE-2023-28771 based on Rapid7's excellent writeup

Requires the scapy Python library for sending IKE packets.

```
usage: CVE-2023-28771-poc.py [-h] [--cmd CMD] [--lhost LHOST] [--lport LPORT] rhost

positional arguments:
  rhost

options:
  -h, --help     show this help message and exit
  --cmd CMD
  --lhost LHOST
  --lport LPORT
```

Either use --cmd to run an arbitrary command, or use --lport and --lhost to spawn a revshell
