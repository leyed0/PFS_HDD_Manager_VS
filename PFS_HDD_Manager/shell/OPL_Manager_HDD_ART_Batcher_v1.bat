@echo off
REM ############################################################################
REM 6/4/2018
REM 
REM This is designed to push ART files downloaded via OPL_Manager_v21(or later)
REM on to the a local PS2 HDD (connected via USB / or directly)
REM 
REM WARNING - this bat assumes you already have a +OPL Partition on a PS2 formatted HDD
REM 
REM Copy this .bat file, hdl_dump_090.exe, and all Pfshell files into the folder:
REM
REM ....OPL_Manager_V21\hdl_hdd
REM
REM Then right click on the .BAT flie and select "Run as Administrator"
REM
REM Note: if you don't run as admin, Hdl_dump_090.exe won't run at all.  

REM These scripts are based on another useful one HDL_HDD_Batcher.bat,and ELF_Batcher found and modified 
REM at www.ps2-home.com
REM 
REM Please use and amend as needed for this or other projects (i've added a few 
REM comments)
REM ~Dekkit
REM ############################################################################


REM Changes folder to where current batch file is
REM "%~dp0" is the cmd line for finding the folder location of the .bat file

cd "%~dp0"
cls
echo ***THIS PROGRAM TO BE  "RUN AS ADMINISTRATOR" ***
echo Now scanning for Playstation 2 (PS2) HDDs...

REM Runs HDL to query all hdds connected to PC to help us find the PS2 HDD
hdl_dump_090 query

REM Added some help text
REM Edit script to add more hdd options if needed.
REM
echo -
echo Look above for HDD "formatted Playstation 2 HDDs"
echo Select where your PS2 HDD is located:
echo =======
echo -
echo 1) hdd1:
echo 2) hdd2:
echo 3) hdd3:
echo 4) hdd4:
echo 5) QUIT


CHOICE /C 12345 /M "Select your PS2 HDD"

IF ERRORLEVEL 1 set @hdl_path=hdd1:
IF ERRORLEVEL 2 set @hdl_path=hdd2:
IF ERRORLEVEL 3 set @hdl_path=hdd3:
IF ERRORLEVEL 4 set @hdl_path=hdd4:
IF ERRORLEVEL 5 GOTO :EOF
echo -
echo -
echo During the ART transfer process you will see "+OPL ART"  repeated several times - this is normal!
echo -
echo Ready to push your ART files onto %@hdl_path%?
Pause

REM This will copy all JPGs and PNG to hdd  
REM +OPL is the partition hosting the ART folder
REM is will create a directory on the PS2 to mirror each folder containing jpgs etc

pfsdir %@hdl_path% +OPL *.JPG
pfsdir %@hdl_path% +OPL *.PNG

REM Please Use, Copy/Distribute, Improve (and share improvements) as you wish!
