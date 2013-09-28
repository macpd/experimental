#ifndef QUEUE_TP_H_
#define QUEUE_TP_H_

#include <cstddef>


template <typename T>
class QueueTP {
  private:
      class Node {
        public:
          T val;
          Node* next;
          Node() {next = NULL;}
          Node(Node & n) { val = n->val; next = NULL; }
          explicit Node(const T& t) {val = t; next = NULL;}
          Node(const T& t, const Node* n) { val = t; next = n;}
          // NOTE: assignment sets value of next to NULL
          Node & operator=(const Node n) {
            val = n->val;
            next = NULL;
          }
      };
    Node* head;
    Node* tail;
    QueueTP<T> & operator=(const QueueTP<T>);
  public:
    QueueTP() { head = tail = NULL; };
    QueueTP(const T & t);
    // QueueTP(T t);
    QueueTP(const QueueTP &);
    ~QueueTP();
    void Push(const T&);
    T Pop();
    bool IsEmpty() const { return head == NULL ? true : false; }
};

#endif
