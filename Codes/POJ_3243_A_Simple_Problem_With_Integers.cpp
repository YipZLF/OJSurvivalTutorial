/*
#include<iostream>
#include<cstdio>
#define DEBG 0
using namespace std;


//inc 是这个节点的【子节点】需要在sum里面加入的数。inc不需要加入到【本节点】。
struct Node{
    int L,R;
    long long sum,inc;
    int pLeft,pRight;
    int Mid(){return (L+R)/2;}
};
Node tree[200100];
int _count = 0;

void buildTree(int curNode, int left,int right)
{
    tree[curNode].L = left;
    tree[curNode].R = right;
    tree[curNode].sum = 0;
    tree[curNode].inc = 0;
    if(left == right){
        return ;
    }
    _count++;
    tree[curNode].pLeft = _count;
    _count++;
    tree[curNode].pRight = _count;
    buildTree(tree[curNode].pLeft,left,tree[curNode].Mid());
    buildTree(tree[curNode].pRight,tree[curNode].Mid()+1,right);
}

void Insert(int curNode,int idx,int num)
{
    if(tree[curNode].L == tree[curNode].R){
        tree[curNode].sum = num;
        return ;
    }
    tree[curNode].sum += num;
    if(idx<=tree[curNode].Mid()){
        Insert(tree[curNode].pLeft,idx,num);
    }else{
        Insert(tree[curNode].pRight,idx,num);
    }
}

int Add(int curNode,int left,int right, int inc)
{
    if(left == tree[curNode].L && right == tree[curNode].R){
        tree[curNode].inc += inc;
        return 0;
    }
    tree[curNode].sum += (right-left+1) * inc;
    if( right <= tree[curNode].Mid()){
        Add(tree[curNode].pLeft,left,right,inc);
    }else if(tree[curNode].Mid() < left){
        Add(tree[curNode].pRight,left,right,inc);
    }else{
        Add(tree[curNode].pLeft,left,tree[curNode].Mid(),inc);
        Add(tree[curNode].pRight,tree[curNode].Mid()+1,right,inc);
    }
}

long long querySum(int curNode, int left, int right)
{
    #ifdef DEBUG
        cout<<tree[curNode].L<<" ** "<<tree[curNode].R<<endl;
        cout<<left<<' '<<right<<endl;
    #endif // DEBUG
    if(left == tree[curNode].L && right == tree[curNode].R){
        return tree[curNode].sum + (right - left + 1) * tree[curNode].inc;
    }else{
        tree[curNode].sum += (tree[curNode].R-tree[curNode].L+1)*tree[curNode].inc;
        tree[tree[curNode].pLeft].inc += tree[curNode].inc;
        tree[tree[curNode].pRight].inc += tree[curNode].inc;
        tree[curNode].inc = 0;
        if(right <= tree[curNode].Mid()){
            return querySum(tree[curNode].pLeft,left,right);
        }
        else if(tree[curNode].Mid()<left){
            return querySum(tree[curNode].pRight,left,right);
        }
        else{
            return querySum(tree[curNode].pLeft,left,tree[curNode].Mid()) +
                    querySum(tree[curNode].pRight,tree[curNode].Mid()+1,right);
        }
    }
}

int main()
{
    freopen("3243.in","r",stdin);
    int n,q,a;
    int i,j,k;
    char cmd[10];
    scanf("%d%d",&n,&q);
    _count = 0;
    buildTree(0,1,n);
    for(i = 0; i<n;i++){
        scanf("%d",&a);
        //Insert(0,i+1,a);
        Add(0,i+1,i+1,a);
    }
    while(q--){
        int left,right,inc;
        scanf("%s",cmd);
        if(cmd[0] =='Q'){
            scanf("%d%d",&left,&right);
            printf("%lld\n",querySum(0,left,right));
        }else{
            scanf("%d%d%d",&left,&right,&inc);
            Add(0,left,right,inc);
        }
    }
    return 0;
}*/

#include<iostream>
#include<cstdio>
using namespace std;
const int MAXN = 100100;
int cnt;
long long int ans;

struct node{
    long long int sum ,inc;
    int L,R;
    int pL,pR;
    int Mid(){
        return (L+R)>>1;
    }
}tree[2*MAXN];

void buildTree(int root, int left, int right){
    tree[root].L = left;
    tree[root].R = right;
    tree[root].sum = 0;
    tree[root].inc = 0;
    if(left == right)
        return ;
    tree[root].pL = ++cnt;
    tree[root].pR = ++cnt;
    buildTree(tree[root].pL,left,tree[root].Mid());
    buildTree(tree[root].pR,tree[root].Mid()+1,right);
}

void Add(int root, int s, int e, int incr){
    if(tree[root].L==s && tree[root].R==e){
        tree[root].inc += incr;
        return;
    }
    tree[root].sum += incr * (e-s +1);
    if(e<=tree[root].Mid()){
        Add(tree[root].pL,s,e,incr);
    }else if(tree[root].Mid()<s){
        Add(tree[root].pR,s,e,incr);
    }else{
        Add(tree[root].pL,s,tree[root].Mid(),incr);
        Add(tree[root].pR,tree[root].Mid()+1,e,incr);
    }
    
}

void Query(int root ,int s,int e){
    if(tree[root].L == s && tree[root].R == e){
        ans += tree[root].sum + (tree[root].R-tree[root].L+1) * tree[root].inc;
    }else{
        tree[root].sum += (tree[root].R-tree[root].L+1) * tree[root].inc;
        tree[tree[root].pL].inc += tree[root].inc;
        tree[tree[root].pR].inc += tree[root].inc;
        tree[root].inc = 0;

        if(e<=tree[root].Mid()){
            Query(tree[root].pL,s,e);
        }else if(tree[root].Mid()+1<=s){
            Query(tree[root].pR,s,e);
        }else{
            Query(tree[root].pL,s,tree[root].Mid());
            Query(tree[root].pR,tree[root].Mid()+1,e);
        }
    }
}

int main (){
    freopen("3243.in","r",stdin);
    int N ,Q;
    int val;
    char op[3];
    int a,b,c;
    scanf("%d%d",&N,&Q);
    buildTree(0,1,N);
    for(int i = 1; i <= N ; ++i){
        scanf("%d",&val);
        Add(0,i,i,val);
    }
    for (int i =0 ; i < Q; ++i){
        ans = 0;
        scanf("%s",op);
        if(op[0]=='Q'){
            scanf("%d%d",&a,&b);    
            Query(0,a,b);
            printf("%lld\n",ans);
        }else if (op[0]=='C'){
            scanf("%d%d%d",&a,&b,&c);
            Add(0,a,b,c);
        }
    }
}