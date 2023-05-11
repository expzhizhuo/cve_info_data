# Tenda CP3 Unauthenticated RCE

## CVE Number

[CVE-2023-30353](https://www.cve.org/CVERecord?id=CVE-2023-30353)

## Summary

It is possible to execute arbitrary commands with root privileges via Unauthenticated RCE on the Shenzen Tenda Technology IP Camera CP3 V11.10.00.2211041355.

## Tested Versions

Shenzen Tenda Technology IP Camera CP3 V11.10.00.2211041355

## Product URLs

[Vendor Website](https://www.tendacn.com/us/product/CP3v22.html)

## CVSSv3 Score

TBA

## CWE

- CWE-77: Improper Neutralization of Special Elements used in a Command
('Command Injection')

## Details

By sending a forget XML string as the body of a post request to a service exposed by the Tenda CP3 camera it is possible to remotely inject commands that are executed with root privileges.