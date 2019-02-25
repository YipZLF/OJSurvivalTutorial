#include<iostream>
using namespace std;

struct node{
    int value;
    struct node* pLeft,*pRight,*pParent;
};

class BSTree{
    struct node *root;
}


void BSTree<T>::InsertNode(node* root, * newpointer)
{
    node *tmp;
    if(root ==NULL){
        Initialize(newpointer);
        return ;
    }
    tmp = root;
    while(true){
        if(newpointer->val==tmp->val)
            return;
        else if(newpointer->val < tmp->val){
            if(tmp->pLeft)
                tmp = tmp->pLeft;
            else{
                tmp->pLeft = newpointer;
                return;
            }
        }else{
            if(tmp->pRight)
                tmp = tmp->pRight;
            else{
                tmp->pRight = newpointer;
                return;
            }
        }
    }
}

void BSTree<T>::DeleteNodeEx(node * delpointer)
{
    node * delparent = Parent(delpointer);
    node * replpointer, * replparent = NULL;
    if(delpointer->pLeft == NULL)
        replpointer = delpointer->pRight;
    else{
        replpointer = delpointer->pLeft;
        while(replpointer->pRight!=NULL){
            replparent = replpointer;
            replpointer = replpointer->pRight;
        }
        if(replparent == NULL){
            delpointer->pLeft = pointer->pLeft;
        }else{
            replparent->pRight = replpointer->pLeft;
        }
        replpointer->pLeft = delpointer->pLeft;
        replpointer->pRight = delpointer->pRight;
    }
    if(delparent == NULL)
        root = replpointer;
    else if(delparent->pLeft == delpointer)
        delparent->pLeft = replpointer;
    else
        delparent->pRight = replpointer;
    delete delpointer;
    delpointer = NULL;
    return ;
}
