#include<iostream>
#include<cstdio>
using namespace std;
const int MAX=31000;
int parent[MAX],sum[MAX],under[MAX];

int getRoot(int a)
{
    if(parent[a]==a) return a;
    else{
        int t = getRoot(parent[a]);
        under[a] += under[parent[a]];   //if pa is the lowest, under[pa]==0; if not, update under[a]
        parent[a] = t; //compress the path

        return parent[a];
    }
}


void Merge(int a,int b) //put a above b
{
    int pa = getRoot(a);
    int pb = getRoot(b);
    if(pa==pb) return;
    parent[pa] = pb;    //pa's parent becomes pb instead of the origin one.
    under[pa] = sum[pb];  //put a above b
    sum[pb]+=sum[pa];   // stack containing b becomes larger
}

int main()
{
    //initialization
    for(int i = 0; i < MAX; i++)
    {
        parent[i] = i;
        sum[i] = 1;
        under[i] = 0;
    }

    int p = 0;
    cin>>p;
    for(int i = 0; i< p; i++)
    {
        char s[20];
        int a,b;
        scanf("%s",s);
        if(s[0] == 'M')
        {
            cin>>a>>b;
            Merge(a,b);  //put a above b
        }
        else if(s[0] == 'C')
        {
            cin>>a;
            getRoot(a); //update under[a];
            cout<<under[a]<<endl;
        }
    }
    return 0;
}
