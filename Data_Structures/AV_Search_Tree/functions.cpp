//Miray Dicle

#include <iostream>
#include "worditem.h"

using namespace std;

/**
  * Construct the tree.
  */
template <class Key, class Value>
AVLSearchTree<Key, Value>::AVLSearchTree()
    :ITEM_NOT_FOUND("notFound"), root(NULL)
{}

/**
  * Internal method to get element field in node t.
  * Return the element field or ITEM_NOT_FOUND if t is NULL.
  */
template <class Key, class Value>
const Key& AVLSearchTree<Key, Value>::elementAt(AvlNode<Key, Value>* t) const
{
    return t == NULL ? ITEM_NOT_FOUND : t->key;
}

/**
  * Find item x in the tree.
  * Return the matching item or ITEM_NOT_FOUND if not found.
  */
template <class Key, class Value>
const Key& AVLSearchTree<Key, Value>::find(const Key& x) const
{
    return elementAt(find(x, root));
}

//finds head of the value of the node
template <class Key, class Value>
DocumentItem* AVLSearchTree<Key, Value>::findHead(const Key& x) const
{
    return find(x, root)->value->list;
}

/**
 * Internal method to find an item in a subtree.
 * x is item to search for.
 * t is the node that roots the tree.
 * Return node containing the matched item.
 */
template <class Key, class Value>
AvlNode<Key, Value>*AVLSearchTree<Key, Value>::find(const Key& x, AvlNode<Key, Value>* t) const
{
    if (t == NULL)
        return NULL;
    else if (x < t->key)
        return find(x, t->left);
    else if (t->key < x)
        return find(x, t->right);
    else
        return t;    // Match
}

/**
  * Find the smallest item in the tree.
  * Return smallest item or ITEM_NOT_FOUND if empty.
  */
template <class Key, class Value>
const Key& AVLSearchTree<Key, Value>::findMin() const
{
    return elementAt(findMin(root));
}

/**
 * Internal method to find the smallest item in a subtree t.
 * Return node containing the smallest item.
 */
template <class Key, class Value>
AvlNode<Key, Value>*AVLSearchTree<Key, Value>::findMin(AvlNode<Key, Value>* t) const
{
    if (t == NULL)
        return NULL;
    if (t->left == NULL)
        return t;
    return findMin(t->left);
}

/**
  * Find the smallest item in the tree.
  * Return smallest item or ITEM_NOT_FOUND if empty.
  */
template <class Key, class Value>
const Key& AVLSearchTree<Key, Value>::findMax() const
{
    return elementAt(findMax(root));
}

/**
 * Internal method to find the largest item in a subtree t.
 * Return node containing the largest item.
 */
template <class Key, class Value>
AvlNode<Key, Value>*AVLSearchTree<Key, Value>::findMax(AvlNode<Key, Value>* t) const
{
    if (t != NULL)
        while (t->right != NULL)
            t = t->right;
    return t;
}

/**
  * Insert x into the tree; duplicates are ignored.
  */
template <class Key, class Value>
void AVLSearchTree<Key, Value>::insert(const Key& x, const Value& y)
{
    insert(x, y, root);
}

/**
  * Remove x from the tree. Nothing is done if x is not found.
  */
template <class Key, class Value>
void AVLSearchTree<Key, Value>::remove(const Key& x)
{
    remove(x, root);
}
/**
 * Internal method to remove from a subtree.
 * x is the item to remove.
 * t is the node that roots the tree.
 * Set the new root.
 * (MODIFICATION MIGHT BE NEEDED-conditions in insert)
 */
template <class Key, class Value>
void AVLSearchTree<Key, Value>::remove(const Key& x, AvlNode<Key, Value>*& t) const
{
    if (t == NULL)
        return;   // Item not found; do nothing
    if (x < t->key)
        remove(x, t->left);
    else if (t->key < x)
        remove(x, t->right);
    else if (t->left != NULL && t->right != NULL) // Two children
    {
        t->key = findMin(t->right)->key;
        remove(t->key, t->right);
    }
    else // one or no children
    {
        AvlNode<Key, Value>* oldNode = t;
        t = (t->left != NULL) ? t->left : t->right;
        delete oldNode;
    }
}

/**
  * Make the tree logically empty.
  */
template <class Key, class Value>
void AVLSearchTree<Key, Value>::makeEmpty()
{
    makeEmpty(root);
}

/**
 * Internal method to make subtree empty.
 */
template <class Key, class Value>
void AVLSearchTree<Key, Value>::makeEmpty(AvlNode<Key, Value>*& t) const
{
    if (t != NULL)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = NULL;
}

/**
  * Print the tree contents in sorted order.
  */
//template <class Key, class Value>
//void AVLSearchTree<Key, Value>::printTree() const
//{
//    if (isEmpty())
//        cout << "Empty tree" << endl;
//    else
//        printTree(root);
//}

/**
  * Destructor for the tree.
  */
template <class Key, class Value>
AVLSearchTree<Key, Value> ::~AVLSearchTree()
{
    makeEmpty();
}

/**
  * Copy constructor.
  */
template <class Key, class Value>
AVLSearchTree<Key, Value>::AVLSearchTree(const AVLSearchTree<Key, Value>& rhs)
    :root(NULL), ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND)
{
    *this = rhs;
}


/**
        * Return the height of node t, or -1, if NULL.
*/
template <class Key, class Value>
int AVLSearchTree<Key, Value>::height(AvlNode<Key, Value>* t)
const
{
    if (t == NULL)
        return -1;

    return t->height;
}

/**
         * Return maximum of lhs and rhs.
 */
template <class Key, class Value>
int AVLSearchTree<Key, Value>::max(int lhs, int rhs)
const
{
    if (lhs > rhs)
        return lhs;

    return rhs;
}

/**
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the tree.
 * Set the new root.
 */
template <class Key, class Value>
void AVLSearchTree<Key, Value>::insert(const Key& x, const Value& y, AvlNode<Key, Value>*& t) const
{
    if (t == NULL)
        t = new AvlNode<Key, Value>(x, y, NULL, NULL);

    else if (x < t->key) {
        // X should be inserted to the left tree!
        insert(x, y, t->left);

        // Check if the left tree is out of balance (left subtree grew in height!)
        if (height(t->left) - height(t->right) == 2)
            if (x < t->left->key)  // X was inserted to the left-left subtree!
                rotateWithLeftChild(t);
            else			     // X was inserted to the left-right subtree!
                doubleWithLeftChild(t);
    }

    else if (t->key < x)
    {    // Otherwise X is inserted to the right subtree
        insert(x, y, t->right);
        if (height(t->right) - height(t->left) == 2)
            // height of the right subtree increased
            if (t->right->key < x)
                // X was inserted to right-right subtree
                rotateWithRightChild(t);
            else // X was inserted to right-left subtree
                doubleWithRightChild(t);
    }
    else
        ;  // Duplicate; do nothing

  // update the height the node
    t->height = max(height(t->left), height(t->right)) + 1;
}
/**
  * Rotate binary tree node with left child.
  * For AVL trees, this is a single rotation for case 1.
  * Update heights, then set new root.
  */
template <class Key, class Value>
void AVLSearchTree<Key, Value>::rotateWithLeftChild(AvlNode<Key, Value>*& k2) const
{
    AvlNode<Key, Value>* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
}
/**
 * Rotate binary tree node with right child.
 * For AVL trees, this is a single rotation for case 4.
 * Update heights, then set new root.
 */
template <class Key, class Value>
void AVLSearchTree<Key, Value>::rotateWithRightChild(AvlNode<Key, Value>*& k1) const
{
    AvlNode<Key, Value>* k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->right), k1->height) + 1;
    k1 = k2;
}
/**
  * Double rotate binary tree node: first left child.
  * with its right child; then node k3 with new left child.
  * For AVL trees, this is a double rotation for case 2.
  * Update heights, then set new root.
  */
template <class Key, class Value>
void AVLSearchTree<Key, Value>::doubleWithLeftChild(AvlNode<Key, Value>*& k3) const
{
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}
/**
 * Double rotate binary tree node: first right child.
 * with its left child; then node k1 with new right child.
 * For AVL trees, this is a double rotation for case 3.
 * Update heights, then set new root.
 */
template <class Key, class Value>
void AVLSearchTree<Key, Value>::doubleWithRightChild(AvlNode<Key, Value>*& k1) const
{
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
}

//checks if the tree is empty or not
template <class Key, class Value>
bool AVLSearchTree<Key, Value>::isEmpty() const
{
    if (root == NULL)
    {
        return true;
    }

    return false;
}