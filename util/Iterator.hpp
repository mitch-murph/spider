#ifndef ITERATOR_H
#define ITERATOR_H

template <typename T>
class Iterator {
private:
    const std::vector<T*> *ptr;
    size_t position;
public:
    Iterator(const Iterator&);
    Iterator(std::vector<T*>&, size_t);
    ~Iterator();
    Iterator operator=(const Iterator&);
    bool operator==(const Iterator&) const;
    bool operator!=(const Iterator&) const;
    Iterator operator++();
    Iterator operator++(int);
    T* operator*() const;
    T* operator->() const;
};

template <class T> Iterator<T>::Iterator(const Iterator& other){
    ptr = other.ptr;
    position = other.position;
}
template <class T> Iterator<T>::Iterator(std::vector<T*>& r, size_t position){
    this->ptr = &r;
    this->position = position;
}
template <class T> Iterator<T>::~Iterator(){}
template <class T> Iterator<T> Iterator<T>::operator=(const Iterator& other){
    return Iterator(*this);
}
template <class T> bool Iterator<T>::operator==(const Iterator& other) const {
    return (ptr == other.ptr && position == other.position);
}
template <class T>bool Iterator<T>::operator!=(const Iterator& other) const {
    return !(*this == other);
}
template <class T> Iterator<T> Iterator<T>::operator++(){
    position++;
    return *this;
} 
template <class T> Iterator<T> Iterator<T>::operator++(int){
    Iterator temp = *this;
    ++position;
    return temp;
}
template <class T> T* Iterator<T>::operator*() const {
    return (*ptr)[position];
} 
template <class T> T* Iterator<T>::operator->() const {
    return *(*ptr)[position];
}

#endif