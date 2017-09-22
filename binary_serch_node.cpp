#include<iostream>
#include<vector>
using namespace std;

class Node {
public:
	Node() {}
	Node(int a) : value(a), left(NULL), right(NULL) {  }
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
	~Node() { }
};


class Tree {
public:
	Node* root=NULL;
	int howMany;
	vector<Node*> do_zniszczenia;
	Tree(int a) : root(new Node(a)) { do_zniszczenia.push_back(root); howMany = 1;}
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
		if(root != NULL) {
			Node* n = findFreeNode(newNode->getValue(), root);
			if(newNode->getValue() < n->getValue()) {
				n->left = newNode;
			} else {
				n->right = newNode;
			}
		} else {
			root = newNode;
		}
		howMany++;
	}
	Node* findFreeNode(int a, Node* node) {
		if(node->getRight() == NULL && a > node->getValue()) { return node;}
		if(node->getLeft() == NULL && a < node->getValue()) { return node;}


		if(a < node->getValue()) return findFreeNode(a, node->getLeft());
		if(a > node->getValue()) return findFreeNode(a, node->getRight());
	}
	int getValue() {
		return root->getValue();
	}
	Node* goLeft() {
		return root->left;
	}

	Node* search(int a, Node* node) {
		if(node == NULL) return NULL;
		if(node->getValue() == a) return node;
		if(a < node->getValue()) return search(a, node->getLeft());
		if(a > node->getValue()) return search(a, node->getRight());
	}
	void reset() {
		for(vector<Node*>::reverse_iterator itr = do_zniszczenia.rbegin(); itr != do_zniszczenia.rend(); ++itr) {
			delete *itr;
		}
		do_zniszczenia.erase(do_zniszczenia.begin(),do_zniszczenia.end());
		root = NULL;
	}

	void remove(int a) {
		Node* node = search(a, root);
		if(node == NULL) {
			cout << "I cann't remove numebr " << a << ", beacause tree hasn't this number!" << endl;
		} else {
			if(a < root->getValue()) {
				Node* nodeBefore = findLeftNodePointingForInt(a,root);
				cout << "Node Before " << a << "  is "<< nodeBefore->getValue() << endl;
				nodeBefore->left = node->getRight();
			} else {
				cout << "a is biggerthan root" << endl;
			}
		}
	}
	Node* findLeftNodePointingForInt(int a, Node *node) {
	cout << node->getLeft()->getValue() << " ~!!!!" << endl;
		if(node == NULL) {  cout << "NULL" << endl; return NULL;}
		if(node->getLeft()->getValue() == a) { cout << "==" << endl; return node; }
		if(a < node->getValue()) {
//cout << "LLL" << endl; return findLeftNodePointingForInt(a, node->getLeft());
}
		if(a > node->getValue()) {
//cout << "RRR" << endl; return findLeftNodePointingForInt(a, node->getRight());
}
	}


	void printTree() {
		int t=300;
		int v[100][t];
		char c[100][t];
		int k=t/2;
		int h=15;
		Node* n;
		for(int j=0; j<t; j++) {
			for(int i=0; i<h; i++) {
				if(v[i][j] != 0) {
					v[i][j] = 0;
				}
			}
		}
		for(int j=0; j<t; j++) {
			for(int i=0; i<h; i++) {
				if(c[i][j] != 0) {
					c[i][j] = 0;
				}
			}
		}
		v[1][k] = root->getValue();

		for(int i=0; i<h; i++) {
			k = k*0.7;
			for(int j=0; j<t; j++) {
				if(v[i][j] != 0) {
					n = search(v[i][j], root)->getLeft();
					if(n != NULL) {
						for(int a=0; a<k; a++) c[i+1][j-a] = '-';
						v[i+2][j-k] = n->getValue();
					}
					n = search(v[i][j], root)->getRight();
					if(n != NULL) {
						for(int a=0; a<k; a++) c[i+1][j+a] = '>';
						v[i+2][j+k] = n->getValue();
					}
				}
			}
		}
		for(int i=0; i<h; i++) {
			for(int j=0; j<t; j++) {
				if (i%2) {
					if(v[i][j] != 0) {
						cout << v[i][j];
					} else {
						cout << " ";
					}
				} else {
					if(c[i][j] != 0) {
						cout << c[i][j];
					} else {
						cout << " ";
					}
				}
			}
		cout << endl;
		}

	}
	void printLeft(Node* node, int h) {
		if(node == NULL) return;
		printChar(h/2, ' ');
		cout << "|";
		printChar(h/2, '-');
		cout << "^";
		cout << endl;
		printChar(h/2, ' ');
		cout << node->getValue();
		cout << endl;
		printLeft(node->getLeft(), h/2);
	}
	void printRight(Node* node, int h) {
		if(node == NULL) return;
		printChar(h/2, '-');
		cout << "|";
		cout << endl;
		printChar(h/2, ' ');
		cout << node->getValue();
		cout << endl;
		printLeft(node->getLeft(), h/2);
	}
	void printChar(int a, char c) {
		while(a--) cout << c;
	}
	void printSpace(int a) {
		while(a--) cout << " ";
	}
	~Tree() {
		if(!do_zniszczenia.empty()) {
			for(vector<Node*>::reverse_iterator itr = do_zniszczenia.rbegin(); itr != do_zniszczenia.rend(); ++itr) {
				delete *itr;
			}
		}
	}

};

int main()
{
	Tree t(29);

	t.addNode(7);
	t.addNode(6);
	t.addNode(55);
	t.addNode(10);
	t.addNode(4);
	t.addNode(1);
	t.addNode(12);
	t.addNode(15);
	t.addNode(18);
	t.addNode(13);
	t.addNode(11);
	t.addNode(9);
	t.addNode(54);
	t.addNode(53);
	t.addNode(51);
/*	t.addNode(20);
	t.addNode(23);
	t.addNode(10);
	t.addNode(15);
	t.addNode(30);

	t.remove(18);
*/
	cout << "Tree has ";
	if(t.search(5, t.root) == NULL) cout << "not ";
	cout  << "number " << 5 << endl;

	t.printTree();
return 0;
}
