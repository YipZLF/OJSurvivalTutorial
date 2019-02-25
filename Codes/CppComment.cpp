#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
char codeLine[210],outputLine[210];

int main()
{
    freopen("CppComment.in","r",stdin);
    bool inComment = false;
    int i = 0;
    do{
    cin.getline(codeLine,210);
    cout<<codeLine;
    if(inComment){
        for(i = 0;codeLine[i];i++){
            if(codeLine[i++]=='*'){
                if(codeLine[i++]=='/'){
                    inComment = false;
                    break;
                }
            }
        }
        for(;codeLine[i];i++){
            outputLine[i] = codeLine[i];
        }
    }else{
        for(i = 0;codeLine[i];i++){
            if(codeLine[i]=='/'){
                if(codeLine[i+1]=='*'){
                    inComment = true;
                    break;
                }
            }
            outputLine[i] = codeLine[i];
        }
    }
    //cout<<outputLine;
    }while(codeLine[0]!=NULL);
    return 0;
}
