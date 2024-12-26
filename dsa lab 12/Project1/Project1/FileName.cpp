#include <iostream>
using namespace std;
class TNode {
public:
	int data;
	TNode* left;
	TNode* right;

	TNode() : data(0), left(nullptr), right(nullptr) {}
	TNode(int val) : data(val), left(nullptr), right(nullptr) {}
};
class BST {
public:
	TNode* root;
	BST() : root(nullptr) {}
	void insert(TNode*& node, int val) {
		if (node == nullptr) {
			node = new TNode(val);
			return;
		}

		if (val < node->data) {
			insert(node->left, val);
		}
		else {
			insert(node->right, val);
		}
	}
	bool search(TNode* node, int val) {
		if (node == nullptr) return false;
		if (node->data == val) return true;
		if (val < node->data) return search(node->left, val);
		else return search(node->right, val);
	}
	TNode* delete_node(TNode* node, int val) {
		if (node == nullptr) return node;
		if (val < node->data) {
			node->left = delete_node(node->left, val);
		}
		else if (val > node->data) {
			node->right = delete_node(node->right, val);
		}
		else {
			if (node->left == nullptr) {
				TNode* temp = node->right;
				delete node;
				return temp;
			}
			else if (node->right == nullptr) {
				TNode* temp = node->left;
				delete node;
				return temp;
			}

			TNode* temp = findmin(node->right);
			node->data = temp->data;
			node->right = delete_node(node->right, temp->data);
		}
		return node;
	}
	bool isEmpty() {
		return root == nullptr;
	}
	void in_orderTraverse(TNode* node) {
		if (node == nullptr) return;
		in_orderTraverse(node->left);
		cout << node->data << " ";
		in_orderTraverse(node->right);
	}
	TNode* findmin(TNode* node) {
		while (node && node->left != nullptr) {
			node = node->left;
		}
		return node;
	}
	TNode* getParent(TNode* node, int val) {
		return getParentHelper(root, nullptr, val);
	}
private:
	TNode* getParentHelper(TNode* node, TNode* parent, int val) {
		if (node == nullptr) return nullptr;

		if (node->data == val) return parent;

		if (val < node->data) {
			return getParentHelper(node->left, node, val);
		}
		else {
			return getParentHelper(node->right, node, val);
		}
	}
};
int main() {
	BST bst;

	bst.insert(bst.root, 10);
	bst.insert(bst.root, 5);
	bst.insert(bst.root, 15);
	bst.insert(bst.root, 3);
	bst.insert(bst.root, 7);
	bst.insert(bst.root, 13);
	bst.insert(bst.root, 18);

	cout << "In-order Traversal: ";
	bst.in_orderTraverse(bst.root);
	cout << endl;

	if (bst.search(bst.root, 7)) {
		cout << "Found 7 in the tree." << endl;
	}
	else {
		cout << "7 not found in the tree." << endl;
	}

	bst.delete_node(bst.root, 15);
	cout << "After deleting 15, In-order Traversal: ";
	bst.in_orderTraverse(bst.root);
	cout << endl;


	TNode* parent = bst.getParent(bst.root, 7);
	if (parent) {
		cout << "Parent of 7 is: " << parent->data << endl;
	}
	else {
		cout << "Parent of 7 not found." << endl;
	}

	cout << "Is the tree empty? " << (bst.isEmpty() ? "Yes" : "No") << endl;

	return 0;
}
