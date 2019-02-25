#include<iostream>
#include<cstring>
#include<stack>
#include<deque>
#include<queue>
#include<map>
#include<string>
#define INF 0xffffff
using namespace std;
int D[31][31],G[31][31],path[31][31],P,Q;
string node[31];

int getIdx(string str){
    int i = 0;
    for( i = 0 ; i < P;i++){
        if(node[i]==str) return i;
    }
}

void Init(){
    memset(path,0xff,sizeof(path));
    int i, j ,k;
    for(int i = 0 ; i < P;++i){
        for(int j = 0 ;j<P;++j){
            if(i ==j){
                path[i][j] = i;
                D[i][j] = 0;
            }else{
                path[i][j] = -1;
                D[i][j] = INF;
            }
        }
    }
}

void Floyd(){
    memcpy(G,D,sizeof(D));
    int i ,j ,k;
    for(i = 0 ; i < P;++i){
        for(j = 0 ;j<P;++j){
            for(k = 0 ; k < P;++k){
                if( D[j][i]+D[i][k]<D[j][k]){
                    D[j][k] = D[j][i]+D[i][k];
                    path[j][k] = path[i][k];
                }
            }
        }
    }
}

int main(){
    freopen("0713.in","r",stdin);

    cin>>P;
    for(int i= 0 ; i < P; ++i){
        cin>>node[i];
    }

    Init();

    cin>>Q;
    for(int i = 0;i < Q;++i){
        string s,e;
        int idxs,idxe;

        cin>>s>>e;
        idxs=getIdx(s);
        idxe=getIdx(e);

        cin>>D[idxs][idxe];
        D[idxe][idxs] = D[idxs][idxe];
        path[idxs][idxe] = idxs;
        path[idxe][idxs] = idxe;
    }

    Floyd();


    int R= 0;
    cin>>R;
    for(int i=0;i<R;i++){
        string s,e;
        deque<int> q;
        int idxs,idxe;
        cin>>s>>e;
        idxs=getIdx(s);
        idxe=getIdx(e);

        q.push_back(idxe);
        int tmp = q.back();
        while(q.back()!=idxs){
            q.push_back(path[idxs][tmp]);
            tmp = path[idxs][tmp];
        }

        tmp = q.back();q.pop_back();
        cout<<node[tmp];
        while(!q.empty()){
            cout<<"->("<<G[tmp][q.back()]<<")->"<<node[q.back()];
            tmp = q.back(); q.pop_back();
        }
        cout<<endl;

    }

    return 0;


}
