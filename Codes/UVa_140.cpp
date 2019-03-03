#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 8;
int id[256],letter[MAXN];

int main(){
    char input[2000];
    while(scanf("%s",input) && input[0]!='#'){
        int n = 0;
        for(char ch='A';ch<='Z';ch++){
            if(strchr(input,ch)!=NULL){
                id[ch]=n++;
                letter[id[ch]]=ch;
            }
        }

        int len = strlen(input),p=0,q=0;
        vector<int> u,v;
        while(true){
            while(p<len&input[p]!=':')
                p++;
            if(p==len)
                break;
            while(q<len&input[q]!=';')
                q++;
            for(int i = p+1;i<q;i++){
                u.push_back(id[input[p-1]]);
                v.push_back(id[input[i]]);
            }
            p++;q++;
        }

        int P[MAXN],bestP[MAXN],pos[MAXN],ans = n;
        for(int i = 0; i<n;++i)
            P[i] = i;
        do{
            int bw=0;
            for(int i = 0 ; i < n;++i){
                pos[P[i]]=i;
            }
            for(int i = 0 ; i< u.size();++i){
                bw= max(bw,abs(pos[u[i]]-pos[v[i]]));
            }
            if(bw<ans){
                ans = bw;
                memcpy(bestP,P,sizeof(P));
            }
        }while(next_permutation(P,P+n));
    
    for(int i = 0 ; i < n ; ++i)
        printf("%c ",letter[bestP[i]]);
    printf("-> %d",ans);
    }

return 0;
}