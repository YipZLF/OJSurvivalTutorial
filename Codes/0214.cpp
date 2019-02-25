#include<iostream>
#include<cstdio>
using namespace std;

int dp(int m,int n){
    if(n==1 || m == 0||m==1)
        return 1;
    if(m<n)
        return dp(m,m);
    else
        return dp(m,n-1)+dp(m-n,n);
}

int main(){
    int t;
    cin>>t;
    while(t--){
        int n,m;
        cin>>m>>n;
        printf("%d\n",dp(m,n));
    }
}