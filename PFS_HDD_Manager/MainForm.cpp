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

System::Void PFSHDDManager::MainForm::ViewPath()
{
	if (!UpdateView) return;
	if (!DirInfoHistory->Peek()->Exists) return;
	Path_View->Clear();
	System::Windows::Forms::ImageList^  IMAGELIST;
	if (Path_View->View == System::Windows::Forms::View::LargeIcon)  IMAGELIST = Path_View->LargeImageList;
	if (Path_View->View == System::Windows::Forms::View::SmallIcon)  IMAGELIST = Path_View->SmallImageList;

	for each (IO::DirectoryInfo^ Dinfo in DirInfoHistory->Peek()->GetDirectories())
	{
		Path_View->Items->Add(Dinfo->Name, IMAGELIST->Images->Count - 1);
	}
	for each (IO::FileInfo^ Finfo in DirInfoHistory->Peek()->GetFiles())
	{
		if(Finfo->Extension->ToUpper() == ".ISO") Path_View->Items->Add(Finfo->Name, IMAGELIST->Images->Count - 3);
		else Path_View->Items->Add(Finfo->Name, IMAGELIST->Images->Count - 2);
	}
	TXTBX_Path_View->Text = DirInfoHistory->Peek()->FullName;
	UpdateView = false;
}

System::Void PFSHDDManager::MainForm::ViewPath(System::String ^ path)
{
}

System::Void PFSHDDManager::MainForm::MainForm_Load(System::Object ^ sender, System::EventArgs ^ e)
{
	PFSHistory = gcnew System::Collections::Generic::Stack <File^>;
	PathHistory = gcnew System::Collections::Generic::Stack <String^>;
	DirInfoHistory = gcnew System::Collections::Generic::Stack <IO::DirectoryInfo^>;
	DRIVE_LTR->Items->AddRange(IO::DriveInfo::GetDrives());
	ListPS2HDD();

	return System::Void();
}

System::Void PFSHDDManager::MainForm::íconesGrandesToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	//PATH_VIEW->View = System::Windows::Forms::View::LargeIcon;
	return System::Void();
}

System::Void PFSHDDManager::MainForm::íconesPequenosToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	//PATH_VIEW->View = System::Windows::Forms::View::SmallIcon;
	return System::Void();
}

System::Void PFSHDDManager::MainForm::detalhesToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	//PATH_VIEW->View = System::Windows::Forms::View::Details;
	return System::Void();
}

System::Void PFSHDDManager::MainForm::listaToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	//PATH_VIEW->View = System::Windows::Forms::View::List;
	return System::Void();
}

System::Void PFSHDDManager::MainForm::gradeToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	//PATH_VIEW->View = System::Windows::Forms::View::Tile;
	return System::Void();
}

System::Void PFSHDDManager::MainForm::BTN_GO_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (String::IsNullOrEmpty(TXTBX_Path_View->Text)) return;
	if (IO::DirectoryInfo(TXTBX_Path_View->Text).Exists)
		DirInfoHistory->Push(gcnew IO::DirectoryInfo(TXTBX_Path_View->Text + "\\"));
	UpdateView = true;
	ViewPath();
	return System::Void();
}

System::Void PFSHDDManager::MainForm::TXTBX_PATH_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == '\r') BTN_GO_Click(sender, e);
}

System::Void PFSHDDManager::MainForm::BTN_BACK_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	try {
		DirInfoHistory->Pop();
		UpdateView = true;
		ViewPath();
	}
	catch (System::Exception ^error) {

	}
}

System::Void PFSHDDManager::MainForm::DRIVE_LTR_SelectedIndexChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	DirInfoHistory->Push(gcnew IO::DirectoryInfo(DRIVE_LTR->Text));
	UpdateView = true;
	ViewPath();
}

System::Void PFSHDDManager::MainForm::Path_View_MouseDoubleClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	if (DirInfoHistory->Count <= 0) return;
	//if (Path_View->SelectedItems->Count > 0) MessageBox::Show("done");
	String^ Test = DirInfoHistory->Peek()->FullName + Path_View->SelectedItems[0]->Text + "\\";
	DirInfoHistory->Push(gcnew IO::DirectoryInfo(DirInfoHistory->Peek()->FullName + Path_View->SelectedItems[0]->Text + "\\"));
	UpdateView = true;
	ViewPath();
}

System::Void PFSHDDManager::MainForm::Debug_Button_Click(System::Object^  sender, System::EventArgs^  e) {
}


System::Void PFSHDDManager::MainForm::StartProcess(System::String^ fileName, System::String^ arguments)
{
}



System::Void PFSHDDManager::MainForm::DRIVE_LTR_SelectedValueChanged(System::Object^  sender, System::EventArgs^  e) {
	UpdateView = true;
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
	UpdatePfsView = true;
	ViewPFSPath();
}



System::Void PFSHDDManager::MainForm::ViewPFSPath() {
	if (!UpdatePfsView)return;
	//HDD->Query();
	PFS_View->Clear();
	System::Windows::Forms::ImageList^ IMAGELIST;
	if (PFS_View->View == System::Windows::Forms::View::LargeIcon)  IMAGELIST = ICONS_LARGE;
	if (PFS_View->View == System::Windows::Forms::View::SmallIcon)  IMAGELIST = ICONS_SMALL;

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
			try { HDD->Query_File_Path(PFSHistory->Peek()); }
			catch (String^ Error) {
				if (MessageBox::Show("the selected partition is not in PFS System. Initialize it now?",
					"Non PFS Partition", System::Windows::Forms::MessageBoxButtons::YesNo) == Forms::DialogResult::Yes)
					HDD->PFS_Mkfs(PFSHistory->Peek());
				else {
					PFSHistory->Pop();
					UpdatePfsView = true;
					ViewPFSPath();
					return;
				}
			}
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
	UpdatePfsView = false;
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
	UpdatePfsView = true;
	ViewPFSPath();
}

System::Void PFSHDDManager::MainForm::BTN_BACK2_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (PFSHistory->Count > 1) {
		PFSHistory->Pop();
		UpdatePfsView = true;
		ViewPFSPath();
	}
	
}


System::Void PFSHDDManager::MainForm::PFS_View_DoubleClick(System::Object^ sender, System::EventArgs^ e)
{
}

System::Void PFSHDDManager::MainForm::PFS_View_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{

}

System::Void PFSHDDManager::MainForm::PFS_View_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
}

System::Void PFSHDDManager::MainForm::PFS_View_MouseDoubleClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	if (e->Button == Windows::Forms::MouseButtons::Left) {
		if (PFSHistory->Peek()->Type == File::Types::Device) {
			if (PFSHistory->Peek()->GetChildName(PFS_View->SelectedItems[0]->Text)->Type == File::Types::Game)TestStrip1->Show(MousePosition.X, MousePosition.Y);
			else {
				PFSHistory->Push(PFSHistory->Peek()->GetChildName(PFS_View->SelectedItems[0]->Text));
				UpdatePfsView = true;
				ViewPFSPath();
			}
		}
		else {
			if (PFSHistory->Peek()->GetChildName(PFS_View->SelectedItems[0]->Text)->Type == File::Types::File)TestStrip1->Show(MousePosition.X, MousePosition.Y);
			if (PFSHistory->Peek()->GetChildName(PFS_View->SelectedItems[0]->Text)->Type == File::Types::Folder) {
				UpdatePfsView = true;
				PFSHistory->Push(PFSHistory->Peek()->GetChildName(PFS_View->SelectedItems[0]->Text));
				ViewPFSPath();
			}
		}
	}
	//if (Path->EndsWith("\\")) Path = Path->Substring(0, Path->Length - 1);
	//Path = PFSHistory->Peek()->Path;
	//lista arquivos
	//HDD->Query_Part_Path(CurrDev, HDD->GetPartName(CurrDev, PFS_View->SelectedItems[0]->Text));

	return System::Void();
}
System::Void PFSHDDManager::MainForm::PFS_ContextMenu_Opening(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e)
{
	if (CurrDev == nullptr || !CurrDev->PFS)
		for each (System::Windows::Forms::ToolStripItem ^ item in PFS_ContextMenu->Items)
		{
			item->Visible = false;
		}
	else {
		for each (System::Windows::Forms::ToolStripItem ^ item in PFS_ContextMenu->Items)
		{
			item->Visible = true;
		}

	}
	return System::Void();
}
System::Void PFSHDDManager::MainForm::PATH_VIEW_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
{
	/*if (Char::IsControl(e->KeyChar))
		PATH_VIEW->SelectedItems->Clear();
		if (e->KeyChar == wchar_t::Parse(""))for each (Windows::Forms::ListViewItem^ item in PATH_VIEW->Items)
		{
			for each (ListViewItem^ item in PATH_VIEW->Items)
			{
				item->Selected = true;
			}
		};*/
	return System::Void();
}
System::Void PFSHDDManager::MainForm::BTN_Put_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (Path_View->SelectedItems->Count > 0 && PFSHistory->Count > 0 && (PFSHistory->Peek()->Type == File::Types::Folder || PFSHistory->Peek()->Type == File::Types::Partition)) {
		for each (ListViewItem ^ item in Path_View->SelectedItems)
		{
			if (IO::DirectoryInfo(DirInfoHistory->Peek()->FullName + "\\" + item->Text).Exists) {
				HDD->PFS_MkDir(PFSHistory->Peek(), item->Text);
				Put_PFS(gcnew IO::DirectoryInfo(DirInfoHistory->Peek()->FullName + "\\" + item->Text), PFSHistory->Peek()->GetChildName(item->Text));
			}
			if (IO::FileInfo(DirInfoHistory->Peek()->FullName + "\\" + item->Text).Exists)
				if (item->Text != "desktop.ini")
					if (!item->Text->ToUpper()->Contains(".ISO") && !item->Text->ToUpper()->Contains(".CUE"))
						HDD->PFS_Put(DirInfoHistory->Peek()->FullName->Replace("\\", "/"), item->Text, PFSHistory->Peek());
					else NotImplemented("Dumping ISO files is not fully working yet!");
		}
		UpdatePfsView = true;
	}
	ViewPFSPath();
}

System::Void PFSHDDManager::MainForm::Put_PFS(IO::DirectoryInfo^ dir, File^ file) {
	for each (IO::DirectoryInfo^ item in dir->GetDirectories())
	{
		HDD->PFS_MkDir(file, item->Name);
		Put_PFS(item, file->GetChildName(item->Name));
	}
	for each (IO::FileInfo^ fli in dir->GetFiles())
	{
		if(fli->Name != "desktop.ini")
			if(fli->Extension->ToUpper() != ".ISO" && fli->Extension->ToUpper() != ".CUE")
				HDD->PFS_Put(dir->FullName, fli->Name, file);
			else NotImplemented("Dumping ISO files is not fully working yet!");
	}
}

System::Void PFSHDDManager::MainForm::ReInitializeDeviceToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	HDD->PFS_Initialize(PFSHistory->Peek());
	UpdatePfsView = true;
	ViewPFSPath();
}

System::Void PFSHDDManager::MainForm::GetToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	for each (ListViewItem ^ itm in PFS_View->SelectedItems)
	{
		Get(PFSHistory->Peek()->GetChildName(itm->Text), DirInfoHistory->Peek()->FullName);
	}
}

System::Void PFSHDDManager::MainForm::RenameToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	File^ file = PFSHistory->Peek()->GetChildName(PFS_View->SelectedItems[0]->Text);

	if (PFS_View->SelectedItems->Count != 1) return;

	if (file->Type != File::Types::File && file->Type != File::Types::Folder) return;

	InputBox^ Name = gcnew InputBox;
	if (Name->Show("Name: ", file->Name) != Forms::DialogResult::OK) return;

	HDD->PFS_Rename(PFSHistory->Peek()->GetChildName(PFS_View->SelectedItems[0]->Text), Name->Text);
	UpdatePfsView = true;
	ViewPFSPath();
}

System::Void PFSHDDManager::MainForm::BTN_Get_Click(System::Object^ sender, System::EventArgs^ e)
{
	for each (ListViewItem^ itm in PFS_View->SelectedItems)
	{
		Get(PFSHistory->Peek()->GetChildName(itm->Text), DirInfoHistory->Peek()->FullName);
	}
}

System::Void PFSHDDManager::MainForm::Get(File^ Origin, String^ Dest) {
	if (Origin->Type == File::Types::Folder) {
		if (!IO::DirectoryInfo(Dest + "\\" + Origin->Name).Exists)
			IO::Directory::CreateDirectory(Dest + "\\" + Origin->Name);
		for each (File ^ child in Origin->Childs)
		{
			Get(child, Dest + "\\" + Origin->Name);
		}
	}
	else if (Origin->Type == File::Types::File)
		HDD->PFS_Get(Origin, Dest);
	UpdateView = true;
	ViewPath();
}

System::Void PFSHDDManager::MainForm::RemoveToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if(PFS_View->SelectedItems->Count>0)
		for each (ListViewItem ^ item in PFS_View->SelectedItems)
		{
			PFSHistory->Peek()->GetChildName(item->Text);
			try { HDD->Remove(PFSHistory->Peek()->GetChildName(item->Text)); }
			catch (String^ Error) { MessageBox::Show(Error); }
		}
	UpdatePfsView = true;
	ViewPFSPath();
}

System::Void PFSHDDManager::MainForm::CreatePartitionToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	InputBox^ Name = gcnew InputBox, ^Size = gcnew InputBox;
	if(Name->Show("Partition Name:") == Forms::DialogResult::OK)
		if(Size->Show("Partition Size:\n(Power of 2 in MB)")== System::Windows::Forms::DialogResult::OK)
		try { 
		File^ tmp = HDD->PFS_Mkpart(CurrDev, Name->Text, Convert::ToInt32(Size->Text));
		if (MessageBox::Show("Create PFS on the partition?", "Initialize?", MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes)
			HDD->PFS_Mkfs(tmp);
		UpdatePfsView = true;
		ViewPFSPath();
	}
	catch (String^ Error) { MessageBox::Show(Error, "ERROR!"); }
	return System::Void();
}
System::Void PFSHDDManager::MainForm::NewFolderToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	InputBox^ name = gcnew InputBox;
	if (name->Show("Folder Name:") == Forms::DialogResult::OK) {
		HDD->PFS_MkDir(PFSHistory->Peek(), name->Text);
		UpdatePfsView = true;
		ViewPFSPath();
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