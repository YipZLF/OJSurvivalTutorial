#include<iostream>
#include<cstdio>
using namespace std;
const int MAX = 2100;
int parent[MAX],gender[MAX];

//return gender to root
int getGender(int a, int &r)
{
    int g;
    if(parent[a]==a)
    {
        r = a;
        return 0;
    }
    else
    {
        g = getGender(parent[a],r);
        parent[a] = r;
        gender[a] = (gender[a] + g)%2;
        return gender[a];
    }
}

void Merge(int a, int b)
{
    int ga,gb,pa,pb;
    ga = getGender(a,pa);
    gb = getGender(b,pb);

    {
        parent[pb] = pa;
        gender[pb] = (ga+1+gb)%2;
    }
}
int main()
{
    freopen("2492.in","r",stdin);
    int numSen,numBugs,numInter;
    scanf("%d",&numSen);
    for(int i = 1; i <= numSen; i++)
    {
        printf("Scenario #%d:\n",i);
        bool susFound=false;
        scanf("%d %d",&numBugs,&numInter);
        for (int j = 1; j<= numBugs;j++)
        {
            parent[j] = j;
            gender[j] = 0;
        }

        while(numInter)
        {
            int a,b,pa,pb;
            scanf("%d %d",&a,&b);
            int ga = getGender(a,pa);
            int gb = getGender(b,pb);
            if(pa==pb)
            {
                if(ga==gb)
                    {susFound = true;}
            }
            else
                    Merge(a,b);

            numInter--;
        }

        if(susFound)
            printf("Suspicious bugs found!\n\n");
        else
            printf("No suspicious bugs found!\n\n");
    }
    return 0;
}
