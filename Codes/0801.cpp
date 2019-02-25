#include<iostream>
#include<cstdio>
using namespace std;
int A[10010];

void sort(int left, int right){
    for(int i = left; i <= right; ++i){
        bool flag= false;
        int tmp= 0 ;
        for(int j = right;j>=i;j--){
            if(A[j]<A[j-1]){
                tmp = A[j];
                A[j] = A[j-1];
                A[j-1] = tmp;
                flag = true;
            }
        }
        if(flag==false)
            break;
    }
}

int main(){
    int N;
    scanf("%d",&N);
    for(int i = 0 ; i < N ;++i){
        scanf("%d",A+i);
    }
    sort(0,N-1);
    if(N%2==0){
        printf("%1f\n",((float)A[N/2]+A[N/2-1])/2);
    }else{
        printf("%d\n",A[N/2]);
    }
    return 0;
}