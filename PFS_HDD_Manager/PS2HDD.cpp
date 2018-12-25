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
				if (tmp->Name->Contains("Optical")) break;
		if (tmp->Name->Contains("hdd")) {
			if (tmp->Name->Contains("MB")) {
				tmp->Name = tmp->Name->Substring(tmp->Name->LastIndexOf("	") + 1);

				if (tmp->Name->Contains("formatted Playstation 2")) tmp->PS2 = true;
				else tmp->PS2 = false;
				if (!tmp->Name->Contains("MB")) tmp->Size = -1;

				String^ tmpstr;
				tmpstr = tmp->Name->Substring(tmp->Name->IndexOf(" ") + 1);
				tmpstr->Remove(tmpstr->IndexOf("MB") - 1);
				tmpstr = tmpstr->Substring(0, tmpstr->IndexOf(" "));
				//if(tmp->Size != -1) tmp->Size = int::Parse(0);
				//tmp->Name = tmp->Name->Substring(tmp->Name->IndexOf(":") + 1);
				//GetTOC(tmp);
				tmp->Size = Int32::Parse(tmpstr);
				tmp->Name = tmp->Name->Substring(0, tmp->Name->IndexOf(":") + 1);
				if (tmp->Name != "Hard drives:") devices.Add(tmp);
			}
		}
	}
}


Void PS2HDD::GetTOC(Device^ dev) {
	HDLDump->StartInfo->Arguments = "toc " + dev->Name;
	HDLDump->Start();
	String^ tmp = HDLDump->StandardOutput->ReadToEnd();

	StringReader = gcnew System::IO::StringReader(output);
	StringReader->ReadLine();
	do {
		dev->Partition.Add(StringReader->ReadLine());
	} while (!dev->Partition.Contains("Total slice"));
}


System::String^ PS2HDD::GetOutput() {
	ListDevices();
	String^ tmp;
	for (int i = 0; i < devices.Count; i++) {
		tmp += "\n" + devices[i]->Name;
	}
	return tmp;
}