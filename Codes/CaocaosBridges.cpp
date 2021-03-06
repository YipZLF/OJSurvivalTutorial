#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<stack>
#define INF 0x7ffffff
using namespace std;
const int MAXN = 1100;

struct edge{
    int to,id,weight;
    edge(int _to,int _id,int _weight)
        {to = _to;id = _id; weight = _weight;}
};

vector<edge> G[MAXN];
int dfn[MAXN],low[MAXN];
int idx = 0,edgeID = 0;
int N,M,ans=INF;

void Tarjan(int u,int fatherEdge)
{
    dfn[u] = low[u] = ++idx;
    for(int i = 0 ; i < G[u].size()  ;i++){
        int v = G[u][i].to;
        if(!dfn[v]){
            Tarjan(v,G[u][i].id);
            low[u] = min(low[u],low[v]);
        }else if( G[u][i].id!=fatherEdge )
            low[u] = min(low[u],dfn[v]);
        if(dfn[u]<low[v])
            ans = min(ans,G[u][i].weight);
    }
    return ;
}

int main()
{

    freopen("CaocaosBridge.in","r",stdin);
    while(scanf("%d %d",&N,&M)==2){
        if(N==0 && M ==0) break;
    /* initialize*/
        idx = 0;
        edgeID = 0;
        ans = INF;
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        for(int i = 1;i<=N;i++){
            G[i].clear();
        }
        int W;

        while(M--){
            int U,V,W;
            scanf("%d %d %d",&U,&V,&W);
            edgeID ++;
            struct edge _u(U,edgeID,W),_v(V,edgeID,W);
            G[U].push_back(_v);
            G[V].push_back(_u);
        }

        Tarjan(1,0);

        if(ans>=INF)
            cout<<-1<<endl;
        else if(idx<N)
            cout<<0<<endl;
        else if(ans == 0)
            cout<<1<<endl;
        else
            cout<<ans<<endl;

    }
    return 0;
}

