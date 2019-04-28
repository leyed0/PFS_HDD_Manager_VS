#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace PFSHDDManager;
using namespace Windows;

[STAThreadAttribute]
int main(array<String^>^ argv) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	PFSHDDManager::MainForm form;
	Application::Run(%form);
	return 0;
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
	History->Push(Path);
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
		return ;
	}
	return System::Void();
}

System::Void PFSHDDManager::MainForm::MainForm_Load(System::Object ^ sender, System::EventArgs ^ e)
{
	History = gcnew System::Collections::Generic::Stack <System::String^>;
	DRIVE_LTR->Items->AddRange(System::IO::Directory::GetLogicalDrives());
	Path = System::IO::Directory::GetLogicalDrives()[0];
	ViewPath(Path);
	ListPS2HDD();

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
	if (Path == History->Peek()) History->Pop();
	ViewPath(Path);
	return System::Void();
}

System::Void PFSHDDManager::MainForm::TXTBX_PATH_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == '\r') BTN_GO_Click(sender, e);
}

System::Void PFSHDDManager::MainForm::BTN_BACK_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	try {
		if (History->Count <= 1) return;
		if (History->Peek() == Path) History->Pop();
		ViewPath(History->Pop());
		return System::Void();
	}
	catch (System::Exception ^error) {

	}
}

System::Void PFSHDDManager::MainForm::DRIVE_LTR_SelectedIndexChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	return System::Void();
}

System::Void PFSHDDManager::MainForm::Debug_Button_Click(System::Object^  sender, System::EventArgs^  e) {
	//HDD->PFS_Mkpart(HDD->GetDevName("hdd5:"),"Debug", 128);
	//richTextBox1->Text = HDD->output;
	richTextBox1->Text = HDD->Debug();

	//PFSShell->OutputDataReceived();
	//PFS->StartInfo->FileName = "shell\\1_090.exe";
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



System::Void PFSHDDManager::MainForm::DRIVE_LTR_SelectedValueChanged(System::Object^  sender, System::EventArgs^  e) {
	ViewPath(DRIVE_LTR->Text);
}

System::Void PFSHDDManager::MainForm::BTN_GO2_Click(System::Object^  sender, System::EventArgs^  e) {
	array<IO::DriveInfo^>^ test = IO::DriveInfo::GetDrives();
	MessageBox::Show(Convert::ToString( test->Length));
	//for each (IO::DriveInfo^ var in test)
	//{
	//	DRIVE_LTR2->Items->Add(var->Name);
	//	//HDD
	//}
}

System::Void PFSHDDManager::MainForm::ListPS2HDD() {
	HDD->Query();
	for each (PS2HDD::Device^ var in HDD->devices)
	{
		DRIVE_LTR2->Items->Add(var->Name);
	}
}

System::Void PFSHDDManager::MainForm::DRIVE_LTR2_SelectedIndexChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	CurrDev = HDD->GetDevName(DRIVE_LTR2->Text);
	if (!CurrDev->PFS) {
		if (MessageBox::Show("The selected device doesnt contains a PFS Partition table. Initialize it with PFS Table ?", "Error", System::Windows::Forms::MessageBoxButtons::OKCancel) == System::Windows::Forms::DialogResult::OK
			&& MessageBox::Show("Are You sure ?", "Error", System::Windows::Forms::MessageBoxButtons::OKCancel) == System::Windows::Forms::DialogResult::OK
			&& MessageBox::Show("Are You really sure ?", "Error", System::Windows::Forms::MessageBoxButtons::OKCancel) == System::Windows::Forms::DialogResult::OK
			&& MessageBox::Show("this will erase everything on the drive", "Error", System::Windows::Forms::MessageBoxButtons::OKCancel) == System::Windows::Forms::DialogResult::OK
			&& MessageBox::Show("allright then", "Error", System::Windows::Forms::MessageBoxButtons::OKCancel) == System::Windows::Forms::DialogResult::OK)
		HDD->InitDev(CurrDev);
	}


	System::Windows::Forms::ImageList^ IMAGELIST;
	if (PATH_VIEW2->View == System::Windows::Forms::View::LargeIcon)  IMAGELIST = PATH_VIEW->LargeImageList;
	if (PATH_VIEW2->View == System::Windows::Forms::View::SmallIcon)  IMAGELIST = PATH_VIEW->SmallImageList;


	CurrDev = HDD->GetDevName(DRIVE_LTR2->Text);
	if (CurrDev->PFS) {
		HDD->Query_Part(CurrDev);
			PATH_VIEW2->Clear();
		for each (PS2HDD::Partition^ part in CurrDev->Partitions)
		{
			PATH_VIEW2->Items->Add(part->Name, IMAGELIST->Images->Count - 1);
		}
		for each (PS2HDD::Game^ game in CurrDev->Games)
		{
			PATH_VIEW2->Items->Add(game->Name, IMAGELIST->Images->Count - 3);
		}
	}
}

/*Readings:
0x0001 00000000.:  1   128MB __mbr
0x0100 00040000.:  1   128MB Debug
0x1337 00080000.:  3  1280MB PP.HDL.Contra
0x1337 00300000.:  4  1408MB PP.HDL.silenthill
0x1337 005c0000.:  4  1536MB PP.HDL.godhand
0x1337 008c0000.:  3  1664MB PP.HDL.needprostreet
0x1337 00c00000.:  4  1920MB PP.HDL.bombapatch
Total slice size: 238472MB, used: 8064MB, available: 230400MB


type     size flags           startup      name
DVD 1228736KB                 SLPS_257.65  Contra
DVD 1416704KB                 SLUS_218.99  silenthill
DVD 1530944KB                 SLUS_215.03  godhand
DVD 1613824KB                 SLUS_216.58  needprostreet
DVD 1861632KB                 SLPM_663.74  bombapatch
total 238464MB, used 8064MB, available 230400MB

type		size			name
drwxrwxrwx        512 2019-04-27 00:56 .
drwxrwxrwx        512 2019-04-27 00:56 ..
drwxrwxrwx        512 2019-04-25 20:28 teste
drwxrwxrwx        512 2019-04-27 00:55 teste2
drwxrwxrwx        512 2019-04-27 00:55 teste3
-rw-rw-rw-         64 2019-04-27 00:56 hello.bat
-rw-rw-rw-      36818 2019-04-27 00:56 pfsshell.exe
*/