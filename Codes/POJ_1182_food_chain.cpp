#include<iostream>
#include<cstdio>
using namespace std;
const int MAXN=51000;
int parent[MAXN],relation[MAXN]; //relation to its father
int N,K;

// relation[a] is a's relation to its parent
// 2: eaten by parent, 0: same, 1: eat parent
int find(int a){
    if(parent[a] == a){
        return a;
    }else{
        int tmp = find(parent[a]);
        relation[a] = (3 + relation[a] + relation[tmp])%3;
        return parent[a] = tmp;
    }
}

bool merge(int a,int b, int op){
    int pa = find(a);
    int pb = find(b);
    if(pa==pb){ //if known
        if(op == 1 && relation[a]!= relation[b]){
            return false;
        }if(op == 2 && (relation[a] - relation[b] +3)%3 != 1){
            return false;
        }
    }else{//if unknown
        parent[pb] = pa;
        if(op == 1){
            relation[pb] = (relation[a]-relation[b] +3)%3;
        }else if( op ==2){
            relation[pb] = (relation[a]-relation[b] +2)%3;
        }
    }
    return true;
}

int main(){
    freopen("1182.in",stdin);
    int cnt = 0;
    scanf("%d%d",&N,&K);
    for(int i = 0 ; i < K;++i){
        int D,X,Y;
        scanf("%d%d%d",&D,&X,&Y);
        if((X>N || Y > N) || (D==2 && X==Y))
            {cnt++; continue;}
        if(!merge(X,Y,D)){
            cnt ++;
        }
    }
    printf("%d\n",cnt);
}
/*
int cal(int Rel2Par, int ParRel2Root)
{
    if(ParRel2Root == 1) return Rel2Par;
    else if(ParRel2Root == 0) return (Rel2Par-1 + 3) %3;
    else if(ParRel2Root == 2) return (Rel2Par+1 + 3) %3;
}

int getRel(int a,int & root)
{
    if(parent[a]==a)
    {   root = a;
        return 1;
    }
    else
    {
        int rel = getRel(parent[a],root);
        parent[a] = root;
        relation[a] = cal(relation[a],rel);
        return relation[a];
    }
}

bool process(int D,int X,int Y,int N)
{
    if ((D==2 && X==Y) ||
        (X>N) || (Y>N) )
        return false;
    int px,py;
    int rx = getRel(X,px);
    int ry = getRel(Y,py);
    if(px != py)
    {//attach x to y
        parent[px] = py;

        int xr;
        if(rx==1)xr = 1;
        else xr = (1-rx +1 +3) %3;

        relation[px] = cal(xr,cal(D,ry));
        return true;
    }
        else
        {
            if(rx!=cal(D,ry))
            {return false;}
            else return true;
        }
}

int main()
{
    freopen("1182.in","r",stdin);

    int N,K,number = 0;
    scanf("%d %d",&N,&K);
    for(int i = 1; i<=N; i++)
    {
        parent[i] = i;
        relation[i] = 1;
    }
    for(int i = 0; i<K; i++)
    {
        int D,X,Y;
        scanf("%d %d %d",&D,&X,&Y);
        if(!process(D,X,Y,N))
            number ++;
    }
    printf("%d\n",number);
    return 0;
}
*/