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

	devices = gcnew System::Collections::Generic::List <Device^>;
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
				tmp->Size = Int32::Parse(tmpstr);
				tmp->Name = tmp->Name->Substring(0, tmp->Name->IndexOf(":") + 1);
				if(tmp->PS2) GetTOC(tmp);
				devices->Add(tmp);
			}
		}
	}
}


Void PS2HDD::GetTOC(Device^ dev) {
	//PS2HDD();
	HDLDump->StartInfo->Arguments = "toc " + dev->Name;
	HDLDump->Start();
	String^ tmp = HDLDump->StandardOutput->ReadToEnd();

	System::IO::StringReader^ tmpStringReader = gcnew System::IO::StringReader(tmp);
	tmpStringReader->ReadLine();
	do {
		dev->Partition->Add(tmpStringReader->ReadLine());
	} while (!dev->Partition[dev->Partition->Count-1]->Contains("Total slice"));
}


System::String^ PS2HDD::GetOutput() {
	ListDevices();
	String^ tmp;
	for (int i = 0; i < devices->Count; i++) {
		tmp += "\n" + devices[i]->Name + "\t" + devices[i]->Size;
		if (devices[i]->PS2) {
			for (int j=0; j<devices[i]->Partition->Count; j++)
			{
				tmp += ("\n\t") + devices[i]->Partition[j];
			}
		}
	}
	return tmp;
}


Void PS2HDD::GetCDVDInfo(String^ Path) {
	HDLDump->StartInfo->Arguments = "cdvd_info2 " + Path;
	HDLDump->Start();
	return;
}

Void PS2HDD::GetPartitionInfo(Device^ Dev) {
	HDLDump->StartInfo->Arguments = "info " + Dev->Name + "\"" + Dev->Partition[0];
	HDLDump->Start();

	return;
}