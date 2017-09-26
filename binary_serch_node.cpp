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
	void addNode(int a) {
			Node* newNode = new Node(a);
			do_zniszczenia.push_back(newNode);
		if(root != NULL) {
			Node* n = findFreeNode(newNode->getValue(), root);
			if(n->getValue() == a) {
				cout << "Numebr " << a << " is currently in the tree!" << endl;
			} else {
				if(newNode->getValue() < n->getValue()) {
					n->left = newNode;
				} else {
					n->right = newNode;
				}
			}
		} else {
			root = newNode;
		}
		howMany++;
	}
	Node* findFreeNode(int a, Node* node) {
		if(node->getValue() == a) { return node;}
		if(node->getRight() == NULL && a > node->getValue()) { return node;}
		if(node->getLeft() == NULL && a < node->getValue()) { return node;}


		if(a < node->getValue()) return findFreeNode(a, node->getLeft());
		if(a > node->getValue()) return findFreeNode(a, node->getRight());
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
		if(node->getValue() == root->getValue()) {
			if(root->getLeft() != NULL) {
				Node* r = root;
				Node* rL = root->getLeft()->getRight();
				Node* nodeLeftNULL = findLeftNodePointingForNULL(r->getRight());
				root = r->getLeft();
				root->right = r->getRight();
				nodeLeftNULL->left = rL;
			} else if(root->getRight() != NULL) {
				Node* rR = root->getRight();
				Node* rL = root->getLeft();
				Node* nodeLeftNULL = findLeftNodePointingForNULL(rR->getLeft());

				if(nodeLeftNULL == NULL) {
					root = rR;
					root->left = rL;
				} else {
					root = rR;
					root->right = rR->getRight();
					nodeLeftNULL->left = rL;
				}
			} else {
				cout << "I cann't remove root numebr " << a << "!" << endl;
			}
			return;
		}
		if(node == NULL) {
			cout << "I cann't remove numebr " << a << ", beacause tree hasn't this number!" << endl;
		} else {
			Node* nodeBefore = findNodePointingForInt(a, root);
			Node* nodeLeftNULL = findLeftNodePointingForNULL(node->getRight());
			cout << "After nodeLeftNULL" << endl;
			if(a < nodeBefore->getValue()) {
				if(nodeLeftNULL == NULL) {
					nodeBefore->left = node->getLeft();
				} else {
				cout << "Node Before " << a << "  is "<< nodeBefore->getValue() << endl;
				nodeBefore->left = node->getRight();
				cout << "Node left NULL " << a << "  is "<< nodeLeftNULL->getValue() << endl;
				nodeLeftNULL->left = node->getLeft();
				}
			} else {
				if(nodeLeftNULL == NULL) {
					nodeBefore->right = node->getLeft();
				} else {
					cout << "Node Before " << a << "  is "<< nodeBefore->getValue() << endl;
					nodeBefore->right = node->getRight();
					cout << "Node left NULL " << a << "  is "<< nodeLeftNULL->getValue() << endl;
					nodeLeftNULL->left = node->getLeft();
				}

			}
		}
	}

/*********************************/
	Node* findLeftNodePointingForNULL(Node *node) {
//		int a = node->getValue();
		if(node == NULL) {  cout << "NULL" << endl; return NULL;}
		if(node->getLeft() == NULL) { cout << "==" << endl; return node; }
		while(node->getLeft() != NULL) {
			node = node->getLeft();
		}
		return node;
	}
/***************************/




	Node* findNodePointingForInt(int a, Node *node) {
	        cout << "I'm in findNodePointingForINT" << endl;
                if(node == NULL) {  cout << "NULL" << endl; return NULL;}
                if(node->getLeft() == NULL && node->getRight() != NULL) {
			if(node->getRight()->getValue() == a) return node;
			cout << "!!!!!!!!!" << endl;
			return findNodePointingForInt(a, node->getRight());
		}
                if(node->getRight() == NULL && node->getLeft() != NULL) {
			if(node->getLeft()->getValue() == a) return node;
			return findNodePointingForInt(a, node->getLeft());
		}
		if(node->getLeft()->getValue() == a || node->getRight()->getValue() == a) { cout << "==" << endl; return node; }


                if(a < node->getValue()) {
cout << "LLL" << endl; return findNodePointingForInt(a, node->getLeft());
		}
                if(a > node->getValue()) {
cout << "RRR" << endl; return findNodePointingForInt(a, node->getRight());
		}

        }




	void printTreeFromNode(Node *node) {
		int t=170;
		int v[100][t];
		char c[100][t];
		int k=t/2;
		int h=18;
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
		v[1][k] = node->getValue();

		for(int i=0; i<h; i++) {
			k = k*0.7;
			for(int j=0; j<t; j++) {
				if(v[i][j] != 0) {
					n = search(v[i][j], root)->getLeft();
					if(n != NULL) {
						if(k <= 0) c[i+1][j-1] = 'L';
						for(int a=0; a<k; a++) c[i+1][j-a] = '-';
						v[i+2][j-k] = n->getValue();
					}
					n = search(v[i][j], root)->getRight();
					if(n != NULL) {
						if(k <= 0) c[i+1][j+1] = 'R';
						for(int a=0; a<k; a++) c[i+1][j+a] = '>';
						if(v[i+2][j+k] == 0) {
							v[i+2][j+k] = n->getValue();
						} else {
							v[i+2][j+k+2] = n->getValue();
						}
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

	t.addNode(9);
	t.addNode(36);
	t.addNode(57);
	t.addNode(13);
	t.addNode(4);
	t.addNode(1);
	t.addNode(12);
	t.addNode(15);
	t.addNode(18);

	t.addNode(11);
	t.addNode(20);
	t.addNode(54);
	t.addNode(53);
	t.addNode(51);
	t.addNode(555);
	t.addNode(550);
	t.addNode(55);
	t.addNode(56);
	t.addNode(50);
	t.addNode(14);
	t.addNode(3);
	t.addNode(6);
	t.addNode(5);
	t.addNode(8);
	t.addNode(7);
	t.addNode(13);
	t.addNode(25);
	t.addNode(22);
	t.addNode(26);
	t.addNode(24);
	t.addNode(19);



	cout << "Tree has ";
	if(t.search(13, t.root) == NULL) cout << "not ";
	cout  << "number " << 13 << endl;
	t.printTreeFromNode(t.search(29, t.root));
	int a=8;

	while(a != 0) {
//		cout << "Head of tree is number: " << t.root->getValue() << endl;
//		cout << "Give number node, which you want print (press 0 to quit): ";
		cout << "Give number node, which you want delete: ";
		cin >> a;

		if(t.search(a, t.root) != NULL ) {
//			t.printTreeFromNode(t.search(a, t.root));
			t.remove(a);
			t.printTreeFromNode(t.root);
		} else {
			cout << "In the tree no number: " << a << endl;
		}
	}

	Node* ab = t.findLeftNodePointingForNULL(t.search(12, t.root));
	cout << ab->getValue() << endl;

return 0;
}
