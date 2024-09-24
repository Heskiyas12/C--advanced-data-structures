#ifndef ListNode_c
#define ListNode_c

#include "ListNode.hpp"

template <typename T>
ListNode<T>::ListNode() {
	command = nullptr;
	description = nullptr;
	pNext = nullptr;
}

template <typename T>
ListNode<T>::ListNode(T newCommand, T newDescription) {//constructor with input
	command = newCommand;
	description = newDescription;
	pNext = nullptr;
}

template <typename T>
ListNode<T>::ListNode(ListNode* copyNode) {
	command = copyNode->getCommand();
	description = copyNode->getDescription();
}

template <typename T>
ListNode<T>::~ListNode() {
	//apparently we only have to delete what we create with "new"
}

template <typename T>
T ListNode<T>::getCommand() {
	return command;
}

template <typename T>
T ListNode<T>::getDescription() {
	return description;
}

template <typename T>
void ListNode<T>::setCommand(T newCommand) {
	command = newCommand;
}

template <typename T>
void ListNode<T>::setDescription(T newDescription) {
	description = newDescription;
}

template <typename T>
ListNode<T>* ListNode<T>::getNextPtr() {
	return pNext;
}

template <typename T>
void ListNode<T>::setNextPtr(ListNode<T>* newPNext) {
	pNext = newPNext;
}

#endif