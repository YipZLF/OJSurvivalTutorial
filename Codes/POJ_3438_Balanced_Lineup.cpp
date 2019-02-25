/*
下标序号不要搞错
*/
/*
#include<iostream>
#include<cstdio>
using namespace std;
const int INF = 0x0ffffff0;
int maxV = -INF, minV = INF;

struct Node{
    int L,R;
    int maxV, minV;
    int Mid(){return (L+R)/2;}
};
Node tree[202000];

void buildTree(int curNode, int left,int right)
{
    tree[curNode].L = left;
    tree[curNode].R = right;
    tree[curNode].maxV = -INF;
    tree[curNode].minV = INF;
    if(left != right){
        buildTree(curNode*2+1, left, (left+right)/2);
        buildTree(curNode*2+2, (left+right)/2+1,right);
    }
}


int change(int curNode,int i, int updatedVal)
{
    if(tree[curNode].L == tree[curNode].R){
        tree[curNode].minV = tree[curNode].maxV = updatedVal;
        return 0;
    }
    tree[curNode].minV=min(tree[curNode].minV,updatedVal);
    tree[curNode].maxV=max(tree[curNode].maxV,updatedVal);
    if( i<= tree[curNode].Mid())
        change(2* curNode +1,i,updatedVal);
    else
        change(2* curNode +2, i,updatedVal);
}

void Query(int curNode, int left, int right)
{
    if(tree[curNode].minV>=minV && tree[curNode].maxV<=maxV){
        return ;
    }
    if(left == tree[curNode].L && right == tree[curNode].R){
        maxV = max(tree[curNode].maxV,maxV);
        minV = min(tree[curNode].minV,minV);
        return ;
    }else{
        if(right <= tree[curNode].Mid())
            Query(curNode*2+1,left,right);
        else if(tree[curNode].Mid()<left)
            Query(curNode*2+2,left,right);
        else{
            Query(curNode*2+1,left,tree[curNode].Mid());
            Query(curNode*2+2,tree[curNode].Mid()+1,right);
        }
    }
}

int main()
{
    freopen("3438.in","r",stdin);
    int n,q,h;
    int i,j,k;
    scanf("%d %d",&n,&q);
    buildTree(0,1,n);
    for(i = 0; i<n;i++){
        scanf("%d",&h);
        change(0,i+1,h);
    }
    while(q--){
        int left,right;
        scanf("%d %d",&left,&right);
        minV = INF;
        maxV = -INF;
        Query(0,left,right);
        printf("%d\n",maxV-minV);
    }
    return 0;
}
*/
#include<iostream>
#include<cstdio>
using namespace std;

const int INF = 0x0ffffff0;
const int MAXN = 50020;
int minVal,maxVal;

struct node{
    int L,R;
    int minV,maxV;
    node(){
        L = R = -1;minV = INF;maxV = -INF;
    }
    int Mid(){
        return (L+R)>>1;
    }
}tree[4*MAXN];

void buildTree(int root, int left,int right){
    int mid = (left + right)>>1;
    tree[root].L = left;
    tree[root].R = right;
    if(left != right){
        buildTree(root*2 +1,left,mid);
        buildTree(root*2 +2,mid+1,right);
    }
}

void Insert(int root, int idx, int val){
    if(tree[root].L == tree[root].R ){
        tree[root].minV = tree[root].maxV = val;
        return;
    }else{
        int mid = (tree[root].Mid());
        tree[root].minV = min(val,tree[root].minV);
        tree[root].maxV = max(val,tree[root].maxV);
        if(idx<=mid){
            Insert(root*2+1,idx,val);
        }else{
            Insert(root*2+2,idx,val);
        }
    }
}

void Query(int root, int s,int e){
    if(tree[root].minV>minVal &&tree[root].maxV<maxVal){
        return;
    }//这一步可以减少很多搜索的时间
    if(tree[root].L==tree[root].R){
        minVal = min(minVal,tree[root].minV);
        maxVal = max(maxVal,tree[root].maxV);
        return ;
    }else{
        if(e<= tree[root].Mid()){
            Query(root*2+1,s,e);
        }else if(tree[root].Mid() < s){
            Query(root*2+2,s,e);
        }else{
            Query(root*2+1,s,tree[root].Mid());
            Query(root*2+2,tree[root].Mid()+1,e);
        }
    }
}

int main(){
    freopen("3438.in","r",stdin);
    int N, Q,height;
    int s,e;
    scanf("%d %d",&N,&Q);
    buildTree(0,1,N);
    for(int i = 1 ; i <= N ; ++i){
        scanf("%d",&height);
        Insert(0,i,height);

    }
    for(int i = 0 ;i < Q ; ++i){
        minVal = INF;
        maxVal = -INF;

        scanf("%d%d",&s,&e);
        Query(0,s,e);
        printf("%d\n",maxVal-minVal);
    }
}