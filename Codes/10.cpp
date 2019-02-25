#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#define MAXN 1010
#define LETTER 26
using namespace std;

int m,n;
char pt[122],sen[1010];

int cnt = 0;

struct node{
    node* pChild[LETTER];
    node* pPrev;
    bool isBad;
    node(){
        memset(pChild,0,sizeof(pChild));
        pPrev = NULL;
        isBad =false;
    }
}tree[122*MAXN];

void Insert(node* pRoot,char* str){
    node* ptr = pRoot;
    for(int i = 0 ; str[i];++i){
        if(ptr->pChild[str[i]-'a']==NULL){
            ptr->pChild[str[i]-'a'] = tree+(cnt++);
        ptr = ptr->pChild[str[i]-'a'];
        }
        ptr->isBad = true;
    }
}

void buildTrie(){
    for(int i =0 ; i< LETTER; ++i){
        tree[0].pChild[i] = tree+1;
    }
    tree[0].pPrev = NULL;
    tree[1].pPrev = tree;
    queue<node*> q;
    q.push(tree+1);
    node* ptr = tree+1;
    while(!q.empty()){
        ptr = q.front();q.pop();
        for(int i=  0 ;i <LETTER;++i){
            node * p = ptr->pChild[i];
            if(p){
                node* pre = ptr->pPrev;
                while(pre->pChild[i]==NULL){
                    pre = pre->pPrev;
                }
                p->pPrev = pre->pChild[i];
                if(p->pPrev->isBad)
                    p->isBad= true;
                q.push(p);
            }
        }
    }
}
bool Query(char* str){
    node* p = tree+1;
    for(int i = 0 ;str[i];i++){
        while(p->pChild[str[i]-'a']==NULL)
            p= p->pPrev;
        p = p->pChild[str[i]-'a'];
        if(p->isBad)
            return true;
    }
    return false;
}
int main(){
	freopen("TrieGraph.in","r",stdin);
    
    cnt= 2;
	scanf("%d",&n);
	for(int i = 0 ;i<n;i++){
		scanf("%s",pt);
		Insert(tree+1,pt);
	}
	buildTrie();
	scanf("%d",&m);
	for(int i = 0 ;i<m;i++){
		scanf("%s",sen);
		if(Query(sen)){
			cout<<"YES\n";
		}else{
			cout<<"NO\n";
		}
	}
	return 0;
}