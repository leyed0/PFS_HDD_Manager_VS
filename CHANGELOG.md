V0.29.16.13{
	FIXED:
		Files and Folders on Subfolders would not be renamed
		If pasted a path on the left explorer and double clicked a folder nothing would happen
		Creating a new partition would always return a error
}

V0.29.16.10{
	ADDED:
		Get Function working for files and folders
		Rename function working
		Left Go button working
		Reinitialize device working
		Iso images being identified with disc icon
		InputBox have option to start with default text in it

	FIXED:
		Issue where the right view was updating when right clicked

	TODO:
		Implement right Go button
		Install isos in the PS2 HDD
}

V0.23.16.14{
	FIXED:
		Fatal error when deleting a Partition

	TODO:
		ProgressBar when putting files
		Implement Go button
		Implement re-initialize code
		Implement toolstrip Get Button
		Identify game ISO`s with the game icon
		Install isos in the PS2 HDD
}

V0.23.16.13{
	FIXED:
		AutoRefresh not working when copying something to subfolder
		AutoRefresh not working when removing something from subfolder
		Fatal error when removing a newly created subfolder
		Function to update the view being called multiple times at once

	TODO:
		ProgressBar when putting files
		Implement Go button
		Implement re-initialize code
		Implement toolstrip Get Button
		Identify game ISO`s with the game icon
		Install isos in the PS2 HDD
}

V0.23.16.9{
	ADDED:
		ScreenShot added
		Now the program can transfer files and folders.
		Now folders with subfolders and files can be removed
		MessageBox to identify Functions that needs implementation
		Conditions in PFS_Put function
		Functions to handle Multipla ways of usage to PUT command

	CHANGED:
		Reimplemented File explorer entirely

	FIXED:
		Some wrong codding in the "MKFile" function
		Missplaced code in RMDir function
		Missplaced code in RM function

	REMOVED:
		PFS_Puts function

	TODO:
		Implement Go button
		Implement re-initialize code
		Implement toolstrip Get Button
		Identify game ISO`s with the game icon
		Install isos in the PS2 HDD

V0.19.15.7{
	ADDED:

	CHANGED:

	FIXED:
		Bug where new folder would always be ceated in to the partition root

	REMOVED:

	TODO:
		Implement Go button
		Implement re-initialize code
		Implement toolstip Get Button
		Reimplement File explorer
		Identify game ISO`s with the game icon

V0.19.15.6{
	ADDED:
		Toolstrip Menu in PFSView
		Buttons to transfer files beetwen host and PS2Hdd
		Custom Made "InputBox" class to get input for folder and partition names

	CHANGED:
		Some function names in PS2HDD class
		Renamed Second Tab

	FIXED:
		if you created a partition or file wit "spaces" on its name, the program would freeze

	REMOVED:
		Debug Button and TextBox on the window
		last codes using "CurrentPartition"

	TODO:
		Implement Go button
		Implement re-initialize code
		Implement toolstip Get Button
		Reimplement File explorer
		Identify game ISO`s with the game icon

V0.16.13.5{
	ADDED:
		Right click menu in right explorer
			Remove Option: Delete the selected File - works only for files - not folders
		Specific function to populate the right explorer(PFS_View)
		history on PFS_View
		Function to use the back button on PFS_View
		Now the PFS path is shown in the text bar

	CHANGED:
		Every Query Function:
			Query()
			Query_Part()
			Query_File_Path
			Now they are using a folder structure, to make easier to manipulate the explorer
		Some object names - there are more to change
		now, everytime PFS_View is updated, the system rescan the device to make sure it's showing the current state of device

	FIXED:
		Bug in the file listing process
		Path being written in the wrong format


	REMOVED:
		"Files" atribute from partition struct

	TODO:
		Implement method to insert the desired path and click the button "go"
		Identify game ISO`s with the game icon


V0.12.7.3{
	ADDED:
		Now, when a device is selected in the right side of the GUI, in the case it is PFS formated, it lists the partitions in the device
		Implemented Game and Partition structs usage
		Function that lists the files in a given partition(Query_Part_Path) - maybe change the name in the future
		Aded Disc icon to identify game partitions
		Aded Memory Card Icon For Future Use
		Aded Dark Icon Counterparts

	CHANGED:
		File struct moved to PS2HDD class... Its usage will be more direct

	FIXED:
		Fixed some missdirected calls on the query sequence

	REMOVED:

	TODO:
		Implement the function that will list the folders after a partition is selected
		Identify game ISO`s with the game icon


V0.6.6.2{
	Added:
		Now, when a device is selected in the right side of the GUI, in the case that the device is not PFS ready, the user will be prompted to fomat it in the PFS system
			It will be anoyingly repeat asking if the user is sure about this, and then format the device using PFSShell functions
		Implemented almost every PFSShell and some HDLDump functions. (in a rudmentary way, but fully functional - no error handling yet)

	Changed:
		changed some structs on PS2HDD class
			-created a specific ISO struct, wich is gona be used to list the ISO`s on host device
			-Edited "Partition" struct to be an specific identifier to the PFS device partitions
			-Edited "Game" struct to be an specific identifier to the PFS device game partitions

	Fixed:
		

	Removed:
		Functions from mainform:		
			HDLScanHdds();
			SetProcesses();

	Todo:
		Implement the usage of the "Partition" and "Game" structs
		Implement the view of the PFS Partitions and files in the right side of GUI

V0.4.3.2{
	Added:
		Filesystem libs
			classes:
				Tree: multiway tree that is gonna manage the folder structure
				File: the name is self explanatory - Are gonna have the files basic info
				Filesystem: concatenates Tree and File
	
	Changed:
		MainForm windows title
		Tabs names
		Debug button now call Filesystem functions and log them in the RichTextBox bellow
		README text detailed

	Fixed:
		

	Removed:
		Functions from mainform:		
			HDLScanHdds();
			SetProcesses();

	Todo:
	read https://semver.org/spec/v2.0.0.html }

V: 0.0.0.0{
	Added:
		Added this Changelog file
		Added the README file
		Project`s PS2-HOME thread set-up
		Started PS2HDD library
	
	Changed:
		Changed PS2HDD variables to managed ones

	Fixed:
		Fixed drop-down button to choose Partition on host device

	Removed:
		Removed some debug code that is not usable

	Todo:
	read https://semver.org/spec/v2.0.0.html 
}

	defined versionning:
	V: X.Y.Z.W
	where:
		X = Major version
		Y = Function added
		Z = Function changed
		W = Bugs fixed
