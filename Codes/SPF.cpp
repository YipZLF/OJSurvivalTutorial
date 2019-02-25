#include<iostream>
#include<cstdio>
#include<vector>
#include<set>
#include<cstring>
#include<stack>
#define INF 0x7ffffff
using namespace std;
const int MAXN = 1100;

struct edge{
    int to;
    bool isVisited;
    edge(int _to)
        {to = _to;isVisited = false;}
};

vector<edge> G[MAXN];
set<int> ANS;
int dfn[MAXN],low[MAXN];
int idx = 0,nodeNum = 0;

void Tarjan(int u,int father)
{
    dfn[u] = low[u] = ++idx;

    for(int i = 0 ; i < G[u].size()  ;i++){
        int v = G[u][i].to;
        if(!dfn[v]){

            int j = 0;
            for(j = 0; j<G[v].size();j++)
                {if(G[v][j].to==u) break;}
            G[v][j].isVisited = true;
            G[u][i].isVisited = true;

            Tarjan(v,u);
            low[u] = min(low[u],low[v]);
        }else if( v !=father )
            low[u] = min(low[u],dfn[v]);
        if(dfn[u] <= low[v]){    //u is a cut vertice
            ANS.insert(u);
        }
    }
    return ;
}

bool DFS(int &start, int u,int idx){
    bool flag = true;
    if(G[u][idx]==start)
        flag = true;
    for
}

int main()
{

    freopen("SPF.in","r",stdin);
    int number = 0;
    int u,v;
        while(scanf("%d",&u)){
            if(u==0){
                if(v == 0) break;

                printf("Network #%d\n",++number);
                Tarjan(1,0);
                for(set<int>::iterator i = ANS.begin(); i!=ANS.end();i++)
                    cout<<(*i)<<endl;
                bool AnsExists = false;
                for(set<int>::iterator i = ANS.begin(); i!=ANS.end();i++){
                    int cnt= 0;
                    for(int j = 0; j < G[(*i)].size();j++){
                        if(G[(*i)][j].isVisited) cnt++;
                    }
                    if(cnt>=2){
                        AnsExists = true;
                        printf("  SPF node %d leaves %d subnets\n",(*i),cnt);
                    }
                }
                if(!AnsExists)
                printf("  No SPF nodes\n");
                printf("\n");
                /* initialize for next loop*/
                for(int i = 1;i<=idx;i++){
                    G[i].clear();
                }
                ANS.clear();
                idx = 0;
                v = 0;
                memset(dfn,0,sizeof(dfn));
                memset(low,0,sizeof(low));

                continue;
            }

            scanf("%d",&v);
            struct edge _u(u),_v(v);
            G[u].push_back(_v);
            G[v].push_back(_u);

        }

    return 0;
}

