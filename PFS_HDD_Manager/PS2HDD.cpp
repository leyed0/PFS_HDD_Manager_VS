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
}
System::Void PS2HDD::Query() {
	devices = gcnew System::Collections::Generic::List <Device^>;
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
				tmp->DevFile = gcnew File(tmp->Name);
				devices->Add(tmp);
			}
		}
	} while (!tmp->Name->Contains("Optical"));
}

System::Void PS2HDD::Query_Part(Device^ Dev) {
	if (Dev->PFS) {
		Dev->Partitions = gcnew System::Collections::Generic::List < PS2HDD::Partition^>;
		Dev->DevFile->Childs = gcnew System::Collections::Generic::List<File^>;
		HDLDump->StartInfo->Arguments = "toc " + Dev->Name;
		HDLDump->Start();
		output = HDLDump->StandardOutput->ReadToEnd();
		System::IO::StringReader^ StringReaderr = gcnew System::IO::StringReader(output->Substring(output->IndexOf("0x")));
		do {
			Partition^ part = gcnew Partition;
			output = StringReaderr->ReadLine();
			if (!output->Contains("Total ")) {
				part->Type = output->Substring(2, 4);
				part->Size = Int32::Parse(output->Substring(20)->Substring(0, 9)->Trim()->TrimEnd('M', 'B'));
				part->Parts = 1;
				part->Name = output->Substring(output->LastIndexOf("MB") + 2)->Trim();
				File^ tmp;
				if (part->Type->Contains("1337"))tmp = gcnew File(part->Name, File::Types::Game, Dev->DevFile, Dev->DevFile);
				if (part->Type->Contains("0001"))tmp = gcnew File(part->Name, File::Types::PartitionNull, Dev->DevFile, Dev->DevFile);
				if (part->Type->Contains("0100"))tmp = gcnew File(part->Name, File::Types::Partition, Dev->DevFile, Dev->DevFile);

				tmp->Root = Dev->DevFile;
				tmp->PartRoot = tmp;
				tmp->Path = tmp->Name;
				tmp->Path = tmp->Name;

				part->PartFile = tmp;
				Dev->Partitions->Add(part);
				Dev->DevFile->Childs->Add(part->PartFile);
			}
		} while (!output->Contains("Total "));
	}
}

System::Void PS2HDD::Query_File_Path(File^ file)
{
	file->Childs = gcnew System::Collections::Generic::List<File^>;
	PFSShell->Start();
	PFSShell->StandardInput->WriteLine("device " + file->Root->Name);
	PFSShell->StandardInput->WriteLine("mount \"" + file->PartRoot->Name+"\"");
	String^ teste = file->Path->Substring(file->Path->IndexOf("/") + 1);
	if(file->Type == File::Types::Folder) PFSShell->StandardInput->WriteLine("cd \"" + file->Path->Substring(file->Path->IndexOf("/")+1) + "\"");
	PFSShell->StandardInput->WriteLine("ls");
	PFSShell->StandardInput->WriteLine("exit");

	output = PFSShell->StandardOutput->ReadToEnd();
	if (output->Contains("Invalid magic/version")) {
		file->Type = File::Types::PartitionNull; throw(Convert::ToString("Not PFS Partition"));
	}
	System::IO::StringReader^ tmpStringReader = gcnew System::IO::StringReader(output->Substring(output->IndexOf(" ..")));
	output = tmpStringReader->ReadLine();
	File^ tmpFile;
	do {
		output = tmpStringReader->ReadLine();
		if (output->Contains("# ")) break;
		if ((!output->Contains("drwxrwxrwx")&& !output->Contains("-rw-rw-rw-"))|| output->Contains(" ..")) continue;
		if (output->Contains("-rw-rw-rw-"))tmpFile = gcnew File(output->Substring(38)->Trim(), output->Substring(output->LastIndexOf(".") + 1)->Trim(), 64, file);
		if (output->Contains("drwxrwxrwx"))tmpFile = gcnew File(output->Substring(38)->Trim(), File::Types::Folder, file);
		tmpFile->PartRoot = file->PartRoot;
		tmpFile->Root = file->Root;
		tmpFile->Path = file->Path + "/" + tmpFile->Name;

		file->Childs->Add(tmpFile);
	} while (output != "# ");
	for each (File^ child in file->Childs)
	{
		if(child->Type == File::Types::Folder) Query_File_Path(child);
	}
}


System::String^ PS2HDD::Debug() {
	String^ tmp;
	return tmp;
}

PS2HDD::Device^ PS2HDD::GetDevByName(String^ Name)
{
	for each (Device^  var in devices)
	{
		if (var->Name == Name)
			return var;
	}
	return nullptr;
}

PS2HDD::Partition^ PS2HDD::GetPartByName(Device^ Dev, String^ Name)
{
	for each (Partition^ part in Dev->Partitions)
	{
		if (part->Name == Name)
			return part;
	}
	return nullptr;
}



System::Void PS2HDD::GetCDVDInfo(String^ Path) {
	HDLDump->StartInfo->Arguments = "cdvd_info2 " + Path;
	HDLDump->Start();
	return;
}


System::Void PS2HDD::InitDev(Device^ Dev)
{
	HDLDump->StartInfo->Arguments = "initialize " + Dev->Name;
	HDLDump->Start();
	devices->Clear();
	Query();
}

System::Void PS2HDD::MkPart(File^ Parent, String^ PartName, System::Int32 Size)
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

System::Boolean PS2HDD::HDL_Remove(File^ Part)
{
		HDLDump->StartInfo->Arguments = "delete " + Part->Root->Name + " \"" + Part->PartRoot->Name+ "\"";
		HDLDump->Start();
		HDLDump->WaitForExit();
		output = HDLDump->StandardOutput->ReadToEnd();
		output = HDLDump->StandardError->ReadToEnd();
		if (output->Contains("not found")) return false;
		if (output->Contains("Operation is not allowed")) { throw (Convert::ToString("not allowed")); return false; }
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

File^ PS2HDD::PFS_Mkpart(Device^ dev, String^ Name, Int32 Size)
{
	if (Math::Floor(System::Math::Log(Size, 2)) - System::Math::Log(Size, 2) != 0) throw(Convert::ToString("The size is not a power of two!\nOperation Aborted!"));
	PFSShell->Start();
	PFSShell->StandardInput->WriteLine("device " + dev->Name);
	PFSShell->StandardInput->WriteLine("mkpart \""+Name + "\" " + Size + "MB");
	PFSShell->StandardInput->WriteLine("exit");
	output = PFSShell->StandardOutput->ReadToEnd();
	output += PFSShell->StandardError->ReadToEnd();
	if (output->Contains("error")) throw(Convert::ToString("Error"));
	File^ ptfl = gcnew File(Name, File::Types::PartitionNull, dev->DevFile, dev->DevFile);
	dev->DevFile->Childs->Add(ptfl);
	return ptfl;
}

System::Void PS2HDD::PFS_Mkfs(File^ file)
{
	PFSShell->Start();
	PFSShell->StandardInput->WriteLine("device " + file->Root->Name);
	PFSShell->StandardInput->WriteLine("mkfs \"" + file->Name + "\"");
	PFSShell->StandardInput->WriteLine("exit");
	output = PFSShell->StandardOutput->ReadToEnd();
	output += PFSShell->StandardError->ReadToEnd();
	if (output->Contains("error")) throw(Convert::ToString("Error"));
	return;
}

System::Void PS2HDD::PFS_MkDir(File^ parent, String^ name)
{
	PFSShell->Start();
	PFSShell->StandardInput->WriteLine("device " + parent->Root->Name);
	PFSShell->StandardInput->WriteLine("mount \"" + parent->PartRoot->Name+"\"");
	if(parent->Type == File::Types::Folder)PFSShell->StandardInput->WriteLine("cd \"" + parent->Path->Substring(parent->Path->IndexOf("/")) + "\"");
	PFSShell->StandardInput->WriteLine("mkdir \"" + name + "\"");
	PFSShell->StandardInput->WriteLine("exit");
	PFSShell->WaitForExit();
	output = PFSShell->StandardOutput->ReadToEnd();
	output += PFSShell->StandardError->ReadToEnd();
	Query_File_Path(parent);
	if (output->Contains("error")) return;
	return;
}

System::Void  PS2HDD::PFS_RmDir(File^ dir)
{
	/*if (dir->Childs->Count > 0) for each (File^ fl in dir->Childs)
	{
		Remove(fl);
	} */
	PFSShell->Start();
	PFSShell->StandardInput->WriteLine("device " + dir->Root->Name);
	PFSShell->StandardInput->WriteLine("mount " + dir->PartRoot->Name);
	PFSShell->StandardInput->WriteLine("rmdir \"" + dir->Path->Substring(dir->Path->IndexOf("/")) + "\"");
	PFSShell->StandardInput->WriteLine("exit");
	output = PFSShell->StandardOutput->ReadToEnd();
	output += PFSShell->StandardError->ReadToEnd();
	if (output->Contains("error")) return;
	//Query_File_Path(dir->Parent);
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

System::Void  PS2HDD::PFS_Put(String^ Orig, String^ Name, File^ Dest)
{
	PFSShell->Start();
	PFSShell->StandardInput->WriteLine("lcd \"" + Orig+"\"");
	PFSShell->StandardInput->WriteLine("device " + Dest->Root->Name);
	PFSShell->StandardInput->WriteLine("mount \"" + Dest->PartRoot->Name + "\"");
	if(Dest->Type == File::Types::Folder) PFSShell->StandardInput->WriteLine("cd \"" + Dest->Path->Substring(Dest->Path->IndexOf("/")) + "\"");
	PFSShell->StandardInput->WriteLine("put \"" + Name + "\"");
	PFSShell->StandardInput->WriteLine("exit");
	PFSShell->WaitForExit();
	output = PFSShell->StandardOutput->ReadToEnd();
	output += PFSShell->StandardError->ReadToEnd();
	if (output->Contains("error")) return;
	Query_File_Path(Dest);
	return;
}

System::Void  PS2HDD::PFS_RM(File^ file)
{
	String^ tmp = file->Path;
	if (file->Parent->Type != File::Types::Partition) {
		tmp = tmp->Substring(file->Path->IndexOf("/") + 1);
		tmp = tmp->Substring(0, tmp->LastIndexOf("/"));
	}

	PFSShell->Start();
	PFSShell->StandardInput->WriteLine("device " + file->Root->Name);
	PFSShell->StandardInput->WriteLine("mount \"" + file->PartRoot->Name + "\"");
	PFSShell->StandardInput->WriteLine("cd \"" + tmp + "\"");
	PFSShell->StandardInput->WriteLine("rm \"" + file->Name + "\"");
	PFSShell->StandardInput->WriteLine("exit");
	PFSShell->WaitForExit();
	output = PFSShell->StandardOutput->ReadToEnd();
	output += PFSShell->StandardError->ReadToEnd();
	
	//file->Parent->Childs->Remove(file);
	if (output->Contains("error")) return;
	//Query_File_Path(file->Parent);
	return;
}

System::Void  PS2HDD::PFS_Rename(File^ Origin, String^ NewName)
{
	PFSShell->Start();
	PFSShell->StandardInput->WriteLine("device " + Origin->Root->Name);
	PFSShell->StandardInput->WriteLine("mount \"" + Origin->PartRoot->Name + "\"");
	PFSShell->StandardInput->WriteLine("cd \"" + Origin->Path + "\"");
	PFSShell->StandardInput->WriteLine("rename \"" + Origin->Name + "\" \"" + NewName+"\"");
	PFSShell->StandardInput->WriteLine("exit");
	output = PFSShell->StandardOutput->ReadToEnd();
	output += PFSShell->StandardError->ReadToEnd();
	if (output->Contains("error")) return;
	Query_File_Path(Origin->Parent);
	return;
}

System::Void PS2HDD::Remove(File^ file)
{
	try {
		switch (file->Type)
		{
		case File::Types::Game:
		case File::Types::PartitionNull:
		case File::Types::Partition:
			HDL_Remove(file);
			break;
		case File::Types::File:
			PFS_RM(file);
			break;
		case File::Types::Folder:
			for each (File ^ child in file->Childs)
			{
				Remove(child);
			}
			PFS_RmDir(file);
			break;
		default:
			break;
		}
		Query_File_Path(file->Parent);
	}
	catch (String^ Error) { throw Error; };
	return System::Void();
}
