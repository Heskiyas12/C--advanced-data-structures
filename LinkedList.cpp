#ifndef LinkedList_c
#define LinkedList_c

#include "LinkedList.hpp"

template <typename T>
LinkedList<T>::LinkedList() {

	pHead = nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList() {

	ListNode<T>* traverser = pHead;

	while (traverser != nullptr) {

		ListNode<T>* nextPtr = traverser->getNextPtr();
		delete traverser;
		traverser = nextPtr;
	}
}

template <typename T>
void LinkedList<T>::insert(T newCommand, T newDescription) {

	ListNode<T>* newNode = new ListNode<T>(newCommand, newDescription);

	if (pHead == nullptr) {//if empty list
		pHead = newNode;
	}

	else {

		/*
		ListNode<T>* traverser = pHead;

		while (traverser->getNextPtr() != nullptr) {

			traverser = traverser->getNextPtr();
		}

		traverser->setNextPtr(newNode);
		*/

		ListNode<T>* head = pHead;
		newNode->setNextPtr(pHead);
		pHead = newNode;
	}
}

template <typename T>
void LinkedList<T>::printList() {

	ListNode<T>* traverser = pHead;

	while (traverser != nullptr) {

		std::cout << traverser->getCommand() << "," << traverser->getDescription() << std::endl;
		traverser = traverser->getNextPtr();
	}
}

template <typename T>
void LinkedList<T>::loadCsv(std::string filename) {

	std::fstream commandFile;
	commandFile.open(filename, std::ios::in);

	std::string curLine, curCommand, curDescription;

	if (commandFile.is_open()) {
		
		int temp = 0;
		while (std::getline(commandFile, curLine) && temp < 31) {                                 //while not at end of file grab a line!

			curCommand = curLine.substr(0, curLine.find(","));                       //grab everything b4 comma (command)
			curDescription = curLine.substr(curCommand.length() + 1, curLine.npos);  //grab all after comma (description)
			temp++;

			this->insert(curCommand, curDescription);                              //TODO do I need to pass their pointers?
		}

		commandFile.close();
	}
}

template <typename T>
void LinkedList<T>::writeList() {

	ListNode<T>* pTrav = pHead;

	std::ofstream writefile("commands.csv");

	if (writefile.is_open()) {

		while (pTrav != nullptr) {

			T* command = pTrav->getCommand();
			T* description = pTrav->getDescription();

			writefile << command << "," << description << std::endl;

			pTrav = pTrav->getNextPtr();
		}
	}
	writefile.close();
}

template <typename T>
void LinkedList<T>::deleteNode(T deleteCommand) 
{

	if (pHead->getCommand() == deleteCommand) 
	{

		pHead = pHead->getNextPtr();
	}

	else 
	{
		
		ListNode<T>* traverser = pHead;
		//ListNode<T>* next = traverser->getNextPtr();     //for some reason that's unallocated????
		/*
		while (traverser->getNextPtr() != nullptr && traverser->getNextPtr()->getCommand() != deleteCommand) {

			if (traverser->getNextPtr() != nullptr) {

				traverser->setNextPtr(traverser->getNextPtr()->getNextPtr());
				//delete next;
			}

			traverser = traverser->getNextPtr();
		}
		*/

		while (traverser != nullptr) {

			if (traverser->getNextPtr() != nullptr && traverser->getNextPtr()->getCommand() == deleteCommand) {

				traverser->setNextPtr(traverser->getNextPtr()->getNextPtr());
				//delete next;
			}

			traverser = traverser->getNextPtr();
		}
	}
}

template <typename T>
ListNode<T>* LinkedList<T>::getRandNode() {

	ListNode<T>* returnPointer = pHead;

	int range = 30 - 0 + 1;
	int num = rand() % range + 0;

	for (int i = 0; i < num-1; i++) {

		returnPointer = returnPointer->getNextPtr();

	}

	return returnPointer;
};

template <typename T>
ListNode<T>* LinkedList<T>::getHead() {

	return pHead;
}

#endif