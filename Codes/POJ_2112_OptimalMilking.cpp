#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x0ffffff
using namespace std;
int Dist[250][250],G[250][250],K,C,M,Layer[250],maxDist;
bool isVisited[250];

void Floyd(){
    for(int i = 1 ; i <= K + C; i++){
        for(int j = 1 ; j <= K + C; j++){
            for(int k = 1 ; k <= K + C; k++){
                int length = Dist[j][i]+Dist[i][k];
                if(length<Dist[j][k] && Dist[j][k] != 0 && Dist[i][k] != 0)
                    Dist[j][k] = length;
            }
        }
    }
}

void buildGraph(){
// 0 as t, K+C+1 as s
    for(int i = 1; i<=K;i++){
        G[0][i] = G[i][0] = M;
    }
    for(int i = K+1; i<=K+C; i++){
        G[K+C+1][i] = G[i][K+C+1] = 1;
    }
    memset(G,0x7f,sizeof(G));
}

bool CountLayer()
{
	int layer = 0;
    deque<int> q;
    memset(Layer,0xff,sizeof(Layer));
    Layer[K+C+1] = 0; q.push_back(0);
    while(!q.empty()){
        int v = q.front();q.pop_front();
        for(int j = K+C; j >= 0 ;--j){
            if(G[v][j]>0  && Layer[j]==-1){
                Layer[j] = Layer[v]+1;
                if(j==0)
                    return true;
                else
                    q.push_back(j);
            }
        }
    }
    return false;
}

int Dinic(int Start,int End)
{
    int i, s, nMaxFlow = 0;
    int v;
    deque<int> q;
    while(CountLayer()){
        q.push_back(Start);
        memset(isVisited,0,sizeof(isVisited));
        isVisited[Start] = true;
        while(!q.empty()){
            v = q.back();
            if(v != End){
                for(i = Start; i<=End;i++){
                    if(G[v][i]>0 && Layer[i] == Layer[v]+1 && isVisited[i] == false&& Dist[v][i] <= maxDist){
                        isVisited[i]=1;
                        q.push_back(i);
                        break;
                    }
                }
                if(i>End)
                    q.pop_back();
            }else{
                int ns,ne,minFlow =INF,minS;
                for(i = 1 ; i< q.size();i++){
                    ns = q[i-1];
                    ne = q[i];
                    if(G[ns][ne]>0){
                        if(minFlow>G[ns][ne]){
                            minFlow = G[ns][ne];
                        	minS = ns;
                        }
                    }
                }
                nMaxFlow += minFlow;
                for(int i = 1 ; i < q.size();i++){
                    int vs = q[i-1],ve =q[i];
                    G[vs][ve] -= minFlow;
                    G[ve][vs] += minFlow;


                }
                while(!q.empty() && q.back()!=minS){
                    isVisited[q.back()]=false;
                    q.pop_back();
                }
            }
        }
    }
    return nMaxFlow;
}


int main()
{
    freopen("2112.in","r",stdin);

    scanf("%d %d %d",&K,&C,&M);
    for(int i = 1 ; i <= K + C; i++){
        for(int j = 1 ; j <= K + C; j++){
            scanf("%d",&Dist[i][j]);
        }
    }

    for(int i = 1 ; i <= K + C; i++){
        for(int j = 1 ; j <= K + C; j++){
            printf("%d",Dist[i][j]);
        }
        putchar('\n');
    }
    Floyd();
    for(int i = 1 ; i <= K + C; i++){
        for(int j = 1 ; j <= K + C; j++){
            printf("%d",Dist[i][j]);
        }
        putchar('\n');
    }
}
/*if( (vs-ve) !=N && vs!=0 && ve!=2*N){
                        from[cnt]=vs;
                        to[cnt]=ve;
                        coop[cnt]=minFlow;
                        cnt++;
                    }*/
