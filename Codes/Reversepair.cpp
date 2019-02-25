
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int A[500100],T[500100];
int64_t cnt = 0;

void merge_sort(int left,int right){
    if(right - left < 1)
        return;
    int mid = (left+right )/2;
    int l=left,r=mid+1,i = left;
    merge_sort(left,mid);
    merge_sort(mid+1,right);
    while(l<=mid && r <=right){
        if(A[l]<=A[r] || r>right )
            T[i++] = A[l++];
        else if(A[l] > A[r] || l>mid){
            T[i++] = A[r++];
            cnt += mid + 1 - l;
        }
    }
    while(l<=mid){
        T[i++] = A[l++];
    }
    while(r<=right){
        T[i++] = A[r++];
    }
    for(i = left;i<=right;++i)
        {A[i] = T[i];}

}

int main(){
    int N;
    while(scanf("%d",&N) && N != 0){
        memset(A,0,sizeof(A));
        cnt = 0;

        for(int i = 0 ; i < N ; ++i){
            scanf("%d",A+i);
        }
        merge_sort(0,N-1);
        printf("%ld\n",cnt);
    }
}
