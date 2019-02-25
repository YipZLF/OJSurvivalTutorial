#include<iostream>
#include<cstdio>
int minl=0xffff;
char map[5][5];
int dx[5]={0,1,-1,0,0};
int dy[5]={0,0,0,1,-1};
int t;

void flip(int x,int y){
    for(int i = 0;i<5;++i){
        int _x = x+dx[i];
        int _y = y+dy[i];
        if(_x<0 || _y<0 || _x>=4 || _y >=4)
            continue;
        if(map[_x][_y]=='b')
            map[_x][_y]='w';
        else
            map[_x][_y]='b';
    }
}

bool check(){
    int i , j;
    for(i = 0 ; i<4;++i){
        for(j = 0; j<4;++j){
            if(map[i][j]!=map[0][0])
                return false;
        }
    }
    return true;
}

void dfs(int x, int y, int step){
    if(check()){
        minl = std::min(minl,step);
        return ;
    }
    if(x >=4) 
        return;
    
    flip(x,y);
    if(y==3)
        dfs(x+1,0,step+1);
    else
        dfs(x,y+1,step+1);
    
    flip(x,y);
    if(y==3)
        dfs(x+1,0,step);
    else
        dfs(x,y+1,step);
}

int main(){
    int i;
    for(i=0;i<4;++i){
        scanf("%s",map[i]);
    }
    dfs(0,0,0);
        printf("%d\n",minl);
    if(minl<=16){
    }
    else printf("Impossible\n");
}