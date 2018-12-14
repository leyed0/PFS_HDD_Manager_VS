#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace PFSHDDManager;

[STAThreadAttribute]
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	PFSHDDManager::MainForm form;
	Application::Run(%form);
}



System::Void PFSHDDManager::MainForm::ViewPath(System::String ^ path)
{
	System::Windows::Forms::ImageList^  IMAGELIST;
	if (PATH_VIEW->View == System::Windows::Forms::View::LargeIcon)  IMAGELIST = PATH_VIEW->LargeImageList;
	if (PATH_VIEW->View == System::Windows::Forms::View::SmallIcon)  IMAGELIST = PATH_VIEW->SmallImageList;

	Path = path;
	TXTBX_PATH->Text = Path;
	PATH_VIEW->Clear();
	History.Push(Path);
	try {
		int j = 20;
		array<String^>^ dir = IO::Directory::GetDirectories(Path);
		array<String^>^ file = IO::Directory::GetFiles(Path);
		for (int i = 0; i < dir->Length; i++) {
			PATH_VIEW->Items->Add(dir[i]->Substring(dir[i]->LastIndexOf("\\") + 1), IMAGELIST->Images->Count - 1);
		}
		for (int i = 0; i < file->Length; i++) {
			PATH_VIEW->Items->Add(file[i]->Substring(file[i]->LastIndexOf("\\") + 1), IMAGELIST->Images->Count - 2);
		}
	}
	catch (int err)
	{
		err += 1;
	}
	return System::Void();
}

System::Void PFSHDDManager::MainForm::MainForm_Load(System::Object ^ sender, System::EventArgs ^ e)
{
	DRIVE_LTR->Items->AddRange(System::IO::Directory::GetLogicalDrives());
	Path = System::IO::Directory::GetLogicalDrives()[1];
	ViewPath(Path);
	return System::Void();
}

System::Void PFSHDDManager::MainForm::PATH_VIEW_DoubleClick(System::Object ^ sender, System::EventArgs ^ e)
{
	if (Path->EndsWith("\\"))Path = Path->Substring(0, Path->Length - 1);
	Path = Path + "\\" + PATH_VIEW->SelectedItems[0]->Text;
	TXTBX_PATH->Text = Path;
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
