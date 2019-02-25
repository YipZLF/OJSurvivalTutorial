#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int N = 1010;
const int H = 10007;
int ptx[N],pty[N];

struct Node{
    int x;
    int y;
    int next;
}node[N];

int cur;
int n;
long ans;
int hashTable[H];

void initHash(){
    memset(hashTable,0xff,sizeof(hashTable));
    cur = 0;
    ans = 0;
}

void insertHash(int x,int y){
    int h = (x * x + y * y) % H;
    node[cur].x = x;
    node[cur].y = y;
    node[cur].next = hashTable[h];
    hashTable[h] = cur;
    cur++;
}

bool searchHash(int x,int y){
    int h = (x * x + y * y) %H;
    int next;
    next = hashTable[h];
    while(next!=-1){
        if(x == node[next].x && y == node[next].y)
            return true;
        next = node[next].next;
    }
    return false;
}

int main(){
    freopen("1002.in","r",stdin);
    while(scanf("%d",&n)!=EOF && n){
        initHash();
        for(int i =0 ; i < n ; ++i){
            scanf("%d%d",&ptx[i],&pty[i]);
            insertHash(ptx[i],pty[i]);
        }
        for(int i = 0; i < n; ++i){
            for(int j = 0;j<n;++j){
                if(j==i)
                    continue;
                int dx = pty[j] - pty[i];
                int dy = ptx[j] - ptx[i];
                int x1 = ptx[i] - dx;
                int x2 = ptx[j] - dx;
                int y1 = pty[i] + dy;
                int y2 = pty[j] + dy;
                if(searchHash(x1,y1)&&searchHash(x2,y2))
                    ans++;
            }
        }
        ans = ans>>2;
        printf("%lld\n",ans);
    }
    return 0;
}