#include<iostream>
#include<cstdio>
#include<queue>
#include<deque>
#include<list>
using namespace std;

struct node{
    int inDegree;
    list<int> son;
    bool isVis;
    node(){
        inDegree = 0; isVis = false;
    }
}g[10000];

int main(){
    freopen("0719.in","r",stdin);
    int v,a;
    scanf("%d %d",&v,&a);
    for(int i = 0 ; i < a; ++i){
        int from,to ;
        scanf("%d %d",&from,&to);
        g[to].inDegree++;
        g[from].son.push_back(to);
        //cout<<from<<endl;
    }
    for(int i = 1 ;i <= v; i++){
        cout<<g[i].inDegree<<endl;
    }
    deque<int> qe;
    for(int i = 1 ; i <= v;++i){
        if(g[i].inDegree==0)
            qe.push_back(i);
    }
    while(!qe.empty()){
        int v = qe.front();qe.pop_front();
        g[v].isVis = true;
        printf("v%d ",v);
        list<int>::iterator k;
        for(k = g[v].son.begin();
                k != g[v].son.end();++k){
                    g[*k].inDegree;
                    if(g[*k].inDegree==0){
                        qe.push_back(*k);
                    }
                }


    }
    /*
    bool flag;
    while(true){
    flag = false;
    for(int i = 1 ; i <= v;++i){
        if(g[i].inDegree ==0 && g[i].isVis==false){
            flag = true;
            printf("v%d ",i);
            g[i].isVis = true;
            for(list<int>::iterator k = g[i].son.begin();
                k != g[i].son.end();++k){
                    g[ *k ].inDegree--;
                }
        }
    if(flag ==false)
        break;
    }
    }*/
    return 0;
}
