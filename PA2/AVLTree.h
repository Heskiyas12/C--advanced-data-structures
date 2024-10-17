#include <iostream>
#include <limits>
#include <vector>
using namespace std;
template <typename Comparable>
class AVLTree
{
public:
	AVLTree();
	~AVLTree();
	void makeEmpty();
	const Comparable& findMin() const;
	const Comparable& findMax() const;
	bool contains(const Comparable& x) const;
	void insert(const Comparable& x);
	void remove(const Comparable& x);
	int treeSize() const;
	int computeHeight() const;
	int readRootHeight() const;
	bool isBalanced() const;
	bool isBST() const;
	double averageDepth() const;
	void removeByRank(int rank);
	// the next line follows textbook Figure 4.42, Line 19
	static const int ALLOWED_IMBALANCE = 1;
private:
	struct AVLNode // refer to textbook, Figure 4.40
	{
		Comparable element;
		AVLNode* left;
		AVLNode* right;
		int height;
		AVLNode(const Comparable& theElement, AVLNode* lt, AVLNode* rt) :
			element(theElement), left(lt), right(rt) {}
		AVLNode(Comparable&& theElement, AVLNode* lt, AVLNode* rt) :
			element(move(theElement)), left(lt), right(rt) {}
	};
	AVLNode* root;
	AVLNode* findMin(AVLNode* t) const;
	AVLNode* findMax(AVLNode* t) const;
	int height(AVLNode* t) const;
	

	
	bool contains(const Comparable& x, AVLNode* t) const {
		if (t == nullptr) {
			return false;
		}
		if (x < t->element){
			return contains(x, t->left); 
		}
		if (x > t->element) {
			return contains(x, t->right);
		}
		
		return true;             
	}
	
	void insert(const Comparable& x, AVLNode*& t) {
		// If the tree is empty, create a new node
		if (!t) {
			t = new AVLNode(x, nullptr, nullptr);
			balance(t);
			return;
		}

		// Recursive insertion in left or right subtree based on the value of x
		AVLNode*& child = (x < t->element) ? t->left : t->right;

		if (x != t->element) {  
			insert(x, child);
		}

		
		balance(t);
	}


	void remove(const Comparable& x, AVLNode*& t) {
		if (!t) return;  

		
		if (x < t->element) {
			remove(x, t->left);
		}
		else if (x > t->element) {
			remove(x, t->right);
		}
		else {  
			// Case 1: Node has no children or one child
			if (!t->left || !t->right) {
				AVLNode* oldNode = t;
				t = (t->left) ? t->left : t->right;  // Set t to its non-null child (if any) or null
				delete oldNode;
			}
			// Case 2: Node has two children
			else {
				AVLNode* successor = findMin(t->right);  // Find in-order successor in the right subtree
				t->element = successor->element;         // Replace current node's value with successor's value
				remove(t->element, t->right);            // Remove the successor node
			}
		}

		// Balance the tree after deletion
		if (t) {
			balance(t);
		}
	}

	bool isBalanced(AVLNode* t) const {
		// Base case: an empty tree is balanced
		if (!t) return true;

		
		int balanceFactor = height(t->left) - height(t->right);

		// Check if the current node is balanced and recursively check its subtrees
		bool leftBalanced = isBalanced(t->left);
		bool rightBalanced = isBalanced(t->right);

		// Return the combined result
		return abs(balanceFactor) <= ALLOWED_IMBALANCE && leftBalanced && rightBalanced;
	}

	bool isBST(AVLNode* t, const Comparable* min, const Comparable* max) const {
		// Base case: an empty subtree is a valid BST
		if (!t) return true;

		// Check if the current node's value violates the BST property
		bool violatesMin = (min && t->element <= *min);
		bool violatesMax = (max && t->element >= *max);

		if (violatesMin || violatesMax) {
			return false;
		}

		// Recursively validate left and right subtrees
		bool leftIsValid = isBST(t->left, min, &t->element);
		bool rightIsValid = isBST(t->right, &t->element, max);

		// Return true only if both subtrees are valid
		return leftIsValid && rightIsValid;
	}

	int treeSize(AVLNode* t) const {
		if (t == nullptr) {
			return 0;
		}
		else {
			return 1 + treeSize(t->left) + treeSize(t->right);
		}
	}
	int computeHeight(AVLNode* t) const {
		if (t == nullptr) {
			return -1;  // Height of an empty subtree is -1
		}
		// Height is 1 + max of left and right subtree heights
		return 1 + std::max(computeHeight(t->left), computeHeight(t->right));
	}
	AVLNode* removeByRank(AVLNode* t, int rank, int& currentRank) {
		if (!t) return nullptr;  // Base case: no node found

		// Traverse the left subtree
		t->left = removeByRank(t->left, rank, currentRank);

		// Check if the current node matches the target rank
		if (currentRank == rank) {
			if (!t->left || !t->right) {
				AVLNode* child = t->left ? t->left : t->right;
				delete t;
				return child;  // Return the child node or null
			}
			else {
				AVLNode* successor = findMin(t->right);
				t->element = successor->element;
				t->right = removeByRank(t->right, rank, currentRank);
			}
		}
		else {
			++currentRank;
			t->right = removeByRank(t->right, rank, currentRank);
		}

		balance(t);  
		return t;
	}

	void computeTotalDepth(AVLNode* t, int depth, int& totalDepth, int& totalNodes) const {
		if (t == nullptr) {
			return;  // Base case: empty node
		}
		totalDepth += depth;  
		totalNodes++;  

		// Recur for left and right children, increasing the depth by 1
		computeTotalDepth(t->left, depth + 1, totalDepth, totalNodes);
		computeTotalDepth(t->right, depth + 1, totalDepth, totalNodes);
	}
	void makeEmpty(AVLNode*& t);
	void balance(AVLNode*& t);
	void rotateWithLeftChild(AVLNode*& t);
	void rotateWithRightChild(AVLNode*& t);
	void doubleWithLeftChild(AVLNode*& t);
	void doubleWithRightChild(AVLNode*& t);
};

// constructor
template <class Comparable>
AVLTree<Comparable>::AVLTree() : root(NULL) {}
// destructor
template <class Comparable>
AVLTree<Comparable>::~AVLTree()
{
	makeEmpty();
}
// public makeEmpty: follow the makeEmpty in BST, referring to textbook, Figure 4.27
template <typename Comparable>
void AVLTree<Comparable>::makeEmpty() {
	makeEmpty(root);
}
// private recursive makeEmpty: follow the makeEmpty in BST, referring to textbook, Figure 4.27
template <typename Comparable>
void AVLTree<Comparable>::makeEmpty(AVLNode * &t) {
	if (t != NULL) {
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
		t = NULL;
	}
}
// public findMin: follow the findMin in BST, referring to textbook, Figure 4.20
template <typename Comparable>
const Comparable& AVLTree<Comparable>::findMin() const {
	if (root == NULL) {
		throw underflow_error("Tree is empty");
	}
	return findMin(root)->element;
}
// private findMin: follow the findMin in BST, referring to textbook, Figure 4.20
template <typename Comparable>
typename AVLTree<Comparable>::AVLNode* AVLTree<Comparable>::findMin(AVLNode* t)
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
// public findMax: follow the findMax in BST, referring to textbook, Figure 4.21
template <typename Comparable>
const Comparable& AVLTree<Comparable>::findMax() const {
	if (root == NULL) {
		throw underflow_error("Tree is empty");
	}
	return findMax(root)->element;
}
// private findMax: follow the findMax in BST, referring to textbook, Figure 4.21
template <typename Comparable>
typename AVLTree<Comparable>::AVLNode* AVLTree<Comparable>::findMax(AVLNode* t)
const {
	if (t == NULL) {
		return NULL;
	}
	else if (t->right == NULL) {
		return t;
	}
	else {
		return findMax(t->right);
	}
}
// start our implementation:
// public contains: follow the contains in BST, referring to textbook, Figure 4.17 and Figure 4.18
template<typename Comparable>
bool AVLTree<Comparable>::contains(const Comparable & x) const {
	return contains(x, root);
}
// public insert: following BST, referring to textbook, Figure 4.17 and Figure 4.23
template<typename Comparable>
void AVLTree<Comparable>::insert(const Comparable& x) {
	insert(x, root);
}
// public remove: refer to textbook, Figure 4.17 and Figure 4.26
template<typename Comparable>
void AVLTree<Comparable>::remove(const Comparable& x) {
	remove(x, root);
}
// private balance: refer to textbook, Figure 4.42, Line 21 - 40
// assume t is the node that violates the AVL condition, and we then identify which case to use(out of 4 cases)
template<typename Comparable>
void AVLTree<Comparable>::balance(AVLNode * &t) {
	if (t == nullptr)
		return;

	// Left-heavy case
	if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) {
		if (height(t->left->left) >= height(t->left->right)) {
			rotateWithLeftChild(t);  // Single rotation case
		}
		else {
			doubleWithLeftChild(t);  // Double rotation case
		}
	}
	// Right-heavy case
	else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) {
		if (height(t->right->right) >= height(t->right->left)) {
			rotateWithRightChild(t);  // Single rotation case
		}
		else {
			doubleWithRightChild(t);  // Double rotation case
		}
	}

	// Update height after balancing
	t->height = std::max(height(t->left), height(t->right)) + 1;
}
// private rotateWithLeftChild: for case 1, referring to textbook, Figure 4.44 (code) and Figure 4.43 (visualization)
template<typename Comparable>
void AVLTree<Comparable>::rotateWithLeftChild(AVLNode * &k2) {
	AVLNode* k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = std::max(height(k2->left), height(k2->right)) + 1;
	k1->height = std::max(height(k1->left), height(k1->right)) + 1;
	k2 = k1;
}
// private rotateWithRightChild: for case 4 (the mirrored case of case 1)
template<typename Comparable>
void AVLTree<Comparable>::rotateWithRightChild(AVLNode * &k2) {
	AVLNode* k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	k2->height = std::max(height(k2->left), height(k2->right)) + 1;
	k1->height = std::max(height(k1->left), height(k1->right)) + 1;
	k2 = k1;
}
// private doubleWithLeftChild: for case 2, see textbook, Figure 4.46 (code) and Figure 4.45 (visualization)
template<typename Comparable>
void AVLTree<Comparable>::doubleWithLeftChild(AVLNode * &k3) {
	rotateWithRightChild(k3->left);
	rotateWithLeftChild(k3);
}
// private doubleWithRightChild: for case 3 (the mirrored case of case 2)
template<typename Comparable>
void AVLTree<Comparable>::doubleWithRightChild(AVLNode * &k3) {
	rotateWithLeftChild(k3->right);
	rotateWithRightChild(k3);
}
// public isBalanced
template <class Comparable>
bool AVLTree<Comparable>::isBalanced() const {
	return isBalanced(root);
}
// public isBST
template <class Comparable>
bool AVLTree<Comparable>::isBST() const {
	return isBST(root, nullptr, nullptr);
}
// public treeSize
template <typename Comparable>
int AVLTree<Comparable>::treeSize() const {
	return treeSize(root);
}
// public computeHeight. See Figure 4.61 in Textbook
template <typename Comparable>
int AVLTree<Comparable>::computeHeight() const {
	return computeHeight(root);
}
// public readRootHeight
template <typename Comparable>
int AVLTree<Comparable>::readRootHeight() const {
	return root == nullptr ? -1 : root->height;

}
// public averageDepth
template <typename Comparable>
double AVLTree<Comparable>::averageDepth() const {
	if (root == nullptr) {
		return 0.0;  // If the tree is empty, return 0
	}
	int totalDepth = 0;
	int totalNodes = 0;
	computeTotalDepth(root, 0, totalDepth, totalNodes);  // Start at depth 0
	return static_cast<double>(totalDepth) / totalNodes;
}
// public removeByRank
template <typename Comparable>
void AVLTree<Comparable>::removeByRank(int rank) {
	int currentRank = 0;
	root = removeByRank(root, rank, currentRank);
}
template <typename Comparable>
int AVLTree<Comparable>::height(AVLNode* t) const {
	return t == nullptr ? -1 : t->height;
}

