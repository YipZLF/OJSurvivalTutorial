#include<iostream>
#include<cstdio>
#include<memory>
#include<string.h>
#include<queue>
using namespace std;
const int MAXN = 1010;
const int INF = 0xfffffff;
char str[MAXN];
int nodeCnt = 0;
int dp[1000][52*20];//如何初始化

struct Node{
    bool isBadNode;
    Node *pChild[4];
    Node *pPrev;
    Node(){
        isBadNode = false;
        pPrev = NULL;
        memset(pChild,0,sizeof(pChild));
    }
};
Node TrieGraph[52*20];

void Insert(Node * pRoot, char* str)
{
    for(int i= 0;str[i];i++){
        if(pRoot->pChild[str[i]-1]==NULL){
            pRoot->pChild[str[i]-1] = &TrieGraph[nodeCnt];
            nodeCnt++;
        }
        pRoot = pRoot->pChild[str[i]-1];
    }
    pRoot->isBadNode = true;
}

void buildPrev()
{
    for(int i = 0;i < 4;i++){
        TrieGraph[0].pChild[i] = TrieGraph + 1;
    }
    TrieGraph[0].pPrev = NULL;
    TrieGraph[1].pPrev = TrieGraph;

    queue<Node *> qe;
    qe.push(TrieGraph+1);
    while(!qe.empty()){
        Node* curNode = qe.front();
        qe.pop();
        for(int i = 0;i<4;i++){
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


int DP(char * str)
{
    memset(dp,0x7f,sizeof(dp));
    dp[0][1] = 0;
    int i,son;
    for(i = 0; str[i];i++){
        for(int j = 1; j<nodeCnt;j++){
            for(int k = 0; k<4;k++){
                Node * p = &TrieGraph[j];
                while(p->pChild[k]==NULL)
                    p = p->pPrev;
                son = p->pChild[k] - TrieGraph;
                if(!TrieGraph[son].isBadNode)
                    dp[i+1][son] = min(dp[i+1][son],dp[i][j]+((k+1)!=str[i]));
            }
        }
    }
    int minVal = INF;
    for(int m = 0; m <nodeCnt;m++){
        if(dp[i][m]<minVal)
            minVal = dp[i][m];
    }
    if(minVal >= i)
        return -1;
    else
        return minVal;
}


char* str2array(char* str){
    for(int i = 0 ; str[i];i++){
        switch(str[i]){
            case 'A':str[i] = 1;break;
            case 'G':str[i] = 2;break;
            case 'C':str[i] = 3;break;
            case 'T':str[i] = 4;break;
            default: break;
        }
    }
    return str;
}

int main()
{
    freopen("DNA.in","r",stdin);
    int n, m,idx = 1;
    while(scanf("%d",&n)==1){
        if(n==0)
            break;

        nodeCnt = 2;
        memset(TrieGraph,0,sizeof(TrieGraph));
        for(int i = 0;i <n ;i++){
            scanf("%s",str);
            Insert(TrieGraph + 1,str2array(str));
        }
        buildPrev();
        scanf("%s",str);

        cout<<"Case "<<idx++<<": "<<DP(str2array(str))<<endl;
    }
    return 0;
}

