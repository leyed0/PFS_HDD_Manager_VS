@echo off
echo Usage: pfsdir.bat device partition file_wildcard
echo Usage Example: pfsdir.bat hdd1: __common *.jpg
echo Must run as administrator
echo Directory names cannot contain the . character
set ps2xfer=%CD%\ps2xfer.txt
set rootdir=%CD%
echo device %1 > %ps2xfer%
echo mount %2 >> %ps2xfer%
for %%Y in (%3) do (echo put "%%Y") >> %ps2xfer%
for /d %%X in (*) do (
 echo mkdir "%%~nX" >> %ps2xfer%
 echo cd "%%~nX" >> %ps2xfer%
 echo lcd "%%~nX" >> %ps2xfer%
 cd "%%~nX"
 for %%Y in (%3) do (echo put "%%Y") >> %ps2xfer%
 cd ..
 echo lcd .. >> %ps2xfer%
 echo cd .. >> %ps2xfer%
)
echo umount >> %ps2xfer%
echo exit >> %ps2xfer%
cd %rootdir%
type ps2xfer.txt | pfsshell
echo .
echo DONE
echo .
del ps2xfer.txt

