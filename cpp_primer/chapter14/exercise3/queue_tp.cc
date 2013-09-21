#include "queue_tp.h"

template <typename T>
QueueTP<T>::QueueTP(T& t) {
  head = new Node<T>;
  tail = head;
  head->val = t;
  head->next = tail->next = NULL;
}

template <typename T>
QueueTP<T>::QueueTP(T t) {
  head = new Node<T>;
  tail = head;
  head->val = t;
  head->next = tail->next = NULL;
}

template <typename T>
QueueTP<T>::QueueTP(const QueueTP & q) {
  head = new Node<T>;
  //*head = *(q.head);
  Node<T>* temp = head;
  Node<T>* other_temp = *(q.head);
  while(other_temp != NULL) {
    temp->val = other_temp->val;
    temp->next = new Node<T>;
    temp = temp->next;
    other_temp = other_temp->next;
  }
  tail = temp;
}

template <typename T>
QueueTP<T>::~QueueTP() {
  if(head == NULL) {
    return;
  }
  Node<T>* cur = head->next;
  delete head;
  while(cur != NULL) {
    head = cur;
    cur = cur->next;
    delete head;
  }
  delete tail;
}

template <typename T>
void QueueTP<T>::Push(T& t) {
  if(IsEmpty()) {
    head = new Node<T>;
    head->val = t;
    tail = head;
  } else {
    tail->next = new Node<T>;
    tail = tail->next;
    tail->val = t;
  }
}

/*
template <typename T>
void QueueTP<T>::Push(T t) {
  if(IsEmpty()) {
    head = new Node<T>;
    head->val = t;
    tail = head;
  } else {
    tail->next = new Node<T>;
    tail = tail->next;
    tail->val = t;
  }
}
*/

template <typename T>
T QueueTP<T>::Pop() {
  T ret = head->val;
  Node<T>* temp = head;
  head = head->next;
  delete temp;
  return ret;
}

template <typename T>
bool QueueTP<T>::IsEmpty() {
  return head == NULL ? true : false;
}

