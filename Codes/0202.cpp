#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
int good[50050];
int main(){
    int N,P,K;
    queue<int> qe;
    scanf("%d%d%d",&N,&K,&P);
    for(int i = 1; i <=K;++i){
        qe.push(i);
    }
    int i = 0,cnt=0;
    while(!qe.empty()){
        i++;
        if(i%N==0 ){
            good[cnt++]=qe.front();
        }
        qe.pop();
        for(int j = 0 ; j <P;j++){
            qe.push(qe.front());
            qe.pop();
        }
    }
    sort(good,good+cnt);
    for(int i = 0 ; i < cnt; ++i){
        cout<<good[i]<<endl;
    }
    return 0;
}