#include<iostream>
#include<cstdio>
#include<string>
#include<string.h>
#include<stack>
#include<queue>
using namespace std;

struct node{
    char name[20];
    int Next,Sub;
    node(){
        Next = -1;Sub = -1;
    }
};

struct node tree[100];

queue<int> qe;

int Search(int index,char sName[20]){
    qe.push(0);
    while(!qe.empty()){
        index = qe.front();qe.pop();
        if(tree[index].Sub!=-1)
            qe.push(index);
        bool flag = true;
        for(int i = 0; tree[index].name[i] && sName[i];i++){
            if(tree[index].name[i] != sName[i])
                {flag = false; break;}
        }
        if(flag)
            return index;
        index = tree[index].Next;
    }
    return -1;
}

int main(){
    freopen("Material.in","r",stdin);
    int T;
    scanf("%d\n",&T);
    while(T--){
        stack<int> st;
        st.push(0);
        memset(tree,0,sizeof(tree));
        char tmp[20],line[20];
        int lineSize=20;
        int cnt = 0;

        while(true){
            cin.getline(line, lineSize, '\n');
            sscanf(line, "%s", tmp);
            cout<<cnt<<" "<<tmp[0]<<endl;
            if(tmp[0]=='{'){
                cin.getline(line, lineSize, '\n');
                sscanf(line, "%s", tmp);

                cout<<cnt<<" "<<tmp[0]<<endl;
                tree[st.top()].Sub = cnt++;
                st.push(cnt);
                strcpy(tree[cnt].name,tmp);
            }
            else if(tmp[0]=='}'){
                tree[st.top()].Next = -1;
                if(st.size()==1)
                    break;
                st.pop();
            }
            else{
                tree[st.top()].Next = cnt++;
                st.pop();st.push(cnt);
                strcpy(tree[cnt].name,tmp);
            }
        }


        cin.getline(line, lineSize, '\n');
        sscanf(line, "%s", tmp);
        cin.getline(line, lineSize, '\n');
        cin.getline(line, lineSize, '\n');
        int idx = Search(0,tmp);

        if(idx == -1)
            cout<<"No\n";
        else{
            while(tree[idx].Next!=-1){
                cout<<tree[idx].name;
                idx = tree[idx].Next;
            }
        }
    }
    return 0;
}
