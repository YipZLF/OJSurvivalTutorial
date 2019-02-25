#include<iostream>
#include<cstdio>
#include<memory>
#include<string.h>
#include<queue>
using namespace std;
const int MAXN = 1010;
const int LETTER = 26;
char str[MAXN];
int nodeCnt = 0;

struct Node{
    bool isBadNode;
    Node *pChild[LETTER];
    Node *pPrev;
    Node(){
        isBadNode = false;
        pPrev = NULL;
        memset(pChild,0,sizeof(pChild));
    }
};
Node TrieGraph[MAXN*20];

void Insert(Node * pRoot, char* str)
{
    for(int i= 0;str[i];i++){
        if(pRoot->pChild[str[i]-'a']==NULL){
            pRoot->pChild[str[i]-'a'] = &TrieGraph[nodeCnt];
            nodeCnt++;
        }
        pRoot = pRoot->pChild[str[i]-'a'];
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

bool isMatched(char * str){
    Node * pRoot = TrieGraph+1;
    for(int i = 0; str[i];i++){
        while(pRoot->pChild[str[i]-'a']==NULL){
            pRoot = pRoot->pPrev;
        }
        pRoot = pRoot->pChild[str[i]-'a'];
        if(pRoot->isBadNode)
            return true;
    }
    return false;
}

int main()
{
    freopen("TrieGraph.in","r",stdin);
    int n, m;
    nodeCnt = 2;
    scanf("%d",&n);
    for(int i = 0;i <n ;i++){
        scanf("%s",str);
        Insert(TrieGraph + 1,str);
    }
    buildPrev();
    scanf("%d",&m);
    for(int i = 0;i < m ;i++){
        scanf("%s",str);
        if(isMatched(str))
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
