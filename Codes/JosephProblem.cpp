#include<iostream>
#include<cstdio>
using namespace std;
struct node{
    int index;
    struct node * next;
};


int main()
{
    int m,n,idx = 0;
    cin>>n>>m;
    for(int i = 2;i<=n; i++){
        idx = (idx + m)% i ;
    }
    cout<<idx+1;
}
   /* struct node* ptr, * tmp;
    struct node* head = new struct node;
    head->index = 1;
    ptr = head;
    for(int i = 2; i <= n ;i++){
        ptr->next = new struct node;
        ptr = ptr->next;
        ptr->index = i;
    }
    ptr->next = head;

    while(n>1){
        for(int i = 0 ; i < m; i++){
            tmp = ptr;
            ptr = ptr->next;
        }
        tmp->next = ptr->next;
        delete ptr;
        ptr = tmp;
        n--;
    }
    printf("%d",ptr->index);
}
*/
