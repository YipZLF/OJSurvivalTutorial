#include<iostream>
#include<cstdio>
#include<vector>
#include<stack>
#define DEBUG
using namespace std;
const int MAXCOWS = 10100;

typedef vector<int> Edge;
Edge G[MAXCOWS];
int dfn[MAXCOWS],low[MAXCOWS],outDegree[MAXCOWS],Color[MAXCOWS],cnt[MAXCOWS];
bool isInCurrentPath[MAXCOWS];
int idx = 0, numColor = 0;
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
        numColor++;
        int v;
        while(st.top()!=u){
            v = st.top(); st.pop();
            isInCurrentPath[v] = false;
            Color[v] = numColor;
            cnt[numColor]++;

        #ifdef DEBUG
            cout<<v<<endl;
        #endif // DEBUG
        }
        v = st.top(); st.pop();
        isInCurrentPath[v] = false;
        Color[v] = numColor;
        cnt[numColor]++;
        #ifdef DEBUG
            cout<<v<<endl;
            cout<<"Color : "<<Color[v]<<endl;
            cout<<"Color cnt: "<<cnt[Color[v]]<<endl;
        #endif // DEBUG
    }
    return ;
}

int main()
{

            #ifdef DEBUG
    freopen("2186.in","r",stdin);
            #endif
    int N,M;
    scanf("%d %d",&N,&M);
    while(M--){
        int from,to;
        scanf("%d %d",&from,&to);
        G[from].push_back(to);
    }
    for(int u = 1; u<=N;u++){
        if(!dfn[u])
            Tarjan(u);
    }

    for(int u = 1 ; u <=N;u++){
        for(int j = 0;j<G[u].size();j++){
            #ifdef DEBUG
                cout<<"edge from "<<u<<" to "<<G[u][j]<<endl;
            #endif

            if(Color[u]!=Color[G[u][j]])
            {   outDegree[Color[u]]++;

            }
        }
    }

    int ans = 0,ansColor = 0;
    for(int i = 1 ; i <= numColor;i++){
        if(outDegree[i]==0)
            {ans++;ansColor = i;

            #ifdef DEBUG
                cout<<"answer color: "<<ansColor<<endl;
            #endif
            }
    }
    if(ans==1)
        printf("%d\n",cnt[ansColor]);
    else
        printf("0\n");
    return 0;
}
