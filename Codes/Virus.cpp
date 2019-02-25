#include<iostream>
#include<cstdio>
#include<memory>
#include<string.h>
#include<queue>
#include<iostream>
using 
using namespace std;
const int MAXN = 30030;
char str[MAXN];
int nodeCnt = 0;
struct Node{
   bool isBadNode;
    bool hasVisited;
    Node *pChild[2];
    Node *pPrev;
    Node(){
        isBadNode = false;
        hasVisited = false;
        pPrev = NULL;
        memset(pChild,0,sizeof(pChild));
    }
};
Node TrieGraph[MAXN];

void Insert(Node * pRoot, char* str)
{
    for(int i= 0;str[i];i++){
        if(pRoot->pChild[str[i]-'0']==NULL){
            pRoot->pChild[str[i]-'0'] = &TrieGraph[nodeCnt];
            nodeCnt++;
        }
        pRoot = pRoot->pChild[str[i]-'0'];
    }
    pRoot->isBadNode = true;
 }

void buildPrev()
{
    for(int i = 0;i < 2;i++){
        TrieGraph[0].pChild[i] = TrieGraph + 1;
    }
    TrieGraph[0].pPrev = NULL;
    TrieGraph[1].pPrev = TrieGraph;

    queue<Node *> qe;
    qe.push(TrieGraph+1);
    while(!qe.empty()){
        Node* curNode = qe.front();
        qe.pop();
        for(int i = 0;i<2;i++){
            Node * p = curNode->pChild[i];
            if(p){
                Node* pPrev= curNode->pPrev;
                while(pPrev->pChild[i] == NULL)
                    pPrev = pPrev->pPrev;
                p->pPrev = pPrev->pChild[i];
                if(p->pPrev->isBadNode)
                    p->isBadNode = true;
                qe.push(p);
            }
        }
    }
    qe.push(TrieGraph+1);
    while(!qe.empty()){
        Node* curNode = qe.front();
        qe.pop();
        for(int i = 0;i<2;i++){
            Node * p = curNode->pChild[i];
            if(!p){
                Node* pPrev= curNode->pPrev;
                while(pPrev->pChild[i] == NULL)
                    pPrev = pPrev->pPrev;
                curNode->pChild[i] = pPrev->pChild[i];
            }else{
                qe.push(p);
            }
        }
    }
}

bool DFS(Node * pRoot){
    bool flag = false;
    if(pRoot->hasVisited)
        return true;
    pRoot->hasVisited = true;
    for(int i = 0; i<2;i++){
        if(pRoot->pChild[i] && !pRoot->pChild[i]->isBadNode && !flag){
            flag = DFS(pRoot->pChild[i]);
        }
    }
    pRoot->hasVisited = false;
    return flag;
}

int main()
{
    freopen("VirusThatCantEscape.in","r",stdin);
    int n, m;
    nodeCnt = 2;
    scanf("%d",&n);
    for(int i = 0;i <n ;i++){
        scanf("%s",str);
        Insert(TrieGraph + 1,str);
    }
    buildPrev();
    if(DFS(TrieGraph + 1))
        cout<<"TAK\n";
    else
        cout<<"NIE\n";
    return 0;
}
