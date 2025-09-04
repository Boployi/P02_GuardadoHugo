#ifndef __LISTDOBLE_HPP__
#define __LISTDOBLE_HPP__

using namespace std;
#include <exception>
#include <string>

template <class T>
class ListDoble {
private:
  class Node {
    public:
      typedef Node* Position;

    private:
      T data;
      Position next = nullptr;
      Position prev = nullptr; 


    public:
      Node();
      Node(const T&);


      T& getData();
      Position getNext();
      Position getPrev();

      void setData(const T&);
      void setNext(const Position&);
      void setPrev(const Position&);
  };
public:
  typedef typename Node::Position Position;


private:
  Position anchor = nullptr;


  bool isValidPos(const Position&) const;


  void addData(const ListDoble<T>&);


 public:
  class Exception : public std::exception {
  private:
    std::string msg;


  public:
    explicit Exception(const std::string& message) : msg(message) {}


    virtual const char* what() const noexcept override {
        return msg.c_str();
    }
  };


  ListDoble();
  ListDoble(const ListDoble<T>&);
  ~ListDoble();


  bool isEmpty() const;


  void insertData(const Position&, const T&);
  void deleteData(const Position&);


  Position getFirstPos() const;
  Position getLastPos() const;


  Position getPrevPos(const Position&) const;
  Position getNextPos(const Position&) const;


  T* retrieve(const Position&) const;
  Position findData(const T&) const;
  //int findDataL(const T&, int (*compare)(const T&, const T&)) const;
 
  /*
  void sortDataBubble(int(const T&,const T&));
  void sortDataInsert(int(const T&,const T&));
  void sortDataSelect(int(const T&,const T&));
  void sortDataShell(int(const T&,const T&));
  */
  std::string toString() const;


  void deleteAll();


  ListDoble<T>& operator=(const ListDoble<T>&);
};


// Implementación de nodo
template <class T>
ListDoble<T>::Node::Node() {}


template <class T>
ListDoble<T>::Node::Node(const T& e) :data(e) {}


template <class T>
T& ListDoble<T>::Node::getData() {
  return this->data;
}

template <class T>
typename ListDoble<T>::Node::Position ListDoble<T>::Node::getNext() {
  return this->next;
}

template <class T>
typename ListDoble<T>::Node::Position ListDoble<T>::Node::getPrev() {
  return this->prev;
}

template <class T>
void ListDoble<T>::Node::setData(const T& e) {
  this->data = e;
}

template <class T>
void ListDoble<T>::Node::setNext(const Position& p) {
   this->next = p;
}

template <class T>
void ListDoble<T>::Node::setPrev(const Position& p) {
  this->prev = p;
}

template <class T>
bool ListDoble<T>::isValidPos(const Position& p) const {
  Position aux(this->anchor);


  while (aux != nullptr) {
    if (aux == p) {
      return true;
    }
    aux = aux->getNext();
  }
  return false;
}


template <class T>
void ListDoble<T>::addData(const ListDoble<T>& other) {
  Position aux(other.anchor),lastInserted(this->getLastPos()),newNode;
  while (aux != nullptr) {
    if((newNode = new(nothrow) Node(aux->getData())) == nullptr){
      throw Exception("Memoria no disponible, copyAll");
    }
    if(lastInserted==nullptr){
      this->anchor = newNode;
    }
    else{
      lastInserted->setNext(newNode);
      newNode->setPrev(lastInserted);
    }
    lastInserted = newNode;
    aux = aux->getNext();
  }


  /*while (aux!=nullptr) {
    this->insertData(this->getLastPos(), aux->getData());
    aux = aux->getNext();
  }*/ //basura


}


template <class T>
ListDoble<T>::ListDoble() { }


//Implementacion de ListDoble


template <class T>
ListDoble<T>::ListDoble(const ListDoble<T>& l) {
  addData(l);
}


template <class T>
ListDoble<T>::~ListDoble() {
  deleteAll();
}


template <class T>
bool ListDoble<T>::isEmpty() const {
  return this->anchor == nullptr;
}


template <class T>
void ListDoble<T>::insertData(const Position& p, const T& e) {
  if (p != nullptr and !this->isValidPos(p)) {
    throw Exception("Posicion invalida, insertData");
  }
 Position newNode(new(nothrow) Node(e));


  if (newNode == nullptr) {
    throw Exception("Memoria no disponible, insertData");
  }
  if (p == nullptr) { //al principio
    if (this->anchor != nullptr) {
      this->anchor->setPrev(newNode); 
    }
    newNode->setNext(this->anchor);

    this->anchor = newNode;
  } else { //otra posicion
    newNode->setPrev(p);
    newNode->setNext(p->getNext());

    if(p->getNext() != nullptr) {
      p->getNext()->setPrev(newNode); 
    }
    p->setNext(newNode);
  }
}


template <class T>
void ListDoble<T>::deleteData(const Position& p) {
  if (!isValidPos(p)) {
    throw Exception("Posición inválida, deleteData");
  }

  // Si es el primer nodo
  if (p == this->anchor) {
    this->anchor = p->getNext();
    if (this->anchor != nullptr) {
      this->anchor->setPrev(nullptr);
    }
  } else {
    // Actualizar el nodo anterior
    p->getPrev()->setNext(p->getNext());
    if (p->getNext() != nullptr) {
      // Actualizar el nodo siguiente
      p->getNext()->setPrev(p->getPrev());
    }
  }

  delete p; // Liberar memoria del nodo eliminado
}


template <class T>
typename ListDoble<T>::Position ListDoble<T>::getFirstPos() const {
  return this->anchor;
}


template <class T>
typename ListDoble<T>::Position ListDoble<T>::getLastPos() const {
  if(this->isEmpty()){
    return nullptr;
  }


  Position aux(this->anchor);


  while (aux->getNext() != nullptr) {
    aux = aux->getNext();
  }
  return aux;
}


template <class T>
typename ListDoble<T>::Position ListDoble<T>::getPrevPos(const Position& p) const {
  return this->isValidPos(p) ? p->getPrev() : nullptr;
}


template <class T>
typename ListDoble<T>::Position ListDoble<T>::getNextPos(const Position& p) const {
  /*if(!this->isValidPos(p)){
    return p->getNext();
  }
  return nullptr;*/
  return this->isValidPos(p) ? p->getNext() : nullptr;
}


template <class T>
T* ListDoble<T>::retrieve(const Position& p) const {
  if (!isValidPos(p)) {
    throw Exception("Posición inválida, retrieve");
  }


  return &(p->getData());
}


template <class T>
typename ListDoble<T>::Position ListDoble<T>::findData(const T& e) const {
  Position aux(this->anchor);
  while (aux!=nullptr and aux->getData() != e) {
    aux = aux->getNext();
  }


  return aux;
}
/*
template <class T>
int ListDoble<T>::findDataL(const T& e, int (*compare)(const T&, const T&)) const {
  for (int i = 0; i <= last; ++i) {
    if (compare(*data[i], e) == 0) {
      return i;
    }
  }
  return -1;
}


template <class T>
void ListDoble<T>::sortDataBubble(int cmp(const T&, const T&)) {
  int i = last;
  bool flag;
  do {
    flag = false;
    for (int j = 0; j < i; ++j) {
      if (cmp(*data[j], *data[j + 1]) > 0) {
        swapData(data[j], data[j + 1]);
        flag = true;
      }
    }
    --i;
  } while (flag);
}


template <class T>
void ListDoble<T>::sortDataInsert(int cmp(const T&, const T&)) {
  for (int i = 1; i <= last; ++i) {
    T* aux = data[i];
    int j = i;
    while (j > 0 && cmp(*aux, *data[j - 1]) < 0) {
      data[j] = data[j - 1];
      --j;
    }
    data[j] = aux;
  }
}


template <class T>
void ListDoble<T>::sortDataSelect(int cmp(const T&, const T&)) {
  for (int i = 0; i < last; ++i) {
    int m = i;
    for (int j = i + 1; j <= last; ++j) {
      if (cmp(*data[j], *data[m]) < 0) {
        m = j;
      }
    }
    if (m != i) {
      swapData(data[i], data[m]);
    }
  }
}


template <class T>
void ListDoble<T>::sortDataShell(int cmp(const T&, const T&)) {
  int seq[] = {510774, 227011, 100894, 44842, 19930, 8858, 3937, 1750, 701, 301, 132, 57, 23, 10, 4, 1, 0};
  int pos = 0, dif = seq[pos];
  while (dif > 0) {
    for (int i = dif; i <= last; ++i) {
      int j = i;
      while (j >= dif && cmp(*data[j - dif], *data[j]) > 0) {
        swapData(data[j - dif], data[j]);
        j -= dif;
      }
    }
    dif = seq[++pos];
  }
}
*/


template <class T>
std::string ListDoble<T>::toString() const {
  string result;


  Position aux(this->anchor);


  while (aux != nullptr) {
    result += aux->getData().toString() + "\n";


    aux = aux->getNext();
  }
 
  return result;
}


template <class T>
void ListDoble<T>::deleteAll() {
  Position aux;
  while (this->anchor != nullptr) {
    aux = this->anchor;
    this->anchor = this->anchor->getNext();
    delete aux;
  }
}


template <class T>
ListDoble<T>& ListDoble<T>::operator=(const ListDoble<T>& l) {
  this->deleteAll();
  addData(l);
  return *this;
}


#endif  // __LISTDOBLEDOBLE_HPP__
