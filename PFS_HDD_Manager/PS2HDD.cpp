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
	//this->PFSShell->OutputDataReceived += gcnew System::Diagnostics::DataReceivedEventHandler(this, &PS2HDD::PfsShell_OutputDataReceived);

	HDLDump = gcnew System::Diagnostics::Process;
	HDLDump->StartInfo->FileName = "shell\\hdl_dump.exe";
	HDLDump->StartInfo->CreateNoWindow = true;
	HDLDump->StartInfo->ErrorDialog = false;
	HDLDump->StartInfo->UseShellExecute = false;
	HDLDump->StartInfo->RedirectStandardError = true;
	HDLDump->StartInfo->RedirectStandardInput = true;
	HDLDump->StartInfo->RedirectStandardOutput = true;
	HDLDump->EnableRaisingEvents = true;
	//this->HDLDump->OutputDataReceived += gcnew System::Diagnostics::DataReceivedEventHandler(this, &PS2HDD::HDL_OutputDataReceived);

	devices = gcnew System::Collections::Generic::List <Device^>;
}
void PS2HDD::Query() {
	array<String^>^ ret;
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
	//HDLDump->Kill();
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


System::String^ PS2HDD::Debug() {
	Query();
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

PS2HDD::Device^ PS2HDD::GetDevName(String^ Name)
{
	for each (Device^  var in devices)
	{
		if (var->Name == Name)
			return var;
	}
	return nullptr;
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

void PS2HDD::InitDev(String^ Name)
{
	System::Windows::Forms::MessageBox::Show("Formatting");
	HDLDump->StartInfo->Arguments = "initialize " + Name;
	HDLDump->Start();
	devices->Clear();
	Query();
}

void PS2HDD::MkPart(String^ Dev, String^ PartName, int Size)
{
	throw gcnew System::NotImplementedException();
}

//void PS2HDD::PfsShell_OutputDataReceived(System::Object^ sender, System::Diagnostics::DataReceivedEventArgs^ e)
//{
//	out += e->Data;
//	out += e->Data;
//	out += e->Data;
//	throw gcnew System::NotImplementedException();
//}


void PS2HDD::test()
{
	PFSShell->Start();
	PFSShell->StandardInput->WriteLine("device hdd2:");
}

bool PS2HDD::HDLDeletePart(Device^ dev, Partition^ part)
{
	HDLDump->StartInfo->Arguments = "delete " + dev->Name + " " + part->Name;
	HDLDump->Start();
	output = PFSShell->StandardOutput->ReadToEnd();
	output += PFSShell->StandardError->ReadToEnd();
	if(output->Contains("not fount")) return false;
	return true;
}

bool PS2HDD::PFS_Initialize(Device^ dev)
{
	PFSShell->Start();
	PFSShell->StandardInput->WriteLine("device " + dev->Name);
	PFSShell->StandardInput->WriteLine("initialize yes");
	PFSShell->StandardInput->WriteLine("exit");
	output = PFSShell->StandardOutput->ReadToEnd();
	output += PFSShell->StandardError->ReadToEnd();
	if (output->Contains("error")) return false;
	return true;
}

bool PS2HDD::PFS_Mkpart(Device^ dev, String^ Name, Int16 Size)
{
	PFSShell->Start();
	PFSShell->StandardInput->WriteLine("device " + dev->Name);
	PFSShell->StandardInput->WriteLine("mkpart "+Name + " " + Size + "MB");
	PFSShell->StandardInput->WriteLine("exit");
	output = PFSShell->StandardOutput->ReadToEnd();
	output += PFSShell->StandardError->ReadToEnd();
	if (output->Contains("error")) return false;
	return true;
}

void PS2HDD::PFS_MkDir(Device^ Dev, String^ Part, String^ Name)
{
	PFSShell->Start();
	PFSShell->StandardInput->WriteLine("device " + Dev->Name);
	PFSShell->StandardInput->WriteLine("mount " + Part);
	PFSShell->StandardInput->WriteLine("mkdir " + Name);
	PFSShell->StandardInput->WriteLine("exit");
	output = PFSShell->StandardOutput->ReadToEnd();
	output += PFSShell->StandardError->ReadToEnd();
	if (output->Contains("error")) return;
	return;
}

void PS2HDD::PFS_RmDir(Device^ Dev, String^ Part, String^ Name)
{
	PFSShell->Start();
	PFSShell->StandardInput->WriteLine("device " + Dev->Name);
	PFSShell->StandardInput->WriteLine("mount " + Part);
	PFSShell->StandardInput->WriteLine("rmdir " + Name);
	PFSShell->StandardInput->WriteLine("exit");
	output = PFSShell->StandardOutput->ReadToEnd();
	output += PFSShell->StandardError->ReadToEnd();
	if (output->Contains("error")) return;
	return;
}

void PS2HDD::PFS_Get(Device^ Dev, String^ Part, String^ Orig, String^ Name, String^ Dest)
{
	PFSShell->Start();
	PFSShell->StandardInput->WriteLine("device " + Dev->Name);
	PFSShell->StandardInput->WriteLine("mount " + Part);
	PFSShell->StandardInput->WriteLine("cd " + Orig);
	PFSShell->StandardInput->WriteLine("lcd " + Dest);
	PFSShell->StandardInput->WriteLine("get " + Name);
	PFSShell->StandardInput->WriteLine("exit");
	output = PFSShell->StandardOutput->ReadToEnd();
	output += PFSShell->StandardError->ReadToEnd();
	if (output->Contains("error")) return;
	return;
}

void PS2HDD::PFS_Put(String^ Orig, String^ Name, Device^ Dev, String^ Part, String^ Dest)
{
	PFSShell->Start();
	PFSShell->StandardInput->WriteLine("lcd " + Orig);
	PFSShell->StandardInput->WriteLine("device " + Dev->Name);
	PFSShell->StandardInput->WriteLine("mount " + Part);
	PFSShell->StandardInput->WriteLine("cd " + Dest);
	PFSShell->StandardInput->WriteLine("put " + Name);
	PFSShell->StandardInput->WriteLine("exit");
	output = PFSShell->StandardOutput->ReadToEnd();
	output += PFSShell->StandardError->ReadToEnd();
	if (output->Contains("error")) return;
	return;
}

void PS2HDD::PFS_RM(Device^ Dev, String^ Part, String^ Dest, String^ Name)
{
	PFSShell->Start();
	PFSShell->StandardInput->WriteLine("device " + Dev->Name);
	PFSShell->StandardInput->WriteLine("mount " + Part);
	PFSShell->StandardInput->WriteLine("cd " + Dest);
	PFSShell->StandardInput->WriteLine("rm " + Name);
	PFSShell->StandardInput->WriteLine("exit");
	output = PFSShell->StandardOutput->ReadToEnd();
	output += PFSShell->StandardError->ReadToEnd();
	if (output->Contains("error")) return;
	return;
}

void PS2HDD::PFS_Rename(Device^ Dev, String^ Part, String^ Dest, String^ OldName, String^ NewName)
{
	PFSShell->Start();
	PFSShell->StandardInput->WriteLine("device " + Dev->Name);
	PFSShell->StandardInput->WriteLine("mount " + Part);
	PFSShell->StandardInput->WriteLine("cd " + Dest);
	PFSShell->StandardInput->WriteLine("rename " + OldName + " " + NewName);
	PFSShell->StandardInput->WriteLine("exit");
	output = PFSShell->StandardOutput->ReadToEnd();
	output += PFSShell->StandardError->ReadToEnd();
	if (output->Contains("error")) return;
	return;
}
