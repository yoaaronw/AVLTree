#include <cmath>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
using namespace std;

class AVLTree
{
private:
    struct Node
    {
        string name;
        string ufid;
        int height;
        Node* left;
        Node* right;
        Node(string name, string ufid) : name(name), ufid(ufid), height(1), left(nullptr), right(nullptr) {}
    };

    Node* root = nullptr;
    // Rotation helpers
    AVLTree::Node* helperLeftRotation(Node* helpRoot);
    AVLTree::Node* helperRightRotation(Node* helpRoot);
    AVLTree::Node* helperLeftRightRotation(Node* helpRoot);
    AVLTree::Node* helperRightLeftRotation(Node* helpRoot);
    // Balance helpers
    int helperUpdateHeight(Node* helpRoot);
    int helperBalanceFactor(Node* helpRoot);
    AVLTree::Node* helperBalanceTree(Node* helpRoot, int parentBalance);
    void helperLevelCount(Node* helpRoot);
    // Input helpers
    bool helperValidID(string ufid);
    bool helperValidName(string name);
    bool helperValidInput(Node* helpRoot, string name, string ufid);
    // Searching helpers
    AVLTree::Node* helperSearchID(Node* helpRoot, string ufid);
    bool helperNameFound (Node* helpRoot, string name);
    void helperSearchName(Node* helpRoot, string name);
    // Insert helper
    AVLTree::Node* helperInsert(Node* helpRoot, string name, string ufid);
    // Remove helper
    bool helperPossibleNode(Node* helpRoot, int n);
    bool helperIsANumber(string n);
    AVLTree::Node* helperInorderSuccessor(Node* helpRoot);
    AVLTree::Node* helperRemove(Node* helpRoot, string ufid);
    void helperNodesInorder(Node* helpRoot, int n, vector<string>& ufids);
    // Traversing helpers
    void helperVectorInorder(Node* helpRoot, vector<string>& ufids);
    void helperUpdateInorderVector(vector<string>& ufids);
    void helperInorder(Node* helpRoot);
    void helperPreorder(Node* helpRoot);
    void helperPostorder(Node* helpRoot);
    // Destructor helper
    void helperDeleteTree(Node* helpRoot);

public:
    void insert(string name, string ufid);
    void remove(string ufid);
    void searchID(string ufid);
    void searchName(string name);
    void inorder();
    void preorder();
    void postorder();
    void levelCount();
    void removeInorder(string n);
    ~AVLTree();
};

// Rotation helpers

AVLTree::Node* AVLTree::helperLeftRotation(Node* helpRoot)
{
    Node* grandchild = helpRoot->right->left;
    Node* newParent = helpRoot->right;
    newParent->left = helpRoot;
    helpRoot->right = grandchild;
    // Updates height after rotation
    if (grandchild != nullptr)
    {
        grandchild->height = helperUpdateHeight(grandchild);
    }
    helpRoot->height = helperUpdateHeight(helpRoot);
    newParent->height = helperUpdateHeight(newParent);
    return newParent;
}

AVLTree::Node* AVLTree::helperRightRotation(Node* helpRoot)
{
    Node* grandchild = helpRoot->left->right;
    Node* newParent = helpRoot->left;
    newParent->right = helpRoot;
    helpRoot->left = grandchild;
    // Updates height after rotation
    if (grandchild != nullptr)
    {
        grandchild->height = helperUpdateHeight(grandchild);
    }
    helpRoot->height = helperUpdateHeight(helpRoot);
    newParent->height = helperUpdateHeight(newParent);
    return newParent;
}

AVLTree::Node* AVLTree::helperLeftRightRotation(Node* helpRoot)
{
    helpRoot->left = helperLeftRotation(helpRoot->left);
    return helperRightRotation(helpRoot);
}

AVLTree::Node* AVLTree::helperRightLeftRotation(Node* helpRoot)
{
    helpRoot->right = helperRightRotation(helpRoot->right);
    return helperLeftRotation(helpRoot);
}

// Balance helpers

int AVLTree::helperUpdateHeight(Node* helpRoot)
{
    return 1 + max((helpRoot->right == nullptr ? 0 : helpRoot->right->height), (helpRoot->left == nullptr ? 0 : helpRoot->left->height));
}

int AVLTree::helperBalanceFactor(Node* helpRoot)
{
    return (helpRoot->left == nullptr ? 0 : helpRoot->left->height) - (helpRoot->right == nullptr ? 0 : helpRoot->right->height);
}

AVLTree::Node* AVLTree::helperBalanceTree(Node* helpRoot, int parentBalance)
{
    int childBalance;
    if ((helpRoot->left == nullptr ? 0 : helpRoot->left->height) > (helpRoot->right == nullptr ? 0 : helpRoot->right->height))
    {
        childBalance = helperBalanceFactor(helpRoot->left);
    }
    else
    {
        childBalance = helperBalanceFactor(helpRoot->right);
    }
    // Left-left case = right rotation
    if (parentBalance == 2 && childBalance == 1)
    {
        helpRoot = helperRightRotation(helpRoot);
    }
    // Right-right case = left rotation
    else if (parentBalance == -2 && childBalance == -1)
    {
        helpRoot = helperLeftRotation(helpRoot);
    }
    // Left-right case = left right rotation
    else if (parentBalance == 2 && childBalance == -1)
    {
        helpRoot = helperLeftRightRotation(helpRoot);
    }
    // Right-left case = right left rotation
    else if (parentBalance == -2 && childBalance == 1)
    {
        helpRoot = helperRightLeftRotation(helpRoot);
    }
    return helpRoot;
}

void AVLTree::helperLevelCount(Node* helpRoot)
{
    cout << helperUpdateHeight(helpRoot) << endl;
}

// Input helpers

bool AVLTree::helperValidID(string ufid)
{
    // Regex only allows numbers and 8 digits
    regex test = regex("^[0-9]{8}$");
    return regex_search(ufid, test);
}

bool AVLTree::helperValidName(string name)
{
    // Regex only allows alphabetical and spaces, at least one character
    if (name.empty())
    {
        return false;
    }
    regex test = regex("^[a-zA-z ]*$");
    return regex_search(name, test);
}

bool AVLTree::helperValidInput(Node* helpRoot, string name, string ufid)
{
    if (helperValidID(ufid) && helperValidName(name))
    {
        if (helperSearchID(helpRoot, ufid) == nullptr)
        {
            return true;
        }
    }
    return false;
}

// Search helpers

AVLTree::Node* AVLTree::helperSearchID(Node* helpRoot, string ufid)
{
    // If tree empty return nullptr
    if (helpRoot == nullptr)
    {
        return nullptr;
    }
    // If ufid found return the current node
    else if (helpRoot->ufid == ufid)
    {
        return helpRoot;
    }
    // Recursively checks tree for ufid
    else
    {
        if (ufid < helpRoot->ufid)
        {
            return helperSearchID(helpRoot->left, ufid);
        }
        else
        {
            return helperSearchID(helpRoot->right, ufid);
        }
    }
}

bool AVLTree::helperNameFound(Node* helpRoot, string name)
{
    if (helpRoot == nullptr)
    {
        return false;
    }
    else if (helpRoot->name == name)
    {
        return true;
    }
    else
    {
        // Checks entire
        bool left = helperNameFound(helpRoot->left, name);
        bool right = helperNameFound(helpRoot->right, name);
        // Returns true if at least one instance of name is found
        return left || right;
    }
}

void AVLTree::helperSearchName(Node* helpRoot, string name)
{
    // Recursively checks tree for name and prints out the ufid for all instances of name
    if (helpRoot == nullptr)
    {
        cout << "";
    }
    else
    {
        if (helpRoot->name == name)
        {
            cout << helpRoot->ufid << endl;
        }
        helperSearchName(helpRoot->left, name);
        helperSearchName(helpRoot->right, name);
    }
}

// Insert helper

AVLTree::Node* AVLTree::helperInsert(Node* helpRoot, string name, string ufid)
{
    // Insert node
    if (helpRoot == nullptr)
    {
        return new Node(name, ufid);
    }
    // Recursively move through tree
    else if (ufid < helpRoot->ufid)
    {
        helpRoot->left = helperInsert(helpRoot->left, name, ufid);
    }
    else
    {
        helpRoot->right = helperInsert(helpRoot->right, name, ufid);
    }
    // Update height
    helpRoot->height = helperUpdateHeight(helpRoot);
    // Calculate balance factor (left - right)
    int balanceFactor = helperBalanceFactor(helpRoot);
    // Balance
    if (balanceFactor == 2 || balanceFactor == -2)
    {
        helpRoot = helperBalanceTree(helpRoot, balanceFactor);
    }
    return helpRoot;
}

// Remove helpers

bool AVLTree::helperPossibleNode(Node* helpRoot, int n)
{
    // Max nodes = 2^height - 1
    return n < pow(2, helpRoot->height) - 1;
}

bool AVLTree::helperIsANumber(string n)
{
    // Regex only allows numbers
    regex test = regex("^[0-9]");
    return regex_search(n, test);
}

AVLTree::Node* AVLTree::helperInorderSuccessor(Node* helpRoot)
{
    // Keeps going left until nullptr
    if (helpRoot->left == nullptr)
    {
        return helpRoot;
    }
    else
    {
        return helperInorderSuccessor(helpRoot->left);
    }
}

AVLTree::Node* AVLTree::helperRemove(Node* helpRoot, string ufid)
{
    // Recursively find and delete node
    if (ufid < helpRoot->ufid)
    {
        helpRoot->left = helperRemove(helpRoot->left, ufid);
    }
    else if (ufid > helpRoot->ufid)
    {
        helpRoot->right = helperRemove(helpRoot->right, ufid);
    }
    else
    {
        // If no children, delete and return nullptr
        if (helpRoot->left == nullptr && helpRoot->right == nullptr)
        {
            delete helpRoot;
            return nullptr;
        }
        // If 1 child, delete and replace with child
        else if (helpRoot->right == nullptr)
        {
            Node* temp = helpRoot;
            helpRoot = helpRoot->left;
            delete temp;
        }
        else if (helpRoot->left == nullptr)
        {
            Node* temp = helpRoot;
            helpRoot = helpRoot->right;
            delete temp;
        }
        // If 2 children, delete and replace with inorder successor
        else
        {
            Node* temp = helperInorderSuccessor(helpRoot->right);
            helpRoot->ufid = temp->ufid;
            helpRoot->name = temp->name;
            helpRoot->right = helperRemove(helpRoot->right, temp->ufid);
        }
    }
    // Update height
    helpRoot->height = helperUpdateHeight(helpRoot);
    // Calculate balance factor (left - right)
    int balanceFactor = helperBalanceFactor(helpRoot);
    // Balance
    if (balanceFactor == 2 || balanceFactor == -2)
    {
        helpRoot = helperBalanceTree(helpRoot, balanceFactor);
    }
    return helpRoot;
}

void AVLTree::helperNodesInorder(Node* helpRoot, int n, vector<string>& ufids)
{
    // Passes in address of a vector
    // Add ufids inorder recursively into vector until node is nullptr or vector size is n
    if (helpRoot != nullptr && (int)ufids.size() - 1 != n)
    {
        helperNodesInorder(helpRoot->left, n, ufids);
        ufids.push_back(helpRoot->ufid);
        helperNodesInorder(helpRoot->right, n, ufids);
    }

}

// Traverse helpers

void AVLTree::helperVectorInorder(Node* helpRoot, vector<string>& ufids)
{
    // Passes in address of a vector
    // Add ufids inorder recursively
    if (helpRoot != nullptr)
    {
        helperVectorInorder(helpRoot->left, ufids);
        ufids.push_back(helpRoot->ufid);
        helperVectorInorder(helpRoot->right, ufids);
    }
}

void AVLTree::helperUpdateInorderVector(vector<string>& ufids)
{
    // Calls helperVectorInorder for large insert test case
    helperVectorInorder(this->root, ufids);
}

void AVLTree::helperInorder(Node* helpRoot)
{
    if (helpRoot == nullptr)
    {
        cout << "";
    }
    else
    {
        helperInorder(helpRoot->left);
        if (helpRoot->left != nullptr)
        {
            cout << ", ";
        }
        cout << helpRoot->name;
        if (helpRoot->right != nullptr)
        {
            cout << ", ";
        }
        helperInorder(helpRoot->right);
    }
}

void AVLTree::helperPreorder(Node* helpRoot)
{
    if (helpRoot == nullptr)
    {
        cout << "";
    }
    else
    {
        cout << helpRoot->name;
        if (helpRoot->left != nullptr)
        {
            cout << ", ";
        }
        helperPreorder(helpRoot->left);
        if (helpRoot->right != nullptr)
        {
            cout << ", ";
        }
        helperPreorder(helpRoot->right);
    }
}

void AVLTree::helperPostorder(Node* helpRoot)
{
    if (helpRoot == nullptr)
    {
        cout << "";
    }
    else
    {
        helperPostorder(helpRoot->left);
        if (helpRoot->left != nullptr)
        {
            cout << ", ";
        }
        helperPostorder(helpRoot->right);
        if (helpRoot->right != nullptr)
        {
            cout << ", ";
        }
        cout << helpRoot->name;
    }
}

// Deconstructer helper

void AVLTree::helperDeleteTree(Node* helpRoot)
{
    if (helpRoot != nullptr)
    {
        helperDeleteTree(helpRoot->left);
        helperDeleteTree(helpRoot->right);
        delete helpRoot;
    }
}


// Main functions

void AVLTree::insert(string name, string ufid)
{
    // First checks if the input is valid before inserting
    if (helperValidInput(this->root, name, ufid))
    {
        this->root = helperInsert(this->root, name, ufid);
        cout << "successful" << endl;
    }
    else
    {
        cout << "unsuccessful" << endl;
    }
}

void AVLTree::remove(string ufid)
{
    // First checks if ID exists before removing
    if (helperSearchID(this->root, ufid) != nullptr)
    {
        this->root = helperRemove(this->root, ufid);
        cout << "successful" << endl;
    }
    else
    {
        cout << "unsuccessful" << endl;
    }
}

void AVLTree::searchID(string ufid)
{
    // Checks if ufid is valid before searching
    // Searches for node with ufid and returns that node
    Node* temp = nullptr;
    if (helperValidID(ufid))
    {
        temp = helperSearchID(this->root, ufid);
    }
    if (temp != nullptr)
    {
        cout << temp->name << endl;
    }
    else
    {
        cout << "unsuccessful" << endl;
    }
}

void AVLTree::searchName(string name)
{
    // Checks if name is valid and exists in tree before searching
    if (helperValidName(name) && helperNameFound(this->root, name))
    {
        helperSearchName(this->root, name);
    }
    else
    {
        cout << "unsuccessful" << endl;
    }
}

void AVLTree::inorder()
{
    helperInorder(this->root);
    cout << endl;
}

void AVLTree::preorder()
{
    helperPreorder(this->root);
    cout << endl;
}

void AVLTree::postorder()
{
    helperPostorder(this->root);
    cout << endl;
}

void AVLTree::levelCount()
{
    helperLevelCount(this->root);
}

void AVLTree::removeInorder(string n)
{
    // Checks if n is a number
    if (helperIsANumber(n))
    {
        // Checks if n is a possible index
        int num = stoi(n);
        if (helperPossibleNode(this->root, num))
        {
            // Final check to make sure n is not greater than the total amount of nodes in tree
            vector<string> ufids = {};
            helperNodesInorder(this->root, num, ufids);
            if (num < (int)ufids.size())
            {
                this->root = helperRemove(this->root, ufids.at(num));
                cout << "successful" << endl;
            }
            else
            {
                cout << "unsuccessful" << endl;
            }
        }
        else
        {
            cout << "unsuccessful" << endl;
        }
    }
    else
    {
        cout << "unsuccessful" << endl;
    }
}

AVLTree::~AVLTree()
{
    helperDeleteTree(this->root);
}
