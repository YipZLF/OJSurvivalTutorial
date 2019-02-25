#include<iostream>
#include<cstdio>
using namespace std;
const int MAXN=100100;
int a[MAXN],ans[MAXN];
int cnt = 0 ;

struct node{
    int left,right;
    int len;
    int pL, pR;
}tree[MAXN*2];

void buildTree(int root,int s,int e){
    tree[root].left = s;
    tree[root].right = e;
    tree[root].len= (e-s)+1;
    if(s==e)
        return ;
    int mid = (e+s)>>1;
    cnt++;
    tree[root].pL = cnt;
    cnt++;
    tree[root].pR = cnt;

    buildTree(tree[root].pL,s,mid);
    buildTree(tree[root].pR,mid+1,e);
}

int Query(int root,int val){
    tree[root].len --;
    if(tree[root].left==tree[root].right){
        return tree[root].left;
    }
    
    int len = tree[tree[root].pL].len;
    if(len <= val){
        return Query(tree[root].pL,val);
    }else{
        return Query(tree[root].pR,val-len);
    }
}

int main(){

    freopen("2182.in","r",stdin);
    int N = 0 ;
    scanf("%d",&N);
    buildTree(0,1,N);

    a[1] = 0;
    for(int i = 2; i<=N;i++){
        scanf("%d",a+i);
    }
    for(int i = N; i>=1; i--){
        ans[i] = Query(0,a[i]+1);
    }
    for(int i = 1; i<=N;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}


/*#include<iostream>
#include<cstdio>
using namespace std;
const int MAXN=100100;
int a[MAXN],ans[MAXN];
int cnt = 0 ;

struct node{
    int L,R;
    int len;
    int pL,pR;
    node(){
        L=0;R=0;len = 0;pL=-1;pR = -1;
    }
    int Mid(){return (L+R)>>1;}
}tree[2* MAXN];

void buildTree(int root ,int left ,int right){
    tree[root].L = left;
    tree[root].R = right;
    tree[root].len = (right - left )+1;
    if(left==right)
        return;
    cnt++;
    tree[root].pL = cnt;
    cnt++;
    tree[root].pR = cnt;
    buildTree(tree[root].pL,left,tree[root].Mid());
    buildTree(tree[root].pR,tree[root].Mid()+1,right);
}

int Query(int root, int len){
    tree[root].len --;
    if(tree[root].L==tree[root].R ){
        return tree[root].L;
    }
    int lenL = tree[tree[root].pL].len;
    if(len <= lenL){
        return Query(tree[root].pL,len);
    }else{
        return Query(tree[root].pR,len-lenL);
    }
}



int main (){
    freopen("2182.in","r",stdin);
    int N;
    scanf("%d",&N);
    a[1] = 0;
    for(int i = 2 ; i <= N ; i++){
        scanf("%d",a+i);
    }
    buildTree(0,1,N);
    for(int i = N; i>=1;i--){
        ans[i] = Query(0,a[i]+1);
    }
    for(int i= 1; i <= N ; i++){
        printf("%d\n",ans[i]);
    }
}*/