//Miray Dicle

//header guards
#ifndef WORDITEM_H
#define WORDITEM_H

#include <string>
using namespace std;

struct DocumentItem {
	string documentName;
	int count;
	DocumentItem* next;

	DocumentItem(const string& name, const int& c, DocumentItem* n = NULL)
		: documentName(name), count(c), next(n) { }
};

struct WordItem {
	string word;
    DocumentItem * list;
	// List of DocumentItem�s. In order to keep the documents
	//you can again use the BST that you are going to implement.

	WordItem(const string& w, DocumentItem* l = NULL)
		: word(w), list(l) { }
};

//template <class Key, class Value>
//class AVLSearchTree;

template <class Key, class Value>
struct AvlNode
{
	Key key;
	Value value;
	AvlNode* left;
	AvlNode* right;
	int height;

	AvlNode(const Key& theKey, const Value& theValue, AvlNode* lt, AvlNode* rt, int h = 0)
		: key(theKey), value(theValue), left(lt), right(rt), height(h) { }

	/*friend class AVLSearchTree<Key, Value>;*/
};

template <class Key, class Value>
class AVLSearchTree
{
public:
	explicit AVLSearchTree();
	AVLSearchTree(const AVLSearchTree& rhs);
	~AVLSearchTree();

	const Key& findMin() const;
	const Key& findMax() const;
	const Key& find(const Key& x) const;
	bool isEmpty() const;
	/*void printTree() const;*/

	void makeEmpty();
	void insert(const Key& x, const Value& y);
	void remove(const Key& x);

	DocumentItem* findHead(const Key& x) const; //finds head

	/*const AVLSearchTree& operator=(const AVLSearchTree& rhs);*/
private:
	AvlNode<Key, Value>* root;
	const Key ITEM_NOT_FOUND;

	const Key& elementAt(AvlNode<Key, Value>* t) const;

	void insert(const Key& x, const Value& y, AvlNode<Key, Value>*& t) const;
	void remove(const Key& x, AvlNode<Key, Value>*& t) const;

	AvlNode<Key, Value>* findMin(AvlNode<Key, Value>* t) const;
	AvlNode<Key, Value>* findMax(AvlNode<Key, Value>* t) const;
	AvlNode<Key, Value>* find(const Key& x, AvlNode<Key, Value>* t) const;
	void makeEmpty(AvlNode<Key, Value>*& t) const;
	/*void printTree(AvlNode<Key, Value>* t) const;*/
	/*AvlNode<Key, Value>* clone(AvlNode<Key, Value>* t) const;*/

	// Avl manipulations
	int height(AvlNode<Key, Value>* t) const;
	int max(int lhs, int rhs) const;
	void rotateWithLeftChild(AvlNode<Key, Value>*& k2) const;
	void rotateWithRightChild(AvlNode<Key, Value>*& k1) const;
	void doubleWithLeftChild(AvlNode<Key, Value>*& k3) const;
	void doubleWithRightChild(AvlNode<Key, Value>*& k1) const;
};

#include "functions.cpp"
#endif