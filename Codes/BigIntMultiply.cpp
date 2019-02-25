#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;
int a[205],b[205],c[510];
int main()
{
    freopen("BigIntMultiply.in","r",stdin);
    int alength,blength,mcarry = 0, pcarry = 0, i = 0, j =0;
    string str;
    cin>>str;
    alength = str.length();
    for( i = alength-1; i>=0 ; i--){
        a[alength-1-i] = str[i] - '0';
    }
    cin>>str;
    blength = str.length();
    for( i = blength-1; i>=0 ; i--){
        b[blength-1-i] = str[i] - '0';
    }

    for( i = 0; i < alength;i++){
        for ( j = 0 ; j < blength ; j++){
            c[i+j] += a[i] * b[j];
        }
    }

    i = 0;
    while(i<=alength+blength || c[i+1] != 0){
        c[i+1] += c[i] /10;
        c[i] %= 10;
        i++;
    }

    int flag = alength+blength+1;
    while(c[flag-1]==0){
        flag--;
    }

    str.clear();
    for( i = flag-1;i>=0; i--){
        str = str + (char)(c[i] + '0');
    }

    cout<<str<<endl;
}
