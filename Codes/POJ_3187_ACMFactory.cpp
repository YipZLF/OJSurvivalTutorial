#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int maxn = 120,INF = 0xfffffff;


int G[maxn][maxn],G2[maxn][maxn],Layer[maxn],isVisited[maxn];
int from[maxn],to[maxn],coop[maxn],cnt=0;
struct node{
    int in[10],out[10];
    int per;
} P[maxn];
int Parts,N;

bool OK(int a,int b)
{
    bool flag = true;
    for(int i = 0;i<Parts;i++){
        if(P[a].out[i]!=P[b].in[i] && P[b].in[i] != 2){
            flag = false; break;
        }
    }
    return flag;
}



bool CountLayer()
{
	int layer = 0;
    deque<int> q;
    memset(Layer,0xff,sizeof(Layer));
    Layer[0] = 0; q.push_back(0);
    while(!q.empty()){
        int v = q.front();q.pop_front();
        for(int j = 0; j <= 2*N;j++){
            if(G[v][j]>0 && Layer[j]==-1){
                Layer[j] = Layer[v]+1;
                if(j==2 * N)
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
                    if(G[v][i]>0 && Layer[i] == Layer[v]+1 && isVisited[i] == false){
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
     freopen("ACMFactory.in","r",stdin);

    scanf("%d %d",&Parts,&N);
    for(int i = 1 ; i <= N; i++){
        scanf("%d",&P[i].per);
        for(int j = 0; j<Parts;j++){
            scanf("%d",&P[i].in[j]);
        }
        for(int j =0 ; j<Parts;j++){
            scanf("%d",&P[i].out[j]);
        }
    }
    for(int i =0 ; i<Parts;i++){
        P[0].in[i]=P[0].out[i]=0;
        P[N+1].in[i]=P[N+1].out[i]=1;
    }
    P[0].per=P[N+1].per=INF;
    N++;
    for(int i = 0;i<=N;i++){
        for(int j = 0 ; j<=N ;j++){
            if(i==j){
                G[i+N][j]=P[j].per;
            }else if(OK(i,j)){
                G[i][j+N] = P[i].per;
            }
        }
    }
    memcpy(G2,G,sizeof(G));
    int maxFlow = Dinic(0,2*N);

    for(int i = 1 ; i< N;i++){
        for(int j = 1; j<N;j++){
            if(i==j)
                continue;
            else if (G2[i][j+N] > G[i][j+N]){
                from[cnt]=i;
                to[cnt]=j;
                coop[cnt]=G2[i][j+N] - G[i][j+N];
                cnt++;
            }
        }
    }

    printf("%d %d\n",maxFlow,cnt);

    for(int i = 0 ; i < cnt;i++){
        printf("%d %d %d\n",from[i],to[i],coop[i]);
    }

    return 0;
}
/*if( (vs-ve) !=N && vs!=0 && ve!=2*N){
                        from[cnt]=vs;
                        to[cnt]=ve;
                        coop[cnt]=minFlow;
                        cnt++;
                    }*/
