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

template <class T>
System::Boolean Tree<T>::AddChild(T data) {
	AddChild(data, CurrNode->Parent);
}

template <class T>
System::Boolean Tree<T>::AddChild(T data, Node^ parent) {
	Node^ tmp;
	tmp = gcnew Node;
	tmp->Parent = CurrNode;
	tmp->Data = data;
	tmp->Child = nullptr;
	if (parent->Child == nullptr) parent->Child = gcnew System::Collections::Generic::List<Node^>;
	parent->Child->Add(tmp);
}

template<class T>
typename Tree<T>::Node^ Tree<T>::GetCurrNode()
{
	return CurrNode;
}

template<class T>
T Tree<T>::SetCurrNode(T dt)
{
	if (Root->Data == dt) return Root->Data;
	for each (Node^ nd in Root->Child)
	{
		if (nd->Data == dt) return nd->Data;
		if (nd->Child != nullptr);
	}
}

template<class T>
typename Tree<T>::Node^ Tree<T>::SearchNode(T dt)
{
	SrchNode = SearchNode(dt, Root);
	return SrchNode;
}

template<class T>
typename Tree<T>::Node^ Tree<T>::SearchNode(T dt, Node^ sn)
{
	if (sn->Data == dt) return sn;
	if(SrchNode->Child != nullptr) for each (Node^ nd in SrchNode->Child)
	{
		if (nd->Data == dt) return nd;
		return SearchNode(dt, nd);
	}
	return nullptr;
}


template<class T>
System::Boolean Tree<T>::Delete(Node^ nd)
{
	nd = nullptr;
	return true;
}

template<class T>
System::Collections::Generic::List<T>^ filesystem::Tree<T>::GetChildList()
{
	throw gcnew System::NotImplementedException();
	// TODO: insert return statement here
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
T Tree<T>::GetParent()
{
	return CurrNode->Parent->Data;
}

template<class T>
typename Tree<T>::Node^ Tree<T>::test(Node^)
{
	throw gcnew System::NotImplementedException();
	// TODO: insert return statement here
}