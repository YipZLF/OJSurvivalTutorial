#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int main(){
    char str[20],substr[4],tmp [20];
    while(scanf("%s %s",str,substr)!=EOF){
        int max=-1,maxidx=-1;
        int len = strlen(str);
        int i = 0,j;
        for(i = 0 ; i < len;++i){
            if(str[i] > max){
                max = str[i];
                maxidx = i;
            }
        }

            for(j = maxidx+1;j < len;j++){
                tmp[j-maxidx-1] = str[j];
            }
            for(j = 0; j<3;j++){
                str[maxidx+1+j] = substr[j];
            }
            for(j = 0 ;j<len-maxidx-1;++j){
                str[maxidx+4+j]= tmp[j];
            }
            str[len+3]='\0';
            printf("%s\n",str);
    }
}