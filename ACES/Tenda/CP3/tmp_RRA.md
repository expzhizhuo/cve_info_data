# Tenda CP3 Remote Root Access

## CVE Number

[CVE-2023-30351](https://www.cve.org/CVERecord?id=CVE-2023-30351)

## Summary

It is possible to access a root console of the Shenzen Tenda Technology IP Camera CP3 V11.10.00.2211041355 by exploiting hardcoded and weak access credentials.

## Tested Versions

Shenzen Tenda Technology IP Camera CP3 V11.10.00.2211041355

## Product URLs

[Vendor Website](https://www.tendacn.com/us/product/CP3v22.html)

## CVSSv3 Score

TBA

## CWE

- CWE-798: Use of Hard-coded Credentials

## Details

By using weak credentials (reversed from the content of the `shadow` file found in the camera fs) it is possible to access a root shell on the Tenda CP3 IP Camera via telnet.