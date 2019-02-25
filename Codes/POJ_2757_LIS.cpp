#include<iostream>
#include<cstdio>
using namespace std;
const int MAXN = 300100;
const int INF = 0x0ffffff0;
int LIS[MAXN];
long long int a[MAXN];
long long int low[MAXN];

/*
//nlogn
//本质上是贪心,low[i]是长度为i的LIS的最后一个元素的最小值
//尽可能小地增大LIS最后一个元素，这样比较容易往后接
int binary_search(int val,int s,int e){
    int mid;
    while(s<=e){
        mid = (s+e)>>1;
        if(low[mid]<val)
            s=mid+1;
        else
            e=mid-1;
    }
    return s;
}

int main(){
    freopen("LIS.in","r",stdin);
    int n;
    scanf("%d",&n);
    for(int i = 0 ; i < n;i++){
        scanf("%lld",a+i);
        low[i] = INF;
    }
    int ans = 0;
    low[0] = a[0];
    for(int i = 1; i < n; i++){
        if(a[i]>low[ans]){
            ans ++;
            low[ans] = a[i];
        }else{
            low[binary_search(a[i],0,ans)]=a[i];
        }
    }
    printf("%d\n",ans+1);
    return 0;
}
*/

/*
// 最简单的动态规划n^2
int main(){
    freopen("LIS.in","r",stdin);
    int n;
    scanf("%d",&n);
    for(int i = 0 ; i < n;i++){
        scanf("%lld",a+i);
        LIS[i] = 1;
    }
    for(int i =0 ; i < n ; i++){
        for(int j = 0 ; j <i;j++){
            if(a[j]<a[i])
                LIS[i] = max(LIS[i],LIS[j]+1);
        }
    }
    printf("%d\n",LIS[n-1]);
    return 0;
}
*/