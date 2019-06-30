#ifndef STACK_H
#define STACK_H

#include <vector>

template <typename T>
class Stack {
protected:
    std::vector<T* > v;
public:
    void push(T*);
    void pop();
    bool empty();
    size_t size();
    T* top();
    T* get(int);
};

template <typename T> void Stack<T>::push(T* t){
    v.push_back(t);
}
template <typename T> void Stack<T>::pop(){
    v.pop_back();
}
template <typename T> bool Stack<T>::empty(){
    return size() == 0;
}
template <typename T> size_t Stack<T>::size(){
    return v.size();
}
template <typename T> T* Stack<T>::top(){
    return get(v.size()-1);
}
template <typename T> T* Stack<T>::get(int i){
    return v[i];
}

#endif