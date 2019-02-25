#include<iostream>
#include<cstdio>
#include<algorithm>
#include<set>
#include<map>
#include<stdlib.h>
#include<vector>
using namespace std;

struct node{
    int idx;
    int ti;
    node(int i, int t){
        idx =i; ti =t;
    }    
    bool operator<(const node & op)  const{
        if(this->idx == op.idx)
            return false;
        else{
            if(this->ti==op.ti){
                return this->idx < op.idx;
            }else{
                return this->ti < op.ti;
            }
        }
    }
};

set<node> st;

int main(){
    st.insert(node(1,1));
    st.insert(node(1,2));
    st.insert(node(1,3));
    st.insert(node(2,2));
    st.insert(node(4,2));
    for(set<node>::iterator it = st.begin();it!=st.end();++it){
        printf("%d %d\n",it->idx,it->ti);
    }
}