#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

char dict[10010][16];
char similar[10010][16];

int Replace(const char * stra,const char * strb){
    int cnt = 0;
    for(int i= 0 ; cnt!= 2&&i<strlen(stra);++i){
        if(stra[i]!=strb[i])
            cnt++;
    }
    return cnt;
}

int Delete(const char* stra,const char* strb){
    int i,j,alen=strlen(stra);
    int cnt = 0;
    for(i=0,j=0;cnt <= 1 && i<=alen;++i,++j){
        if(stra[i]!=strb[j]){
            cnt++;
            i--;
        }
    }
    if(cnt !=2)
        return 1;
    else
        return 0;
}

int compareStr(char* stra, char* strb){
    int alen = strlen(stra);
    int blen = strlen(strb);
    if(alen==blen){
        int flag = Replace(stra,strb);
        if(flag == 0) return 2;
        else if(flag == 1) return 1;
        else return 0;
    }
    else if(alen-blen==1){
        return Delete(strb,stra);
    }else if(blen-alen==1){
        return Delete(stra,strb);
    }else{
        return 0;
    }
}


int main(){
    freopen("0201.in","r",stdin);
    char tmp[16];
    int dictnum= 0;
    for(dictnum = 0 ; ;++dictnum){
        int i = dictnum;
        scanf("%s",dict[i]);
        if(dict[i][0]=='#')
            break;
    }
    for(;;){
        bool found=false;
        int numSim = 0;
        scanf("%s",tmp);


        if(tmp[0]=='#')
            break;
        else{
            for(int i = 0 ; i < dictnum;++i){
                int comp = compareStr(tmp,dict[i]);
                if(comp == 0)//not similar
                    continue;
                else if(comp==2){//the same
                    printf("%s is correct\n",tmp);
                    found = true;
                    break;
                }else{
                    strcpy(similar[numSim++],dict[i]);
                }
            }
            if(!found){
                printf("%s:",tmp);
                for(int i = 0 ; i < numSim;++i){
                    printf(" %s",similar[i]);
                }
                printf("\n");
            }
        }
    }
}