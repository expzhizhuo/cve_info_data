# Tenda CP3 Malicious Upgrade

## CVE Number

[CVE-2023-30356](https://www.cve.org/CVERecord?id=CVE-2023-30356)

## Summary

It is possible to trigger the update of the Shenzen Tenda Technology IP Camera CP3 V11.10.00.2211041355 using maliciously-forged firmware images.

## Tested Versions

Shenzen Tenda Technology IP Camera CP3 V11.10.00.2211041355

## Product URLs

[Vendor Website](https://www.tendacn.com/us/product/CP3v22.html)

## CVSSv3 Score

TBA

## CWE

- CWE-798: Use of Hard-coded Credentials
- CWE-353: Missing Support for Integrity Check

## Details

By triggering the update procedure on the camera with a maliciously-modified firmware it is possibile to overwrite the official firmware and to prevent future updates. Any modification to the firmware is persistent.

### Related CVEs:
