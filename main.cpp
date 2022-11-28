// John Dinh
// Fall 2022 - Gatoravl Tree.
#include <iostream>
#include <string>
#include <vector>
using namespace std;
//taken from AVL treeNode slide
struct TreeNode
{
    string name;
    int id;
    TreeNode* left;
    TreeNode* right;
    //constructor
    TreeNode()
    {
        name = "";
        id = 0;
        left = nullptr;
        right = nullptr;
    }
    //setter
    TreeNode(string Name, int ID)
    {
        name = Name;
        id = ID;
        left = nullptr;
        right = nullptr;
    }
};

class Tree
{
    TreeNode* root;
public:
    //constructor
    Tree()
    {
        root = nullptr;
    }
    //setter
    void setRoot(TreeNode* root)
    {
        this->root = root;
    }
    //accessor
    TreeNode* getRoot()
    {
        return root;
    }
    //destructor
    ~Tree()
    {
        destruct(root);
    }
    // helper function to destuct the tree. (Memory Management)
    // Got from programming quiz trees.
    void destruct(TreeNode* root)
    {
        if (root->left != nullptr)
        {
            destruct(root->left);
        }

        if (root->right != nullptr)
        {
            destruct(root->right);
        }
        delete root;
    }
    // Function to insert into tree based sorted by ID.
    //Based off the lecture slides.
    TreeNode* insert(TreeNode* node, string name, int ID)
    {
        // If tree is empty.
        if (node == nullptr)
        {
            TreeNode *node = new TreeNode(name, ID);
            cout << "successful" << endl;
            return node;
        }
        if (node->id > ID)
        {
            node->left = insert(node->left, name, ID);
        }
        else if (node->id < ID)
        {
            node->right = insert(node->right, name, ID);
        }
        // meaning ID already exists.
        else
        {
            cout << "unsuccessful" << endl;
            return node;
        }
        node = balance(node);
        return node;
    }
    // Balance the tree
    // Based off psuedocode and chart from lecture slides.
    TreeNode* balance(TreeNode* node)
    {
        int balanceFactor = findBalanceFactor(node);
        // Check if right heavy
        if (balanceFactor <= -2)
        {
            // Check right subtree is left heavy
            if (findBalanceFactor(node->right) >= 1)
            {
                // Right left rotation
                node->right = rotateRight(node->right);
                node = rotateLeft(node);
            }
            else
            {
                //left rotation
                node = rotateLeft(node);
            }
        }
        // Check if tree is left heavy
        else if (balanceFactor >= 2)
        {
            // Check left subtree is right heavy.
            if (findBalanceFactor(node->left) <= -1)
            {
                // Left right rotation
                node->left = rotateLeft(node->left);
                node = rotateRight(node);
            }
            else
            {
                // Right rotation
                node = rotateRight(node);
            }
        }
        return node;
    }
    // Gets height of tree, used for level count and balance tree.
    // From module 5 stepik solutions on canvas.
    int height(TreeNode* root)
    {
        if (root == nullptr)
        {
            return 0;
        }
        else
        {
            return 1 + max(height(root->left), height(root->right));
        }
    }
    // Gets the balance factor of node.
    // From module 5 stepik solutions on canvas.
    int findBalanceFactor(TreeNode* node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        else
        {
            return height(node->left) - height(node->right);
        }
    }
    //Left rotation
    // From module 5 stepik solutions on canvas.
    TreeNode* rotateLeft(TreeNode *node)
    {
        TreeNode* rightChild = node->right;
        node->right = rightChild->left;
        rightChild->left = node;
        return rightChild;
    }
    // Right rotation
    // From module 5 stepik solutions on canvas.
    TreeNode* rotateRight(TreeNode *node)
    {
        TreeNode* leftChild = node->left;
        node->left = leftChild->right;
        leftChild->right = node;
        return leftChild;
    }
    // Makes a vector of names, sorted inorder
    // From module 5 stepik solutions on canvas.
    void inorderTraversal(TreeNode* root, vector<string>& temp)
    {
        if (root == nullptr)
        {
            return;
        }
        inorderTraversal(root->left, temp);
        temp.push_back(root->name);
        inorderTraversal(root->right, temp);
    }
    // Makes a vector of names, sorted preorder
    void preorderTraversal(TreeNode* root, vector<string>& temp)
    {
        if (root == nullptr)
        {
            return;
        }
        temp.push_back(root->name);
        preorderTraversal(root->left, temp);
        preorderTraversal(root->right, temp);
    }
    // Makes a vector of names, sorted postorder
    void postorderTraversal(TreeNode* root, vector<string>& temp)
    {
        if (root == nullptr)
        {
            return;
        }
        postorderTraversal(root->left, temp);
        postorderTraversal(root->right, temp);
        temp.push_back(root->name);
    }
    //Print function that takes all the prints, and has a string paramater to check which print function was called.
    void printAll(TreeNode* head, string function)
    {
        if (function == "printLevelCount")
        {
            int levelCount = 0;
            if (root == nullptr)
            {
                levelCount = 0;
            }
            else
            {
                levelCount = height(root);
            }
            cout << levelCount << endl;
        }
        else
        {
            vector<string> temp;
            string result = "";
            //Make different vectors with chosen order based on the function that was passed in.
            if (function == "printInorder")
            {
                inorderTraversal(head, temp);
            }
            else if (function == "printPostorder")
            {
                postorderTraversal(head, temp);
            }
            else if (function == "printPreorder")
            {
                preorderTraversal(head, temp);
            }
            // goes through the ordered vector and prints it out seperated by comma and space.
            for (int i = 0; i < temp.size(); i++)
            {
                result = result + temp[i] + ", " ;
            }
            //gets rid of the excess comma and space, if the string result is not empty.
            if (result.length() != 0)
            {
                result.pop_back();
                result.pop_back();
            }
            cout << result << endl;
        }
    }
    // Search function that takes in both commands for search, and two booleans to check if search command is with name or ID.
    void search(TreeNode* node,string target, bool isID, bool isName)
    {
        if (isID)
        {
            // Goes through tree and once the current node id is equal to the node were looking for print the name at that node.
            int ID = stoi(target);
            if (node == nullptr)
            {
                cout << "unsuccessful" << endl;
                return;
            }
            else if (node->id == ID)
            {
                cout << node->name << endl;
                return;
            }
            else if (ID < node->id)
            {
                search(node->left, target, true, false);
            }
            else
            {
                search(node->right, target, true, false);
            }
        }
        if (isName)
        {
            vector<string> IDS;
            //Gets a vector of strings with the IDS that match the target name preorder.
            searchNameHelper(target, root, IDS);
            if (IDS.empty())
            {
                cout << "unsuccessful" << endl;
            }
            else
            {
                int i = 0;
                while (i < IDS.size())
                {
                    if (IDS[i].size() == 8)
                    {
                        cout << IDS[i] << endl;
                    }
                    else
                    {
                        // Checks to see how many leading zeros we have to attach to front of the string.
                        int counter = 8 - IDS[i].size();
                        string temp = "";
                        for (int i = 0; i < counter; i++)
                        {
                            temp = temp + "0";
                        }
                        cout << (temp + IDS[i]) << endl;
                    }
                    i++;
                }
            }
        }
    }
    // Makes a vector of the IDS in preorder.
    // Made for case where people have the same name when using search command.
    void searchNameHelper(string target, TreeNode* node, vector<string>& temp)
    {
        if (node == nullptr)
        {
            return;
        }
        if (node->name == target)
        {
            temp.push_back(to_string(node->id));
        }
        searchNameHelper(target, node->left, temp);
        searchNameHelper(target, node->right, temp);
    }
    TreeNode* removeID(TreeNode* node, int ID)
    {
        if (node == nullptr)
        {
            cout << "unsuccessful" << endl;
            return nullptr;
        }
        // going through the tree to find the node with given ID.
        else if (ID < node->id)
        {
            node->left = removeID(node->left, ID);
        }
        else if (ID > node->id)
        {
            node->right = removeID(node->right, ID);
        }
        // Case: no children.
        else if (node->right == nullptr && node->left == nullptr)
        {
            delete node;
            node = nullptr;
            cout << "successful" << endl;
            return node;
        }
        // Case: only has one child and its the left child.
        else if (node->right == nullptr)
        {
            cout << "successful" << endl;
            TreeNode* temp = node;
            node = node->left;
            delete temp;
            return node;
        }
        // Case: only has one child and its the right child.
        else if (node->left == nullptr)
        {
            cout << "successful" << endl;
            TreeNode* temp = node;
            node = node->right;
            delete temp;
            return node;
        }
        // Case: 2 children
        else if (node->right != nullptr && node->left != nullptr)
        {
            TreeNode *temp = getInorderSuccessor(node->right);
            node->name = temp->name;
            node->id = temp->id;
            node->right = removeID(node->right, node->id);
            return node;
        }
        return node;
    }
    //Gets the inorder succesor for case when there are two children.
    TreeNode* getInorderSuccessor(TreeNode* node)
    {
        if (node->left != nullptr)
        {
            getInorderSuccessor(node->left);
        }
        else
        {
            return node;
        }
    }
    TreeNode* removeInorder(TreeNode* node, int N)
    {
        vector<TreeNode*> res;
        inorderHelper(this->root, res);
        //Makes sure to see if N is a valid index inside the inorder vector.
        if (N <= res.size())
        {
            TreeNode* temp = removeID(this->root, res[N]->id);
            return temp;
        }
        else if (N >= res.size())
        {
            cout << "unsuccessful" << endl;
            return node;
        }
    }
    // Makes a vector of nodes and sorts them inorder. helper for removeInorder
    void inorderHelper(TreeNode* node, vector<TreeNode*>& temp)
    {
        if (node == nullptr)
        {
            return;
        }
        inorderHelper(node->left, temp);
        temp.push_back(node);
        inorderHelper(node->right, temp);
    }
};
// Checks if ID fits constraints
bool checkID (string ID)
{
    bool temp = true;
    bool temp2 = true;
    //Checks if the ID is 8 characters .
    if (ID.length() != 8)
    {
        temp = false;
    }
    // Checks if its a number.
    for (char const &c : ID)
    {
        if (!isdigit(c))
        {
            temp2 = false;
        }
    }
    if (temp == false || temp2 == false)
    {
        return false;
    }
    else
    {
        return true;
    }
}
// Checks if name fits constraints
bool checkName(string name)
{
    bool temp = true;
    for (int i = 0; i < name.length(); i++)
    {
        // Checks if name given only consists of letters and spaces
        if (!isalpha(name[i]) && !isspace(name[i]))
        {
            temp = false;
        }
    }
    return temp;
}
// Check that value N from removeInorder N fits constraints.
bool checkN(string N)
{
    bool temp = true;
    // Checks if N is a number
    for (char const &c : N)
    {
        if (!isdigit(c))
        {
            temp = false;
        }
    }
    return temp;
}


int main()
{
    Tree tree;
    string line;
    string function;
    string name;
    string ID;
    string temp;
    int numCommands = 0;
    getline(cin, line);
    numCommands = stoi(line);

    for (int i = 0; i < numCommands; i++)
    {
        getline(cin, temp);
        int ind = temp.find_first_of(' ');
        function = temp.substr(0, ind);
        if (function == "insert")
        {
            int quote1 = temp.find_first_of('"');
            int quote2 = temp.find_last_of('"');
            name = temp.substr(quote1 + 1, quote2 - quote1 - 1 );
            //Makes sure that there is a space for a number after name input
            if (quote2 != temp.length()-1)
            {
                ID = temp.substr(quote2 + 2, (quote2 + 2) - temp.length());
                // Checks if name and ID are valid
                if (checkName(name) && checkID(ID))
                {
                    int id = stoi(ID);
                    TreeNode* node = tree.insert(tree.getRoot(), name, id);
                    tree.setRoot(node);
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
        else if (function == "remove")
        {
            int firstspace = temp.find_first_of(' ');
            ID = temp.substr(firstspace + 1, (firstspace + 1) - temp.length()-1);
            if(checkID(ID))
            {
                int temp = stoi(ID);
                tree.setRoot(tree.removeID(tree.getRoot(), temp));
            }
            else
            {
                cout << "unsuccessful" << endl;
            }
        }
        else if (function == "search")
        {
            bool isID = false;
            bool isName = false;
            int firstspace = temp.find_first_of(' ');
            string quote = temp.substr(firstspace + 1, 1);
            // Checks for quote, (checks if search is targeting name or id)
            if (quote == "\"")
            {
                int firstQuote = temp.find_first_of('"');
                int lastQuote = temp.find_last_of('"');
                name = temp.substr(firstQuote + 1, lastQuote - firstQuote-1);
                string test =  temp.substr(firstQuote + 1, temp.length() - firstQuote-2);
                if (checkName(name) && test == name)
                {
                    isID = false;
                    isName = true;
                    tree.search(tree.getRoot(), name, isID, isName);
                }
                else
                {
                    cout << "unsuccessful" << endl;
                }
            }
            else
            {
                ID = temp.substr(firstspace + 1, temp.length() - 1);
                if (checkID(ID))
                {
                    isID = true;
                    isName = false;
                    tree.search(tree.getRoot(), ID, isID, isName);
                }
                else
                {
                    cout << "unsuccessful" << endl;
                }
            }
        }
        else if (function == "printInorder")
        {
            tree.printAll(tree.getRoot(), function);
        }
        else if (function == "printPreorder")
        {
            tree.printAll(tree.getRoot(), function);
        }
        else if (function == "printPostorder")
        {
            tree.printAll(tree.getRoot(), function);
        }
        else if (function == "printLevelCount")
        {
            tree.printAll(tree.getRoot(),function);
        }
        else if (function == "removeInorder")
        {
            int firstspace = temp.find_first_of(' ');
            string temp2 = temp.substr(firstspace+1,  line.length()-1 - firstspace);
            if (checkN(temp2))
            {
                int N = stoi(temp2);
                tree.setRoot(tree.removeInorder(tree.getRoot(), N));
            }
            else
            {
                cout << "unsuccessful";
            }
        }
        // If no valid command is typed.
        else
        {
           cout << "unsuccessful" << endl;
        }
    }
}
