#pragma once

namespace filesystem {
	template <class T>
	ref class Tree
	{
	public:
		typedef ref struct Node {
			Node ^Parent;
			System::Collections::Generic::List<Node^>^ Child;
			T Data;
		}Nd;
		Node ^Root, ^CurrNode, ^SrchNode;
	public:
		Tree(T root); //create
		System::Boolean AddChild(T data) { AddChild(data, CurrNode); }; //create
		System::Boolean AddChild(T data, Node^ parent); //create
		Node^ GetCurrNode() { return CurrNode; };
		System::Void SetCurrNode(Node^ Nd) { CurrNode = Nd; };
		Node^ SearchNode(T);
		Node^ SearchNode(T, Node^);
		System::Boolean Delete(Node^);
		System::Collections::Generic::List<Node^>^ GetChildList(Node^ Nd) { return Nd->Child; };
		Node^ GetParent(Node^ Nd) { return Nd->Parent; };
		Node^ test(Node^);
	};
	//Can`t have Node in return and function types

	ref class File {
	public:
		System::String ^Name, ^Path, ^ParentName;
		enum class Type { File, Folder, Partition }type;
		System::String^ extension;
		System::Int32 Size;
	public:
		File(System::String^ Name, Type Tp) { this->Name = Name; this->type = Tp; };
		File(System::String^ Name) { this->Name = Name; this->type = Type::Folder; };
		File(System::String^ Name, System::String^ Ext, System::Int32 Size) { this->type = Type::File; this->Name = Name; this->extension = Ext; this->Size = Size; };
		File(System::String^ Name, System::Int32 Size) { this->Name = Name; this->Size = Size; };
		//System::Collections::Generic::List<T>^ FullPath();
	};

	ref class FileSystem {
	private:
		Tree<File^>^ tree;
	public:
		FileSystem(System::String^ Name) { tree = gcnew Tree<File^>(gcnew File(Name)); };
	};
}