# Tenda CP3 Physical Bootloader Access

## CVE Number

[CVE-2023-30351](https://www.cve.org/CVERecord?id=CVE-2023-30351)

## Summary

It is possible to access a root shell of the Shenzen Tenda Technology IP Camera CP3 V11.10.00.2211041355 by exploiting physical access via UART serial interface.

## Tested Versions

Shenzen Tenda Technology IP Camera CP3 V11.10.00.2211041355

## Product URLs

[Vendor Website](https://www.tendacn.com/us/product/CP3v22.html)

## CVSSv3 Score

TBA

## CWE

- CWE-328: Use of Weak Hash
- CWE-798: Use of Hard-coded Credentials

## Details

After extracting the `shadow` file of the Squashfs found in the Tenda CP3 IP Camera flash, it is possible to reverse the hash of the password that can be used to access the root shell via UART serial interface at the end of the boot process.