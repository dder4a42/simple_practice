#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include<iostream>
using namespace std;

template<typename T>
class Sqlist{
    //storage datas of elements
    T *storage;
    //the valid size of array
    int length;
    //max length of array
    int capacity;
    //as its name suggest
    const static int Default_capacity = 5;
    //double the capacity
    void expand();
public:
    template<typename U>
    friend ostream & operator<<(ostream & os, Sqlist<U> & a);

    Sqlist(int t = Sqlist::Default_capacity, T val = 0);
    Sqlist(const Sqlist& a);
    Sqlist & operator=(const Sqlist &a);    
    ~Sqlist() {delete [] storage;}
    //get numbers of valid elements
    int size() const {return length;}

    //return the i-th element,check the index.
    T & at(int);
    T & operator[] (int index) {return storage[index];}
    const T & operator[] (int index) const {return storage[index];}

    //delete all the element whose value is x.
    void del_val(T x);
    //insert elemrnt to i-th
    int insert(int index, const T& ele);
    //find x in [lh,rh),return its index.if not, return -1.
    int find(const T& a, int lh=0, int rh=0) const;
    //remove interval, return numbers of deleted element.
    int remove(int lh, int rh);
    int remove(int index);
};

template <typename T>
Sqlist<T>::Sqlist(int t, T val):capacity(t), length(0) {
    storage = new T [capacity];
    for(;length<capacity;length++){
        storage[length] = val;
    }
}
template <typename T>
Sqlist<T>::Sqlist(const Sqlist& a){
    capacity = a.capacity;
    storage = new T [2*a.capacity];
    for(length=0;length<capacity;length++){
        storage[length] = a.storage[length];
    }
}

template <typename T>
void Sqlist<T>::expand(){
    if(length < capacity) return;
    T* old_storage = storage;
    storage = new T [capacity <<= 1];//capacity *= 2
    for(int i = 0;i < length;i++)
        storage[i] = old_storage[i];
    delete [] old_storage;
}

template <typename T>
T &Sqlist<T>::at(int index)
{
    if(index >= length)
        {throw "error index";}
    else if(index >= 0)
        {return storage[index];}
    else if(-index < length)
        {return storage[(index+length)%length];}
    else{throw "error index";}
}

template <typename T>
Sqlist<T> &Sqlist<T>::operator=(const Sqlist &a){
    if(this == &a) return *this;
    delete [] storage;
    capacity = a.capacity;
    storage = new T [capacity];
    for(length=0;length<a.length;length++)
        storage[length] = a.storage[length];
    return *this;
}

template<typename T>
void Sqlist<T>::del_val(T x){
    int k=0,i=0;//i快指针，k慢指针
    for(i=0;i<length;i++)
        if(storage[i] != x) {storage[k++] = storage[i];}
    length = k;
}

template <typename T>
int Sqlist<T>::insert(int index, const T &ele){
    expand();
    for(int i=length;i>index;i--)
        storage[i] = storage[i-1];
    storage[index] = ele;
    length++;
    return index;
}

template <typename T>
int Sqlist<T>::find(const T &a, int lh, int rh)const{
    if(lh<0 || rh>=length) throw "error index";
    if(rh==0) rh=length;
    for(;lh<rh;lh++){
        if(a == storage[lh]) return lh;
    }
    return -1;
}

template <typename T>
int Sqlist<T>::remove(int lh, int rh){
    if(lh<0) return -1;
    while(rh<length) storage[lh++] = storage[rh++];
    length = lh;
    return rh-lh;
}

template <typename T>
int Sqlist<T>::remove(int index){
    return remove(index, index+1);
}

template<typename U>
ostream &operator<<(ostream &os, Sqlist<U> &a){
    os << "[";
    for(int i=0;i<a.length;i++){
        os << a[i] << (i<a.length-1 ? ',' : ']');
    }
    return os;
}

#endif