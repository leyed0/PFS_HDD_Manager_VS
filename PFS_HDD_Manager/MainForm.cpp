#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace PFSHDDManager;
using namespace Windows;

[STAThreadAttribute]
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	PFSHDDManager::MainForm form;
	Application::Run(%form);
}



System::Void PFSHDDManager::MainForm::ViewPath(System::String ^ path)
{
	TXTBX_PATH->Text = Path;
	System::Windows::Forms::ImageList^  IMAGELIST;
	if (PATH_VIEW->View == System::Windows::Forms::View::LargeIcon)  IMAGELIST = PATH_VIEW->LargeImageList;
	if (PATH_VIEW->View == System::Windows::Forms::View::SmallIcon)  IMAGELIST = PATH_VIEW->SmallImageList;

	Path = path;
	TXTBX_PATH->Text = Path;
	PATH_VIEW->Clear();
	History.Push(Path);
	try {
		array<String^>^ dir = IO::Directory::GetDirectories(Path);
		array<String^>^ file = IO::Directory::GetFiles(Path);
		for (int i = 0; i < dir->Length; i++) {
			PATH_VIEW->Items->Add(dir[i]->Substring(dir[i]->LastIndexOf("\\") + 1), IMAGELIST->Images->Count - 1);
		}
		for (int i = 0; i < file->Length; i++) {
			PATH_VIEW->Items->Add(file[i]->Substring(file[i]->LastIndexOf("\\") + 1), IMAGELIST->Images->Count - 2);
		}
	}
	catch (System::IO::IOException^ err)
	{
		return;
	}
	return System::Void();
}

System::Void PFSHDDManager::MainForm::MainForm_Load(System::Object ^ sender, System::EventArgs ^ e)
{
	SetProcesses();
	DRIVE_LTR->Items->AddRange(System::IO::Directory::GetLogicalDrives());
	Path = System::IO::Directory::GetLogicalDrives()[1];
	ViewPath(Path);
	return System::Void();
}

System::Void PFSHDDManager::MainForm::PATH_VIEW_DoubleClick(System::Object ^ sender, System::EventArgs ^ e)
{
	if (Path->EndsWith("\\")) Path = Path->Substring(0, Path->Length - 1);
	Path = Path + "\\" + PATH_VIEW->SelectedItems[0]->Text;
	ViewPath(Path);
	return System::Void();
}

System::Void PFSHDDManager::MainForm::íconesGrandesToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	PATH_VIEW->View = System::Windows::Forms::View::LargeIcon;
	return System::Void();
}

System::Void PFSHDDManager::MainForm::íconesPequenosToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	PATH_VIEW->View = System::Windows::Forms::View::SmallIcon;
	return System::Void();
}

System::Void PFSHDDManager::MainForm::detalhesToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	PATH_VIEW->View = System::Windows::Forms::View::Details;
	return System::Void();
}

System::Void PFSHDDManager::MainForm::listaToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	PATH_VIEW->View = System::Windows::Forms::View::List;
	return System::Void();
}

System::Void PFSHDDManager::MainForm::gradeToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	PATH_VIEW->View = System::Windows::Forms::View::Tile;
	return System::Void();
}

System::Void PFSHDDManager::MainForm::BTN_GO_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	Path = TXTBX_PATH->Text;
	if (Path == History.Peek()) History.Pop();
	ViewPath(Path);
	return System::Void();
}

System::Void PFSHDDManager::MainForm::BTN_BACK_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	try {
		if (History.Count <= 1) return;
		if (History.Peek() == Path) History.Pop();
		ViewPath(History.Pop());
		return System::Void();
	}
	catch (System::Exception ^error) {

	}
}

System::Void PFSHDDManager::MainForm::DRIVE_LTR_SelectedIndexChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	return System::Void();
}

System::Void PFSHDDManager::MainForm::button1_Click(System::Object^  sender, System::EventArgs^  e) {
	richTextBox1->Text = HDD.GetOutput();

	//PFS->StartInfo->FileName = "shell\\hdl_dump_090.exe";
	//PFS->StartInfo->FileName = "cmd";
	//PFSShell->StartInfo->CreateNoWindow = true;
	//PFSShell->StartInfo->ErrorDialog = false;
	//PFSShell->StartInfo->UseShellExecute = false;
	//PFSShell->StartInfo->RedirectStandardError = true;
	//PFSShell->StartInfo->RedirectStandardInput = true;
	//PFSShell->StartInfo->RedirectStandardOutput = true;
	//PFSShell->EnableRaisingEvents = true;
	//PFSShell->Start();
	//PFSShell->StandardInput->WriteLine("device hdd2:");
	//PFSShell->StandardInput->WriteLine("mkpart teste2 128");
	//PFSShell->StandardInput->WriteLine("mount +OPL");
	//PFSShell->StandardInput->WriteLine("mkdir APPS");
	//PFSShell->StandardInput->WriteLine("mkdir ART");
	//PFSShell->StandardInput->WriteLine("mkdir CD");
	//PFSShell->StandardInput->WriteLine("mkdir CFG");
	//PFSShell->StandardInput->WriteLine("mkdir CHT");
	//PFSShell->StandardInput->WriteLine("mkdir DVD");
	//PFSShell->StandardInput->WriteLine("mkdir POPS");
	//PFSShell->StandardInput->WriteLine("mkdir VMC");
	//PFSShell->StandardInput->WriteLine("put pesquisa.png");
	//PFSShell->StandardInput->WriteLine("ls");
	//PFSShell->StandardInput->WriteLine("lcd");

	//PFSShell->StandardInput->WriteLine("exit");
	//richTextBox1->Text += PFSShell->StandardOutput->ReadToEnd();
}


System::Void PFSHDDManager::MainForm::StartProcess(System::String^ fileName, System::String^ arguments)
{
	////  Create the process start info.
	//var processStartInfo = new ProcessStartInfo(fileName, arguments);

	////  Set the options.
	//processStartInfo.UseShellExecute = false;
	//processStartInfo.ErrorDialog = false;
	//processStartInfo.CreateNoWindow = true;

	////  Specify redirection.
	//processStartInfo.RedirectStandardError = true;
	//processStartInfo.RedirectStandardInput = true;
	//processStartInfo.RedirectStandardOutput = true;
}

/*System::Void PFSHDDManager::MainForm::log() {
	FILE* fp;
	char result[1000];
	fp = popen("ls -al .", "r");
	fread(result, 1, sizeof(result), fp);
	fclose(fp);
	printf("%s", result);
}*/

System::Void PFSHDDManager::MainForm::HDLScanHdds() {
	HDLDump->StartInfo->Arguments = "query";
	HDLDump->Start();
}


System::Void PFSHDDManager::MainForm::SetProcesses() {
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
	HDLDump->StartInfo->FileName = "shell\\HDLDump.exe";
	HDLDump->StartInfo->CreateNoWindow = true;
	HDLDump->StartInfo->ErrorDialog = false;
	HDLDump->StartInfo->UseShellExecute = false;
	HDLDump->StartInfo->RedirectStandardError = true;
	HDLDump->StartInfo->RedirectStandardInput = true;
	HDLDump->StartInfo->RedirectStandardOutput = true;
	HDLDump->EnableRaisingEvents = true;
}


System::Void PFSHDDManager::MainForm::DRIVE_LTR_SelectedValueChanged(System::Object^  sender, System::EventArgs^  e) {
	ViewPath(DRIVE_LTR->Text);
}