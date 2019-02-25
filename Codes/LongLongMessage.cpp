#include<iostream>
#include<cstring>
using namespace std;
const int MAXN = 200020;
int wa[MAXN],wb[MAXN],wv[MAXN],Ws[MAXN];
int sa[MAXN],Rank[MAXN],height[MAXN];
char str[100010],obj[MAXN];
void buildSA(const char * str, int * sa, int n, int m)
{
    /*
    str: 字符串
    sa：位置->名次 映射
    n:字符串长度
    m:一开始：字符的种类个数，也就是1-后缀的个数，后来变成 不同的j-后缀的个数。
    example: buildSA("banana",sa,6,100);
    */
    int i, j, p , * pm = wa, *k2sa = wv,*t;

    /* 进入循环前的初始化以及第一次操作*/
    for(i = 0 ; i < m ;++i) // memset(Ws,0,sizeof(Ws)); 把计数数组清零
        Ws[i] = 0;
    for(i = 0 ; i < n; ++i) //开始计数,pm是str的复制品,Ws[i]是字符i出现的次数；
        Ws[pm[i] = str[i]]++;//排名不连续，只能保证相对大小正确
    for(i = 1; i<m ; ++i)   //类似积分，类似概率分布函数和累计函数的区别
        Ws[i] += Ws[i-1];   //Ws[i]是编码不大于i的字符出现的次数，也是【排名】不大于i的字符出现的次数
    for(i = n-1; i>=0; i--) //计算名次。注意这里有几个约定：名次从0开始算；排名相同的，越靠右名次越大。
        sa[--Ws[pm[i]]] = i;

    /*进入循环:每次循环开始前：知道j-后缀信息，要求2j-后缀信息。sa[i]是名次为i的j后缀的位置,
    pm[i]是排名为i的j-后缀的排名；j>1时，m是不同j-后缀的个数.
    k2sa[i]是2j-后缀按照第二关键字排序后，名次为i的2j-后缀的起始位置*/
    for(j = p = 1; p<n ; j <<=1, m=p){
        for(p = 0, i=n-j ; i<n ; ++i )//2j-后缀没有第二个关键字的，应该排名均为0.排名相同，越靠左名次越小
            k2sa[p++] = i;  //确定了k2sa[0]-k2sa[j-1]
        for(i = 0; i<n ; ++i)   //确定k2sa[j]往后的,所有第二关键字都是位置>=j的，这里遍历n个j-后缀
            if(sa[i] >= j)
                k2sa[p++] = sa[i] - j;
        //在这里第二关键字排名相同的，第一关键词名次是正确的，因为是从右边往左边（由大往小）收集的。
        //这是基数排序的细节
        for(i = 0; i < m; ++i)
            Ws[i] = 0;
        for(i = 0 ; i < n ; ++i)
            Ws[wv[i] = pm[k2sa[i]]] ++; //wv复制了排名数组,wv[i]的值是2j-后缀第二关键字的唯一标识符
        for(i = 1 ; i <= m; ++i)
            Ws[i] += Ws[i-1];
        for(i = n-1; i>=0 ;--i)
            sa[--Ws[wv[i]]] = k2sa[i];
        //循环内操作与循环前操作对照：
        //wv[i]--字符的编码值ASCII str[i]
        //k2sa[i]--字符str[i]的名次，或者说位置，或者说下标i


        t = pm; pm = k2sa; k2sa = t;
        pm[sa[0]] = 0; 
        p = i = 1;
        for(;i<n;++i){//按名次遍历2j-后缀。p为目前发现的，不同的2j-后缀个数
            int a = sa[i - 1], b = sa[i];
            if(k2sa[a] == k2sa[b] && k2sa[a+j] == k2sa[b+j])
                pm[sa[i]] = p-1;
            else
                pm[sa[i]] = p++;
        }  
    }
    return ;
}

void buildHeight(char * str,int *sa,int n, int * Rank){
/* Height[i]为LCPL(i-1,i)最长公共前缀长度
    H[i] = LCPL(sa[Rank[i]-1],i)
    使用这个函数要注意要求Rank[0]>0，所以用这个函数求Height可以把字符串结尾的\0也当成字符串的一部分
    buildSa("abcd",sa,5,130);
    buildHeight("abcd",5,sa,Rank)；
*/
    int i , j ,k;
    for(i = 0 ; i < n; ++i){
        Rank[sa[i]] = i; //初始化rank数组，sa:位置->名次, rank:名次->位置
    }
    for(i = 0; i < n-1;){
        if(k!=0)
            k--;    //H[i] >= H[i-1]-1
        else{
            j = sa[Rank[i]-1];
        }
        while(str[i+k]==str[j+k])
            k++;
        height[Rank[i]] = k;
    }
}

int main(){
    freopen("llmessage.in","r",stdin);
    scanf("%s",obj);
    scanf("%s",str);
    cout<<strlen(obj)<<endl;

    strcat(obj,"\0*");
    cout<<strlen(obj)<<endl;
    
    buildSA(obj,sa,strlen(obj)+strlen(str)+3,30);
    buildHeight(obj,sa,strlen(obj)+strlen(str)+3,Rank);
}