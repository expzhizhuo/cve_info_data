# Tenda CP3 Network Credential Disclosure

## CVE Number

[CVE-2023-30354](https://www.cve.org/CVERecord?id=CVE-2023-30354)

## Summary

It is possible to exfiltrate WiFi credentials from a Shenzen Tenda Technology IP Camera CP3 V11.10.00.2211041355 by exploiting physical access via UART serial interface.

## Tested Versions

Shenzen Tenda Technology IP Camera CP3 V11.10.00.2211041355

## Product URLs

[Vendor Website](https://www.tendacn.com/us/product/CP3v22.html)

## CVSSv3 Score

TBA

## CWE

- CWE-319: Cleartext Transmission of Sensitive Information

## Details

By connecting via the UART interface to the Tenda IP Camera CP3 it is possible to access to the output of U-Boot. If the camera is connected to a WiFi network, the credentials used to connect to the network are printed in clear by U-Boot.