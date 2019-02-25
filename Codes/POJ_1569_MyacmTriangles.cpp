#include<iostream>
#include<cstdio>
#include<algorithm>
#define EPS 1e-6
using namespace std;

struct Point{
    char name;
    int x,y;
    Point(int xx,int yy) x(xx),y(xx){}
}p[20];

double operator^(Point &a, Point&b){
    return a.x*b.y-a.y*b.x;
}

Point operator-(Point &a, Point&b){
    return Point(a.x-b.x,a.y-b.y);
}

int judge(Point &segStart,Point& segEnd, Point p){
    double ans = ((segEnd-segStart)^(p-segStart));
    if(ans <= EPS && -EPS<=ans)
        return 0;//at the line
    else if(EPS<ans){
        return 1;//at the left side
    }else{
        return 2;//at the right side
    }
}

double abs(double val){
    if (val <0)
        return -val;
    else
        return val;
}

bool avail(int s,int e1,int e2){
    bool isClockwise=(((p[e1]-p[s])^(p[e2]-p[s]))<-EPS);
    if(isClockwise){
        for(int i = 0; i!= s && i<num;++i){
            for(int j =i+1; j!=e1 && j<num;++j){
                for(int k = j+1; k!=e2 && k < num;++k){
                    
                }
            }
        }
    }
}

int main(){
    int num,maxP[3];
    double maxans=-EPS;
    while(scanf("%d",&num)&&num){
        maxans=-EPS;
        for(int i = 0 ; i < num; ++i){
            scanf("%c%d%d",&p[i].name,&p[i].x,&p[i].y);
        }
        for(int i = 0; i < num;++i){
            for(int j = i+1; j < num ;++j){
                for(int k = j+1; k < num ; ++k){
                    doubel area=abs(((p[j]-p[i])^(p[k]-p[i])));
                    if(area > maxans){
                        if(avail(i,j,k)){
                            maxP[0]=i;
                            maxP[1]=j;
                            maxP[2]=k;
                            maxans = area;
                        }
                    }
                }
            }
        }
        printf("%c%c%c\n",p[maxP[0]].name,p[maxP[1]].name,p[maxP[2]].name);
    }
}