#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int poster[10110][2];

struct seg{
    int idx;
    int val;
};
seg Seg[20220];

bool cmp(seg x, seg y){
    return x.val < y.val;
}

struct Node{
    int L,R;
    bool isCovered;
    int pL,pR;
    int Mid(){return (L+R)/2;}
};

Node treeNode[20220];
int nodeNum;
void buildTree(int root,int L,int R)
{
    treeNode[root].isCovered = false;
    treeNode[root].L = L;
    treeNode[root].R = R;
    if(L==R){
        treeNode[root].pL = 0;
        treeNode[root].pR = 0;
    }else{
        treeNode[root].pL = ++nodeNum;
        treeNode[root].pR = ++nodeNum;
        buildTree(treeNode[root].pL,L,treeNode[root].Mid());
        buildTree(treeNode[root].pR,treeNode[root].Mid()+1,R);
    }
}

bool Paste(int root,int left,int right)
{
    if(treeNode[root].isCovered==true){
        return false;
    }
    if(left == treeNode[root].L && right == treeNode[root].R){
            treeNode[root].isCovered = true;
            return true;
    }else{
        if(right<=treeNode[root].Mid()){
            return Paste(treeNode[root].pL,left,right);
        }else if(treeNode[root].Mid()<left){
            return Paste(treeNode[root].pR,left,right);
        }else{
            bool flag = Paste(treeNode[root].pL,left,treeNode[root].Mid());
            flag =flag || Paste(treeNode[root].pR,treeNode[root].Mid()+1,right);
            return flag;
        }
        treeNode[root].isCovered = treeNode[treeNode[root].pL].isCovered &&treeNode[treeNode[root].pR].isCovered;
    }
}

int main()
{
    freopen("2528.in","r",stdin);
    int caseNum = 0, N = 0;
    scanf("%d",&caseNum);
    while(caseNum--){
        scanf("%d",&N);
        /* 离散化*/
        for(int i = 0;i<N;i++){
            scanf("%d %d",&poster[i][0],&poster[i][1]);
            Seg[2*i].val = poster[i][0];
            Seg[2*i+1].val = poster[i][1];
            Seg[2*i].idx = 2*i;
            Seg[2*i+1].idx = 2*i+1;
        }
        sort(Seg,Seg+2*N,cmp);

        int cnt = 0,tmp = -1;
        for(int i =0; i <2*N ; i++){
            if(tmp != Seg[i].val){
                cnt++;
                if(Seg[i].val==tmp+1){
                    poster[Seg[i].idx/2][Seg[i].idx%2] = cnt;
                }else{
                    cnt++;
                    poster[Seg[i].idx/2][Seg[i].idx%2] = cnt;
                }
            }else{
                poster[Seg[i].idx/2][Seg[i].idx%2] = cnt;
            }
            tmp = Seg[i].val;
        }
        nodeNum = 1;
        buildTree(1,1,cnt);

        int numberCanBeSeen = 0;
        for(int i =N-1; i>=0; i--){
            bool flag = Paste(1,poster[i][0],poster[i][1]);
            if(flag){
                numberCanBeSeen++;}
        }
        cout<<numberCanBeSeen<<endl;
    }
    return 0;
}
