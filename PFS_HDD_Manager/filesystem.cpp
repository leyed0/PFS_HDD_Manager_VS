#include "filesystem.h"
using namespace filesystem;

template <class T>
Tree<T>::Tree(T root)
{
	Root = gcnew Node;
	Root->Data = root;
	Root->Parent = nullptr;
	Root->Child = gcnew System::Collections::Generic::List<Node^>;
	CurrNode = Root;
}

//template <class T>
//System::Boolean Tree<T>::AddChild(T data) {
//	AddChild(data, CurrNode);
//}

template <class T>
System::Boolean Tree<T>::AddChild(T data, Node^ parent) {
	Node^ tmp = gcnew Node;
	tmp->Parent = parent;
	tmp->Data = data;
	tmp->Child = gcnew System::Collections::Generic::List<Node^>;
	parent->Child->Add(tmp);
}

//template<class T>
//typename Tree<T>::Node^ Tree<T>::GetCurrNode()
//{
//	return CurrNode;
//}

//template<class T>
//System::Void Tree<T>::SetCurrNode(Node^ Nd)
//{
//	if (Root->Data == dt) return Root->Data;
//	for each (Node^ nd in Root->Child)
//	{
//		if (nd->Data == dt) return nd->Data;
//		if (nd->Child != nullptr);
//	}
//}

template<class T>
typename Tree<T>::Node^ Tree<T>::SearchNode(T dt)
{
	return SearchNode(dt, Root);
}

template<class T>
typename Tree<T>::Node^ Tree<T>::SearchNode(T dt, Node^ sn)
{
	if (sn->Data == dt) return sn;
	for each (Node^ nd in sn->Child)
	{
		if (nd->Data == dt) return nd;
		return SearchNode(dt, nd);
	}
	return nullptr;
}


template<class T>
System::Boolean Tree<T>::Delete(Node^ nd)
{
	if (nd->Child->Count == 0) nd = nullptr;
	else return false;
	return true;
}


//template<class T>
//System::Collections::Generic::List<Tree<T>::Node^>^ Tree<T>::GetChildList()
//{
//	System::Collections::Generic::List<T>^ ret = gcnew System::Collections::Generic::List<T>;
//	if(CurrNode->Child != nullptr) for each (Node^ nd in CurrNode->Child)
//	{
//		ret->Add(nd->Data);
//	}
//	return ret;
//}

template<class T>
typename Tree<T>::Node^ Tree<T>::test(Node^)
{
	throw gcnew System::NotImplementedException();
	// TODO: insert return statement here
}