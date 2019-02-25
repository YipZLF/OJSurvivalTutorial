#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int num[400010];

struct node{
    int l, r;
    long long nsum;
    long long add;
}seg[400010];

void Build(int i,int left,int right){
    seg[i].l = left;
    seg[i].r = right;
    seg[i].add = 0;
    if(left==right){
        seg[i].nsum = num[i];
        return ;
    }
    int mid = (left+right)>>1;
    Build(i<<1,left,mid);
    Build((i<<1)+1,mid+1,right);
    seg[i].nsum =seg[i<<1].nsum+seg[(i<<1)+1].nsum;
}

void Add(int i , int left,int right, long long c){
    if(seg[i].l== left && seg[i].r==right){
        seg[i].add += c;
        return ;
    }
    seg[i].nsum += c*(right-left+1);
    int mid=(seg[i].l+seg[i].r)>>1;
    if(right <= mid){
        Add(i<<1,left,right,c);
    }else if(mid<left ){
        Add((i<<1)+1,left,right,c);
    }else{
        Add(i<<1,left,mid,c);
        Add((i<<1)+1,mid+1,right,c);
    }
}

long long Query(int i,int left,int right){
 
    if(seg[i].l==a&&seg[i].r==b)
    {
        return seg[i].nsum+(b-a+1)*seg[i].add;
    }
    seg[i].nsum+=(seg[i].r-seg[i].l+1)*seg[i].add;
    int mid=(seg[i].l+seg[i].r)>>1;
    Add(i<<1,seg[i].l,mid,seg[i].add);
    Add(i<<1|1,mid+1,seg[i].r,seg[i].add);
    seg[i].add=0;
    if(b<=mid)  return Query(i<<1,a,b);
    else if(a>mid)  return Query(i<<1|1,a,b);
    else return Query(i<<1,a,mid)+Query(i<<1|1,mid+1,b);
}
 /*   if(seg[i].l ==left && seg[i].r==right){
        return seg[i].nsum+ (seg[i].r-seg[i].l +1)* seg[i].add;
    }
    seg[i].nsum += (seg[i].r-seg[i].l +1)* seg[i].add;
    int mid = (seg[i].l+seg[i].r)>>1;
    Add(i<<1,seg[i].l,mid,seg[i].add);
    Add((i<<1)+1,mid+1,seg[i].r,seg[i].add);
    seg[i].add = 0;

    if(right <= mid){
        return Query(i<<1,left,right);
    }else if(left > mid){
        return Query((i<<1)+1,left,right);
    }else{
        return  Query(i<<1,left,mid)+ Query((i<<1)+1,mid+1,right);
    }
*/
}

int main(){
    freopen("0611.in","r",stdin);
    int n,m,i;
    int a,b,c;
    char s[10];
    while(~scanf("%d%d",&n,&m)){
        for(i = 1;i<=n;i++){
            scanf("%d",num+i);
        }
        Build(1,1,n);
        for(i = 0; i < m ; i++){
            scanf("%s",s);
            if(s[0]=='C'){
                scanf("%d%d%d",&a,&b,&c);
                Add(1,a,b,c);
            }else{
                scanf("%d %d",&a,&b);
                printf("%lld\n",Query(1,a,b));
            }
        }
    }
    return 0;
}