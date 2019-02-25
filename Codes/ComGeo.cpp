#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

class CVector{
public:
    double x,y;

    CVector(int _x, int _y){
        x = _x;y=_y;
    }

    
};
CVector operator +(CVector p, CVector q){
        return CVector(p.x+q.x,p.y+q.y);
}

CVector operator -(CVector p, CVector q){
    return CVector(p.x-q.x,p.y-q.y);
}

CVector operator *(double k, CVector q){
    return CVector(k* q.x,k* q.y);
}

double operator*(CVector p,CVector q){
    return (p.x*q.x+p.y*q.y);
}

double length(CVector p){
    return sqrt(p*p);
}

CVector unit(CVector p){
    return 1/length(p)* p;
}

double dot(CVector p,CVector q){
    return (p.x*q.x+p.y+q.y);
}

double project(CVector p, CVector n){
    return dot(p,unit(n));
}

double operator^(CVector p,CVector q){
    return (p.x*q.y-p.y*q.x);
}


int main(){
    return 0;
}