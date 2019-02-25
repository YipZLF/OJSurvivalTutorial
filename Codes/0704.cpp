#include<stdio.h>
#include<string.h>
#include<queue>
#include<iostream>
#define MAXN 110
using namespace std;
int N,M,S;
double V;

struct edge{
    int a,b;
    double c,r;
    edge(){
        a = b = c = r = 0;
    }
}point[2*MAXN];
double sum[MAXN];
int change[MAXN];
bool vis[MAXN];

bool SPFA(int S){
    for(int i = 1; i<=N ; ++i){
        sum[i] = 0;
    }
    sum[S] = V;

    queue<int> qe;
    qe.push(S);
    vis[S] = true;
    while(!qe.empty()){
        int u = qe.front(); qe.pop();
        vis[u] = false;
        for(int j = 0 ; j < M*2 ;++j){
            if(u==point[j].a){
                int a = point[j].a;
                int b = point[j].b;
                if(sum[b]<(sum[a]-point[j].c)*point[j].r){
                    sum[b] = (sum[a]-point[j].c)*point[j].r;
                    if(!vis[b]){
                    qe.push(b);
                    vis[b] = true;
                }
                    change[b]++;
                    if(change[b]>=N)
                        return false;
                }

                }
            }
    }
    return true;
}


int main()
{
    freopen("0704.in","r",stdin);
    scanf("%d %d %d %lf",&N,&M,&S,&V);
    for(int i = 0 ; i < 2 * M;i+=2){
        int a,b,r,c;
        scanf("%d %d",&a,&b);
        scanf("%lf %lf",&point[i].r,&point[i].c);
        scanf("%lf %lf",&point[i+1].r,&point[i+1].c);
        point[i].a = a;
        point[i].b = b;
        point[i+1].a = b;
        point[i+1].b = a;
    }
    if(SPFA(S)){
        printf("NO\n");
    }else{
        printf("YES\n");
    }
    return 0;
}
/*
bool Bellman(int start)
{
    //init
    for(int i = 1 ; i <= N;++i){
        if(i == start)
            sum[i] = V;
        else
            sum[i] = 0;
    }

    //start
    for(int i = 1 ; i <= N-1; ++i){
        for ( int j = 0 ; j < 2 * M ; ++j){
            int a = point[j].a;
            int b = point[j].b;
            if(sum[a]>0){
                sum[b] = max(sum[b],(sum[a]-point[j].c)*point[j].r);
            }
        }
    }
    for(int j = 0 ; j<2 *M ; ++j){
        int a = point[j].a;
        int b = point[j].b;
        if(sum[b]<(sum[a]-point[j].c)*point[j].r){
                return false;
        }

    }
    return true;
}

*/
