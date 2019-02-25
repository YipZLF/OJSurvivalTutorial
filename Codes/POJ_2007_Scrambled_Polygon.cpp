#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define Point Vector
using namespace std;
struct Vector{
    double x,y;
    Vector(double xx,double yy): x(xx),y(yy){ }
    Vector(){}
    double operator^(const Vector & q)const{
        return x*q.y - y*q.x;
    }
};

Vector operator-(const Vector&p,const Vector&q){
    return Vector(p.x-q.x, p.y-q.y);
}

bool operator<(const Vector&p, const Vector&q){
    return ((q-Point(0,0)) ^ (p-Point(0,0)))<0;
}


Point ps[60];
int main(){
    freopen("2007.in","r",stdin);
    int n = 0 ; 
    while(scanf("%lf %lf",&ps[n].x,&ps[n].y)!=EOF){
        n++;
    }
    sort(ps+1,ps+n);
    for(int i = 0 ; i < n;i++){
        printf("(%d,%d)\n",(int)ps[i].x,(int)ps[i].y);
    }
    return 0;
}