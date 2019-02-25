#include<iostream>
#include<cstring>
#include<cstdio>
#define MAXN 30
using namespace std;
int path[MAXN][2],p,q;
bool vis[MAXN][MAXN],flag = false;

int dx[8] = {-1,1,-2,2,-2,2,-1,1};
int dy[8] = {-2,-2,-1,-1,1,1,2,2};

bool valid(int x,int y){
    if( 1 <= x && x <= p &&
        1 <= y && y <= q &&
        vis[x][y]== false &&
        flag==false )
        return true;
    else
        return false;
}

void DFS(int x,int y,int step){
    path[step][0] = x;
    path[step][1] = y;
    if(step == p*q){
        flag = true;
        return ;
    }
    for(int i= 0; i <8; i++){
        int xx = x + dx[i];
        int yy = y + dy[i];
        if(valid(xx,yy)){
            vis[xx][yy] = true;
            DFS(xx,yy,step+1);
            vis[xx][yy] = false;
        }
    }
}

int main()
{
    int n, cnt;
    scanf("%d",&n);
    for(cnt = 1; cnt<= n;cnt++){
        flag = false;
        memset(vis,0,sizeof(vis));

        scanf("%d %d",&p,&q);
        vis[1][1] = 1;
        DFS(1,1,1);

        printf("Scenario #%d:\n",cnt);
        if(flag){
            for(int i = 1 ; i <= q*p; i++){
                printf("%c%d",path[i][1]- 1 + 'A',path[i][0]);
            }
        }else{
            printf("impossible");
        }
        printf("\n\n");
    }
    return 0;
}
