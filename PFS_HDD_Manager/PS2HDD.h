#pragma once

using namespace System;

ref class PS2HDD
{
public:
	PS2HDD();
	Void ListDevices(); 
	System::String^ GetOutput();
private:
	ref struct Device {
		System::String^ Name;
		System::Int16^ Size;
		System::Boolean PS2;
	};
	System::Collections::Generic::List <Device^> devices;
	String^ output;
	String^ index;
	System::Diagnostics::Process^ PFSShell;
	System::Diagnostics::Process^ HDLDump;
	System::IO::StringReader^ StringReader;
};