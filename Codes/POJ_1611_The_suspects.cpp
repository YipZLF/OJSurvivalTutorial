#include<iostream>
#define N 30000
using namespace std;
int parents[N];
int number[N];

int getRoot(int a)
{
    if(parents[a]!=a)
    {
        parents[a] = getRoot(parents[a]);
    }
    return parents[a];
}

void Merge(int a,int b)
{
    int pa = getRoot(a);
    int pb = getRoot(b);
    if(pa==pb)  return;
    else{
        parents[pb] = pa;
        number[pa] += number[pb];
    }
}

int main()
{
    int m,n,k,a,b;
    while(scanf("%d %d",&n,&m)==2)
    {
        if (n==0 && m ==0)
            break;
        else{
        for(int i = 0; i < n;i++)
        {
            parents[i] = i;
            number[i] = 1;
        }
        for(int j = 0; j < m; j++){
            scanf("%d %d",&k,&a);
            for(int i = 1; i<k;i++)
            {
                scanf("%d",&b);
                Merge(a,b);
            }
        }
        printf("%d\n",number[getRoot(0)]);
        }
    }
    return 0;
}
