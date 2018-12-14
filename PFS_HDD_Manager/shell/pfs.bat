echo Usage: pfs.bat device partition file_wildcard
echo Usage Example: pfs.bat hdd1: __common *.jpg
echo Must run as administrator
echo device %1 > ps2xfer.txt
echo mount %2 >> ps2xfer.txt
for %%X in (%3) do (echo put "%%X") >> ps2xfer.txt
echo umount >> ps2xfer.txt
echo exit >> ps2xfer.txt
type ps2xfer.txt | pfsshell
del ps2xfer.txt



