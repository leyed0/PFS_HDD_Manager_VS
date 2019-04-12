#pragma once

using namespace System;

ref class PS2HDD
{
public:
	//Basic info for games (ISO or a partition)
	//Can be used in normal partitions too just by ignoring CDVD and Startup.
	typedef ref struct Game {
		System::String ^Name, ^Startup, ^Path;
		System::Int32 Size;
		System::Boolean CDVD;
	};

	//partitions have various parts that starts in a specifc sector and have a fixed size
	typedef ref struct Partition_Part {
		System::Int32 Sector, Size;
	};

	//Base partition data. Gets use of the Game structure since it have the same base variables.
	//Has a list of parts too since ps2 partition table sometimes divides a partition in various parts.
	typedef ref struct Partition:Game {
		System::Collections::Generic::List <Partition_Part^>^ Parts = gcnew System::Collections::Generic::List<Partition_Part^>;
		System::Boolean Game;
	};

	//device Name: "hddx:" and Size are applicable to any device.
	//Used, Available and partition List are applicable only for PS2 HDD`s - the boolean PS2 defines if the device is a PS2 formatted device
	typedef ref struct Device {
		System::String^ Name;
		System::Int32 Size, Used, Available;
		System::Boolean PS2;
		System::Collections::Generic::List <String^>^ Partition = gcnew System::Collections::Generic::List <String^>;
	};

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

	//list the system devices using HDL_Dump
	void ListDevices(); 

	//Get Table of Contents of a PS2 device. Uses HDL_Dump (could use pfsshell too)
	Void GetTOC(Device^);

	//Get Info over an specific partition
	Void GetPartitionInfo(Device^);

	//Get Info over an ISO image on the host PC using HDL_Dump`s "cdvd_info2".
	//Get if the ISO is a dvd or a cd, it`s size and It startup name (SLUS_XXX.XX)
	Void GetCDVDInfo(String^);

	//function used for debuging
	System::String^ GetOutput();

	//gets device by its name
	Device^ GetDevName(String^ Name);

	//sets device to pfs filesystem with MBR partition with 128mbs
	void InitDev(String^ Name);
};




//research:

//HDL_Dump:		all is network capable
//	query: List system devices
//	dump: dump "device" "file" - create an ISO image from the device
//	compare_iin: compare two ISO inputs???
//	toc: toc "device" - Displays PlayStation 2 HDD TOC. - returns: type(?), start(Starting sector on device), #parts(number of parts the partition is divided), size, name
//	hdl_toc: hdl_toc "device" - lloks like toc, but more precise - type(is a CD or a DVD), size, flags(?), startup(SLUS_XXX_XX), Name
//	delete*: delete "device" "partition/game" - Obvious?
//	info: info "device" "partition" - Gets partition info - Startup, Name, CDVD, parts list, and size
//	extract: extract "device" "name" "output_file" - creates a iso file withe the device partition.
//	inject_cd*,inject_dvd*: inject_cd "target" "name" "source" "[startup]" "[flags]" "[@slice_index]"
//	install*: looks like inject_cd/dvd??? Creates a new HD Loader partition from a source, that has an entry in compatibility list.
//	cdvd_info, cdvd_info2:
//	poweroff:
//	initialize*:
//	backup_toc:
//	restore_toc*:
//	diag:
//	modify*:
//	copy_hdd*:

//PfsShell:
//	lcd[path] - display / set a new local working directory(host)
//	device <device> -tell shell where PS2 HDD is;
//	initialize - blank and create APA on a new PS2 HDD(destructive); doesn`t format the partitions
//	mkpart <part_name> <size> -create a new partition; ATM size must be a power of 2 (128, 256, 512, ...);
//	mkfs <part_name> -blank and create PFS on a new partition(destructive);
//	mount <part_name> -mount(start to use) a partition;
//	umount - un - mount a partition;
//	ls - no mount : list partitions; mount: list files / dirs;
//	mkdir <dir_name> -create a new directory;
//	rmdir <dir_name> -delete an existing directory;
//	pwd - print current PS2 HDD directory;
//	cd <dir_name> -change directory;
//	get <file_name> -copy file from PS2 HDD to current dir;
//	put <file_name> -copy file from current dir to PS2 HDD;
//	file name must not contain a path; rm <file_name> -delete a file;
//	rename <curr_name> <new_name> -rename a file / dir.