#include<iostream>
#include<string>
#include<queue>  
using namespace std;

struct node {
    string word;
    string meaning;
    node* left;
    node* right;

    node(string w, string m) 
    {
        this->word = w;
        this->meaning = m;
        this->left = NULL;
        this->right = NULL;
    }
};

class BinaryTree {
    node* root = NULL;

    // Inorder Traversal
    void inorder2(node* root) 
    {
        if (!root) 
            return;

        inorder2(root->left);
        cout << root->word << " == " << root->meaning << endl;
        inorder2(root->right);
    }

    // Level-order traversal
    void levelOrder(node* root) 
    {
        if (!root) 
           return;

        queue<node*> q;
        q.push(root);

        while (!q.empty())
        {
            node* temp = q.front();
            q.pop();
            cout << temp->word << " : " << temp->meaning << endl;

            if (temp->left) 
                q.push(temp->left);

            if (temp->right) 
                q.push(temp->right);
        }
    }

    void mirror(node* root) 
    {
        if (!root) 
            return;

        swap(root->left, root->right);
        mirror(root->left);
        mirror(root->right);
    }

    node* findMin(node* root) 
    {
        while (root && root->left)
            root = root->left;
        return root;
    }

    node* deleteNode(node* root, string w) 
    {
        if (!root) 
            return root;

        if (w < root->word)
            root->left = deleteNode(root->left, w);
        else if (w > root->word)
            root->right = deleteNode(root->right, w);
        else 
        {
            if (!root->left) 
            {
                node* temp = root->right;
                delete root;
                return temp;
            } 
            else if (!root->right) 
            {
                node* temp = root->left;
                delete root;
                return temp;
            }

            node* temp = findMin(root->right);
            root->word = temp->word;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->word);
        }
        return root;
    }

    node* copyTree(node* root) {
        if (!root) 
            return NULL;
        
        node* newNode = new node(root->word, root->meaning);
        newNode->left = copyTree(root->left);
        newNode->right = copyTree(root->right);
        return newNode;
    }

public:
   
    void insert(string w, string m) 
    {
        node* nn = new node(w, m);

        if (!root) 
        {
            root = nn;
            return;
        }

        node* ptr = root;
        while (ptr) 
        {
            if (ptr->word == w) 
                return;
            else if (ptr->word < w) 
            {
                if (!ptr->right) 
                {
                    ptr->right = nn;
                    return;
                } 
                else
                    ptr = ptr->right;
            } 
            else 
            {
                if (!ptr->left) 
                {
                    ptr->left = nn;
                    return;
                } 
                else
                    ptr = ptr->left;
            }
        }
    }

    //searching in BST
    void search(string w) 
    {
        node* ptr = root;
        while (ptr) 
        {
            if (ptr->word == w) 
            {
                cout << "Found: " << ptr->word << " == " << ptr->meaning << endl;
                return;
            } 
            else if (ptr->word < w)
                ptr = ptr->right;
            else
                ptr = ptr->left;
        }
        cout << "Word not found!\n";
    }

   
    void inorder() 
    {
        inorder2(root);
    }

    void mirrorTree() 
    {
        mirror(root);
        cout << "Dictionary mirrored successfully.\n";
    }

    void LevelWise() 
    {
        levelOrder(root);
    }

    int findHeightNonRecursive() {
        if (root == nullptr) {
            return -1;
        }

        std::queue<node*> queue;
        queue.push(root);
        int height = -1;

        while (!queue.empty()) {
            height++;
            int levelSize = queue.size();
            for (int i = 0; i < levelSize; ++i) {
                node* currentNode = queue.front();
                queue.pop();
                if (currentNode->left) {
                    queue.push(currentNode->left);
                }
                if (currentNode->right) {
                    queue.push(currentNode->right);
                }
            }
        }

        return height;
    }
    void deleteWord(string w) 
    {
        root = deleteNode(root, w);
        cout << "Word deleted "<<endl;
    }

    void copyDictionary() 
    {
        node* newRoot = copyTree(root);
        cout << "Dictionary copied successfully.\n";
    }
};
int main() 
{
    BinaryTree b1;
    b1.insert("book", "pages");
    b1.insert("apple", "fruit");
    b1.insert("zebra", "animal");
    b1.insert("rain", "water");
    b1.insert("cloud", "condensed water vapor");
    b1.insert("library", "collection of books");

    cout << "\nDictionary Inorder Display:\n";
    b1.inorder();
    cout<< b1.findHeightNonRecursive();
    cout << "\nSearching for 'rain':\n";
    b1.search("rain");

    cout << "\nDeleting 'zebra':\n";
    b1.deleteWord("zebra");
    b1.inorder();

    cout << "\nMirroring Dictionary:\n";
    b1.mirrorTree();
    b1.inorder();

    cout << "\nDisplaying Level-wise:\n";
    b1.LevelWise();

    cout << "\nCopying Dictionary:\n";
    b1.copyDictionary();

    return 0;
}
