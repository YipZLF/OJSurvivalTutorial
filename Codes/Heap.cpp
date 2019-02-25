#include<iostream>
#include<cstdio>
using namespace std;


template<class T>
class MinHeap{
private:
    T* heapArray;
    int CurrentSize;
    int MaxSize;
    void BuildHeap();
public:
    MinHeap(const int n);
    virtual ~MinHeap{delete [] heapArray;};
    bool isLeaf(int pos) const;
    int leftChild(int pos) const
        {return 2*pos +1;}
    int rightChild(int pos) const
        {return 2*pos +2;}
    int parent(int pos) const;
        {return (pos-1)/2;}
    bool Remove(int pos, T& node);
    bool Insert(const T& newNode);
    T& RemoveMin();
    void SiftUp(int position);
    void SiftDown(int postion);
}

template<class T>
bool MinHeap<T>::ifLeaf(int pos){
    return (pos>=CurrentSize/2)&&(pos<CurrentSize);
}

template<class T>
bool MinHeap<T>::SiftDown(int pos){
    int i = pos;
    int j = pos*2+1;
    T tmp = HeapArray[pos];
    while(j<CurrentSize){
        if((j<CurrentSize-1) && (HeapArray[j]>HeapArray[j+1]))
            j++;
        if(tmp>HeapArray[j]){
            HeapArray[i] = HeapArray[j];
            i = j;j = j*2 +1;
            }
        else break;
    }
    HeapArray[i] = tmp;
}

template<class T>
bool MinHeap<T>::SiftUp(int pos){
    int temppos =position;
    T tmp =heapArray[temppos];
    while(tempos>0 && HeapArray[parent(tempos)]>tmp){
        HeapArray[temppos] = HeapArray[parent(tempos)];
        temppos = parent(temppos);
    }
    HeapArray[temppos]=tmp;
}


template<class T>
bool MinHeap<T>::Remove(int pos){
    return (pos>=CurrentSize/2)&&(pos<CurrentSize);
}
