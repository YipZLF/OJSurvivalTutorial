#include<iostream>
#include<cstdio>
#include<cstring>
#include<deque>
#define MAXN 1000100
using namespace std;

int a[MAXN],Min[MAXN],Max[MAXN],n,k;
void getMin(){
    deque<int> Q;
    int i ;
    Q.push_back(1);
    Min[1] = a[1];
    for(i = 2; i<=n;i++){
        while((!Q.empty()) && (a[i]<a[Q.back()])){
            Q.pop_back();
        }
        Q.push_back(i);
        while((!Q.empty()) && (Q.front()< i - k +1)){
            Q.pop_front();
        }
        Min[i] = a[Q.front()];
    }
}

void getMax(){
    deque<int> Q;
    int i ;
    Q.push_back(1);
    Max[1] = a[1];
    for(i = 2; i<=n;i++){
        while((!Q.empty()) && (a[i]>a[Q.back()])){
            Q.pop_back();
        }
        Q.push_back(i);
        while((!Q.empty()) && (Q.front()< i - k +1)){
            Q.pop_front();
        }
        Max[i] = a[Q.front()];
    }
}
int main(){
    int i ;
    scanf("%d%d",&n,&k);
    for(i=1;i<=n;i++){
        scanf("%d",a+i);
    }
    getMax();
    getMin();
    for(i=k;i<=n;i++)
        printf("%d ",Min[i]);
    printf("\n");

    for(i=k;i<=n;i++)
        printf("%d ",Max[i]);
    printf("\n");
    return 0;
}