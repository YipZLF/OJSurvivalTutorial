#include<iostream>
#include<cstdio>
#include<stack>
using namespace std;
int n;
struct S{
    int w;
    int h;
}s[50050];
stack<S> st;

int main(){
    int n;
    while(scanf("%d",&n) && n!=-1){
        int maxs = 0;
        scanf("%d%d",&s[0].w,&s[0].h);
        st.push(s[0]);
        for(int i = 1;i<n;++i){
            scanf("%d%d",&s[i].w,&s[i].h);
            if(s[i].h > st.top().h){
                st.push(s[i]);
            }else{

                int tmpw=0;
                while(!st.empty()&&s[i].h<=st.top().h ){
                    tmpw += st.top().w;
                    maxs = max(maxs,st.top().h * tmpw);
                    st.pop();
                }
                S tmp;
                tmp.w = tmpw+s[i].w;
                tmp.h = s[i].h;
                st.push(tmp);
            }
        }
        int tmp = 0;
        while(!st.empty())
        {
            tmp += st.top().w;
            maxs = max(maxs, tmp* st.top().h);
            st.pop();
        }
        printf("%d\n",maxs);
    }
}