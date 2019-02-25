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


void Input(){
    int from,to;
    scanf("p edge %d %d\n",&vNum,&eNum);
    graph = new Node[vNum+1];
    if(!graph){
        printf("Failed\n");
        return ;
    }
    for(int i = 0 ;i < eNum;i++){
        scanf("e %d %d\n",&from,&to);
        #ifdef DEBUG
        printf("from %d to %d \n",from,to);
        #endif
        /*store edges in set*/
        candidateEdge.insert(make_pair(from,to));
        
        /*store edges in graph*/
        Edge* ptr=graph[from].lastEdge;
        if(ptr==NULL){
            graph[from].firstEdge = new Edge(from,to);
            graph[from].lastEdge = graph[from].firstEdge;
        }else{
            ptr->nextEdge = new Edge(from,to);
            graph[from].lastEdge = ptr->nextEdge;
        }
        
        ptr=graph[to].lastEdge;
        if(ptr==NULL){
            graph[to].firstEdge = new Edge(to,from);
            graph[to].lastEdge = graph[to].firstEdge;
        }else{
            ptr->nextEdge = new Edge(to,from);
            graph[to].lastEdge = ptr->nextEdge ;
        }
    }
}

void Init(){
    for(int i = 1; i<=vNum;++i){
        candidateSet.insert(i);
    }
    curE = vNum;
}


void Print(){
    printf("MVC size:%ld\n",candidateSet.size());
    for(set<int>::iterator ptr=candidateSet.begin();
        ptr != candidateSet.end();++ptr){
            printf("%d ",(*ptr));
        }
    printf("\n");
}

void SA(){
    int innerLoop = MAXCHANGE,outerLoop=OUTTERLOOP;
    double T = TEMPERATURE;
    while(outerLoop--){
        #ifdef DEBUG
            if(outerLoop % 100==0){
                printf("----------------------");
                printf("outerLoop :%d\n",outerLoop);
            }
            
        #endif
        innerLoop = MAXCHANGE;
        while(innerLoop>0){
            #ifdef DEBUG
            if(innerLoop % 100==0)
                printf("innerLoop :%d\n",innerLoop);
            #endif
            tempSet = candidateSet;
            tempEdge = candidateEdge;
            //choose PERTURB points
            int * perturb = new int[PERTURB];
            srand((unsigned int)(time(NULL)));
            for (int i = 0 ; i < PERTURB; ++i){
                perturb[i] = rand() % vNum + 1;
            }

            //change it
            for(int i = 0 ; i < PERTURB;++i){
                if(tempSet.find(perturb[i])!=tempSet.end()){    //found perturb[i] in tempSet
                    tempSet.erase(perturb[i]);                  //erase it
                    Edge* ptr=graph[perturb[i]].firstEdge;      
                    while(ptr!=NULL){
                        /*
                        for (u,v), u in tempSet, 
                        if v is not in tempSet
                            delete the edge (u,v) from tempEdge
                        else
                            stay the same
                        */
                        if(tempSet.find(ptr->to)==tempSet.end()){
                            tempEdge.erase(make_pair(min(ptr->from,ptr->to),
                                                    max(ptr->from,ptr->to)));
                        }
                        ptr=ptr->nextEdge;
                    }
                }else{                              //perturb[i] not in tempSet
                    tempSet.insert(perturb[i]);
                    Edge* ptr=graph[perturb[i]].firstEdge;
                    while(ptr!=NULL){        //add the edges that perturb[i] is related to tempEdge
                        tempEdge.insert(make_pair(min(ptr->from,ptr->to),
                                                        max(ptr->from,ptr->to)));
                        ptr=ptr->nextEdge;
                    }
                }
            }
            if(tempEdge.size()<eNum){        //tempSet is not Edge Cover
                #ifdef DEBUG
                printf("tempEdge size: %d\n",tempEdge.size());
                #endif
                continue;
                }
            else if(tempEdge.size()==eNum){
                if(tempSet.size()<=candidateSet.size()){
                    candidateSet = tempSet;//if less points accepts(updates)
                    innerLoop--;
                }else{                     //if got a worse answer, accept it randomly
                    srand((unsigned int)(time(NULL)));
                    #ifdef DEBUG
                    printf("tempsize:%d CandidateSize%d Temperature:%f\n",tempSet.size(),candidateSet.size(), T);
                    #endif
                    double p = exp(-(tempSet.size()-candidateSet.size()) / T);
                    bool accept = ((rand() % 10000)/10000.0<=p);
                    if(accept){
                        candidateSet = tempSet;
                        innerLoop--;
                    }
                }
            }
    }
    T = T * DECAY;
    Print();
    }
    
}


int main(){
    freopen("/home/yipzlf/Courses/Data_Structure_Algorithm_2018/mc_dataset/frb30-15-mis/frb30-15-1.mis","r",stdin);
    Input();
    Init();
    SA();
    Print();
    return 0;
}