#include <iostream>
#include <vector>
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
};

bool printPath(TNode* root, int val, vector<int>& path) {
	if (root == nullptr) return false;

	path.push_back(root->data);

	if (root->data == val) return true;

	if ((root->left && printPath(root->left, val, path)) ||
		(root->right && printPath(root->right, val, path))) {
		return true;
	}

	path.pop_back();
	return false;
}
int findMax(TNode* root) {
	while (root != nullptr && root->right != nullptr) {
		root = root->right;
	}
	return root ? root->data : -1;
}

TNode* findSibling(TNode* root, int val) {
	if (root == nullptr) return nullptr;

	if (root->left && root->left->data == val) return root->right;
	if (root->right && root->right->data == val) return root->left;

	TNode* sibling = findSibling(root->left, val);
	if (sibling) return sibling;

	return findSibling(root->right, val);
}

int main() {
	BST bst;

	bst.insert(bst.root, 10);
	bst.insert(bst.root, 5);
	bst.insert(bst.root, 15);
	bst.insert(bst.root, 3);
	bst.insert(bst.root, 7);
	bst.insert(bst.root, 13);
	bst.insert(bst.root, 18);

	int target = 7;
	vector<int> path;
	if (printPath(bst.root, target, path)) {
		cout << "Path to node " << target << ": ";
		for (int node : path) {
			cout << node << " ";
		}
		cout << endl;
	}
	else {
		cout << "Node " << target << " not found in the tree." << endl;
	}

	int maxVal = findMax(bst.root);
	cout << "Maximum value in the BST: " << maxVal << endl;

	int siblingValue = 7;
	TNode* sibling = findSibling(bst.root, siblingValue);
	if (sibling) {
		cout << "Sibling of node " << siblingValue << ": " << sibling->data << endl;
	}
	else {
		cout << "Sibling of node " << siblingValue << " not found or does not exist." << endl;
	}

	return 0;
}
