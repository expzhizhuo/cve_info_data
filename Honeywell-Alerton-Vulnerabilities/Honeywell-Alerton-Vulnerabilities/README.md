# Honeywell-Alerton-Vulnerabilities
Alerton Ascent Control Module (ACM) &amp; Alerton Visual Logic vulnerabilities 


CVE-2022-30242
--
[Suggested description]
Alerton Ascent Control Module (ACM) through 2022-05-04 allows unauthenticated configuration
changes from remote users. This enables configuration data to be stored
on the controller and then implemented. A user with malicious intent
can send a crafted packet to change the controller
configuration without the knowledge of other users, altering the
controller's function capabilities. The changed configuration is not
updated in the User Interface, which creates an inconsistency between
the configuration display and the actual configuration on the
controller. After the configuration change, remediation requires
reverting to the correct configuration, requiring either physical or
remote access depending on the configuration that was altered.

[VulnerabilityType Other]
Configuration Change (CWE 15)

[Vendor of Product]
Honeywell International Inc

[Affected Product Code Base]
Alerton Ascent Control Module (ACM) - latest

[Affected Component]
Controller Operations

[Attack Type]
Remote

[CVE Impact Other]
Configuration Change

[Attack Vectors]
Remote, send specially crafted packet

[Discoverer]
Adam Engelhart - SCADAfence

[Reference]
https://blog.scadafence.com
https://www.honeywell.com/us/en/product-security

----------------------------------------------------------------------------------------------------------------

CVE-2022-30243
--
[Suggested description]
Alerton Visual Logic through 2022-05-04 allows unauthenticated programming writes
from remote users. This enables code to be stored on the controller and
then run without verification. A user with malicious intent can send a
crafted packet to change and/or stop the program without the
knowledge of other users, altering the controller's function. After the
programming change, the program needs to be overwritten in order for
the controller to restore its original operational function.

[VulnerabilityType Other]
Inclusion of functionality from untrusted control sphere (CWE-829)

[Vendor of Product]
Honeywell International Inc

[Affected Product Code Base]
Alerton Visual Logic - latest

[Affected Component]
Controller Operations

[Attack Type]
Remote

[Impact Code execution]
true

[Attack Vectors]
Remote, send specially crafted packet

[Discoverer]
Adam Engelhart - SCADAfence

[Reference]
https://blog.scadafence.com
https://www.honeywell.com/us/en/product-security

----------------------------------------------------------------------------------------------------------------

CVE-2022-30244
--
[Suggested description]
Alerton Ascent Control Module (ACM) through 2022-05-04 allows unauthenticated programming writes
from remote users. This enables code to be store on the controller and
then run without verification. A user with malicious intent can send a
crafted packet to change and/or stop the program without the
knowledge of other users, altering the controller's function. After the
programming change, the program needs to be overwritten in order for
the controller to restore its original operational function.

[VulnerabilityType Other]
Inclusion of functionality from untrusted control sphere (CWE-829)

[Vendor of Product]
Honeywell International Inc

[Affected Product Code Base]
Alerton Ascent Control Module (ACM) - latest

[Affected Component]
Controller Operations

[Attack Type]
Remote

[Impact Code execution]
true

[Attack Vectors]
Remote, send specially crafted packet

[Discoverer]
Adam Engelhart - SCADAfence

[Reference]
https://blog.scadafence.com
https://www.honeywell.com/us/en/product-security


----------------------------------------------------------------------------------------------------------------

CVE-2022-30245
--
[Suggested description]
Alerton Compass Software 1.6.5 allows unauthenticated configuration
changes from remote users. This enables configuration data to be stored
on the controller and then implemented. A user with malicious intent
can send a crafted packet to change the controller
configuration without the knowledge of other users, altering the
controller's function capabilities. The changed configuration is not
updated in the User Interface, which creates an inconsistency between
the configuration display and the actual configuration on the
controller. After the configuration change, remediation requires
reverting to the correct configuration, requiring either physical or
remote access depending on the configuration that was altered.

[VulnerabilityType Other]
Configuration Change (CWE 15)

[Vendor of Product]
Honeywell International Inc

[Affected Product Code Base]
Alerton Compass Software - 1.6.5

[Affected Component]
Controller Operations

[Attack Type]
Remote

[CVE Impact Other]
Configuration Change

[Attack Vectors]
Remote, send specially crafted packet

[Discoverer]
Adam Engelhart - SCADAfence

[Reference]
https://blog.scadafence.com
https://www.honeywell.com/us/en/product-security


