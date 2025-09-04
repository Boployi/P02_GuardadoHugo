#ifndef __LIST_HPP__
#define __LIST_HPP__

using namespace std;
#include <exception>
#include <string>
#include <fstream>

template <class T>
class List {
private:
  class Node {
    public:
      typedef Node* Position;


    private:
      T data;
      Position next = nullptr;


    public:
      Node();
      Node(const T&);


      T& getData();
      Position getNext();


      void setData(const T&);
      void setNext(const Position&);
  };
public:
  typedef typename Node::Position Position;


private:
  Position anchor = nullptr;


  bool isValidPos(const Position&) const;
  void swapData(Position, Position);

  void addData(const List<T>&);
  Position sortDataMerge(Position head, int cmp(const T&, const T&));
  Position mergeSortedLists(Position left, Position right, int cmp(const T&, const T&));
  Position getMiddle(Position head);
  Position sortDataQuick(Position left, Position right, int cmp(const T&, const T&));
  Position partition(Position left, Position right, int cmp(const T&, const T&));


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


  List();
  List(const List<T>&);
  ~List();


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
  void sortDataMerge(int cmp(const T&, const T&));
  void sortDataQuick(int cmp(const T&, const T&));

  std::string toString() const;


  void deleteAll();


  List<T>& operator=(const List<T>&);

  void writeToDisk(const std::string& fileName) const;
  void readFromDisk(const std::string& fileName);
};


// Implementación de nodo
template <class T>
List<T>::Node::Node() {}


template <class T>
List<T>::Node::Node(const T& e) :data(e) {}


template <class T>
T& List<T>::Node::getData() {
  return this->data;
}


template <class T>
typename List<T>::Node::Position List<T>::Node::getNext() {
  return this->next;
}


template <class T>
void List<T>::Node::setData(const T& e) {
  this->data=e;
}


template <class T>
void List<T>::Node::setNext(const Position& p) {
   this->next = p;
}


template <class T>
bool List<T>::isValidPos(const Position& p) const {
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
void List<T>::swapData(Position a, Position b) {
  if (a == nullptr || b == nullptr) {
    throw Exception("swapData: posición inválida");
  }
  T temp = a->getData();
  a->setData(b->getData());
  b->setData(temp);
}

template <class T>
void List<T>::addData(const List<T>& other) {
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
List<T>::List() { }


//Implementacion de List


template <class T>
List<T>::List(const List<T>& l) {
  addData(l);
}


template <class T>
List<T>::~List() {
  deleteAll();
}


template <class T>
bool List<T>::isEmpty() const {
  return this->anchor == nullptr;
}


template <class T>
void List<T>::insertData(const Position& p, const T& e) {
  if (p != nullptr and !this->isValidPos(p)) {
    throw Exception("Posicion invalida, insertData");
  }
 Position newNode(new(nothrow) Node(e));


  if (newNode == nullptr) {
    throw Exception("Memoria no disponible, insertData");
  }
  if (p == nullptr) { //al principio
    newNode->setNext(this->anchor);
    this->anchor = newNode;
  } else { //otra posicion
    newNode->setNext(p->getNext());
    p->setNext(newNode);
  }
}


template <class T>
void List<T>::deleteData(const Position& p) {
  if (!isValidPos(p)) {
    throw Exception("Posición inválida, deleteData");
  }


  if(p == this->anchor){ //el primero
    this->anchor = p->getNext();
  }
  else { //otra posicion
    this->getPrevPos(p)->setNext(p->getNext());
  }
  delete p;
}


template <class T>
typename List<T>::Position List<T>::getFirstPos() const {
  return this->anchor;
}


template <class T>
typename List<T>::Position List<T>::getLastPos() const {
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
typename List<T>::Position List<T>::getPrevPos(const Position& p) const {
  Position aux(this->anchor);


  while(aux != nullptr and aux->getNext() != p){
    aux = aux->getNext();
  }
 
  return aux;
}


template <class T>
typename List<T>::Position List<T>::getNextPos(const Position& p) const {
  /*if(!this->isValidPos(p)){
    return p->getNext();
  }
  return nullptr;*/
  return this->isValidPos(p) ? p->getNext() : nullptr;
}


template <class T>
T* List<T>::retrieve(const Position& p) const {
  if (!isValidPos(p)) {
    throw Exception("Posición inválida, retrieve");
  }


  return &(p->getData());
}


template <class T>
typename List<T>::Position List<T>::findData(const T& e) const {
  Position aux(this->anchor);
  while (aux!=nullptr and aux->getData() != e) {
    aux = aux->getNext();
  }


  return aux;
}
/*
template <class T>
int List<T>::findDataL(const T& e, int (*compare)(const T&, const T&)) const {
  for (int i = 0; i <= last; ++i) {
    if (compare(*data[i], e) == 0) {
      return i;
    }
  }
  return -1;
}


template <class T>
void List<T>::sortDataBubble(int cmp(const T&, const T&)) {
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
void List<T>::sortDataInsert(int cmp(const T&, const T&)) {
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
void List<T>::sortDataSelect(int cmp(const T&, const T&)) {
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
void List<T>::sortDataShell(int cmp(const T&, const T&)) {
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
void List<T>::sortDataMerge(int cmp(const T&, const T&)) {
  this->anchor = sortDataMerge(this->anchor, cmp);
}

template <class T>
typename List<T>::Position List<T>::sortDataMerge(Position head, int cmp(const T&, const T&)) {
  if (head == nullptr || head->getNext() == nullptr) {
    return head; // Criterio de paro
  }

  // Divide la lista en dos mitades
  Position middle = getMiddle(head);
  Position nextToMiddle = middle->getNext();
  middle->setNext(nullptr);

  // Ordena recursivamente ambas mitades
  Position left = sortDataMerge(head, cmp);
  Position right = sortDataMerge(nextToMiddle, cmp);

  // Combina las dos mitades ordenadas
  return mergeSortedLists(left, right, cmp);
}

template <class T>
typename List<T>::Position List<T>::mergeSortedLists(Position left, Position right, int cmp(const T&, const T&)) {
  if (left == nullptr) return right;
  if (right == nullptr) return left;

  Position result = nullptr;

  if (cmp(left->getData(), right->getData()) <= 0) {
    result = left;
    result->setNext(mergeSortedLists(left->getNext(), right, cmp));
  } else {
    result = right;
    result->setNext(mergeSortedLists(left, right->getNext(), cmp));
  }

  return result;
}

template <class T>
typename List<T>::Position List<T>::getMiddle(Position head) {
  if (head == nullptr) return head;

  Position slow = head, fast = head->getNext();

  while (fast != nullptr && fast->getNext() != nullptr) {
    slow = slow->getNext();
    fast = fast->getNext()->getNext();
  }

  return slow;
}

template <class T>
void List<T>::sortDataQuick(int cmp(const T&, const T&)) {
  this->anchor = sortDataQuick(this->anchor, getLastPos(), cmp);
}

template <class T>
typename List<T>::Position List<T>::sortDataQuick(Position left, Position right, int cmp(const T&, const T&)) {
  if (left == nullptr || left == right || left == right->getNext()) {
    return left; // Criterio de paro
  }

  Position newPivot = partition(left, right, cmp);

  // Ordena recursivamente las dos mitades
  sortDataQuick(left, getPrevPos(newPivot), cmp);
  sortDataQuick(newPivot->getNext(), right, cmp);

  return left;
}

template <class T>
typename List<T>::Position List<T>::partition(Position left, Position right, int cmp(const T&, const T&)) {
  T pivotData = right->getData();
  Position i = getPrevPos(left);

  for (Position j = left; j != right; j = j->getNext()) {
    if (cmp(j->getData(), pivotData) <= 0) {
      i = (i == nullptr) ? left : i->getNext();
      swapData(i, j);
    }
  }

  i = (i == nullptr) ? left : i->getNext();
  swapData(i, right);

  return i;
}

template <class T>
std::string List<T>::toString() const {
  string result;


  Position aux(this->anchor);


  while (aux != nullptr) {
    result += aux->getData().toString() + "\n";


    aux = aux->getNext();
  }
 
  return result;
}


template <class T>
void List<T>::deleteAll() {
  Position aux;
  while (this->anchor != nullptr) {
    aux = this->anchor;
    this->anchor = this->anchor->getNext();
    delete aux;
  }
}


template <class T>
List<T>& List<T>::operator=(const List<T>& l) {
  this->deleteAll();
  addData(l);
  return *this;
}


template <class T>
void List<T>::writeToDisk(const std::string& fileName) const {
    std::ofstream ofs(fileName, std::ios::out | std::ios::trunc);
    if (!ofs) {
        throw Exception("No se pudo abrir el archivo para escritura: " + fileName);
    }
    // Escribir la cantidad de elementos
    int count = 0;
    Position aux = this->anchor;
    while (aux != nullptr) {
        ++count;
        aux = aux->getNext();
    }
    ofs << count << '\n';
    aux = this->anchor;
    while (aux != nullptr) {
        ofs << aux->getData() << '\n';
        aux = aux->getNext();
    }
    ofs.close();
}

template <class T>
void List<T>::readFromDisk(const std::string& fileName) {
    std::ifstream ifs(fileName, std::ios::in);
    if (!ifs) {
        throw Exception("No se pudo abrir el archivo para lectura: " + fileName);
    }
    this->deleteAll();
    int count = 0;
    ifs >> count;
    ifs.ignore(); // Saltar el salto de línea después del número
    for (int i = 0; i < count; ++i) {
        std::string line;
        if (!std::getline(ifs, line)) {
            throw Exception("Error al leer el elemento de disco");
        }
        std::istringstream iss(line);
        T temp;
        if (!(iss >> temp)) {
            throw Exception("Error al leer el elemento de disco");
        }
        this->insertData(this->getLastPos(), temp);
    }
    ifs.close();
}


#endif  // __LIST_HPP__
