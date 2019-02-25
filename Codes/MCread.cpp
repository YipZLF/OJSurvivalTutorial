#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<set>
#include<map>
#include<utility>
#include<stdlib.h>
#include<vector>
using namespace std;

#define DEBUG
#define PERTURB 2
#define DECAY 0.95
#define MAXCHANGE 500
#define OUTTERLOOP 1000
#define TEMPERATURE 10

struct Edge{
    int from,to;
    Edge * nextEdge;
    Edge(){
        from = -1;to=-1;nextEdge=NULL;
    }
    Edge(int f,int t){
        from = f; to = t; nextEdge = NULL;
    }
};

struct Node{
    int idx;
    int edgenum;
    Edge* firstEdge,*lastEdge;
    Node(){
        idx=0;edgenum=0;firstEdge=lastEdge=NULL;
    }
};

Node * graph;
set<pair<int,int>> candidateEdge,tempEdge;
set<int> candidateSet,tempSet;
int vNum,eNum;
int curE;



int main(){
    freopen("/home/yipzlf/Courses/Data_Structure_Algorithm_2018/mc_dataset/frb30-15-mis/frb30-15-1.mis","r",stdin);
    freopen("./mc.in","w",stdout);
    int from,to;
    scanf("p edge %d %d\n",&vNum,&eNum);
    printf("%d %d\n",vNum,eNum);
    
    for(int i = 0 ;i < eNum;i++){
        scanf("e %d %d\n",&from,&to);
        printf("%d %d\n",from,to);
    
    }

    return 0;
}