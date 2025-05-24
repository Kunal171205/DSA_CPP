#include <iostream>
using namespace std;

struct Node {
    int id;
    int score;
    Node* left;
    Node* right;
    int height;

    Node(int id, int s) 
    {
        this->id = id;
        this->score = s;
        this->height = 1; 
        this->left = NULL;
        this->right = NULL;
    }
};

class AVLTree {
private:
    Node* root;

    int getHeight(Node* node) 
    {
        if(!node)
            return 0;

        return node->height;
    }

    int getBalance(Node* node) 
    {
        if(!node)
            return 0;

        return getHeight(node->left) - getHeight(node->right);
    }

    Node* LLrotation(Node* j)
    {
        Node* i = j->left;
        Node* Temp = i->right;

        i->right = j;
        j->left = Temp;

        i->height = max(getHeight(i->left), getHeight(i->right)) + 1;
        j->height = max(getHeight(j->left), getHeight(j->right)) + 1;

        return i;
    }

    Node* RRrotation(Node* j) 
    {
        Node* i = j->right;
        Node* Temp = i->left;

        i->left = j;
        j->right = Temp;

        i->height = max(getHeight(i->left), getHeight(i->right)) + 1;
        j->height = max(getHeight(j->left), getHeight(j->right)) + 1;

        return i;
    }

    Node* LRrotation(Node* j)
    {
        j->left = RRrotation(j->left);
        return LLrotation(j);
    }

    Node* RLrotation(Node* j)
    {   
        j->right = LLrotation(j->right);
        return RRrotation(j);
    }

    Node* insert(Node* node, int id, int score)
    {
        Node* nn = new Node(id, score);
        if (!node) 
            return nn;

        if (score < node->score)
            node->left = insert(node->left, id, score);
        else if (score > node->score)
            node->right = insert(node->right, id, score);
        else
            return node; 

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

        if (balance > 1 && score < node->left->score)
            return LLrotation(node);

        if (balance < -1 && score > node->right->score)
            return RRrotation(node);

        if (balance > 1 && score > node->left->score) 
            return LRrotation(node);

        if (balance < -1 && score < node->right->score) 
            return RLrotation(node);

        return node;
    }

    Node* minValueNode(Node* node) 
    {
        Node* current = node;
        while (current->left)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* root, int score) 
    {
        if (!root) 
            return root;

        if (score < root->score)
            root->left = deleteNode(root->left, score);
        else if (score > root->score)
            root->right = deleteNode(root->right, score);
        else
        {
            if (!root->left || !root->right) 
            {
                Node* temp = root->left ? root->left : root->right;
                if (!temp) 
                {
                    temp = root;
                    root = nullptr;
                }
                else
                    *root = *temp;

                delete temp;
            } 
            else 
            {
                Node* temp = minValueNode(root->right);
                root->score = temp->score;
                root->id = temp->id;
                root->right = deleteNode(root->right, temp->score);
            }
        }

        if (!root) 
            return root;

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return LLrotation(root);

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = RRrotation(root->left);
            return LLrotation(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return RRrotation(root);

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = LLrotation(root->right);
            return RRrotation(root);
        }

        return root;
    }

    void displayDescending(Node* node) 
    {
        if (node) 
        {
            displayDescending(node->right);
            cout << "Player ID: " << node->id << ", Score: " << node->score << endl;
            displayDescending(node->left);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void registerPlayer(int player_id, int score) 
    {
        root = insert(root, player_id, score);
        cout << "Player " << player_id << " with score " << score << " registered successfully.\n";
    }

    void removePlayer(int score) 
    {
        root = deleteNode(root, score);
        cout << "Player with score " << score << " removed from the game.\n";
    }

    void displayLeaderboard() 
    {
        if (!root) 
        {
            cout << "Leaderboard is empty.\n";
            return;
        }
        cout << "===== Leaderboard =====\n";
        displayDescending(root);
        cout << "=======================\n";
    }
};

int main() 
{
    AVLTree game;
    int choice, player_id, score;

    while (true) 
    {
        cout << "\n1. Register Player\n2. Display Leaderboard\n3. Remove Player\n4. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
                cout << "Enter Player ID and Score: ";
                cin >> player_id >> score;
                game.registerPlayer(player_id, score);
                break;
            case 2:
                game.displayLeaderboard();
                break;
            case 3:
                cout << "Enter Score of Player to Remove: ";
                cin >> score;
                game.removePlayer(score);
                break;
            case 4:
                cout << "Exiting the game.\n";
                return 0;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}