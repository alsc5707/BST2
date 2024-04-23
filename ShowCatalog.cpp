#include "ShowCatalog.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
ShowItem *getParent(ShowItem *root, string title) {
    if (root == nullptr || root->title == title){
        return nullptr; 
    }
    ShowItem *parent = nullptr;
    ShowItem *current = root;

    while (current != nullptr && current->title != title) {
        parent = current;
        if (title < current->title){
            current = current->left;
        }else{
            current = current->right;
        }
    }

    return parent;
}
/* Completed functions. DO NOT MODIFY*/
ShowCatalog::ShowCatalog()
{
    root = nullptr;
}

/* Completed functions. DO NOT MODIFY*/
void destroyNode(ShowItem *current)
{
    if (current != nullptr)
    {
        destroyNode(current->left);
        destroyNode(current->right);

        delete current;
        current = nullptr;
    }
}

/* Completed functions. DO NOT MODIFY*/
ShowCatalog::~ShowCatalog()
{
    destroyNode(root);
}

/* Completed functions. DO NOT MODIFY*/
void printShowHelper(ShowItem *m)
{
    if (m != nullptr)
    {
        cout << "Show: " << m->title << " " << m->userRating << endl;
        printShowHelper(m->left);
        printShowHelper(m->right);
    }
}

/* Completed functions. DO NOT MODIFY*/
void ShowCatalog::printShowCatalog()
{
    if (root == nullptr)
    {
        cout << "Tree is Empty. Cannot print" << endl;
        return;
    }
    printShowHelper(root);
}

/* Completed functions. DO NOT MODIFY*/
ShowItem *getShowHelper(ShowItem *current, string title)
{
    if (current == NULL)
        return NULL;

    if (current->title == title)
        return current;

    if (current->title > title)
        return getShowHelper(current->left, title);

    return getShowHelper(current->right, title);
}

/* Completed functions. DO NOT MODIFY*/
void ShowCatalog::getShow(string title)
{
    ShowItem *node = getShowHelper(root, title);
    if (node != nullptr)
    {
        cout << "Show Info:" << endl;
        cout << "==================" << endl;
        cout << "Title :" << node->title << endl;
        cout << "Year :" << node->year << endl;
        cout << "Show Rating :" << node->showRating << endl;
        cout << "User Rating :" << node->userRating << endl;
        return;
    }

    cout << "Show not found." << endl;
}

/* Completed functions. DO NOT MODIFY*/
ShowItem *addNodeHelper(ShowItem *current, ShowItem *newNode)
{
    if (current == nullptr)
    {
        return newNode;
    }

    if (current->title > newNode->title)
    {
        current->left = addNodeHelper(current->left, newNode);
    }
    else
    {
        current->right = addNodeHelper(current->right, newNode);
    }

    return current;
}

/* Completed functions. DO NOT MODIFY*/
void ShowCatalog::addShowItem(string title, int year, string showRating, float userRating)
{
    if (root == nullptr)
    {
        root = new ShowItem(title, year, showRating, userRating);
        return;
    }

    root = addNodeHelper(root, new ShowItem(title, year, showRating, userRating));
}
ShowItem *findMinNode(ShowItem *node)
{
    while (node->left != nullptr){
        node = node->left;
    }
    return node;
}

/* Helper function to perform a right rotation */
ShowItem *rightRotateHelper(ShowItem *y)
{
    if (y == nullptr || y->left == nullptr){
        return y;
    } 
    ShowItem *x = y->left;
    y->left = x->right;
    x->right = y;
    return x;
}

/* Helper function to perform a left rotation */
ShowItem *leftRotateHelper(ShowItem *x)
{
    if (x == nullptr || x->right == nullptr){
        return x;
    }
    ShowItem *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

/* Helper function to remove a show with a given title */
ShowItem *removeShowHelper(ShowItem *root, string title)
{
    if (root == nullptr){
        return root;
    }
    if (title < root->title){
        root->left = removeShowHelper(root->left, title);
    }else if (title > root->title){
        root->right = removeShowHelper(root->right, title);
    }else{
        if (root->left == nullptr){
            ShowItem *temp = root->right;
            delete root;
            return temp;
        }else if (root->right == nullptr){
            ShowItem *temp = root->left;
            delete root;
            return temp;
        }
        ShowItem *temp = findMinNode(root->right);
        root->title = temp->title;
        root->year = temp->year;
        root->showRating = temp->showRating;
        root->userRating = temp->userRating;
        root->right = removeShowHelper(root->right, temp->title);
    }

    return root;
}
/* TODO */
void ShowCatalog::removeShow(std::string title)
{
    root = removeShowHelper(root, title);
}

/* TODO */
void ShowCatalog::rightRotate(std::string title)
{
    ShowItem *node = getShowHelper(root, title);
    if (node != nullptr && node->left != nullptr){
        ShowItem *pivot = node->left;
        node->left = pivot->right;
        pivot->right = node;
        if (node == root){
            root = pivot; 
        }else{
            ShowItem *parent = getParent(root, node->title);
            if (parent->left == node){
                parent->left = pivot;
            }else{
                parent->right = pivot;
            }
        }
    }
}

/* TODO */
void ShowCatalog::leftRotate(std::string title)
{
    // TODO
    ShowItem *node = getShowHelper(root, title);
    if (node != nullptr && node->right != nullptr){
        ShowItem *pivot = node->right;
        node->right = pivot->left;
        pivot->left = node;
        if (node == root){
            root = pivot; 
        }else{
            ShowItem *parent = getParent(root, node->title);
            if (parent->left == node){
                parent->left = pivot;
            }else{
                parent->right = pivot;
            }
        }
    }
}
