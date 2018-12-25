#pragma once

using namespace System;

ref class PS2HDD
{
private:
	ref struct Partition_Part {
		System::Int16 Sector, Size;
	};
	ref struct Partition {
		System::String^ Name;
		System::Int16 Size;
		System::Collections::Generic::List <Partition_Part^> Parts;
		System::Boolean CDVD;
		System::String^ Startup;
	};
	ref struct Device {
		System::String^ Name;
		System::Int32 Size, Used;
		System::Boolean PS2;
		System::Collections::Generic::List <String^> Partition;
	};
	System::Collections::Generic::List <Device^> devices;
	String^ output;
	String^ index;
	System::Diagnostics::Process^ PFSShell;
	System::Diagnostics::Process^ HDLDump;
	System::IO::StringReader^ StringReader;
public:
	PS2HDD();
	Void ListDevices(); 
	System::String^ GetOutput();
	Void GetTOC(Device^);

};