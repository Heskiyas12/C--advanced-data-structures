#ifndef LinkedList_h
#define LinkedList_h
#include "ListNode.hpp"

template <typename T>
class LinkedList {

public:

	LinkedList();   

	~LinkedList();    

	void insert(T newCommand, T newDescription);  

	void printList();  

	void loadCsv(std::string filename);   

	void writeList(); 

	void deleteNode(T deleteCommand);  

	ListNode<T>* getRandNode();

	ListNode<T>* getHead();

private:
	ListNode<T>* pHead = nullptr;
};


#include "LinkedList.cpp"  //Including this because templated functions need their definitions in the same file: 
                           //https://www.youtube.com/watch?v=IiMr1jAQB78

//template class LinkedList<std::string>;   //you also have to define what types of inputs you're expecting  so the compiler 
                                            //knows what templated classes to spin up for you,.          (Apparently the previous is false???)

#endif