#include<iostream>
#include<map>
using namespace std;
int main(){
    int n = 0;
    cin>>n;
    while(n--){
        map<int,int> poly;
        int coef,pow;
        
        while(cin>>coef>>pow)
        {
            if(pow<0)break;
            if(poly.find(pow)!=poly.end())
                poly[pow]+=coef;
            poly.insert(make_pair(pow,coef));
        }
        while(cin>>coef>>pow){
            if(pow<0)break;
            if(poly.find(pow)!=poly.end())
                poly[pow]+=coef;
            else poly.insert(make_pair(pow,coef));
        }
        for(map<int,int>::reverse_iterator rit=poly.rbegin();rit!=poly.rend();++rit){
            if(rit->second !=0){
                cout<<"[ "<<rit->second<<" "<<rit->first<<" ] ";
            }
        }
        cout<<endl;
    }
}