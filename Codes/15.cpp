#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<stack>
using namespace std;
const int MAXN = 10100;
typedef vector<int> Edge;
Edge G[MAXN];
int dfn[MAXN],low[MAXN];
bool instack[MAXN];
int idx = 0,cnt =0;
stack<int> st;

void Tarjan(int u){
    dfn[u]=low[u] = ++idx;
    st.push(u);
    instack[u] =true;

    for(int i =0;i<G[u].size();i++){
        int v =G[u][i];
        if(!dfn[v]){
            Tarjan(v);
            low[u] = min(low[u],low[v]);
        }else if (instack[v]){
            low[u] = min(low[u],dfn[v]);
        }
    }

    if(dfn[u]==low[u]){
         cnt++;
        int v;
        do{
            v = st.top() ;st.pop();
            instack[v] = false;
        }while(v!=u);
    }
    return ;
}

int main(){
    freopen("GoingFromU2V.in","r",stdin);
    int N,M,T;
    scanf("%d",&T);
    while(T--){
        cnt = 0;
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        scanf("%d%d",&N,&M);
        while(M--){
            int from,to;
            scanf("%d%d",&from,&to);
            G[from].push_back(to);
        }
        for(int u =1; u<=N;u++){
            if(!dfn[u])
                Tarjan(u);
        }
        if(cnt ==1)
            cout<<"Yes\n";
        else
            cout<<"No\n";
        
    }
    return 0;
}