net stop bits
net stop wuauserv
net stop appidsvc
net stop cryptsvc
Ren %systemroot%\SoftwareDistribution SoftwareDistribution.old
Ren %systemroot%\system32\catroot2 catroot2.old
net start bits
net start wuauserv
net start appidsvc
net start cryptsvc
