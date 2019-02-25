#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<stack>
//#define DEBUG
#define TRIAL
using namespace std;
const int MAXN = 10100;

typedef vector<int> Edge;
Edge G[MAXN];
int dfn[MAXN],low[MAXN];
bool isInCurrentPath[MAXN];
int idx = 0, cnt = 0;
stack<int> st;

void Tarjan(int u){
    dfn[u] = low[u] = ++idx;
    isInCurrentPath[u] = true;
    st.push(u);

    for(int i = 0 ; i < G[u].size();i++){
        int v = G[u][i];
        if(!dfn[v]){
            Tarjan(v);
            low[u] = min(low[u],low[v]);
        }else if(isInCurrentPath[v]){
            low[u] = min(low[u],dfn[v]);
        }
    }

    if(dfn[u]==low[u]){
        cnt++;
        int v;
        while(st.top()!=u){
            v = st.top(); st.pop();
            isInCurrentPath[v] = false;

        #ifdef DEBUG
            cout<<v<<endl;
        #endif // DEBUG
        }
        v = st.top(); st.pop();
        isInCurrentPath[v] = false;
        #ifdef DEBUG
            cout<<"group: "<<cnt<<" no :"<<v<<endl;
        #endif // DEBUG
    }
    return ;
}

int main()
{

            #ifdef TRIAL
    freopen("GoingFromU2V.in","r",stdin);
            #endif
    int N,M,T;
    scanf("%d",&T);
    while(T--){
    /* initialize*/
        cnt = 0;
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));

        scanf("%d %d",&N,&M);
        while(M--){
            int from,to;
            scanf("%d %d",&from,&to);

            #ifdef DEBUG
            cout<<"I got from "<<from<<" to "<<to<<endl;
            #endif
            G[from].push_back(to);
        }
        for(int u = 1; u<=N;u++){
            if(!dfn[u])
                Tarjan(u);
        }
        if(cnt ==1)
            cout<<"Yes"<<endl;
        else
            cout<<"No"<<endl;

    }
    return 0;
}

