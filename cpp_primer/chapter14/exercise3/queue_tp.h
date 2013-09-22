#ifndef QUEUE_TP_H_
#define QUEUE_TP_H_

#include <cstddef>


template <typename T>
class QueueTP {
  private:
    template <typename TT>
      class Node {
        public:
          TT val;
          Node<TT>* next;
          Node() {next = NULL;}
          Node(Node<TT> & n) { val = n->val; next = NULL; }
          explicit Node(const TT& t) {val = t; next = NULL;}
          Node(const TT& t, const Node<TT>* n) { val = t; next = n;}
          // NOTE: assignment sets value of next to NULL
          Node<TT> & operator=(const Node<TT> n) {
            val = n->val;
            next = NULL;
          }
      };
    Node<T>* head;
    Node<T>* tail;
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
