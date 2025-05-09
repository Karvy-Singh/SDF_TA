#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
using namespace std;

template <typename T> class Node {
public:
  T data;
  Node<T> *next;
  Node<T> *prev;
  Node<T>(T value) : data(value), next(nullptr), prev(nullptr) {}
};

template <typename T> class linkedlist {
private:
  Node<T> *head;
  Node<T> *tail;

public:
  linkedlist() : head(nullptr), tail(nullptr) {}

  Node<T> *getHead() const { return head; }

  // print from head
  void printfrwd() {
    if (head == nullptr) {
      return;
    }
    Node<T> *temp = head;
    while (temp->next != nullptr) {
      cout << temp->data << "->";
      temp = temp->next;
    }
    cout << temp->data << "->null";
    return;
  }
  // print from tail
  void printback() {
    if (head == nullptr) {
      return;
    }
    Node<T> *temp = tail;
    while (temp->prev != nullptr) {
      cout << temp->data << "<-";
      temp = temp->prev;
    }
    cout << temp->data << "null<-";
    return;
  }
  // append at head
  void addstart(T value) {
    Node<T> *newnode = new Node(value);
    if (head == nullptr) {
      head = tail = newnode;
      return;
    }
    newnode->next = head;
    head->prev = newnode;
    head = newnode;
    return;
  }
  // append at tail
  void addback(T value) {
    Node<T> *newnode = new Node(value);
    if (head == nullptr) {
      head = tail = newnode;
      return;
    }
    tail->next = newnode;
    newnode->prev = tail;
    tail = newnode;
    return;
  }
  // from head insert at posiiton
  void insertRandomfromStart(T value, int identity) {
    if (head == nullptr) {
      return;
    }
    Node<T> *temp = head;
    while (temp->next != nullptr && temp->data != identity) {
      temp = temp->next;
    }
    Node<T> *newnode = new Node(value);
    newnode->prev = temp;
    temp->next->prev = newnode;
    newnode->next = temp->next;
    temp->next = newnode;
    return;
  }
  // from tial insert at posiiton
  void insertRandomfromBack(T value, int identity) {
    if (head == nullptr) {
      return;
    }
    Node<T> *temp = tail;
    while (temp->prev != nullptr && temp->data != identity) {
      temp = temp->prev;
    }
    Node<T> *newnode = new Node(value);
    temp->prev->next = newnode;
    newnode->prev = temp->prev;
    newnode->next = temp;
    temp->prev = newnode;
    return;
  }
  // delete tail
  void deleteback() {
    if (head == nullptr) {
      return;
    }
    Node<T> *todelete = tail;
    tail = tail->prev;
    tail->next = nullptr;
    delete todelete;
  }
  // delete head
  void deletefront() {
    if (head == nullptr) {
      return;
    }
    Node<T> *todelete = head;
    head = head->next;
    head->prev = nullptr;
    delete todelete;
    return;
  }
  // from head delete smth
  void deletebegin(const T &value) {
    if (head == nullptr)
      return;

    Node<T> *temp = head;
    while (temp != nullptr && !(temp->data == value)) {
      temp = temp->next;
    }
    if (temp == nullptr)
      return;
    if (temp == head) {
      head = head->next;
      if (head != nullptr)
        head->prev = nullptr;
      else
        tail = nullptr; // list is now empty
    } else if (temp == tail) {
      tail = tail->prev;
      tail->next = nullptr;
    } else {
      temp->prev->next = temp->next;
      temp->next->prev = temp->prev;
    }

    delete temp;
  }
  // from tail delete smth
  void deleteback(T value) {
    if (head == nullptr) {
      return;
    }
    Node<T> *temp = tail;
    while (temp->prev != nullptr && temp->prev->data != value) {
      temp = temp->prev;
    }
    Node<T> *todelete = temp->prev;
    tail->prev = temp->prev->prev;
    temp->prev->next = temp;
    delete todelete;
  }
};

template <typename T, typename Compare>
void genericSort(linkedlist<T> &list, Compare comp) {
  if (!list.getHead())
    return;

  bool swapped;
  do {
    swapped = false;
    for (auto cur = list.getHead(); cur->next; cur = cur->next) {
      if (!comp(cur->data, cur->next->data)) {
        std::swap(cur->data, cur->next->data);
        swapped = true;
      }
    }
  } while (swapped);
}

template <typename T, typename Key, typename Match>
T *genericSearch(linkedlist<T> &list, const Key &key, Match matchFn) {
  for (auto cur = list.getHead(); cur; cur = cur->next) {
    if (matchFn(cur->data, key))
      return &cur->data;
  }
  return nullptr;
}
#endif
