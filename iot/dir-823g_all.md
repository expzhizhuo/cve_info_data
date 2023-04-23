# DIR-823G HNAP Command injection #


DIR-823G
An issue was discovered on D-Link DIR-823G devices with firmware V1.0.2B05. Implement command injection vulnerability in any parameter of the following function.
## Vulnerable Firmware Versions ##
**DIR-823G REVA1 1.02B05(Lastest) **

## Analysis ##
**Command injection in HNAP1 Function**


**payload1:**

![setmulitipleaction.png](https://i.loli.net/2020/09/09/JfmueKDbHG9OV2r.png)

**result1 **

![mulitact_result.png](https://i.loli.net/2020/09/09/CnVJZ84p3LyHWwr.png)

**Before:**

![ggns_init.png](https://i.loli.net/2020/09/09/HCEsX6FVSv2QxUb.png)

**payload2 After: **

![ggns_after.png](https://i.loli.net/2020/09/09/QoxYqTE4SdaAneu.png)

**result**

![ggns_result.png](https://i.loli.net/2020/09/09/H2rKcBVY8RiZx3A.png)

**So,Each parameter in the following function should trigger the vulnerability.**


    SetMultipleActions 
    GetDeviceSettings 
    GetOperationMode 
    GetSmartconnectSettings 
    GetUplinkInterface 
    Login 
    GetWLanRadioSettings 
    GetClientInfo 
    SetClientInfo 
    UpdateClientInfo 
    GetWLanRadioSecurity 
    SetDeviceSettings 
    GetAPClientSettings 
    SetAPClientSettings 
    SetWLanRadioSettings 
    SetWLanRadioSecurity 
    GetParentsControlInfo 
    SetParentsControlInfo 
    SetSmartconnectSettings 
    GetInternetConnUpTime 
    GetAutoRebootSettings 
    SetAutoRebootSettings 
    SetFactoryDefault 
    RunReboot 
    GetFirmwareValidation 
    GetFirmwareStatus 
    GetCAPTCHAsetting 
    GetFactoryDefault 
    GetSystemUpTime 
    GetCurrentInternetStatus 
    GetWanCurrentStatus 
    SetTriggerADIC 
    GetWanStatus 
    GetMyDLinkSettings 
    GetMACFilters2 
    GetRouterLanSettings 
    SetWPSSettings 
    GetWPSSettings 
    GetScheduleSettings 
    GetAdvNetworkSettings 
    SetAdvNetworkSettings 
    SetRouterLanSettings 
    GetGuestNetworkSettings 
    GetWanSpeedTest 
    SetWanSpeedTest 
    GetQoSManagementType 
    SetQoSManagementType 
    GetQoSSettings 
    SetQoSSettings 
    GetFirewallSettings 
    SetFirewallSettings 
    GetDMZSettings 
    SetDMZSettings 
    GetVirtualServerSettings 
    SetVirtualServerSettings 
    GetIPv4FirewallSettings 
    SetIPv4FirewallSettings 
    StartFirmwareDownload 
    PollingFirmwareDownload 
    FirmwareDownloadCancel 
    SetAutoUpgradeFirmware 
    GetAutoUpgradeFirmware 
    GetWanSettings 
    SetWanSettings 
    GetWanConnectionType 
    GetWanplugInfo 
    CheckPasswdSettings 
    SetPasswdSettings 
    GetLocalMacAddress 
    SetIgnoreWizardConfig 
    GetNTPServerSettings 
    SetNTPServerSettings 
    GetDeviceDomainName 
    SetPPPoEServerSettings 
    GetPPPoEServerStatus 
    GetLanWanConflictInfo 
    SetLanWanConflictInfo 
    GetNetworkSettings 
    SetNetworkSettings 
    GetDHCPClientInfo 
    GetStaticClientInfo 
    SetStaticClientInfo 
    SetGuestWLanSettings 
    GetGuestWLanSettings 
    GetUpnpSettings 
    SetUpnpSettings 
    GetStaticRouteSettings 
    SetStaticRouteSettings 
    GetGuestZoneRouterSettings 
    GetDDNSSettings 
    SetDDNSSettings 
    GetNetworkTomographySettings 
    SetNetworkTomographySettings 
    GetNetworkTomographyResult 
    GetRouterInformationSettings 
    GetWifiDownSettings 
    SetWifiDownSettings 
    SetAccessCtlSwitch 
    GetAccessCtlSwitch 
    SetAccessCtlList 
    GetAccessCtlList 

**Vulnerability Description**

This occurs in /bin/goahead when a HNAP API function trigger a call to the system function with untrusted input form the request body.A attacker can execute any command remotely when they control this input.


    la  $v0, aEchoSVarHnaplo  # "echo '%s' >/var/hnaplog"
    addiu   $v1, $fp, 0x1448+var_1390
    move $a0, $v1 A
    li  $a1, 0x1387
    move $a2, $v0
    lw  $a3, 0x1448+arg_18($fp)
    jal snprintf
    nop
    addiu   $v0, $fp, 0x1448+var_1390
    move $a0, $v0 
    jal system

