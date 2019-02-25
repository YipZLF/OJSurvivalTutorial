#include<iostream>
#include<cstring>
#include<stack>
#include<deque>
#include<queue>
#include<map>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
int n,parent[30];
struct Edge{
    int weight;
    int from,to;
    Edge(){
        weight = 0; from = -1;to = -1;
    }
}edge[100];
bool operator<(Edge a,Edge b){
        return a.weight < b.weight;
    }


int findroot(int i){
    if(parent[i]==i)
        return i;
    else{
        parent[i] = findroot(parent[i]);
          return parent[i];
    }
}


int main()
{
    freopen("0714.in","r",stdin);
    cin>>n;
    int edgecnt = 0;
    for( int i = 0 ; i < n-1; ++i){
        char c; cin>>c;
        int s; s = c-'A';
        int cnt; cin>>cnt;
        parent[i] = i;

        while(cnt--){
            edge[edgecnt].from = s;
            cin >>c;
            edge[edgecnt].to = c-'A';
            cin >> edge[edgecnt].weight;
            edgecnt++;
        }

    }
    parent[n-1] = n-1;
    sort(edge,edge+edgecnt);

     int sum = 0;
    int flag = n-1;
    for(int i = 0; i< edgecnt;++i){

        Edge e = edge[i];
        int pa = findroot(e.from);

        int pb = findroot(e.to);

        if(pa != pb){
            parent[pb] = pa;
            sum+=e.weight;
            flag --;
            if(flag ==0)
                break;
        }
    }
    cout<<sum<<endl;
    return 0;
}
