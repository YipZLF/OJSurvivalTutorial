#include<iostream>
#include<cstdio>
#include<memory>
#include<string.h>
#include<queue>
using namespace std;
const int pMAXN = 1010,sMAXN = 5101000;
const int LETTER = 26;
char pStr[pMAXN],sStr[sMAXN],rStr[sMAXN];
int nodeCnt = 0;

struct Node{
    bool isBadNode,isMatched;
    Node *pChild[LETTER];
    Node *pPrev;
    Node(){
        isBadNode = false;
        isMatched = false;
        pPrev = NULL;
        memset(pChild,0,sizeof(pChild));
    }
};
Node TrieGraph[MAXN*260];

void Insert(Node * pRoot, char* str)
{
    for(int i= 0;str[i];i++){
        if(pRoot->pChild[str[i]-'A']==NULL){
            pRoot->pChild[str[i]-'A'] = &TrieGraph[nodeCnt];
            nodeCnt++;
        }
        pRoot = pRoot->pChild[str[i]-'A'];
    }
    pRoot->isBadNode = true;
}

void buildPrev()
{
    for(int i = 0;i < LETTER;i++){
        TrieGraph[0].pChild[i] = TrieGraph + 1;
    }
    TrieGraph[0].pPrev = NULL;
    TrieGraph[1].pPrev = TrieGraph;

    queue<Node *> qe;
    qe.push(TrieGraph+1);
    while(!qe.empty()){
        Node* curNode = qe.front();
        qe.pop();
        for(int i = 0;i<LETTER;i++){
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
}

bool isMatch(char * str){
    Node * pRoot = TrieGraph+1;
    for(int i = 0; str[i];i++){
        while(pRoot->pChild[str[i]-'A']==NULL){
            pRoot = pRoot->pPrev;
        }
        pRoot = pRoot->pChild[str[i]-'A'];
        if(pRoot->isBadNode)
            return true;
    }
    return false;
}

int main()
{
    freopen("VirusPandora.in","r",stdin);
    int testcase,n, m;
    scanf("%d",&testcase);
    while(testcase--){
        nodeCnt = 2;
        scanf("%d",&n);
        for(int i = 0;i <n ;i++){
            scanf("%s",pStr);
            Insert(TrieGraph + 1,pStr);
        }
        buildPrev();
        scanf("%s",sStr);
    }
    }
    return 0;
}
