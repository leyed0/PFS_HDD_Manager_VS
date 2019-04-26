#pragma once

using namespace System;

ref class PS2HDD
{
public:
	//Basic info for	ISO games
	typedef ref struct ISO {
		System::String ^Name, ^Startup, ^Path;
		System::Int32 Size;
		System::Boolean CDVD;
	}ISO;

	//Base info for partitions
	typedef ref struct Partition{
		System::Int32 Size, Parts;
		System::String^ Name;
	}Partition;

	//Base info for game partitions
	typedef ref struct Game:Partition {
		System::Boolean Type;
		String^ Flags, ^ Startup;
	}Game;

	//device Name: "hddx:" and Size are applicable to any device.
	//Used, Available and partition List are applicable only for PS2 HDD`s - the boolean PS2 defines if the device is a PS2 formatted device
	typedef ref struct Device {
		System::String^ Name;
		System::Int32 Size, Used, Available;
		System::Boolean PS2;
		System::Collections::Generic::List <String^>^ Partition = gcnew System::Collections::Generic::List <String^>; //temp
		System::Collections::Generic::List <PS2HDD::Partition^>^ Partitions;
		System::Collections::Generic::List <PS2HDD::Game^>^ Games;
	}Device;

	//list for all the disk drives found on system
	System::Collections::Generic::List <Device^>^ devices;

	//output for the console readdings - Should be removed from here and made local for the specific functions that use it
	String^ output;

	//the process for using PFSShell.exe
	System::Diagnostics::Process^ PFSShell;

	//the process for using HDL_Dump.exe
	System::Diagnostics::Process^ HDLDump;

	//same as output
	System::IO::StringReader^ StringReader;
public:
	//set the processes configs for the program
	PS2HDD();

	//teste
	void HDL_OutputDataReceived(System::Object^ sender, System::EventArgs^ e) { return;};

	//list the system devices using HDL_Dump
	void Query(); 

	//Get Table of Contents of a PS2 device. Uses HDL_Dump (could use pfsshell too)
	Void GetTOC(Device^);

	//Get Info over an specific partition
	Void GetPartitionInfo(Device^);

	//Get Info over an ISO image on the host PC using HDL_Dump`s "cdvd_info2".
	//Get if the ISO is a dvd or a cd, it`s size and It startup name (SLUS_XXX.XX)
	Void GetCDVDInfo(String^);

	//function used for debuging
	System::String^ Debug();

	//gets device by its name
	Device^ GetDevName(String^ Name);

	//OK
	//initializes device into pfs filesystem with 128mb MBR partition
	void InitDev(String^ Name);


	void MkPart(String^ Dev, String^ PartName, int Size);
	
	//void PfsShell_OutputDataReceived(System::Object^ sender, System::Diagnostics::DataReceivedEventArgs^ e);



	void test();

	bool HDLDumpp(Device^ dev, String^ file) { return 0; };

	//OK
	//Delete a specified partition of the specified device
	bool HDLDeletePart(Device^ dev, Partition^ Part);

	//OK
	//Initialize the HDD into PFS system using PFSShell
	bool PFS_Initialize(Device^ dev);

	//OK
	//Make a Partition with the given Name and Size(MB)
	bool PFS_Mkpart(Device^ dev, String^ Name, Int16 Size);

	//Will not be used on this way
	bool PFS_LCD(String^ Path) { return 0; };

	//List Partitions
	void PFS_LS(Device^ Dev) { return; };

	//List Files
	void PFS_LS(Device^ Dev, String^ Part) { return; };

	//OK
	//makes a directory in the given device and partition, with the given name
	void PFS_MkDir(Device^ Dev, String^ Part, String^ Name);
	
	//OK
	//Removes the given directory in the given device partition
	void PFS_RmDir(Device^ Dev, String^ Part, String^ Name);

	//OK
	//copy the fine in the given path from ps2 hdd to the givem system path
	void PFS_Get(Device^ Dev, String^ Part, String^ Orig, String^ Name, String^ Dest);

	//OK
	//Write the given file to the given path, partition and device
	void PFS_Put(String^ Orig, String^ Name, Device^ Dev, String^ Part, String^ Dest);

	//OK
	//Removes the given file from the given path, partition and device
	void PFS_RM(Device^ Dev, String^ Part, String^ Dest, String^ Name);

	//OK
	//Removes the given file from the given path, partition and device
	void PFS_Rename(Device^ Dev, String^ Part, String^ Dest, String^ OldName, String^ NewName);
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
