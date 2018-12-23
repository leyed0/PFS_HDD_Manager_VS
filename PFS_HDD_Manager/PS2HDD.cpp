#include "PS2HDD.h"


//constructor - sets mprocesses StartInfo
PS2HDD::PS2HDD()
{
	PFSShell = gcnew System::Diagnostics::Process;
	PFSShell->StartInfo->FileName = "shell\\pfsshell.exe";
	PFSShell->StartInfo->CreateNoWindow = true;
	PFSShell->StartInfo->ErrorDialog = false;
	PFSShell->StartInfo->UseShellExecute = false;
	PFSShell->StartInfo->RedirectStandardError = true;
	PFSShell->StartInfo->RedirectStandardInput = true;
	PFSShell->StartInfo->RedirectStandardOutput = true;
	PFSShell->EnableRaisingEvents = true;


	HDLDump = gcnew System::Diagnostics::Process;
	HDLDump->StartInfo->FileName = "shell\\hdl_dump.exe";
	HDLDump->StartInfo->CreateNoWindow = true;
	HDLDump->StartInfo->ErrorDialog = false;
	HDLDump->StartInfo->UseShellExecute = false;
	HDLDump->StartInfo->RedirectStandardError = true;
	HDLDump->StartInfo->RedirectStandardInput = true;
	HDLDump->StartInfo->RedirectStandardOutput = true;
	HDLDump->EnableRaisingEvents = true;

}

Void PS2HDD::ListDevices() {
	HDLDump->StartInfo->Arguments = "query";
	HDLDump->Start();
	output = HDLDump->StandardOutput->ReadToEnd();
	StringReader = gcnew System::IO::StringReader(output); 
	Device^ tmp;
	while (true) {
		tmp = gcnew Device;
		tmp->Name = StringReader->ReadLine();


		if (tmp->Name->Contains("formatted Playstation 2")) tmp->PS2 = true;
		else tmp->PS2 = false;
		if (!tmp->Name->Contains("MB")) tmp->Size = nullptr;


		if (tmp->Name->Contains("Optical")) break;
		if(tmp->Name!="" && tmp->Name != "Hard drives:") devices.Add(tmp);
	}
}

System::String^ PS2HDD::GetOutput() {
	ListDevices();
	String^ tmp;
	for (int i = 0; i < devices.Count; i++) {
		tmp += "\n" + devices[i]->Name;
	}
	return tmp;
}