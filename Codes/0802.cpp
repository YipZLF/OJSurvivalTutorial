/*把输入变成数字存好，保存一个数组维护号码重数，*/
#include<iostream>
#include<cstdio>
using namespace std;
int number[100100];
char str[210];
const int c2n[26] = {2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,0,7,7,8,8,8,9,9,9,0};

int char2Int(char c){
    if('0'<=c && c<='9')
        return c-'0';
    else if('a'<=c && c<='z')
        return c2n[c-'a'];
    else if('A'<=c && c<='Z')
        return c2n[c-'A'];
}

void Sort(int start,int end){
    for( int i = 0 ; i <= end; i++){
        int minIdx = i,minVal = 0xffffff;
        for(int j = i ; j <= end; ++j){
            if(number[j]<minVal){
                minIdx = j;
                minVal = number[j];
            }
        }
        int tmp = number[i];
        number[i] = number[minIdx]; 
        number[minIdx] = tmp;
    }

}

int main(){
    freopen("0802.in","r",stdin);
    int n ;
    scanf("%d",&n);
    for(int i = 0 ; i < n;i++){
        scanf("%s",str);
        for(int j = 0 ; str[j];++j){
            if(str[j]=='-')
                continue;
            else
                number[i] = number[i] * 10 + char2Int(str[j]);
        }
    }
    Sort(0,n-1);
    
    bool dup = false;
    int cnt = 1,tmp=number[0];
    for(int i = 1 ; i < n;i++){
        if(number[i]==tmp){
            cnt++;
            dup = true;
        }else{
            if ( cnt >1){
                cout<<tmp/10000<<'-'<<tmp%10000;
                cout<<' '<<cnt<<endl;
            }
            tmp = number[i];cnt = 1;
        }
    }
    if(!dup)
        cout<<"No duplicates.\n";
    return 0;
}