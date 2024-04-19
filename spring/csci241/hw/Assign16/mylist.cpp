#include "mylist.h"

template <class T> 
mylist<T>::~mylist() {
  clear();
}

template <class T> 
mylist<T>::mylist(const mylist<T>& x) {
   
}
template <class T> 
mylist<T>& mylist<T>::operator=(const mylist<T> &x) {

}
template <class T>
void mylist<T>::clear() {

}
template <class T>
size_t mylist<T>::size() const {
  
}
template <class T>
bool mylist<T>::empty() const {

}
template <class T> 
T& mylist<T>::front() const {

}
template <class T> 
const T& mylist<T>::back() {

}
