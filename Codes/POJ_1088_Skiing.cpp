#include<iostream>
#include<cstring>
#include<cstdio>
#define INF 0x7f
using namespace std;
const int MAX= 110;
int field[MAX][MAX],sol[MAX][MAX];

//right -> down -> left -> up
int dp(int i,int j)
{
    int tmp = -1,longestRoot = -1;
    int curHeight = field[i][j];
    if(sol[i][j] > 0)
        return sol[i][j];
    else{
        if(field[i][j+1] < curHeight){
            tmp = dp(i,j+1) + 1;
            longestRoot = (tmp>longestRoot)?tmp:longestRoot;
        }
        if(field[i-1][j] < curHeight){
            tmp = dp(i-1,j) + 1;
            longestRoot = (tmp>longestRoot)?tmp:longestRoot;
        }
        if(field[i][j-1] < curHeight){
            tmp = dp(i,j-1) + 1;
            longestRoot = (tmp>longestRoot)?tmp:longestRoot;
        }
        if(field[i+1][j] < curHeight){
            tmp = dp(i+1,j) + 1;
            longestRoot = (tmp>longestRoot)?tmp:longestRoot;
        }
        if(tmp == -1)
            longestRoot = 1;
        sol[i][j] = longestRoot;
        return sol[i][j];
    }
}

int main()
{
    freopen("1088.in","r",stdin);
    int R,C;
    scanf("%d %d",&R,&C);
    memset(field,INF,sizeof(field));
    memset(sol,-1,sizeof(sol));

    for(int i = 1;i<=R;i++){
        for(int j = 1;j<=C;j++){
            scanf("%d",&field[i][j]);
        }
    }



    int ans = -1;
    for(int i = 1;i<=R;i++){
        for(int j = 1;j<=C;j++){
            sol[i][j] = dp(i,j);
            if(sol[i][j]>ans)
                ans = sol[i][j];
        }
    }
    printf("%d",ans);
    return 0;
}
