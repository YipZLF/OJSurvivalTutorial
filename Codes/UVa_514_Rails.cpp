#include<iostream>
#include<cstdio>
#include<stack>
using namespace std;
int a[1010];
int N;

bool isValid(){
    stack<int> st;
    st.push(0);
    int cur = 0;
    for(int i = 0 ; i < N ;++i){
        if(st.top()>a[i]){
            return false;
        }else{
            if(st.top()==a[i]){
                st.pop();
            }else{
                int j;
                for(j =cur+1;j<a[i];++j){
                    st.push(j);
                }
                cur = j;
            }
        }
    }
    return true;

}

int main(){
    freopen("514.in","r",stdin);
    while(scanf("%d",&N)&& N){
        while(true){
            scanf("%d",&a[0]);
            if(a[0]==0)
                break;
            for(int i = 1 ;i<N;++i){
                scanf("%d",a+i);
            }
            if(isValid()){
                cout<<"Yes"<<endl;
            }else{
                cout<<"No"<<endl;
            }
        }
        cout<<endl;
    }
}