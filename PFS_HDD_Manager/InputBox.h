#pragma once

namespace PFSHDDManager {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>

	/// Sumário para InputBox
	/// </summary>
	public ref class InputBox : public System::Windows::Forms::Form
	{
	public:
		InputBox(void)
		{
			InitializeComponent();
			//this->TXTBX_Input->Location = System::Drawing::Point(64, 8);
			//this->LBL_TXT->
			//
			//TODO: Adicione o código do construtor aqui
			//
		}

	protected:
		/// <summary>
		/// Limpar os recursos que estão sendo usados.
		/// </summary>
		~InputBox()
		{
			if (components)
			{
				delete components;
			}
		}
		enum class InputType { Text, Number}InputType;
	public: String^ Text;
	private: System::Windows::Forms::Button^ BTN_OK;
	private: System::Windows::Forms::Button^ BTN_Cancel;

	private: System::Collections::Generic::List<TextBox^>^ TXTBX;
	private: System::Collections::Generic::List<Label^>^ LBL;
	private: System::Windows::Forms::Label^ LBL_TXT;
	private: System::Windows::Forms::TextBox^ TXTBX_Input;
			 
	private:
		/// <summary>
		/// Variável de designer necessária.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necessário para suporte ao Designer - não modifique 
		/// o conteúdo deste método com o editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->BTN_OK = (gcnew System::Windows::Forms::Button());
			this->BTN_Cancel = (gcnew System::Windows::Forms::Button());
			this->LBL_TXT = (gcnew System::Windows::Forms::Label());
			this->TXTBX_Input = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// BTN_OK
			// 
			this->BTN_OK->Enabled = false;
			this->BTN_OK->Location = System::Drawing::Point(112, 32);
			this->BTN_OK->Name = L"BTN_OK";
			this->BTN_OK->Size = System::Drawing::Size(75, 23);
			this->BTN_OK->TabIndex = 3;
			this->BTN_OK->Text = L"OK";
			this->BTN_OK->UseVisualStyleBackColor = true;
			this->BTN_OK->Click += gcnew System::EventHandler(this, &InputBox::BTN_OK_Click);
			// 
			// BTN_Cancel
			// 
			this->BTN_Cancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->BTN_Cancel->Location = System::Drawing::Point(192, 32);
			this->BTN_Cancel->Name = L"BTN_Cancel";
			this->BTN_Cancel->Size = System::Drawing::Size(75, 23);
			this->BTN_Cancel->TabIndex = 2;
			this->BTN_Cancel->Text = L"Cancel";
			this->BTN_Cancel->UseVisualStyleBackColor = true;
			this->BTN_Cancel->Click += gcnew System::EventHandler(this, &InputBox::BTN_Cancel_Click);
			// 
			// LBL_TXT
			// 
			this->LBL_TXT->AutoSize = true;
			this->LBL_TXT->Location = System::Drawing::Point(8, 12);
			this->LBL_TXT->Name = L"LBL_TXT";
			this->LBL_TXT->Size = System::Drawing::Size(59, 13);
			this->LBL_TXT->TabIndex = 0;
			this->LBL_TXT->Text = L"Enter Text:";
			// 
			// TXTBX_Input
			// 
			this->TXTBX_Input->Location = System::Drawing::Point(64, 8);
			this->TXTBX_Input->Name = L"TXTBX_Input";
			this->TXTBX_Input->Size = System::Drawing::Size(200, 20);
			this->TXTBX_Input->TabIndex = 1;
			this->TXTBX_Input->CursorChanged += gcnew System::EventHandler(this, &InputBox::TXTBX_Input_TextChanged);
			this->TXTBX_Input->TextChanged += gcnew System::EventHandler(this, &InputBox::TXTBX_Input_TextChanged);
			// 
			// InputBox
			// 
			this->AcceptButton = this->BTN_OK;
			this->AccessibleRole = System::Windows::Forms::AccessibleRole::Dialog;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->CancelButton = this->BTN_Cancel;
			this->ClientSize = System::Drawing::Size(290, 66);
			this->ControlBox = false;
			this->Controls->Add(this->TXTBX_Input);
			this->Controls->Add(this->LBL_TXT);
			this->Controls->Add(this->BTN_Cancel);
			this->Controls->Add(this->BTN_OK);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"InputBox";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	public: System::Windows::Forms::DialogResult Show();
	public: System::Windows::Forms::DialogResult Show(String^);
	private: System::Void BTN_OK_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void BTN_Cancel_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void TXTBX_Input_TextChanged(System::Object^ sender, System::EventArgs^ e);
	};
}