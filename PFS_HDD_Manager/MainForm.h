#pragma once
#include"PS2HDD.h"
#include"InputBox.h"

namespace PFSHDDManager {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Sumário para MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//codigo extra
			HDD = gcnew PS2HDD;
		}

	protected:
		/// <summary>
		/// Limpar os recursos que estão sendo usados.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: PS2HDD::Device^ CurrDev;
	private: PS2HDD::Partition^ CurrPart;
	private: System::Diagnostics::Process^ PFSShell;
	private: System::Diagnostics::Process^ HDLDump;
	private: PS2HDD^ HDD;
	private: System::Collections::Generic::Stack <String^>^ PathHistory;
	private: System::Collections::Generic::Stack <String^>^ Path1History;
	private: System::Collections::Generic::Stack <IO::DirectoryInfo^>^ DirInfoHistory;
	private: System::Collections::Generic::Stack <File^>^ PFSHistory;
	//BackgroundWorker^ teste;
	private: array<System::String^> ^dir, ^file;
	private: System::String^ Path;
	private: System::Boolean debug = false, UpdateView = true, UpdatePfsView = true;
	private: System::Windows::Forms::ImageList^ ICONS_LARGE;

	private: System::Windows::Forms::ContextMenuStrip^  PATH_VIEW_CONTEXT;
	private: System::Windows::Forms::ToolStripMenuItem^  exibiçãoToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  íconesGrandesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  íconesPequenosToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  detalhesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  listaToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  gradeToolStripMenuItem;
	private: System::Windows::Forms::ImageList^ ICONS_SMALL;





	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel2;
	private: System::Windows::Forms::ComboBox^  DRIVE_LTR2;
	private: System::Windows::Forms::Button^  BTN_GO2;
	private: System::Windows::Forms::TextBox^  TXTBX_PATH2;

	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel3;
	private: System::Windows::Forms::ComboBox^  DRIVE_LTR;
	private: System::Windows::Forms::Button^  BTN_GO;
	private: System::Windows::Forms::TextBox^ TXTBX_Path_View;


	private: System::Windows::Forms::Button^  BTN_BACK;
	private: System::Windows::Forms::ListView^ PFS_View;


	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  FileManagerTab;
	private: System::Windows::Forms::TabPage^  PartitionManagerTab;

	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel4;
	private: System::Windows::Forms::Button^ BTN_BACK2;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel5;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::ContextMenuStrip^ TestStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ GAME_ToolStrip_Remove;
	private: System::Windows::Forms::ContextMenuStrip^ PFS_ContextMenu;

	private: System::Windows::Forms::ToolStripMenuItem^ createPartitionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ reInitializeDeviceToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ RemoveToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^ getToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ newFolderToolStripMenuItem;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel6;
	private: System::Windows::Forms::Button^ BTN_Put;
	private: System::Windows::Forms::Button^ BTN_Get;
	private: System::Windows::Forms::ListView^ Path_View;
	private: System::Windows::Forms::ToolStripMenuItem^ renameToolStripMenuItem;



	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Variável de designer necessária.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necessário para suporte ao Designer - não modifique 
		/// o conteúdo deste método com o editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->ICONS_LARGE = (gcnew System::Windows::Forms::ImageList(this->components));
			this->PATH_VIEW_CONTEXT = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->exibiçãoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->íconesGrandesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->íconesPequenosToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->detalhesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->listaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->gradeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ICONS_SMALL = (gcnew System::Windows::Forms::ImageList(this->components));
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->DRIVE_LTR2 = (gcnew System::Windows::Forms::ComboBox());
			this->BTN_GO2 = (gcnew System::Windows::Forms::Button());
			this->TXTBX_PATH2 = (gcnew System::Windows::Forms::TextBox());
			this->BTN_BACK2 = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->PFS_View = (gcnew System::Windows::Forms::ListView());
			this->PFS_ContextMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->createPartitionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->newFolderToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->RemoveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->renameToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->getToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->reInitializeDeviceToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->DRIVE_LTR = (gcnew System::Windows::Forms::ComboBox());
			this->BTN_GO = (gcnew System::Windows::Forms::Button());
			this->TXTBX_Path_View = (gcnew System::Windows::Forms::TextBox());
			this->BTN_BACK = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel6 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->BTN_Put = (gcnew System::Windows::Forms::Button());
			this->BTN_Get = (gcnew System::Windows::Forms::Button());
			this->Path_View = (gcnew System::Windows::Forms::ListView());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->FileManagerTab = (gcnew System::Windows::Forms::TabPage());
			this->PartitionManagerTab = (gcnew System::Windows::Forms::TabPage());
			this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel5 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->TestStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->GAME_ToolStrip_Remove = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PATH_VIEW_CONTEXT->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->PFS_ContextMenu->SuspendLayout();
			this->tableLayoutPanel3->SuspendLayout();
			this->tableLayoutPanel6->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->FileManagerTab->SuspendLayout();
			this->PartitionManagerTab->SuspendLayout();
			this->tableLayoutPanel4->SuspendLayout();
			this->tableLayoutPanel5->SuspendLayout();
			this->TestStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// ICONS_LARGE
			// 
			this->ICONS_LARGE->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"ICONS_LARGE.ImageStream")));
			this->ICONS_LARGE->TransparentColor = System::Drawing::Color::Transparent;
			this->ICONS_LARGE->Images->SetKeyName(0, L"5_memory_card-game-controller-save-playstation-512.png");
			this->ICONS_LARGE->Images->SetKeyName(1, L"Game.png");
			this->ICONS_LARGE->Images->SetKeyName(2, L"file.png");
			this->ICONS_LARGE->Images->SetKeyName(3, L"folder.png");
			// 
			// PATH_VIEW_CONTEXT
			// 
			this->PATH_VIEW_CONTEXT->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->exibiçãoToolStripMenuItem });
			this->PATH_VIEW_CONTEXT->Name = L"PATH_VIEW_CONTEXT";
			this->PATH_VIEW_CONTEXT->Size = System::Drawing::Size(118, 26);
			// 
			// exibiçãoToolStripMenuItem
			// 
			this->exibiçãoToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->íconesGrandesToolStripMenuItem,
					this->íconesPequenosToolStripMenuItem, this->detalhesToolStripMenuItem, this->listaToolStripMenuItem, this->gradeToolStripMenuItem
			});
			this->exibiçãoToolStripMenuItem->Name = L"exibiçãoToolStripMenuItem";
			this->exibiçãoToolStripMenuItem->Size = System::Drawing::Size(117, 22);
			this->exibiçãoToolStripMenuItem->Text = L"Exibição";
			// 
			// íconesGrandesToolStripMenuItem
			// 
			this->íconesGrandesToolStripMenuItem->Name = L"íconesGrandesToolStripMenuItem";
			this->íconesGrandesToolStripMenuItem->Size = System::Drawing::Size(163, 22);
			this->íconesGrandesToolStripMenuItem->Text = L"Ícones Grandes";
			this->íconesGrandesToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::íconesGrandesToolStripMenuItem_Click);
			// 
			// íconesPequenosToolStripMenuItem
			// 
			this->íconesPequenosToolStripMenuItem->Name = L"íconesPequenosToolStripMenuItem";
			this->íconesPequenosToolStripMenuItem->Size = System::Drawing::Size(163, 22);
			this->íconesPequenosToolStripMenuItem->Text = L"Ícones Pequenos";
			this->íconesPequenosToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::íconesPequenosToolStripMenuItem_Click);
			// 
			// detalhesToolStripMenuItem
			// 
			this->detalhesToolStripMenuItem->Name = L"detalhesToolStripMenuItem";
			this->detalhesToolStripMenuItem->Size = System::Drawing::Size(163, 22);
			this->detalhesToolStripMenuItem->Text = L"Detalhes";
			this->detalhesToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::detalhesToolStripMenuItem_Click);
			// 
			// listaToolStripMenuItem
			// 
			this->listaToolStripMenuItem->Name = L"listaToolStripMenuItem";
			this->listaToolStripMenuItem->Size = System::Drawing::Size(163, 22);
			this->listaToolStripMenuItem->Text = L"Lista";
			this->listaToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::listaToolStripMenuItem_Click);
			// 
			// gradeToolStripMenuItem
			// 
			this->gradeToolStripMenuItem->Name = L"gradeToolStripMenuItem";
			this->gradeToolStripMenuItem->Size = System::Drawing::Size(163, 22);
			this->gradeToolStripMenuItem->Text = L"Grade";
			this->gradeToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::gradeToolStripMenuItem_Click);
			// 
			// ICONS_SMALL
			// 
			this->ICONS_SMALL->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"ICONS_SMALL.ImageStream")));
			this->ICONS_SMALL->TransparentColor = System::Drawing::Color::Transparent;
			this->ICONS_SMALL->Images->SetKeyName(0, L"5_memory_card-game-controller-save-playstation-512.png");
			this->ICONS_SMALL->Images->SetKeyName(1, L"Game.png");
			this->ICONS_SMALL->Images->SetKeyName(2, L"file.png");
			this->ICONS_SMALL->Images->SetKeyName(3, L"folder.png");
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 4;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				55)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				55)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				55)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				20)));
			this->tableLayoutPanel2->Controls->Add(this->DRIVE_LTR2, 0, 0);
			this->tableLayoutPanel2->Controls->Add(this->BTN_GO2, 2, 0);
			this->tableLayoutPanel2->Controls->Add(this->TXTBX_PATH2, 1, 0);
			this->tableLayoutPanel2->Controls->Add(this->BTN_BACK2, 3, 0);
			this->tableLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel2->Location = System::Drawing::Point(535, 3);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 1;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 27)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 27)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(456, 27);
			this->tableLayoutPanel2->TabIndex = 4;
			// 
			// DRIVE_LTR2
			// 
			this->DRIVE_LTR2->Dock = System::Windows::Forms::DockStyle::Top;
			this->DRIVE_LTR2->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->DRIVE_LTR2->FormattingEnabled = true;
			this->DRIVE_LTR2->Location = System::Drawing::Point(3, 3);
			this->DRIVE_LTR2->MaxDropDownItems = 20;
			this->DRIVE_LTR2->Name = L"DRIVE_LTR2";
			this->DRIVE_LTR2->Size = System::Drawing::Size(49, 21);
			this->DRIVE_LTR2->TabIndex = 0;
			this->DRIVE_LTR2->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::DRIVE_LTR2_SelectedIndexChanged);
			// 
			// BTN_GO2
			// 
			this->BTN_GO2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->BTN_GO2->Location = System::Drawing::Point(349, 3);
			this->BTN_GO2->Name = L"BTN_GO2";
			this->BTN_GO2->Size = System::Drawing::Size(49, 21);
			this->BTN_GO2->TabIndex = 1;
			this->BTN_GO2->Text = L"GO";
			this->BTN_GO2->UseVisualStyleBackColor = true;
			this->BTN_GO2->Click += gcnew System::EventHandler(this, &MainForm::BTN_GO2_Click);
			// 
			// TXTBX_PATH2
			// 
			this->TXTBX_PATH2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->TXTBX_PATH2->Location = System::Drawing::Point(58, 3);
			this->TXTBX_PATH2->Name = L"TXTBX_PATH2";
			this->TXTBX_PATH2->Size = System::Drawing::Size(285, 20);
			this->TXTBX_PATH2->TabIndex = 0;
			// 
			// BTN_BACK2
			// 
			this->BTN_BACK2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->BTN_BACK2->Location = System::Drawing::Point(404, 3);
			this->BTN_BACK2->Name = L"BTN_BACK2";
			this->BTN_BACK2->Size = System::Drawing::Size(49, 21);
			this->BTN_BACK2->TabIndex = 1;
			this->BTN_BACK2->Text = L"BACK";
			this->BTN_BACK2->UseVisualStyleBackColor = true;
			this->BTN_BACK2->Click += gcnew System::EventHandler(this, &MainForm::BTN_BACK2_Click);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->AutoScroll = true;
			this->tableLayoutPanel1->AutoSize = true;
			this->tableLayoutPanel1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->tableLayoutPanel1->ColumnCount = 3;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				70)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->Controls->Add(this->PFS_View, 2, 1);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel3, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel2, 2, 0);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel6, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->Path_View, 0, 1);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(3, 3);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 33)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 100)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(994, 529);
			this->tableLayoutPanel1->TabIndex = 3;
			this->tableLayoutPanel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::tableLayoutPanel1_Paint);
			// 
			// PFS_View
			// 
			this->PFS_View->AllowDrop = true;
			this->PFS_View->ContextMenuStrip = this->PFS_ContextMenu;
			this->PFS_View->Dock = System::Windows::Forms::DockStyle::Fill;
			this->PFS_View->LargeImageList = this->ICONS_LARGE;
			this->PFS_View->Location = System::Drawing::Point(535, 36);
			this->PFS_View->Name = L"PFS_View";
			this->PFS_View->Size = System::Drawing::Size(456, 490);
			this->PFS_View->SmallImageList = this->ICONS_SMALL;
			this->PFS_View->TabIndex = 7;
			this->PFS_View->UseCompatibleStateImageBehavior = false;
			this->PFS_View->DoubleClick += gcnew System::EventHandler(this, &MainForm::PFS_View_DoubleClick);
			this->PFS_View->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::PFS_View_MouseClick);
			this->PFS_View->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::PFS_View_MouseDoubleClick);
			this->PFS_View->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::PFS_View_MouseDown);
			// 
			// PFS_ContextMenu
			// 
			this->PFS_ContextMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->createPartitionToolStripMenuItem,
					this->newFolderToolStripMenuItem, this->RemoveToolStripMenuItem, this->renameToolStripMenuItem, this->getToolStripMenuItem, this->reInitializeDeviceToolStripMenuItem
			});
			this->PFS_ContextMenu->Name = L"PFS_MainStrip";
			this->PFS_ContextMenu->Size = System::Drawing::Size(174, 136);
			this->PFS_ContextMenu->Opening += gcnew System::ComponentModel::CancelEventHandler(this, &MainForm::PFS_ContextMenu_Opening);
			// 
			// createPartitionToolStripMenuItem
			// 
			this->createPartitionToolStripMenuItem->Name = L"createPartitionToolStripMenuItem";
			this->createPartitionToolStripMenuItem->Size = System::Drawing::Size(173, 22);
			this->createPartitionToolStripMenuItem->Text = L"Create Partition";
			this->createPartitionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::CreatePartitionToolStripMenuItem_Click);
			// 
			// newFolderToolStripMenuItem
			// 
			this->newFolderToolStripMenuItem->Name = L"newFolderToolStripMenuItem";
			this->newFolderToolStripMenuItem->Size = System::Drawing::Size(173, 22);
			this->newFolderToolStripMenuItem->Text = L"New Folder";
			this->newFolderToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::NewFolderToolStripMenuItem_Click);
			// 
			// RemoveToolStripMenuItem
			// 
			this->RemoveToolStripMenuItem->Name = L"RemoveToolStripMenuItem";
			this->RemoveToolStripMenuItem->Size = System::Drawing::Size(173, 22);
			this->RemoveToolStripMenuItem->Text = L"Remove";
			this->RemoveToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::RemoveToolStripMenuItem_Click);
			// 
			// renameToolStripMenuItem
			// 
			this->renameToolStripMenuItem->Name = L"renameToolStripMenuItem";
			this->renameToolStripMenuItem->Size = System::Drawing::Size(173, 22);
			this->renameToolStripMenuItem->Text = L"Rename";
			this->renameToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::RenameToolStripMenuItem_Click);
			// 
			// getToolStripMenuItem
			// 
			this->getToolStripMenuItem->Name = L"getToolStripMenuItem";
			this->getToolStripMenuItem->Size = System::Drawing::Size(173, 22);
			this->getToolStripMenuItem->Text = L"Get";
			this->getToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::GetToolStripMenuItem_Click);
			// 
			// reInitializeDeviceToolStripMenuItem
			// 
			this->reInitializeDeviceToolStripMenuItem->AutoToolTip = true;
			this->reInitializeDeviceToolStripMenuItem->Name = L"reInitializeDeviceToolStripMenuItem";
			this->reInitializeDeviceToolStripMenuItem->Size = System::Drawing::Size(173, 22);
			this->reInitializeDeviceToolStripMenuItem->Text = L"Re-Initialize Device";
			this->reInitializeDeviceToolStripMenuItem->ToolTipText = L"Destroys all the Data on It";
			this->reInitializeDeviceToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::ReInitializeDeviceToolStripMenuItem_Click);
			// 
			// tableLayoutPanel3
			// 
			this->tableLayoutPanel3->ColumnCount = 4;
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				55)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				55)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				55)));
			this->tableLayoutPanel3->Controls->Add(this->DRIVE_LTR, 0, 0);
			this->tableLayoutPanel3->Controls->Add(this->BTN_GO, 2, 0);
			this->tableLayoutPanel3->Controls->Add(this->TXTBX_Path_View, 1, 0);
			this->tableLayoutPanel3->Controls->Add(this->BTN_BACK, 3, 0);
			this->tableLayoutPanel3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel3->Location = System::Drawing::Point(3, 3);
			this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			this->tableLayoutPanel3->RowCount = 1;
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 27)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 27)));
			this->tableLayoutPanel3->Size = System::Drawing::Size(456, 27);
			this->tableLayoutPanel3->TabIndex = 6;
			// 
			// DRIVE_LTR
			// 
			this->DRIVE_LTR->Dock = System::Windows::Forms::DockStyle::Top;
			this->DRIVE_LTR->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->DRIVE_LTR->FormattingEnabled = true;
			this->DRIVE_LTR->Location = System::Drawing::Point(3, 3);
			this->DRIVE_LTR->MaxDropDownItems = 20;
			this->DRIVE_LTR->Name = L"DRIVE_LTR";
			this->DRIVE_LTR->Size = System::Drawing::Size(49, 21);
			this->DRIVE_LTR->TabIndex = 0;
			this->DRIVE_LTR->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::DRIVE_LTR_SelectedIndexChanged);
			this->DRIVE_LTR->SelectedValueChanged += gcnew System::EventHandler(this, &MainForm::DRIVE_LTR_SelectedValueChanged);
			// 
			// BTN_GO
			// 
			this->BTN_GO->Dock = System::Windows::Forms::DockStyle::Fill;
			this->BTN_GO->Location = System::Drawing::Point(349, 3);
			this->BTN_GO->Name = L"BTN_GO";
			this->BTN_GO->Size = System::Drawing::Size(49, 21);
			this->BTN_GO->TabIndex = 1;
			this->BTN_GO->Text = L"GO";
			this->BTN_GO->UseVisualStyleBackColor = true;
			this->BTN_GO->Click += gcnew System::EventHandler(this, &MainForm::BTN_GO_Click);
			// 
			// TXTBX_Path_View
			// 
			this->TXTBX_Path_View->Dock = System::Windows::Forms::DockStyle::Fill;
			this->TXTBX_Path_View->Location = System::Drawing::Point(58, 3);
			this->TXTBX_Path_View->Name = L"TXTBX_Path_View";
			this->TXTBX_Path_View->Size = System::Drawing::Size(285, 20);
			this->TXTBX_Path_View->TabIndex = 0;
			this->TXTBX_Path_View->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::TXTBX_PATH_KeyPress);
			// 
			// BTN_BACK
			// 
			this->BTN_BACK->Dock = System::Windows::Forms::DockStyle::Fill;
			this->BTN_BACK->Location = System::Drawing::Point(404, 3);
			this->BTN_BACK->Name = L"BTN_BACK";
			this->BTN_BACK->Size = System::Drawing::Size(49, 21);
			this->BTN_BACK->TabIndex = 1;
			this->BTN_BACK->Text = L"BACK";
			this->BTN_BACK->UseVisualStyleBackColor = true;
			this->BTN_BACK->Click += gcnew System::EventHandler(this, &MainForm::BTN_BACK_Click);
			// 
			// tableLayoutPanel6
			// 
			this->tableLayoutPanel6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tableLayoutPanel6->ColumnCount = 1;
			this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel6->Controls->Add(this->BTN_Put, 0, 1);
			this->tableLayoutPanel6->Controls->Add(this->BTN_Get, 0, 2);
			this->tableLayoutPanel6->Location = System::Drawing::Point(465, 36);
			this->tableLayoutPanel6->Name = L"tableLayoutPanel6";
			this->tableLayoutPanel6->RowCount = 4;
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 30)));
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 30)));
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel6->Size = System::Drawing::Size(64, 490);
			this->tableLayoutPanel6->TabIndex = 8;
			// 
			// BTN_Put
			// 
			this->BTN_Put->Dock = System::Windows::Forms::DockStyle::Fill;
			this->BTN_Put->Location = System::Drawing::Point(3, 218);
			this->BTN_Put->Name = L"BTN_Put";
			this->BTN_Put->Size = System::Drawing::Size(58, 24);
			this->BTN_Put->TabIndex = 0;
			this->BTN_Put->Text = L">>";
			this->BTN_Put->UseVisualStyleBackColor = true;
			this->BTN_Put->Click += gcnew System::EventHandler(this, &MainForm::BTN_Put_Click);
			// 
			// BTN_Get
			// 
			this->BTN_Get->Dock = System::Windows::Forms::DockStyle::Fill;
			this->BTN_Get->Location = System::Drawing::Point(3, 248);
			this->BTN_Get->Name = L"BTN_Get";
			this->BTN_Get->Size = System::Drawing::Size(58, 24);
			this->BTN_Get->TabIndex = 0;
			this->BTN_Get->Text = L"<<";
			this->BTN_Get->UseVisualStyleBackColor = true;
			this->BTN_Get->Click += gcnew System::EventHandler(this, &MainForm::BTN_Get_Click);
			// 
			// Path_View
			// 
			this->Path_View->AllowDrop = true;
			this->Path_View->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Path_View->LargeImageList = this->ICONS_LARGE;
			this->Path_View->Location = System::Drawing::Point(3, 36);
			this->Path_View->Name = L"Path_View";
			this->Path_View->Size = System::Drawing::Size(456, 490);
			this->Path_View->SmallImageList = this->ICONS_SMALL;
			this->Path_View->TabIndex = 9;
			this->Path_View->UseCompatibleStateImageBehavior = false;
			this->Path_View->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::Path_View_MouseDoubleClick);
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->FileManagerTab);
			this->tabControl1->Controls->Add(this->PartitionManagerTab);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(1008, 561);
			this->tabControl1->TabIndex = 4;
			// 
			// FileManagerTab
			// 
			this->FileManagerTab->Controls->Add(this->tableLayoutPanel1);
			this->FileManagerTab->Location = System::Drawing::Point(4, 22);
			this->FileManagerTab->Name = L"FileManagerTab";
			this->FileManagerTab->Padding = System::Windows::Forms::Padding(3);
			this->FileManagerTab->Size = System::Drawing::Size(1000, 535);
			this->FileManagerTab->TabIndex = 0;
			this->FileManagerTab->Text = L"File Manager";
			this->FileManagerTab->UseVisualStyleBackColor = true;
			// 
			// PartitionManagerTab
			// 
			this->PartitionManagerTab->Controls->Add(this->tableLayoutPanel4);
			this->PartitionManagerTab->Location = System::Drawing::Point(4, 22);
			this->PartitionManagerTab->Name = L"PartitionManagerTab";
			this->PartitionManagerTab->Padding = System::Windows::Forms::Padding(3);
			this->PartitionManagerTab->Size = System::Drawing::Size(1000, 535);
			this->PartitionManagerTab->TabIndex = 1;
			this->PartitionManagerTab->Text = L"In Construction";
			this->PartitionManagerTab->UseVisualStyleBackColor = true;
			// 
			// tableLayoutPanel4
			// 
			this->tableLayoutPanel4->ColumnCount = 1;
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				20)));
			this->tableLayoutPanel4->Controls->Add(this->tableLayoutPanel5, 0, 0);
			this->tableLayoutPanel4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel4->Location = System::Drawing::Point(3, 3);
			this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
			this->tableLayoutPanel4->RowCount = 2;
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 33)));
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel4->Size = System::Drawing::Size(994, 529);
			this->tableLayoutPanel4->TabIndex = 0;
			// 
			// tableLayoutPanel5
			// 
			this->tableLayoutPanel5->ColumnCount = 4;
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				55)));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				55)));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				55)));
			this->tableLayoutPanel5->Controls->Add(this->label1, 0, 0);
			this->tableLayoutPanel5->Controls->Add(this->comboBox1, 1, 0);
			this->tableLayoutPanel5->Controls->Add(this->button2, 2, 0);
			this->tableLayoutPanel5->Controls->Add(this->button3, 3, 0);
			this->tableLayoutPanel5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel5->Location = System::Drawing::Point(3, 3);
			this->tableLayoutPanel5->Name = L"tableLayoutPanel5";
			this->tableLayoutPanel5->RowCount = 1;
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel5->Size = System::Drawing::Size(988, 27);
			this->tableLayoutPanel5->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(3, 7);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(44, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Device:";
			// 
			// comboBox1
			// 
			this->comboBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(58, 3);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(817, 21);
			this->comboBox1->TabIndex = 1;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(881, 3);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(49, 21);
			this->button2->TabIndex = 2;
			this->button2->Text = L"button2";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(936, 3);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(49, 21);
			this->button3->TabIndex = 3;
			this->button3->Text = L"button3";
			this->button3->UseVisualStyleBackColor = true;
			// 
			// TestStrip1
			// 
			this->TestStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->GAME_ToolStrip_Remove });
			this->TestStrip1->Name = L"TestStrip1";
			this->TestStrip1->Size = System::Drawing::Size(118, 26);
			// 
			// GAME_ToolStrip_Remove
			// 
			this->GAME_ToolStrip_Remove->Name = L"GAME_ToolStrip_Remove";
			this->GAME_ToolStrip_Remove->Size = System::Drawing::Size(117, 22);
			this->GAME_ToolStrip_Remove->Text = L"Remove";
			this->GAME_ToolStrip_Remove->Click += gcnew System::EventHandler(this, &MainForm::GAME_ToolStrip_Remove_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1008, 561);
			this->Controls->Add(this->tabControl1);
			this->MinimumSize = System::Drawing::Size(800, 600);
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"PFS HDD Manager by Leyed";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->PATH_VIEW_CONTEXT->ResumeLayout(false);
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->PFS_ContextMenu->ResumeLayout(false);
			this->tableLayoutPanel3->ResumeLayout(false);
			this->tableLayoutPanel3->PerformLayout();
			this->tableLayoutPanel6->ResumeLayout(false);
			this->tabControl1->ResumeLayout(false);
			this->FileManagerTab->ResumeLayout(false);
			this->FileManagerTab->PerformLayout();
			this->PartitionManagerTab->ResumeLayout(false);
			this->tableLayoutPanel4->ResumeLayout(false);
			this->tableLayoutPanel5->ResumeLayout(false);
			this->tableLayoutPanel5->PerformLayout();
			this->TestStrip1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion


	private: System::Void ViewPath();
	private: System::Void ViewPath(System::String^ path);
	private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e);
	private: System::Void íconesGrandesToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void íconesPequenosToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void detalhesToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void listaToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void gradeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void BTN_GO_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void BTN_BACK_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void Debug_Button_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void StartProcess(System::String^ fileName, System::String^ arguments);
	private: System::Void DRIVE_LTR_SelectedValueChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void tableLayoutPanel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
}
	private: System::Void TXTBX_PATH_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void BTN_GO2_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void ListPS2HDD();
	private: System::Void DRIVE_LTR2_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
			 System::Void ViewPFSPath();
	private: System::Void GAME_ToolStrip_Remove_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void BTN_BACK2_Click(System::Object^ sender, System::EventArgs^ e);

private: System::Void PFS_View_DoubleClick(System::Object^ sender, System::EventArgs^ e);
private: System::Void PFS_View_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
private: System::Void PFS_View_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
private: System::Void PFS_View_MouseDoubleClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
private: System::Void PFS_ContextMenu_Opening(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e);
private: System::Void PATH_VIEW_ItemDrag(System::Object^ sender, System::Windows::Forms::ItemDragEventArgs^ e) {
}
private: System::Void PATH_VIEW_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e);
private: System::Void BTN_Put_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void BTN_Get_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void Get(File^Origin, String^ Dest);
private: System::Void RemoveToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void CreatePartitionToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void NewFolderToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void DRIVE_LTR_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
private: System::Void Path_View_MouseDoubleClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		 System::Void Put_PFS(IO::DirectoryInfo^, File^);
		 System::Void NotImplemented(String^ txt) { MessageBox::Show(txt, "Not implemented yet"); }
private: System::Void ReInitializeDeviceToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void GetToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void RenameToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
};
}
