#pragma once

namespace filesystem {
	template <class T>
	ref class Tree
	{
	private:
		typedef ref struct Node {
			Node ^Parent;
			System::Collections::Generic::List<Node^>^ Child;
			T Data;
		}Node;
		Node ^Root, ^CurrNode, ^SrchNode;
	public:
		Tree(T root); //create
		System::Boolean AddChild(T data); //create
		System::Boolean AddChild(T data, Node^ parent); //create
		Node^ GetCurrNode();
		T SetCurrNode(T);
		Node^ SearchNode(T);
		Node^ SearchNode(T, Node^);
		System::Boolean Delete(Node^);
		System::Collections::Generic::List<T>^ GetChildList();
		T GetParent();
		Node^ test(Node^);
	};
	//Can`t have Node in return and function types

	ref class File {
	private:
		System::String ^Name, ^Path, ^ParentName;
		enum class Type { file, folder, partition };
		System::Char^ extension;
		System::Int32 Size;
	public:
		File(System::String^ Name) { this->Name = Name; };
		//System::Collections::Generic::List<T>^ FullPath();
	};

	ref class FileSystem {
	private:
		Tree<File^>^ tree;
	public:
		FileSystem(System::String^ Name) { tree = gcnew Tree<File^>(gcnew File(Name)); };
	};
}