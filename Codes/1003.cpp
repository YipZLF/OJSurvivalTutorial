#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;

const int N = 100010;
const int H = 38833;

struct Node{
    char eng[11];
    char fgn[11];
    int next;
}node[N];

int cur;
int n;
long cnt = 0;
int hashTable[H];

void initHash(){
    memset(hashTable,0xff,sizeof(hashTable));
    cur = 0;
    ans = 0;
}

void insertHash(int idx){
    int h=0;
    for(int i =0;node[idx].fgn[i];++i){
        h = h*10 + node[idx].fgn[i];
    }
    h = h % H;
    node[idx].next = hashTable[h];
    hashTable[h] = idx;
}

bool isMatch(int idx,string * str){
    int i;
    for(i = 0 ; str[i];++i){
        if(node[idx].fgn[i]!=str[i])
            return false;
    }
    if(i< strlen(node[idx].fgn))
        return false;
    return true;
}

int searchHash(string & str){
    int h=0;
    for(int i =0;str[i];++i){
        h = h*10 + str[i];
    }
    h = h % H;
    int next;
    next = hashTable[h];
    while(next!=-1){
        if(isMatch(next,str))
            return next;
        next = node[next].next;
    }
    return -1;
}

int main(){
    freopen("1003.in","r",stdin);
    string l;
    while(true){
        scanf("%s %s",node[cnt].eng,node[cnt].fgn);
        if(node[cnt].eng[0]=='-')
            break;
        insertHash(cnt);
        cnt++;
    }
    
    string str;
    while(scanf("%s",str);){
        
        int idx = searchHash(str);
        if(idx==-1){
            printf("eh\n");
        }else{
            printf("%s\n",node[idx].eng);
        }
        }
    return 0;
}