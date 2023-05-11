# Tenda CP3 Physical Bootloader Access

## CVE Number

[CVE-2023-30354](https://www.cve.org/CVERecord?id=CVE-2023-30354)

## Summary

It is possible to access to the bootloader of the Shenzen Tenda Technology IP Camera CP3 V11.10.00.2211041355 by exploiting physical access via UART serial interface.

## Tested Versions

Shenzen Tenda Technology IP Camera CP3 V11.10.00.2211041355

## Product URLs

[Vendor Website](https://www.tendacn.com/us/product/CP3v22.html)

## CVSSv3 Score

TBA

## CWE

- CWE-798: Use of Hard-coded Credentials

## Details

By interrupting the U-Boot process and inserting the boot password (found hardcoded in the image of the camera) it is possible to obtain root access to the U-Boot console. 