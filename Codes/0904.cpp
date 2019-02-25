#include<iostream>
#include<cstdio>
using namespace std;
const int MAXN=500010;
int a[MAXN],b[MAXN];
long long ans;
void mergeSort(int left,int right){
    if(right-left < 1){
        return ;
    }
    int mid = (right+left)>>1;
    mergeSort(left,mid);
    mergeSort(mid+1,right);
    int pl = left ,pr = mid+1, x = left;
    while(pl<=mid && pr <= right){
        if(a[pl]<= a[pr]){
            b[x++] = a[pl++];
        }else if(a[pl]> a[pr]){
            ans += mid-pl +1;
            b[x++] = a[pr++];
        }
    }
    while(pr<=right){
        b[x++] = a[pr++];
    }
    while(pl<=mid){
        b[x++] = a[pl++];
    }
    for(int i = left;i<=right;++i)
        {a[i] = b[i];}  
}

int main(){
    int n;
    while(scanf("%d",&n)&&n){
        ans = 0;
        for(int i = 1 ; i <= n;i++){
            scanf("%d",a+i);
        }
        mergeSort(1,n);
        printf("%lld\n",ans);
    }
    return 0;
}