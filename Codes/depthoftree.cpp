#include<iostream>
#include<cstdio>
using namespace std;
int maxlength = -1;
struct node{
    int idx;
    int pL,pR;
};
struct node tree[11];

void DFS(int node,int depth){
    if(tree[node].pL != -1){
        DFS(tree[node].pL,depth+1);
    }
    if(tree[node].pR != -1){
        DFS(tree[node].pR,depth+1);
    }
    if(depth>maxlength)
        maxlength = depth;
    return ;
}

int main()
{
    int n ;
    cin>>n;
    for(int i = 1 ; i<=n;i++){
        scanf("%d %d",&tree[i].pL,&tree[i].pR);
    }
    DFS(1,1);
    printf("%d",maxlength);
}
