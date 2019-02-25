#include<iostream>
#include<cstdio>
using namespace std;
const int MAXN= 50050;
int N, K;
int parent[MAXN],rel[MAXN];

// 0(a,b) a==b; 1(a,b) a eats b; 2(a,b) b eats a;
int getRoot(int a){
    if(parent[a]==a){
        return a;
    }else{
        int tmp = getRoot(parent[a]);
        rel[a] = (rel[tmp] + rel[a]) %3;
        parent[a] = tmp;
        return parent[a];
    }
}

int main(){
    freopen("001.in","r",stdin);
    scanf("%d%d",&N,&K);
    for(int i = 1 ; i <= N ;i++){
        parent[i] = i;
        rel[i] =0;
    }
    int ans = 0;
    for(int i= 0 ; i<K;++i){
        int op, a , b; 
        scanf("%d%d%d",&op,&a,&b);
        if(a>N || b>N ||(op==2 && a==b)){
            ans++;
            continue;
        }
        int pa = getRoot(a);
        int pb = getRoot(b);
        if(op==1){
            if(pa==pb){
                if(rel[a]!=rel[b]){
                    ans++;
                }
            }else{
                parent[b] = pa;
            }
        }else if(op==2){
            if(pa==pb){
                if((rel[a]-rel[b]+3)%3!=1)
                    ans++;
            }else{
                parent[b] = pa;
                rel[pb] = (rel[a] +2 - rel[b]) %3;
            }
        }

    }
    cout<<ans<<endl;
}