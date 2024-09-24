#ifndef ListNode_h
#define ListNode_h

#include <iostream>
#include <fstream>
#include <sstream>

template <typename T>
class ListNode {

public:
	ListNode();

	ListNode(T newCommand, T newDescription);

	ListNode(ListNode* copyNode);

	~ListNode();

	T getCommand();

	T getDescription();

	void setCommand(T newCommand);

	void setDescription(T newDescription);

	ListNode<T>* getNextPtr();

	void setNextPtr(ListNode<T>* newPNext);

private:
	T command;
	T description;
	ListNode<T>* pNext;
};


#include "ListNode.cpp"  //When using templates to define functions you need the definitions in the same file, hence this include.


#endif