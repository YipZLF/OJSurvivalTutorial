/*后序+中序-》前序。二叉树*/
#include<cstdio>
#include<iostream>
#include<string.h>
using namespace std;
const int MAXN = 1000;
int seq[MAXN];
int cnt = 0,len;

struct node{
    int val;
    int pL,pR;
    node(){val = 0;pL=pR=-1;}
};
struct node tree[MAXN];

int getIndex(int val,int * arr)
{
    int i = 0;
    for(i=0;i <= len;i++)
        if(arr[i]==val){
            return i;
        }
    return -1;
}

void buildTree(int &root,int sIdx,int eIdx){
    if(root <= len) return ;
    int thisnode = cnt;
    tree[thisnode].val = seq[root];

    if(sIdx==eIdx)
        return ;

    int newIdx = getIndex(tree[thisnode].val,seq);

    if(newIdx<eIdx){
        tree[thisnode].pR = ++cnt;
        root --;
        buildTree(root,newIdx+1,eIdx);
    }
    if(newIdx > sIdx){
        tree[thisnode].pL = ++cnt;
        root --;
        buildTree(root,sIdx,newIdx-1);
    }
    return ;
}

void DFS(int root){
    printf("%d ",tree[root].val);
    if(tree[root].pL!=-1)
        DFS(tree[root].pL);
    if(tree[root].pR!=-1)
        DFS(tree[root].pR);
}

int main()
{
    freopen("backmid2front.in","r",stdin);
    int i = 0;
    while(scanf("%d",seq+i)==1)
        i++;
    len = (i-1)/2;
    i--;
    buildTree(i,0,len);
    DFS(0);
    return 0;
}
