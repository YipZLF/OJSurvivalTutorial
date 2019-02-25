#include<iostream>
#include<string.h>
#include<cstdio>
using namespace std;

int main()
{
    freopen("2934.in","r",stdin);
    char str[10010],substr[10010],tmp[10010];
    int maxidx = 0,maxnum = -1;
    scanf("%s %s",str,substr);
        for(int i = 0; str[i]!='\0';i++){
            if((int)str[i] > maxnum){
                maxnum = str[i];
                maxidx = i;
            }
        }
        strcpy(tmp,str+maxidx+1);
        strcpy(str+maxidx+1,substr);
        strcat(str+maxidx+1,tmp);
        printf("%s\n",str);

    return 0;
}
