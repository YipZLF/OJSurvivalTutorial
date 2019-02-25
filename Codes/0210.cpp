#include<iostream>
#include<cstdio>
using namespace std;
bool vis[26];
int R,C;
char map[21][21];
int maxpos = -1;
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};

void dfs(int x,int y, int step){
    if(step > maxpos){
        maxpos = step;
    }
    for(int i = 0 ; i < 4; ++i){
        int _x = x+dx[i];
        int _y = y+dy[i];
        if(_x<0 || _x >=R || _y < 0|| _y >=C)
            continue;
        if(vis[map[_x][_y]-'A'] == false){
            vis[map[_x][_y]-'A']=true;
            dfs(_x,_y,step+1);
            vis[map[x][y]-'A']=false;
        }
    }
    return ;
}

int main(){
    scanf("%d%d",&R,&C);
    for(int i = 0 ; i < R; i++){
        scanf("%s",map[i]);
    }
    vis[map[0][0]-'A'] == true;
    dfs(0,0,1);
    printf("%d\n",maxpos);
    return 0;
}