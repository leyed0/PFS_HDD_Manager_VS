#pragma once
#include "File.h"

using namespace System;

ref class PS2HDD
{
public:
#pragma region Struct definitions
	//Basic info for	ISO games
	typedef ref struct ISO {
		System::String ^Name, ^Startup, ^Path;
		System::Int32 Size;
		System::Boolean DVD;
	}ISO;

	//Base info for partitions
	typedef ref struct Partition{
		System::Single Size;
		System::Int32 Parts;
		System::String^ Name, ^Type, ^Startup;
		System::Boolean Game = false, DVD;
		File^ PartFile;

	}Partition;

	//device Name: "hddx:" and Size are applicable to any device.
	//Used, Available and partition List are applicable only for PS2 HDD`s - the boolean PS2 defines if it is a PFS formatted device
	typedef ref struct Device {
		System::String^ Name;
		System::Int32 Size, Used, Available;
		System::Boolean PFS;
		File^ DevFile;
		System::Collections::Generic::List <PS2HDD::Partition^>^ Partitions = nullptr;
	}Device;
#pragma endregion Struct definitions

#pragma region Variables
	//list all the disk drives found on system
	System::Collections::Generic::List <Device^>^ devices;

	//output for the console readdings - Used for Debugging
	String^ output;

	//same as output - auxiliar
	System::IO::StringReader^ StringReader;

	//the process for using PFSShell.exe
	System::Diagnostics::Process^ PFSShell;

	//the process for using HDL_Dump.exe
	System::Diagnostics::Process^ HDLDump;

#pragma endregion Variables

	//set the processes configs for the program
	PS2HDD();

	//list the system devices using HDL_Dump
	System::Void Query();

	//list the partitions in the given device
	System::Void Query_Part(Device^ Dev);


	//System::Void Query_Part_Path(Device^ Dev, Partition^ Part);

	System::Void Query_File_Path(File^ file);

	// System::Void Query_Part_Path(File^ Dev, File^ Part);

	//System::Void Query_Childs(File^ file);


	//test
	System::Void HDL_OutputDataReceived(System::Object^ sender, System::EventArgs^ e) { return;};

	//Get Table of Contents of a PS2 device. Uses HDL_Dump (could use pfsshell too)
	//Void GetTOC(Device^);

	//Get Info over an specific partition
	//Void GetPartitionInfo(Device^);

	//Get Info over an ISO image on the host PC using HDL_Dump`s "cdvd_info2".
	//Get if the ISO is a dvd or a cd, it`s size and It startup name (SLUS_XXX.XX)
	Void GetCDVDInfo(String^);

	//function used for debuging
	System::String^ Debug();

	//gets device by its name
	Device^ GetDevByName(String^ Name);


	//gets partition by its name
	Partition^ GetPartByName(Device^ Dev,String^ Name);

	//OK
	//initializes device into pfs filesystem with 128mb MBR partition
	System::Void InitDev(Device^ Dev);


	System::Void MkPart(File^ Parent, String^ PartName, System::Int32 Size);
	
	//void PfsShell_OutputDataReceived(System::Object^ sender, System::Diagnostics::DataReceivedEventArgs^ e);

	System::Void test();

	System::Boolean HDLDumpp(Device^ dev, String^ file) { return 0; };

	//OK
	//Delete a specified partition of the specified device
	System::Boolean HDL_Remove(File^ Part);

	//OK
	//Initialize the HDD into PFS system using PFSShell
	System::Boolean PFS_Initialize(Device^ dev);

	//OK
	//Make a Partition with the given Name and Size(MB)
	File^ PFS_Mkpart(Device^ dev, String^ Name, Int32 Size);


	System::Void PFS_Mkfs(File^);


	//Will not be used on this way
	System::Boolean PFS_LCD(String^ Path) { return 0; };

	//List Partitions
	System::Boolean PFS_LS(Device^ Dev) { return false; };

	//List Files
	System::Void PFS_LS(Device^ Dev, String^ Part) { return; };

	//OK
	//makes a directory in the given device and partition, with the given name
	System::Void PFS_MkDir(File^ , String^ );
	
	//OK
	//Removes the given directory in the given device partition
	System::Void PFS_RmDir(File^);

	//OK
	//copy the fine in the given path from ps2 hdd to the givem system path
	System::Void PFS_Get(Device^ Dev, String^ Part, String^ Orig, String^ Name, String^ Dest);

	//OK
	//copy the fine in the given path from ps2 hdd to the givem system path
	System::Void PFS_Gets(Device^ Dev, String^ Part, String^ Orig, System::Collections::Generic::List <String^>^ Names, String^ Dest);

	//OK
	//Write the given file to the given path, partition and device
	System::Void PFS_Put(String^ Orig, String^ Name, File^ Dest);

	//OK
	//Write the given file to the given path, partition and device
	System::Void PFS_Puts(String^ Orig, System::Collections::Generic::List <String^>^ Names, Device^ Dev, String^ Part, String^ Dest);

	//OK
	//Removes the given file from the given path, partition and device
	System::Void PFS_RM(File^);

	//OK
	//Removes the given file from the given path, partition and device
	System::Void PFS_Rename(Device^ Dev, String^ Part, String^ Dest, String^ OldName, String^ NewName);

	//Remove the given path - removes child files if exists
	System::Void Remove(File^);
};

//research:
//ok = declaration done
//OK = implementation done
//>> = not direc usage
//XX = not used

//PfsShell: //mount device busy: dont know why... Just umount and mount again
//ok	lcd[path] - display / set a new local working directory(host)
//>>	device <device> -tell shell where PS2 HDD is;
//ok	initialize - blank and create APA on a new PS2 HDD(destructive); doesn`t format the partitions (__mbr - 128, __net - 128, __system - 256, __sysconf - 512, __comon - 1024) NEED MKFS
//ok	mkpart <part_name> <size> -create a new partition; ATM size must be a power of 2 (128, 256, 512, ...);
//>>	mkfs <part_name> -blank and create PFS on a new partition(destructive);
//>>	mount <part_name> -mount(start to use) a partition;
//>>	umount - un - mount a partition;
//ok	ls - no mount : list partitions; mount: list files / dirs;
//ok	mkdir <dir_name> -create a new directory; - work with composite path
//ok	rmdir <dir_name> -delete an existing directory; - dir must be empty
//XX	pwd - print current PS2 HDD directory; - trash
//>>	cd <dir_name> -change directory on pfs side; // can use composite paths
//ok	get <file_name> -copy file from PS2 HDD to current dir; file name must not contain a path; 
//ok	put <file_name> -copy file from current dir to PS2 HDD; file name must not contain a path; 
//ok	rm <file_name> -delete a file; - work with composite path
//ok	rename <curr_name> <new_name> -rename a file / dir. - works with composite path

//HDL_Dump:		all is network capable
//	query: List system devices
//	dump: dump "device" "file" - create an ISO image from the device (cdvd, loaded cd on game)
//	compare_iin: compare two ISO inputs???
//	toc: toc "device" - Displays PlayStation 2 HDD TOC. - returns: type(?), start(Starting sector on device), #parts(number of parts the partition is divided), size, name
//	hdl_toc: hdl_toc "device" - lloks like toc, but more precise - type(is a CD or a DVD), size, flags(?), startup(SLUS_XXX_XX), Name
//OK	delete*: delete "device" "partition/game" - Obvious?
//	info: info "device" "partition" - Gets partition info - Startup, Name, CDVD, parts list, and size
//	extract: extract "device" "name" "output_file" - creates a iso file with the  selected device partition.
//	inject_cd*,inject_dvd*: inject_cd "target" "name" "source" "[startup]" "[flags]" "[@slice_index]" create a partition in the target device with the given parameters
//	install*: looks like inject_cd/dvd??? create a partition in the target device with the parameter on the compatibility list.
//	cdvd_info, cdvd_info2: cdvd_info "file": tell image type(Cd or DVD?), size, and startup code (SLUS_XXX.XX)
//	poweroff: poweroff "ip": turn off the device
//	initialize*: create pfs partition table on device (inclued __MBR with 128MB)
//	backup_toc:
//	restore_toc*:
//	diag: diag "device": scans device for partition errors 
//	modify*:
//	copy_hdd*: copy the hdd
