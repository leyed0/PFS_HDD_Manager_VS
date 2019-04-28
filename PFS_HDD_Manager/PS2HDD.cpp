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
System::Void PS2HDD::Query() {
	HDLDump->StartInfo->Arguments = "query";
	HDLDump->Start();
	output = HDLDump->StandardOutput->ReadToEnd();
	StringReader = gcnew System::IO::StringReader(output);
	Device^ tmp;
	do {
		tmp = gcnew Device;
		tmp->Name = StringReader->ReadLine();
		if (tmp->Name->Contains("hdd")) {
			if (tmp->Name->Contains("MB")) {
				tmp->Name = tmp->Name->Substring(tmp->Name->LastIndexOf("	") + 1);

				if (tmp->Name->Contains("formatted Playstation 2")) tmp->PFS = true;
				else tmp->PFS = false;

				String^ tmpstr;
				tmpstr = tmp->Name->Substring(tmp->Name->IndexOf(" ") + 1);
				tmpstr->Remove(tmpstr->IndexOf("MB") - 1);
				tmpstr = tmpstr->Substring(0, tmpstr->IndexOf(" "));
				tmp->Size = Int32::Parse(tmpstr);
				tmp->Name = tmp->Name->Substring(0, tmp->Name->IndexOf(":") + 1);
				if(tmp->PFS) Query_Part(tmp);
				devices->Add(tmp);
			}
		}
	} while (!tmp->Name->Contains("Optical"));
	//HDLDump->Kill();
}

System::Void PS2HDD::Query_Part_Path(Device^ Dev, Partition^ Pt)
{
	if (Pt->Type->Contains("0100")) {
		PFSShell->Start();
		PFSShell->StandardInput->WriteLine("device " + Dev->Name);
		PFSShell->StandardInput->WriteLine("mount " + Pt);
		PFSShell->StandardInput->WriteLine("ls");
		PFSShell->StandardInput->WriteLine("exit");

		String^ tmp = PFSShell->StandardOutput->ReadToEnd();

		System::IO::StringReader^ tmpStringReader = gcnew System::IO::StringReader(tmp->Substring(tmp->IndexOf(" ..")));
		tmpStringReader->ReadLine();

	}
}

System::Void PS2HDD::Query_Part(Device^ Dev) {
	if (Dev->PFS) {
		HDLDump->StartInfo->Arguments = "toc " + Dev->Name;
		HDLDump->Start();
		output = HDLDump->StandardOutput->ReadToEnd();
		System::IO::StringReader^ StringReaderr = gcnew System::IO::StringReader(output->Substring(output->IndexOf("0x")));
		Dev->Partitions = gcnew System::Collections::Generic::List < PS2HDD::Partition^>;
		Dev->Games = gcnew System::Collections::Generic::List < PS2HDD::Game^>;
		do{
			Partition^ part = gcnew Partition;
			output = StringReaderr->ReadLine();
			if (!output->Contains("PP.HDL")&& !output->Contains("Total ")) {
				part->Type = output->Substring(2, 4);
				part->Size = Int32::Parse(output->Substring(20)->Substring(0, 9)->Trim()->TrimEnd('M','B'));
				part->Parts = 1;
				part->Name = output->Substring(output->LastIndexOf("MB")+2)->Trim();
				Dev->Partitions->Add(part);
			}
		} while (!output->Contains("Total "));

		HDLDump->StartInfo->Arguments = "hdl_toc " + Dev->Name;
		HDLDump->Start();
		output = HDLDump->StandardOutput->ReadToEnd();
		StringReaderr = gcnew System::IO::StringReader(output);
		output = StringReaderr->ReadLine();
		do{
			Game^ game = gcnew Game;
			output = StringReaderr->ReadLine();
			if (!output->Contains("total")) {
				game->DVD = output->Substring(0, output->IndexOf(" ")) == "DVD";
				game->Size = Single::Parse(output->Substring(3)->Substring(0, 10)->Trim()->TrimEnd('K', 'B'))/1000;
				game->Flags = output->Substring(output->LastIndexOf("KB ")+2, 17)->Trim();
				game->Startup = output->Substring(30, 13)->Trim();
				game->Name = output->Substring(43)->Trim();
				game->Type = "Game";
				Dev->Games->Add(game);
			}
		} while (!output->Contains("total "));
	}
}

System::Void PS2HDD::GetTOC(Device^ dev) {
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
	//Query();
	String^ tmp;
	for (int i = 0; i < devices->Count; i++) {
		tmp += devices[i]->Name + "\t" + devices[i]->Size + "\n";
		if (devices[i]->PFS) {
			for (int j=0; j<devices[i]->Partition->Count; j++)
			{
				tmp += ("\t") + devices[i]->Partition[j] + "\n";
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



System::Void PS2HDD::GetCDVDInfo(String^ Path) {
	HDLDump->StartInfo->Arguments = "cdvd_info2 " + Path;
	HDLDump->Start();
	return;
}

System::Void PS2HDD::GetPartitionInfo(Device^ Dev) {
	HDLDump->StartInfo->Arguments = "info " + Dev->Name + "\"" + Dev->Partition[0];
	HDLDump->Start();
	return;
}

System::Void PS2HDD::InitDev(Device^ Dev)
{
	//System::Windows::Forms::MessageBox::Show("Formatting");
	HDLDump->StartInfo->Arguments = "initialize " + Dev->Name;
	HDLDump->Start();
	devices->Clear();
	Query();
}

System::Void PS2HDD::MkPart(String^ Dev, String^ PartName, int Size)
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


System::Void PS2HDD::test()
{
	PFSShell->Start();
	PFSShell->StandardInput->WriteLine("device hdd2:");
}

System::Boolean PS2HDD::HDLDeletePart(Device^ dev, Partition^ part)
{
	HDLDump->StartInfo->Arguments = "delete " + dev->Name + " " + part->Name;
	HDLDump->Start();
	output = PFSShell->StandardOutput->ReadToEnd();
	output += PFSShell->StandardError->ReadToEnd();
	if(output->Contains("not fount")) return false;
	return true;
}

System::Boolean PS2HDD::PFS_Initialize(Device^ dev)
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

System::Boolean PS2HDD::PFS_Mkpart(Device^ dev, String^ Name, Int16 Size)
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

System::Void PS2HDD::PFS_MkDir(Device^ Dev, String^ Part, String^ Name)
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

System::Void  PS2HDD::PFS_RmDir(Device^ Dev, String^ Part, String^ Name)
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

System::Void  PS2HDD::PFS_Get(Device^ Dev, String^ Part, String^ Orig, String^ Name, String^ Dest)
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

System::Void  PS2HDD::PFS_Gets(Device^ Dev, String^ Part, String^ Orig, System::Collections::Generic::List<String^>^ Names, String^ Dest)
{
	PFSShell->Start();
	PFSShell->StandardInput->WriteLine("device " + Dev->Name);
	PFSShell->StandardInput->WriteLine("mount " + Part);
	PFSShell->StandardInput->WriteLine("cd " + Orig);
	PFSShell->StandardInput->WriteLine("lcd " + Dest);
	for each (String^ Name in Names)
	{
		PFSShell->StandardInput->WriteLine("get " + Name);
	}
	PFSShell->StandardInput->WriteLine("exit");
	output = PFSShell->StandardOutput->ReadToEnd();
	output += PFSShell->StandardError->ReadToEnd();
	if (output->Contains("error")) return;
	return;
}

System::Void  PS2HDD::PFS_Put(String^ Orig, String^ Name, Device^ Dev, String^ Part, String^ Dest)
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

System::Void  PS2HDD::PFS_Puts(String^ Orig, System::Collections::Generic::List<String^>^ Names, Device^ Dev, String^ Part, String^ Dest)
{
	PFSShell->Start();
	PFSShell->StandardInput->WriteLine("lcd " + Orig);
	PFSShell->StandardInput->WriteLine("device " + Dev->Name);
	PFSShell->StandardInput->WriteLine("mount " + Part);
	PFSShell->StandardInput->WriteLine("cd " + Dest);
	for each (String^ Name in Names)
	{
		PFSShell->StandardInput->WriteLine("put " + Name);
	}
	PFSShell->StandardInput->WriteLine("exit");
	output = PFSShell->StandardOutput->ReadToEnd();
	output += PFSShell->StandardError->ReadToEnd();
	if (output->Contains("error")) return;
	return;
}

System::Void  PS2HDD::PFS_RM(Device^ Dev, String^ Part, String^ Dest, String^ Name)
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

System::Void  PS2HDD::PFS_Rename(Device^ Dev, String^ Part, String^ Dest, String^ OldName, String^ NewName)
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
