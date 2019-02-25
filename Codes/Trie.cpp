#include<iostream>
#include<cstdio>
#include<cstring>
#include<deque>
using namespace std;

int n,m;




















/*
int n,m;
const int MAXN = 1010;
char str[MAXN];
const int LETTERS = 26;
int nNodesCount = 0;
struct CNode{
    CNode* pChilds[LETTERS];
    CNode * pPrev;
    bool bBadNode;
    CNode(){
        memset(pChilds, 0 ,sizeof(pChilds));
        bBadNode = false;
        pPrev = NULL;
    }
}Tree[20*MAXN];

void Insert(CNode * pRoot, char *s){
    for(int i = 0 ; s[i];i++){
        if(pRoot->pChilds[s[i]-'a']==NULL){
            pRoot->pChilds[s[i]-'a'] = Tree + nNodesCount;
            nNodesCount++;
        }
        pRoot = pRoot->pChilds[s[i]-'a'];
    }
    pRoot->bBadNode = true;
}

void BuildDfa(){//BFS
    for(int i =0; i < LETTERS; i++){
        Tree[0].pChilds[i]==Tree+1;
    }
    Tree[0].pPrev = NULL;
    Tree[1].pPrev = Tree;
    deque<CNode*> q;
    q.push_back(Tree+1);
    while(!q.empty()){
        CNode* pRoot = q.front();
        q.pop_front();
        for(int i = 0 ;i < LETTERS ; i++){
            CNode* p = pRoot->pChilds[i];
            if(p){
                CNode * pPrev = pRoot->pPrev;
                while(pPrev->pChilds[i]==NULL){
                    pPrev = pPrev->pPrev;
                }
                p->pPrev = pPrev->pChilds[i];
                if(p->pPrev->bBadNode){
                    p->bBadNode=true;
                }
                q.push_back(p);
            }
        }
    }
}

bool SearchDFA(char * s){
    CNode * p = Tree+1;
    for(int i = 0 ; s[id];++i){
        while(p->pChilds[s[i]-'a']==NULL)
            p = p->pPrev;
        p = p->pChilds[s[i]-'a'];
        if(p->bBadNode)
            return true;
    }
    return false;
}

int main(){
    nNodesCount = 2;
    scanf("%d",&n);
    for(int i = 0 ; i < ;++i){
        scanf("%s",str);
        Insert(Tree+1,str);
    }
    BuildDfa();
    scanf("%d",&m);
    for(int i = 0 ; i <m;++i){
        scanf("%s",str);
        if(SearchDFA(str))
            cout<<"YES\n";
        else
            cout<<"NO\n";
    }
    return 0;
}*/