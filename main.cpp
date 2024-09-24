#include "main.hpp"
/*
ADVANTAGES/DISADVANTAGES LINKED LIST:
- Advantage: A linked list allows for dynamic memory allocation, so commands and descriptions can be added or removed easily without needing to resize the data structure. This is beneficial for this assignment since commands may vary in number or need to be modified frequently during the course of the program.
- Disadvantage: Linked lists have slower access times compared to arrays because they require traversal from the head to the desired element. This can be inefficient if there are many commands to store and we frequently need to access specific ones.

ADVANTAGES/DISADVANTAGES ARRAY:
- Advantage: Arrays provide constant-time access to elements via indexing, which is helpful when storing user profiles that may need to be accessed frequently in this assignment.
- Disadvantage: Arrays have a fixed size, which means that once they are full, you cannot add more user profiles unless you resize the array, which is inefficient and can be costly in terms of memory usage.
*/


int main() {

	Menue* menue = new Menue;

	menue->runMenue();

	return 0;
}