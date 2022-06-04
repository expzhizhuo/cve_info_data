HTTP/1.1 200 OK
Content-Type: text/xml; charset=utf-8

<?
echo "\<\?xml version='1.0' encoding='utf-8'\?\>";

include "/htdocs/phplib/xnode.php";
include "/htdocs/phplib/inf.php";
include "/htdocs/phplib/trace.php";
include "/htdocs/webinc/config.php";

$nodebase = "/runtime/hnap/SetVirtualServerSettings";
$node_info = $nodebase."/VirtualServerList/VirtualServerInfo";
$vsvr= "/nat/entry/virtualserver";
$vsvr_entry = $vsvr."/entry";

$result = "OK";

function getWOLMAC($ipv4addr)
{
	$cmd = "scut -p ".$ipv4addr." -f 3 /proc/net/arp";
	setattr("/runtime/wakeonlan/mac", "get", $cmd);
	$mac = get("", "/runtime/wakeonlan/mac");
	del("/runtime/wakeonlan/mac");
	return $mac;
}

foreach($node_info) //Prevent the security issue of Command Injection
{
	if(isdigit(get("x", "InternalPort"))==0 || isdigit(get("x", "ExternalPort"))==0)
	{
		$result = "ERROR";
		break;
	}
}

if($result == "OK")
{
	set("/runtime/hnap/dummy", "");
	movc($vsvr, "/runtime/hnap/dummy"); //Remove the children nodes of /nat/entry/virtualserver
	del("/runtime/hnap/dummy");

	set($vsvr."/seqno", "1");
	set($vsvr."/max", "24");
	set($vsvr."/count", "0");

	foreach($node_info)
	{
		set($vsvr."/seqno", $InDeX+1);
		set($vsvr."/count", $InDeX);

		$enable = get("x", "Enabled");
		if ($enable == "true") { set($vsvr_entry.":".$InDeX."/enable", "1"); }
		else { set($vsvr_entry.":".$InDeX."/enable", "0"); }

		set($vsvr_entry.":".$InDeX."/uid", "VSVR-".$InDeX);

		$schedule = get("x", "ScheduleName");
		set($vsvr_entry.":".$InDeX."/schedule", XNODE_getscheduleuid($schedule));

		set($vsvr_entry.":".$InDeX."/inbfilter", "");

		$description = get("x", "VirtualServerDescription");
		set($vsvr_entry.":".$InDeX."/description", $description);

		$protocol = get("x", "ProtocolType");
		if($protocol=="Both") $protocol = "TCP+UDP";
		set($vsvr_entry.":".$InDeX."/protocol", $protocol);

		if ($protocol == "TCP") {$protocolnum = 6;}
		else if ($protocol == "UDP") {$protocolnum = 17;}
		else if ($protocol == "TCP+UDP") {$protocolnum = 256;}
		else if ($protocol == "Other") {$protocolnum = get("x", "ProtocolNumber");}

		set($vsvr_entry.":".$InDeX."/protocolnum", $protocolnum);

		set($vsvr_entry.":".$InDeX."/internal/inf", $LAN1);
		$ipv4addr = get("x", "LocalIPAddress");
		$mask = INF_getcurrmask($LAN1);
		$hostid = ipv4hostid($ipv4addr, $mask);
		set($vsvr_entry.":".$InDeX."/internal/hostid", $hostid);

		$internal = get("x", "InternalPort");
		set($vsvr_entry.":".$InDeX."/internal/start", $internal);

		set($vsvr_entry.":".$InDeX."/tport_str", "");
		set($vsvr_entry.":".$InDeX."/uport_str", "");

		$external = get("x", "ExternalPort");
		set($vsvr_entry.":".$InDeX."/external/start", $external);
		set($vsvr_entry.":".$InDeX."/external/end", $external);

		if($description == "Wake-On-Lan")
		{
			$wolmac = getWOLMAC($ipv4addr);
			set($vsvr_entry.":".$InDeX."/wakeonlan_mac", $wolmac);
		}
	
		TRACE_debug("$enable=".$enable);
		TRACE_debug("$schedule=".$schedule);
		TRACE_debug("$description=".$description);
		TRACE_debug("$ipv4addr=".$ipv4addr);
		TRACE_debug("$mask=".$mask);
		TRACE_debug("$hostid=".$hostid);
		TRACE_debug("$protocol=".$protocol);
		TRACE_debug("$internal=".$internal);
		TRACE_debug("$external=".$external);
	}
}

if($result == "OK")
{
	fwrite("a",$ShellPath, "event DBSAVE > /dev/console\n");
	fwrite("a",$ShellPath, "service VSVR.NAT-1 restart > /dev/console\n");
	fwrite("a",$ShellPath, "xmldbc -s /runtime/hnap/dev_status '' > /dev/console\n");
	set("/runtime/hnap/dev_status", "ERROR");
}
else
{
	fwrite("a",$ShellPath, "echo \"We got a error in setting, so we do nothing...\" > /dev/console");
}

?>
<soap:Envelope xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" 
	xmlns:xsd="http://www.w3.org/2001/XMLSchema" 
	xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/">
	<soap:Body>
    <SetVirtualServerSettingsResponse xmlns="http://purenetworks.com/HNAP1/">
      <SetVirtualServerSettingsResult><?=$result?></SetVirtualServerSettingsResult>
    </SetVirtualServerSettingsResponse>
  </soap:Body>
</soap:Envelope>