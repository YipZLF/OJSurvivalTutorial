#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXT=1100;
int ans[MAXT];

int main()
{
    int T,M,t,v;
    memset(ans,0,sizeof(ans));
    scanf("%d %d",&T,&M);
    while(M--){
        scanf("%d %d",&t,&v);
        for(int i = T;i>=t;i--)
            ans[i] = max(ans[i],ans[i-t]+v);
    }
    printf("%d",ans[T]);
    return 0;
}
