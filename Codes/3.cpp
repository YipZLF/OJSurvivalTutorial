#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
const int MAXN = 100100;
vector<int> tree[MAXN];
int s[MAXN],e[MAXN],C[2*MAXN],N,M;
bool A[MAXN*2];

int lowbit(int x){
    return (-x)&x;
}
int cnt = 0;
void dfs(int root){
    s[root] = ++cnt;
    for(int i = 0 ; i < tree[root].size();++i){
        dfs(tree[root][i]);
    }
    e[root]= ++cnt;
}

int addC(int idx){
    int ret = 0;
    for(int i = idx-lowbit(idx)+1;i<=idx;++i){
        ret += A[i];
    }
    return ret;
}

int Query(int idx){
    int ans = 0;
    for(int i = idx; i>0;i-=lowbit(i)){
        ans += C[i];
    }
    return ans;
}

void Update(int idx){
    bool flag = A[idx];
    for(int i = idx; i<=2*N;i+=lowbit(i)){
        if(flag)
            C[i]--;
        else
            C[i]++;
    }
    A[idx] = !A[idx];
}
int main(){
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
            printf("%d\n",(Query(e[idx])-Query(s[idx]-1))/2);
        }else if(op[0]=='C'){
            Update(s[idx]);
            Update(e[idx]);
            
        }
    }
    return 0;
}


bool SPFA(int s){
    for(int i = 1;i<=N;++i){
        sum[i] = 0;
    }
    sum[s] = V;
    queue<int> qe;
    qe.push(s);
    vis[s] = true;
    while(!qe.empty()){
        int u = qe.front();qe.pop();
        vis[u] = false;
        for(int j =0 ; j<2*M;j++){
            if(u==point[j].a){
                int a= point[j].a;
                int b= point[j].b;
                if(sum[b]<(sum[a]-point[j].c)*point[j].r){
                    sum[b] = lsdkjflksdjkafksd
                    if(!)
                }
            }
        }
    }
}