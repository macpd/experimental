#include "queue_tp.h"
#include "queue_tp.cc"
#include <iostream>
#include <string>

int main() {
  using std::string;
  QueueTP<string> s_queue;

  QueueTP<int>* del = new QueueTP<int>;
  delete del;

  QueueTP<int> int_queue;

  for(int i = 0; i < 10 ; i++) {
    int_queue.Push(i);
  }

  std::cout << "3 strings please:" << std::endl;
  string temp;
  for(int i = 0; i < 3; i++) {
    getline(std::cin, temp);
    s_queue.Push(temp);
  }

  while(!int_queue.IsEmpty()) {
    std::cout << int_queue.Pop() << std::endl;
  }

  while(!s_queue.IsEmpty()) {
    std::cout << s_queue.Pop() << std::endl;
  }
}
