#include "queue_tp.h"

template <typename T>
QueueTP<T>::QueueTP(const T& t) {
  head = new Node;
  tail = head;
  head->val = t;
  head->next = tail->next = NULL;
}

/* template <typename T>
QueueTP<T>::QueueTP(T t) {
  head = new Node;
  tail = head;
  head->val = t;
  head->next = tail->next = NULL;
} */

template <typename T>
QueueTP<T>::QueueTP(const QueueTP & q) {
  head = new Node;
  Node* temp = head;
  Node* other_temp = *(q.head);
  while(other_temp != NULL) {
    temp->val = other_temp->val;
    temp->next = new Node;
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
  Node* cur = head->next;
  delete head;
  while(cur != NULL) {
    head = cur;
    cur = cur->next;
    delete head;
  }
}

template <typename T>
void QueueTP<T>::Push(const T& t) {
  if(IsEmpty()) {
    head = new Node;
    head->val = t;
    tail = head;
  } else {
    tail->next = new Node;
    tail = tail->next;
    tail->val = t;
  }
}

/*
template <typename T>
void QueueTP<T>::Push(T t) {
  if(IsEmpty()) {
    head = new Node;
    head->val = t;
    tail = head;
  } else {
    tail->next = new Node;
    tail = tail->next;
    tail->val = t;
  }
}
*/

template <typename T>
T QueueTP<T>::Pop() {
  T ret = head->val;
  Node* temp = head;
  head = head->next;
  delete temp;
  return ret;
}
