#include<iostream>
#include<cstdio>
using namespace std;

struct node{
    int val;
    node* pL,*pR;
};
node Tree[10000];
int seq[10000];

int main()
{
    freopen("DFSTransform.in","r",stdin);
    int i = 0,offset = 0;
    while(scanf("%d ",seq+i++)==1){}
    offset = i/2;

}
