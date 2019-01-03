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