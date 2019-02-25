#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
const int MAXN = 100100;
vector<int> G[MAXN];
int s[MAXN],e[MAXN],N,M;
bool A[MAXN*2];

struct node{
    int left,right;
    int apple;
    int pL,pR;
    int Mid(){return (right+left)>>1;}
}tree[2*MAXN];

int cnt=0;
void buildTree(int root,int l,int r){
    tree[root].left = l;
    tree[root].right = r;
    tree[root].apple = (r-l)+1;
    if(l==r)
        return;
    tree[root].pL = ++cnt;
    buildTree(tree[root].pL,l,tree[root].Mid());
    tree[root].pR = ++cnt;
    buildTree(tree[root].pR,tree[root].Mid()+1,r);
}


void dfs(int root){
    s[root] = ++cnt;
    for(int i = 0; i < G[root].size();i++){
        dfs(G[root][i]);
    }
    e[root] = ++cnt;
}

int Query(int root,int l,int r){
    if(tree[root].left == l && tree[root].right == r){
        return tree[root].apple;
    }
    int mid = tree[root].Mid();
    if(r<=mid){
        return Query(tree[root].pL,l,r);
    }else if(mid< l){
        return Query(tree[root].pR,l,r);
    }else{
        return Query(tree[root].pL,l,mid)+Query(tree[root].pR,mid+1,r);
    }
}

void Update(int root,int idx){
    if(tree[root].left == idx && tree[root].right ==idx){
        if(A[idx]){
            tree[root].apple --;
        }else{
            tree[root].apple ++;
        }
        A[idx] = !A[idx];
        return ;
    }
    if(A[idx]){
        tree[root].apple --;
    }else{
        tree[root].apple ++;
    }
    int mid = tree[root].Mid();
    if(idx <= mid){
        Update(tree[root].pL,idx);
    }else{
        Update(tree[root].pR,idx);
    }
}

int main(){
    freopen("Apple.in","r",stdin);
    scanf("%d",&N);
    int a,b;
    for(int i = 0 ; i < N-1;i++){
        scanf("%d%d",&a,&b);
        G[a].push_back(b);
    }

    cnt=0;
    dfs(1);

    memset(A,true,sizeof(A));
    
    cnt=0;
    buildTree(0,1,2*N);

    scanf("%d",&M);
    for(int i = 0 ; i < M ; i++){
        char op[3];
        int idx;
        scanf("%s",op);
        scanf("%d",&idx);
        if(op[0]=='Q'){
            printf("%d\n",(Query(0,s[idx],e[idx]))/2);
        }else if(op[0]=='C'){
            Update(0,s[idx]);
            Update(0,e[idx]);
        }
    }
    return 0;
}




/*
int s[MAXN],e[MAXN],C[2*MAXN],N,M;
bool A[MAXN*2];

int lowbit(int x){
    return (-x)&x;
}

int cnt=0;
void dfs(int root){
    s[root] = ++cnt;
    for(int i = 0; i < tree[root].size();i++){
        dfs(tree[root][i]);
    }
    e[root] = ++cnt;
}

int addC(int idx){
    int ret = 0;
    for(int i = idx-lowbit(idx)+1; i <= idx;++i){
        ret += A[i];
    }
    return ret;
}

int Query(int idx){
    int ans = 0;
    for(int i =idx; i > 0; i-=lowbit(i)){
        ans += C[i];
    }
    return ans;
}

void Update(int idx){
    bool flag = A[idx];
    for(int i = s[idx]; i<=2*N;i+=lowbit(i) ){
        if(flag)
            C[i]--;
        else
            C[i]++;
    }
    for(int i = e[idx]; i<=2*N;i+=lowbit(i) ){
        if(flag)
            C[i]--;
        else
            C[i]++;
    }
    A[idx]= !A[idx];
}

int main(){
    freopen("Apple.in","r",stdin);
    scanf("%d",&N);
    int a,b;
    for(int i = 0 ; i < N-1;i++){
        scanf("%d%d",&a,&b);
        tree[a].push_back(b);
    }
    dfs(1);
    memset(A,true,sizeof(A));
    for(int i = 1; i<=2*N;++i){
        C[i] = addC(i);
    }
    scanf("%d",&M);
    for(int i = 0 ; i < M ; i++){
        char op[3];
        int idx;
        scanf("%s",op);
        scanf("%d",&idx);
        if(op[0]=='Q'){
            //printf("end:%d\n",(Query(s[idx]-1)));
            //printf("end:%d\n",(Query(e[idx])));
            printf("end:%d\n",(Query(e[idx])-Query(s[idx]-1))/2);
        }else if(op[0]=='C'){
            Update(idx);
            
        }
    }
    return 0;
}

*/







/*
const int MAX = 1000100;
vector<int> tree[MAX];
int Start[MAX],End[MAX],C[2*MAX];
bool A[MAX];

// iter : the time when current node is searched
int dfs(int node,int & iter){
    Start[node] = iter;
    for(int i = 0;i<tree[node].size();i++){
        iter++;
        dfs(tree[node][i],iter);
    }
    End[node] = ++iter;
}

int lowbit(int x){
    return x&(-x);
}

int query(int k, int * C){
    int sum = 0;
    for(int i = k ; i>0 ; i = i-lowbit(i)){
        sum += C[i];
    }
    return sum;
}

void change(int k, int * C,const int & Size){
    if(!A[k]){  //i exists apple
        A[k] = true;
        for(int i = Start[k]; i <= 2*Size;i = i+lowbit(i)){
            C[i] -= 1;
        }
        for(int i = End[k]; i <= 2*Size;i = i+lowbit(i)){
            C[i] -= 1;
        }
    }else if(A[k]){
        A[k] = false;
        for(int i = Start[k]; i <= 2*Size;i = i+lowbit(i)){
            C[i] += 1;
        }
        for(int i = End[k]; i <= 2*Size;i = i+lowbit(i)){
            C[i] += 1;
        }
    }
}

int main()
{
    freopen("Apple.in","r",stdin);
    int N,u,v,M;
    char action;
    scanf("%d",&N);
    for(int i = 0;i < N-1; i++){
        scanf("%d %d",&u,&v);
        tree[u].push_back(v);
    }
    int iter = 1;
    dfs(1,iter);
//construct TreeArray
    for(int i = 1; i<=2*N;i++){
        C[i] = lowbit(i);
    }

    scanf("%d\n",&M);
    while(M--){
        scanf("%c %d\n",&action,&u);
        if(action=='Q'){
            printf("%d\n",
                   (query(End[u],C)-query(Start[u]-1,C))/2);

        }else if(action=='C'){
            change(u,C,N);
        }
    }
    return 0;
}




*/