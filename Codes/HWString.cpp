#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char hw[51][51],a[50],b[50],c[50],_str[50];

char* lowerCase(char * str)
{
    for(int i =0; str[i];i++){
        if('A'<=str[i] && str[i]<='Z'){
            str[i] -= 'A'-'a';
        }
    }
    return str;
}

bool match(char* str)
{
    strcpy(_str,str);
    lowerCase(_str);
    bool isMatch = true;
    int i = 0,j = 0;

    for(i = 0; a[i];i++){
        if(_str[i]!=a[i]){
            return false;
        }
    }
    isMatch = false;
    for(j = 0; b[j];j++){
        if(b[j]==_str[i])
            {isMatch = true; break;}
    }
    if(!isMatch)
        return false;
    i++;
    for(j = 0; c[j];j++){
        if(_str[i++]!=c[j])
            return false;
    }
    return isMatch;
}

int main()
{
    freopen("HWString.in","r",stdin);
    int n;
    cin>>n;
    for(int i = 0; i<n;i++){
        scanf("%s",hw[i]);
    }
    scanf("\n%[^[]",a);
    lowerCase(a);
    scanf("[%[^]]",b);
    lowerCase(b);

    scanf("]%s",c);
    lowerCase(c);

    for(int i = 0 ; i<n;i++){
        if(match(hw[i]))
            printf("%d %s\n",i+1,hw[i]);
    }
}
