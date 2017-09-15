#include<iostream>
#include<vector>
using namespace std;

class Node {
public:
	Node() {}
	Node(int a) : value(a), left(NULL), right(NULL) { cout << "Utworzylem nod " << a << endl; }
	int value;
	Node* left;
	Node* right;
	int getValue() {
		return value;
	}
	Node* getLeft() {
		return left;
	}
	Node* getRight() {
		return right;
	}
	~Node() { cout << "Zniszczyłem nod " << value << endl;  }
};


class Tree {
public:
	Node* root;
	vector<Node*> do_zniszczenia;
	Tree(int a) : root(new Node(a)) { do_zniszczenia.push_back(root);}
	void addNodeRight(Node *newNode, Node *place) {
			Node* n = place->getRight();
			place->right = newNode;
			newNode->right = n;
	}
	void addNodeLeft(Node *newNode, Node *place) {
			Node* n = place->getLeft();
			place->left = newNode;
			newNode->left = n;
	}
	void addNode(int a) {
		Node* newNode = new Node(a);
		do_zniszczenia.push_back(newNode);
		Node* n = findFreeNode(newNode->getValue(), root);
		if(newNode->getValue() < n->getValue()) {
			n->left = newNode;
		} else {
			n->right = newNode;
		}
	}
	Node* findFreeNode(int a, Node* node) {
		if(node->getRight() == NULL && a > node->getValue()) { cout << "== Right of " << node->getValue() << " puts " << a << endl; return node;} 
		if(node->getLeft() == NULL && a < node->getValue()) { cout << "== Left of " << node->getValue() << " puts " << a << endl; return node;}


		if(a < node->getValue()) return findFreeNode(a, node->getLeft());
		if(a > node->getValue()) return findFreeNode(a, node->getRight());
	}
	int getValue() {
		return root->getValue();
	}
	Node* goLeft() {
		return root->left;
	}

	bool search(int a, Node* node) {
		if(node == NULL) return 0;
		if(node->getValue() == a) return 1;
		if(a < node->getValue()) return search(a, node->getLeft());
		if(a > node->getValue()) return search(a, node->getRight());
	}

	~Tree() {
		for(vector<Node*>::reverse_iterator itr = do_zniszczenia.rbegin(); itr != do_zniszczenia.rend(); ++itr) {
			delete *itr;
		}
	}

};

int main()
{
	Tree t(8);

	t.addNode(20);
	t.addNode(10);
	t.addNode(5);
	t.addNode(7);
	t.addNode(3);
	t.addNode(4);
	t.addNode(1);
	t.addNode(2);

	cout << "Tree has " << 2 << " - " << t.search(2, t.root) << endl;

return 0;
}
