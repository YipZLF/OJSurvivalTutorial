#include<iostream>
#include<queue>
#include<cstdio>
#include<cstring>

using namespace std;
const int INF = 999999999;
int G[300][300];
int Layer[300];
bool Visited[300];
int n,m;

bool CountLayer(){
    int layer = 0; 
    deque<int> q;
    memset(Layer, 0xff,sizeof(Layer));
    Layer[1] = 0 ; q.push_back(1);
    while(!q.empty()){
        int v = q.front();q.pop_front();
        for(int j= 1; j<=m ;j++){
            if(G[v][j]>0 && Layer[j]==-1){
                Layer[j] = Layer[v]+1;
                if(j==m)
                    return true;
                else
                    q.push_back(j);
            }
        }
    }

        return false;
}

int Dinic(){
    int i,s,nMaxFlow = 0;
    deque<int> q;
    while(CountLayer()){
        q.push_back(1);
        memset(Visited,0,sizeof(Visited));
        Visited[1] = 1;
        while(!q.empty()){
            int nd = q.back();
            if(nd==m){
                int nMinC = INF;
                int nMinC_vs;
                for(int i = 1; i <q.size();i++){
                    int vs = q[i-1];
                    int ve = q[i];
                    if(G[vs][ve]>0){
                        if(nMinC>G[vs][ve]){
                            nMinC = G[vs][ve];
                            nMinC_vs = vs;
                        }
                    }
                }
                        nMaxFlow += nMinC;
                        for(i =1; i<q.size();++i){
                            int vs= q[i-1];
                            int ve = q[i];
                            G[vs][ve]-=nMinC;
                            G[ve][vs]+=nMinC;
                        }
                        while(!q.empty()&& q.back()!=nMinC_vs){
                            Visited[q.back()] = 0;
                            q.pop_back();
                        }
            }else{
                for(i = 1; i<=m;++i){
                    if(G[nd][i]>0 && Layer[i]==Layer[nd]+1 && !Visited[i]){
                        Visited[i] = true;
                        q.push_back(i);
                        break;
                    }
                }
                if(i>m)
                    q.pop_back();
            }
        }
    }
    return nMaxFlow;
}
/*
int Augment(){
    int v;
    int i;
    deque<int> q;
    memset(Prev, 0 ,sizeof(Prev));
    memset(Visited,0,sizeof(Visited));
    Prev[1] = 0;
    Visited[1] = true;

    q.push_back(1);
    bool bFindPath = false;
    while(!q.empty()){
        v = q.front();q.pop_front();
        for(int i =1; i <= m ;i++){
            if(G[v][i]>0 && Visited[i]==false){
                Prev[i] = v;
                Visited[i] = true;
                if(i==m){
                    bFindPath = true;
                    q.clear();
                    break;
                }else{
                    q.push_back(i);
                }
            }
        }
    }
    if(!bFindPath){
        return 0;
    }else{
        int nMinFlow = 99999999;
        v = m;
        while(Prev[v]){
            nMinFlow = min(nMinFlow,G[Prev[v]][v]);
            v = Prev[v];
        }
        v = m;
        while(Prev[v]){
            G[Prev[v]][v] -= nMinFlow;
            G[v][Prev[v]] += nMinFlow;
            v = Prev[v];
        }
        return nMinFlow;
    }
}
*/
int main(){
    freopen("1273.in","r",stdin);
    while(scanf("%d%d",&n,&m)!=EOF){
        int i,j,k;
        int s,e,c;
        memset(G,0,sizeof(G));
        for(i = 0 ;i < n ; i++){
            cin>>s>>e>>c;
            G[s][e]+=c;
        }
        cout<<Dinic()<<endl;
    }
}