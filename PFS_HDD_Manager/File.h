#pragma once
ref class File
{
public:
	//Files
	System::String^ Name, ^ Path;
	enum class Types { File, Folder }Type;
	System::String^ Extension = "";
	System::Int32 Size;
	File^ Parent, ^ Root;
	System::Collections::Generic::List <File^>^ Childs;

	File(System::String^ Name) { this->Name = Name; this->Type = Types::Folder; };
	File(System::String^ Name, File^ Parent, File^ Root) { this->Name = Name; this->Type = Types::Folder; this->Parent = Parent; this->Root = Root; this->Parent->Childs->Add(this); };
	File(System::String^ Name, System::String^ Extension, System::Int32 Size, File^ Parent) { this->Name = Name; this->Extension = Extension; this->Size = Size; this->Parent = Parent; this->Root = this->Parent->Root;};
};