#include<iostream>
#include<map>
using namespace std;
int num[100100];
int main(){
    int i,j;
    int N,M,val,check;
    char op;
    cin>>N>>M;
    for(int i =0 ; i<N;++i){
        cin>>num[i];
    }
    for(int j = 0 ; j<M;++j){
        cin>>op;
        cin>>val;
        if(op=='C'){
            for(int i =0 ;i <N;i++){
                num[i]+=val;
                num[i]%=65536;
            }
        }else if(op=='Q'){
            int cnt = 0;
            for(int i = 0 ;i<N;++i ){
                cnt+= (num[i]>>val) & 0x1;
            }
            cout<<cnt<<endl;
        }
    }
  return 0;
}