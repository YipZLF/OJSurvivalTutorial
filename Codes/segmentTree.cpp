/*
 use segment tree to sum A1,A2,...,An
*/

#include<iostream>
using namespace std;
const int MAXN = 10;
struct CNode
{
    int L,R;
    int sum;
};
CNode tree[4*MAXN - 1];

void buildTree(int cur_node,int left, int right)
{
    tree[cur_node].sum = 0;
    tree[cur_node].L = left;
    tree[cur_node].R = right;
    if(left!=right){
        buildTree(cur_node*2 + 1, left,(left+right)/2);
        buildTree(cur_node*2 + 2, (left+right)/2 + 1,right);
    }
}

int Add(int cur_node,int left, int right, int *sum)
{
    if(left == tree[cur_node].L &&
       right == tree[cur_node].R){
        *sum += tree[cur_node].sum;
    }else{
        int mid = (tree[cur_node].L + tree[cur_node].R)/2;
        if( (mid <= left){
            Add(cur_node * 2 + 2, left,right,sum);
        }else if( (mid >= right){
            Add(cur_node * 2 + 1 , left, right ,sum);
        }else{
            Add(cur_node*2+1,left,mid,sum);
            Add(cur_node*2+2,mid + 1,right,sum);
        }
    }
    return *sum;
}

/* THIS Change is not finished for it doesn't completely updated all the nodes.
    It stops when left = L and right = R, but the subtree of that very node is not updated.
    Needs more "memory" to take care whether node itself has been updated or not.
*/
int Change(int cur_node,int left,int right,int updatedSum)
{
    if(left == tree[cur_node].L &&
       right == tree[cur_node].R){
        tree[cur_node].sum = updateSum;
        return tree[cur_node].sum;
    }else{
        int mid = (tree[cur_node].L + tree[cur_node].R)/2;
        int tmp = 0;
        if( (mid <= left){
            Change(cur_node * 2 + 2, left,right,updatedSum);
        }else if( (mid >= right){
            Change(cur_node * 2 + 1, left,right,updatedSum);
        }else{
            Change(cur_node*2+1,left,mid,updatedSum);
            Change(cur_node*2+2,mid,right,updatedSum);
        }
        tree[cur_node].sum = tree[cur_node].sum + tree[cur_node].sum;
        return tree[cur_node].sum;
    }
}

int main()/*unfinished*/
{
    int T = 2;
    char action;
    while(T--){
        scanf("%c",)
    }
}
