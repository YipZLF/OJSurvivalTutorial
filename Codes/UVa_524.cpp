#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN = 16;
int n;
bool isp[MAXN*2],vis[MAXN];
int A[MAXN];

bool isPrime(int num){
    for(int i = 2;i*i<=num;++i){
        if(num%i==0){
            return false;
        }
    }
    return true;
}

void dfs(int cur){
    if(cur == n  && isp[A[0]+A[n-1]]){
        for(int i =0;i<n;++i){
            printf("%d ",A[i]);
        }
        printf("\n");
    }
    for(int k = 2; k <=n;++k){
        if(!vis[k] && isp[A[cur-1]+k]){
            A[cur] = k;
            vis[k] = true;
            dfs(cur+1);
            vis[k] = false;
        }
    }
}

int main(){
    isp[1] = true;
    isp[2] = true;
    for(int i = 3; i< MAXN*2; ++i){
        isp[i] = isPrime(i);
    }
    A[0] = 1;
    int k = 1;
    while(scanf("%d",&n)!=EOF){
        memset(vis,0,sizeof(vis));
        printf("Case %d:\n",k++);
        dfs(1);
        printf("\n");
    }

}