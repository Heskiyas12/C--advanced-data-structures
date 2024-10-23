#ifndef __BST_H
#define __BST_H
#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <stack>  
#include <algorithm>  


using namespace std;
template <typename Comparable>
class BST
{
public:
	BST();
	~BST();
	void makeEmpty();
	const Comparable& findMin() const;
	const Comparable& findMax() const;
	bool contains(const Comparable& x) const;
	void insert(const Comparable& x);
	void remove(const Comparable& x);
	int treeSize() const;
	int treeHeight() const;
	void printInOrder() const;
	void printLevels() const;
	void printMaxPath() const;
private:
	struct BinaryNode
	{
		Comparable element;
		BinaryNode* left;
		BinaryNode* right;
		BinaryNode(const Comparable& theElement, BinaryNode* lt, BinaryNode
			* rt) : element(theElement), left(lt), right(rt) {}
		BinaryNode(Comparable&& theElement, BinaryNode* lt, BinaryNode* rt) :
			element(move(theElement)), left(lt), right(rt) {}
	};
	BinaryNode* root;
	BinaryNode* findMin(BinaryNode* t) const;
	BinaryNode* findMax(BinaryNode* t) const;
	void makeEmpty(BinaryNode*& t);
};

template<typename Comparable>
BST<Comparable>::BST() : root(NULL) {}
// destructor, refer to textbook, Figure 4.27
template<typename Comparable>
BST<Comparable>::~BST() {
	makeEmpty();
}
// public makeEmpty: refer to textbook, Figure 4.27
template <typename Comparable>
void BST<Comparable>::makeEmpty() {
	makeEmpty(root);
}
// private recursive makeEmpty: refer to textbook, Figure 4.27
template <typename Comparable>
void BST<Comparable>::makeEmpty(BinaryNode*& t) {
	if (t != NULL) {
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
		t = NULL;
	}
}
// // public findMin
template <typename Comparable>
const Comparable& BST<Comparable>::findMin() const {
	if (root == NULL) {
		throw underflow_error("Tree is empty");
	}
	return findMin(root)->element;
}
// private findMin: refer to textbook, Figure 4.20
template <typename Comparable>
typename BST<Comparable>::BinaryNode* BST<Comparable>::findMin(BinaryNode* t)
const {
	if (t == NULL) {
		return NULL;
	}
	else if (t->left == NULL) {
		return t;
	}
	else {
		return findMin(t->left);
	}
}
// public findMax
template <typename Comparable>
const Comparable& BST<Comparable>::findMax() const {
	if (root == NULL) {
		throw underflow_error("Tree is empty");
	}
	return findMax(root)->element;
}
// private findMax: refer to textbook, Figure 4.21
template <typename Comparable>
typename BST<Comparable>::BinaryNode* BST<Comparable>::findMax(BinaryNode* t)
const {
	if (t == NULL) {
		return NULL;
	}
	else if (t->right == NULL) {
		return t;
	}
	else {
		return findMin(t->right);
	}
}
// public contains: refer to textbook, Figure 4.17, Line 4 - 7
template<typename Comparable>
bool BST<Comparable>::contains(const Comparable& x) const {
	BinaryNode* current = root;
	while (current) {
		if (x < current->element) {
			current = current->left;
		}
		else if (x > current->element) {
			current = current->right;
		}
		else {
			return true;
		}
	}
	return false;
}
// public insert: refer to textbook, Figure 4.17, Line 12 - 15
template<typename Comparable>
void BST<Comparable>::insert(const Comparable& x) {
	if (!root) {
		// If the tree is empty, create a new node as the root
		root = new BinaryNode(x, nullptr, nullptr);
	}
	else {
		
		BinaryNode* current = root;
		BinaryNode* parent = nullptr;

		while (current) {
			parent = current;
			if (x < current->element) {
				
				current = current->left;
			}
			else if (x > current->element) {
				// Move to the right child
				current = current->right;
			}
			else {
				
				return;
			}
		}

		
		if (x < parent->element) {
			parent->left = new BinaryNode(x, nullptr, nullptr);
		}
		else {
			parent->right = new BinaryNode(x, nullptr, nullptr);
		}
	}
}

template<typename Comparable>
void BST<Comparable>::remove(const Comparable& x) {
	if (root == nullptr) {
		return;  
	}

	BinaryNode* parent = nullptr;
	BinaryNode* current = root;

	while (current != nullptr && current->element != x) {
		parent = current;
		if (x < current->element) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}

	if (current == nullptr) {
		return; 
	}

	if (current->left == nullptr && current->right == nullptr) {
		if (current == root) {
			root = nullptr;
		}
		else if (parent->left == current) {
			parent->left = nullptr;
		}
		else {
			parent->right = nullptr;
		}
		delete current;
	}
	
	else if (current->left == nullptr) {
		if (current == root) {
			root = current->right;
		}
		else if (parent->left == current) {
			parent->left = current->right;
		}
		else {
			parent->right = current->right;
		}
		delete current;
	}
	
	else if (current->right == nullptr) {
		if (current == root) {
			root = current->left;
		}
		else if (parent->left == current) {
			parent->left = current->left;
		}
		else {
			parent->right = current->left;
		}
		delete current;
	}
	
	else {
		
		BinaryNode* successorParent = current;
		BinaryNode* successor = current->right;
		while (successor->left != nullptr) {
			successorParent = successor;
			successor = successor->left;
		}

		current->element = successor->element;

		if (successorParent->left == successor) {
			successorParent->left = successor->right;
		}
		else {
			successorParent->right = successor->right;
		}
		delete successor;
	}
}
// public treeSize
template <typename Comparable>
int BST<Comparable>::treeSize() const {
	
	if (!root) {
		return 0;
	}

	
	std::queue<BinaryNode*> nodesQueue;
	nodesQueue.push(root);

	int count = 0;

	while (!nodesQueue.empty()) {
		
		BinaryNode* currentNode = nodesQueue.front();
		nodesQueue.pop();
		count++;

		
		if (currentNode->left) {
			nodesQueue.push(currentNode->left);
		}

		if (currentNode->right) {
			nodesQueue.push(currentNode->right);
		}
	}

	return count;
	return 0;
}
// public treeHeight
template <typename Comparable>
int BST<Comparable>::treeHeight() const {
	if (!root) {
		return -1; 
	}

	int height = 0;

	
	BinaryNode* current = root;

	
	while (current) {
		height++;
		current = current->left ? current->left : current->right;
	}

	return height - 1;
}

template<typename Comparable>
void BST<Comparable>::printInOrder() const {
	BinaryNode* current = root;

	while (current) {
		if (!current->left) {
			std::cout << current->element << ' ';
			current = current->right; 
		}
		else {
			BinaryNode* predecessor = current->left;
			while (predecessor->right && predecessor->right != current) {
				predecessor = predecessor->right; 
			}
			if (!predecessor->right) {
				predecessor->right = current; 
				current = current->left; 
			}
			else {
				predecessor->right = nullptr; 
				std::cout << current->element << ' '; 
				current = current->right; 
			}
		}
	}
}
// public printLevels
template <typename Comparable>
void BST<Comparable>::printLevels() const {
	if (!root) {
		return; // 
	}

	std::queue<BinaryNode*> q; 
	q.push(root); 

	while (!q.empty()) {
		int levelSize = q.size(); 

		
		for (int i = 0; i < levelSize; ++i) {
			BinaryNode* node = q.front(); 
			q.pop(); 

			std::cout << node->element << " "; 

			
			if (node->left) {
				q.push(node->left);
			}
			if (node->right) {
				q.push(node->right);
			}
		}

		std::cout << std::endl; 
	}
}
// public printMaxPath
template <typename Comparable>
void BST<Comparable>::printMaxPath() const {
	BinaryNode* trav = root;

	while (trav) {
		cout << trav->element << " ";

		if (trav->left) {
			trav = trav->left;
		}
		else if (trav->right) {
			trav = trav->right;
		}
		else {
			
			break;
		}
	}
	cout << endl;
}
#endif


