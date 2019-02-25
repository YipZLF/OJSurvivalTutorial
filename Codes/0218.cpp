#include<iostream>
#include<cstdio>
using namespace std;

int main(){
    int M,N,m,n;
    cin>>N>>M;
    n = N; m = M;
    while(m > 4*(n-1)){
        m -= 4*(n-1);
        n -=2;
    }
    int r,c;
    if(1<= m && m<= n-1){
        r = 1;
        c = m;
    }
    if(n<= m && m<= 2*n-2){
        r = m - n + 1;
        c = n;
    }
    if(2* n - 1<= m&& m <= 3*n-3){
        r = n;
        c = n-(m - 2* n +1);
    }
    if( 3* n - 2<= m && m<= 4*n-4){
        r = n - (m - 3 * n + 2);
        c = 1;
    }
    r += (N-n)/2;
    c += (N-n)/2;
    printf("%d %d\n",r,c);
    return 0;
}