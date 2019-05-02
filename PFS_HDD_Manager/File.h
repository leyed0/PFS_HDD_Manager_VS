#pragma once
ref class File
{
public:
	//Files
	System::String^ Name, ^ Path;
	enum class Types { File, Folder, Device, Partition, PartitionNull, Game }Type;
	System::String^ Extension = "";
	System::Int32 Size;
	File^ Parent = nullptr, ^ Root, ^PartRoot = nullptr;
	System::Collections::Generic::List <File^>^ Childs = nullptr;

	//Creates a Device typed File (usable for Devices)
	File(System::String^ Name) { File::Name = Name; File::Type = Types::Device; File::Root = this; };
	//Creates a File with given type and Parent - The root is reused from Parent(usable for Partitions And Folders)
	File(System::String^ Name, Types Type, File^ Parent) { File::Name = Name; File::Type = Type; File::Parent = Parent; File::Root = Parent->Root; };
	//Creates a File with given type and Parent - The root is reused from Parent(usable for Partitions And Folders)
	//File(System::String^ Name, Types Type, File^ Parent, bool Root) { File::Name = Name; File::Type = Type; File::Parent = Parent; File::Root = Parent->Root; File::PartRoot = this; };
	//Creates a File with given type and Parent and Root (usable for Partitions And Folders)
	File(System::String^ Name, Types Type, File^ Parent, File^ Root) { File::Name = Name; File::Type = Type; File::Parent = Parent, File::Root = Root;};
	//Creates an actual File, With Name, Extension and Size - Root is given by its parent
	File(System::String^ Name, System::String^ Extension, System::Int32 Size, File^ Parent) { File::Name = Name; File::Extension = Extension; File::Size = Size; File::Parent = Parent; File::Root = File::Parent->Root; File::Type = File::Types::File; };
	
	File^ GetChildName(System::String^ Name) {
		if (this->Childs == nullptr) return nullptr;
		for each (File^ child in this->Childs)
		{
			if (child->Name == Name) return child;
		}
		return nullptr;
	};
};