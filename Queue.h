#ifndef _QUEUE_H
#define _QUEUE_H

#include "DoubleLinkedList.h"

template <class T> class Queue {
public:
  Queue() {}
  ~Queue() {}

  void insert(T value)  { data_.insertBack(value); }
  T remove()            { return data_.removeFront(); }
  T peek() const        { return data_.get(0); }
  bool isEmpty() const  { return data_.getSize() == 0; }
  void display() const  { data_.printList(); }
  int size() const { return data_.getSize(); }
private:
  DoubleLinkedList<T> data_;
};

#endif
