#include<iostream>
#include<cstdio>
using namespace std;
int parent[100100],relation[100100];

int getRoot(int a){
    if (parent[a]==a){
        return a;
    }else{
        int tmp = getRoot(parent[a]);
        relation[a] = (relation[parent[a]]+relation[a]) %2;
        parent[a] = tmp;
        return parent[a];
    }
}

int main(){
    int T,N,M;
    cin>>T;
    while(T--){
        scanf("%d%d",&N,&M);
        for(int i=1;i<=N;i++){
            parent[i] = i;
            relation[i] = 0;
        }
        for(int i = 0 ; i <M;++i){
            char op[2];
            int a ,b;
            scanf("%s",op);
            scanf("%d%d",&a,&b);

            int pa  = getRoot(a);
            int pb  = getRoot(b);
            if(op[0]=='D'){
                parent[pb] = pa;
                relation[pb] = (relation[a] + relation[b] +1)%2;
            }else if(op[0]=='A'){
                if(pa != pb){
                    cout<<"Not sure yet.\n";
                }else if(relation[a]==relation[b]){
                    cout<<"In the same gang.\n";
                }else if(relation[a]!=relation[b]){
                    cout<<"In different gangs.\n";
                }

            }
        }
    }
}