#include<iostream>
#include<queue>
using namespace std;
struct node{
    int data;
    node * left,right;

    node(int data)
    {
        this->data = data;
        this->right = NULL;
        this->left = NULL;
    }
};
int main()
{
    int x;
    queue<node *>q;

    cout<<"Enter the root value ";
    cin>>x;
    node * root = new node(x);
    q.push(root);

    while(!q.empty())
    {
        node * temp = q.front();
        q.pop();

        int left;
        cout<<"Enter left child of "<<temp->data<<" ";
        cin>>left;
        if(left != -1)
        {
            temp->left = new node(left);
            q.push(temp->left);
        }

        int right;
        cout<<"Enter right child of "<<temp->data<<" ";
        cin>>right;
        if(right != -1)
        {
            temp->right = new node(left);
            q.push(temp->right);
        }
    }
    
/* 

# Time complexity for creation of binary tree is O(n)
# Space complexity for creation of binary tree is height of the tree

*/
}
