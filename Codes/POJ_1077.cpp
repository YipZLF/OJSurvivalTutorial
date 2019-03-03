/*
 This cpp is left unfinished.
*/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
typedef int state[9];
const hashsize = 1000003;
const int maxstate = 1000000;
const int dx[] = {-1,1,0,0};
const int dy[] = {0,0,-1,1};
char move[4]={'r','l','u','d'};
vector<int> ht[hashsize];

state st[maxstate],goal={1,2,3,4,5,6,7,8,0};
int st_rear = 0;

char last_move[maxstate],path[maxstate];
int father[maxstate];

void init_hash(){
    for(int i = 0 ; i < hashsize;++i){
        ht[i].clear();
    }
}

int hash(state & s){
    int result = 0;
    for(int i = 0 ; i<9;i++){
        result = result*10 + (s[i]-'0')
    }
    return result % hashsize;
}

void insertHash(state &s,int idx){
    int hvalue = hash(s);
    if(ht[hvalue].empty()){
        ht[hvalue][0] = idx;
    }else{
        ht[hvalue].append(idx);
    }
}

bool visit(state & s){
    int hvalue = hash(s);
    if(ht[hvalue].empty())
        return false;
    else{
        for(auto it = 0;it<ht[hvalue].size();++it){
            if(memcpy(st[ht[hvalue][it]],&s,sizeof(s))==0)
                return true;
        }
        return false;
    }
}

int bfs(){
    queue<int> idx_qe,move_qe;
    idx_qe.push(1);
    move_qe.push(-1);
    st_rear = 1;
    init_hash();

    while(!idx_qe.empty()){
        int tmp_idx = idx_qe.front();idx_qe.pop();
        state & s = st[tmp_idx]; 
        
        //get 0 coordinates
        int z;
        for(int z = 0 ;z < 9 ;z++){if(s[i]==0)break;}
        int x = z/3, y = z%3;

        for(int i = 0 ; i<4;i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(0<=nx && nx<3 && 0<=ny && ny<3){
                int nz = nx*3 +ny;
                state & t;
                memcpy(&t,&s,sizeof(s));
                t[nz] = s[z];
                t[z] = s[nz];
                if(visit(t))
                    break;
                else{
                    rear++;
                    memcpy(st[rear],&t,sizeof(t));
                    father[rear] = idx_qe;
                    last_move[rear] = move[i];
                    if(memcmp(&t,&goal,sizeof(goal))==0)
                        return true;
                }
            }
        }
    }

    return false;
}

int main(){
    char tmp[9];
    for(int i = 0 ; i < 9;i++){
        scanf("%c ",tmp+i);
        if(tmp[i]==x)
            start[1][i]=0;
        else
            start[1][i]=tmp[i]-'0'; 
    }
    if(bfs()){
        int i =0,idx = rear;
        while(last_move[idx]!=0){
            path[i++] = last_move[idx];
            idx = father[idx];
        }
        int len = strlen(path);
        for(int j = 0 ; j< len/2;++j){
            char tmp = path[i];
            path[i] = path[len-i];
            path[len-i] = tmp;
        }
        printf("%s",path);
    }else{
        printf("unsolvable\n");
    }

    return 0;
}