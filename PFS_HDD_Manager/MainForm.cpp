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
	Path1History->Push(Path);
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
	PFSHistory = gcnew System::Collections::Generic::Stack <File^>;
	Path1History = gcnew System::Collections::Generic::Stack <System::String^>;
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
	if (Path == Path1History->Peek()) Path1History->Pop();
	ViewPath(Path);
	return System::Void();
}

System::Void PFSHDDManager::MainForm::TXTBX_PATH_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == '\r') BTN_GO_Click(sender, e);
}

System::Void PFSHDDManager::MainForm::BTN_BACK_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	try {
		if (Path1History->Count <= 1) return;
		if (Path1History->Peek() == Path) Path1History->Pop();
		ViewPath(Path1History->Pop());
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
	//array<IO::DriveInfo^>^ test = IO::DriveInfo::GetDrives();
	//MessageBox::Show(Convert::ToString( test->Length));
	return;
}

System::Void PFSHDDManager::MainForm::ListPS2HDD() {
	HDD->Query();
	for each (PS2HDD::Device^ var in HDD->devices)
	{
		DRIVE_LTR2->Items->Add(var->Name);
	}
}

//must be separated!!!!!!!
System::Void PFSHDDManager::MainForm::DRIVE_LTR2_SelectedIndexChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	CurrDev = HDD->GetDevByName(DRIVE_LTR2->Text);
	if (!CurrDev->PFS) {
		if (MessageBox::Show("The selected device is NOT a PS2 Device. Blank and Create PS2 APA Now?", "Non PS2 Device", System::Windows::Forms::MessageBoxButtons::OKCancel) == System::Windows::Forms::DialogResult::OK
			&& MessageBox::Show("Are You sure ?", "Error", System::Windows::Forms::MessageBoxButtons::OKCancel) == System::Windows::Forms::DialogResult::OK
			&& MessageBox::Show("Are You really sure ?", "Error", System::Windows::Forms::MessageBoxButtons::OKCancel) == System::Windows::Forms::DialogResult::OK
			&& MessageBox::Show("this will erase everything on the drive", "Error", System::Windows::Forms::MessageBoxButtons::OKCancel) == System::Windows::Forms::DialogResult::OK
			&& MessageBox::Show("allright then", "Error", System::Windows::Forms::MessageBoxButtons::OKCancel) == System::Windows::Forms::DialogResult::OK)
		HDD->InitDev(CurrDev);
	}
	PFSHistory->Push(CurrDev->DevFile);
	ViewPFSPath();
}


System::Void PFSHDDManager::MainForm::PFS_View_DoubleClick(System::Object^ sender, System::EventArgs^ e)
{

	if (PFSHistory->Peek()->Type == File::Types::Device){
		if(PFSHistory->Peek()->GetChildName(PFS_View->SelectedItems[0]->Text)->Type == File::Types::Game)TestStrip1->Show(MousePosition.X, MousePosition.Y);
		else {
			PFSHistory->Push(PFSHistory->Peek()->GetChildName(PFS_View->SelectedItems[0]->Text));
			ViewPFSPath();
		}
	}
	else {
		if(PFSHistory->Peek()->GetChildName(PFS_View->SelectedItems[0]->Text)->Type == File::Types::File)TestStrip1->Show(MousePosition.X, MousePosition.Y);
		if (PFSHistory->Peek()->GetChildName(PFS_View->SelectedItems[0]->Text)->Type == File::Types::Folder) {
			PFSHistory->Push(PFSHistory->Peek()->GetChildName(PFS_View->SelectedItems[0]->Text));
			ViewPFSPath();
		}
	}
	//lista arquivos
	//HDD->Query_Part_Path(CurrDev, HDD->GetPartName(CurrDev, PFS_View->SelectedItems[0]->Text));
	
	return System::Void();
}

System::Void PFSHDDManager::MainForm::ViewPFSPath() {
	HDD->Query();
	PFS_View->Clear();
	System::Windows::Forms::ImageList^ IMAGELIST;
	if (PFS_View->View == System::Windows::Forms::View::LargeIcon)  IMAGELIST = PATH_VIEW->LargeImageList;
	if (PFS_View->View == System::Windows::Forms::View::SmallIcon)  IMAGELIST = PATH_VIEW->SmallImageList;

	//CurrDev = HDD->GetDevName(DRIVE_LTR2->Text);
	//CurrDev = HDD->GetDevName(PFSHistory->Peek()->Root->Name);
	if (CurrDev->PFS) {
		TXTBX_PATH2->Text = PFSHistory->Peek()->Path;
		switch (PFSHistory->Peek()->Type)
		{
		case File::Types::Device:
			HDD->Query_Part(CurrDev);
			for each (File ^ file in CurrDev->DevFile->Childs)
			{
				if (file->Type == File::Types::Game)PFS_View->Items->Add(file->Name, IMAGELIST->Images->Count - 3);
				else PFS_View->Items->Add(file->Name, IMAGELIST->Images->Count - 1);
			}
			break;
		case File::Types::Partition:
			CurrPart = HDD->GetPartByName(CurrDev, PFSHistory->Peek()->Name);
			if (HDD->GetPartByName(CurrDev, PFSHistory->Peek()->Name)->Type->Contains("0001")) {
				System::Windows::Forms::MessageBox::Show("the selected partition is not in PFS System. Initialize it now?", "Non PFS Partition", System::Windows::Forms::MessageBoxButtons::YesNo);
			}
			//CurrPart = HDD->GetPartName(CurrDev, PFSHistory->Peek()->PartRoot->Name);
			PFSHistory->Peek()->Childs;
			HDD->Query_File_Path(PFSHistory->Peek());
			for each (File ^ file in PFSHistory->Peek()->Childs)
			{
				if (file->Type == File::Types::File) PFS_View->Items->Add(file->Name, IMAGELIST->Images->Count - 2);
				if (file->Type == File::Types::Folder) PFS_View->Items->Add(file->Name, IMAGELIST->Images->Count - 1);
			}
			break;
		case File::Types::File:
			break;
		case File::Types::Folder:
			for each (File ^ file in PFSHistory->Peek()->Childs)
			{
				if (file->Type == File::Types::File) PFS_View->Items->Add(file->Name, IMAGELIST->Images->Count - 2);
				if (file->Type == File::Types::Folder) PFS_View->Items->Add(file->Name, IMAGELIST->Images->Count - 1);
			}
			break;

		default:
			break;
		}
	}
	/*if (CurrDev->PFS) {
		HDD->Query_Part(CurrDev);
		for each (PS2HDD::Partition ^ part in CurrDev->Partitions)
		{
			if (part->Game)PFS_View->Items->Add(part->Name, IMAGELIST->Images->Count - 3);
			else PFS_View->Items->Add(part->Name, IMAGELIST->Images->Count - 1);
		}
	}*/
}

System::Void PFSHDDManager::MainForm::GAME_ToolStrip_Remove_Click(System::Object^ sender, System::EventArgs^ e)
{
	switch (PFSHistory->Peek()->GetChildName(PFS_View->SelectedItems[0]->Text)->Type)
	{
	case File::Types::File:
		HDD->PFS_RM(PFSHistory->Peek()->GetChildName(PFS_View->SelectedItems[0]->Text));
		break;
	default:
		break;
	}
	ViewPFSPath();
}

System::Void PFSHDDManager::MainForm::BTN_BACK2_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (PFSHistory->Count > 1) {
		PFSHistory->Pop();
		ViewPFSPath();
	}
	
}

System::Void PFSHDDManager::MainForm::PFS_View_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
}

System::Void PFSHDDManager::MainForm::PFS_View_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	if (e->Button == Windows::Forms::MouseButtons::Right && PFS_View->SelectedItems->Count == 0)
		PFS_MainStrip->Show(MousePosition.X, MousePosition.Y);
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