#include<stdio.h>
int main(){
int n=10, s=0,i,j,k;
for( k = 1; k < n - 1; k++)
    for( j = n; j >= k; j--)
        s = s + 1;
printf("%d",s);
}
