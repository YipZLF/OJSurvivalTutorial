#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;

bool function(vector<int> & seq)
{
    bool isValid = true;
    vector<int> _stack(seq.size(),0);
    int maxnum=0,top=0;
    for(int i=0;i<seq.size();i++){
        if(seq[i] > maxnum){
            for(int j = maxnum+1;j<seq[i];j++){
                _stack[top++]=j;
            }
            maxnum = seq[i];
        }
        else{
            if(seq[i] != _stack[--top])
                isValid = false;
        }
    }
    return isValid;
}

int main()
{
    vector<int> seq;
    seq ={3,1,2,4};
    cout<<seq[0]<<endl;
    if(function(seq))
        cout<<"Valid"<<endl;
    else
        cout<<"Invalid."<<endl;
    return 0;
}
