#ifndef __RECIPE_HPP__
#define __RECIPE_HPP__
#include <string>
#include "list.hpp"
#include "listdoble.hpp"
#include <iomanip>
#include <sstream>

template <class TAuthor, class TIngredient>
class Recipe {
 private:
  std::string category;
  std::string name;
  TAuthor author;
  ListDoble<TIngredient> ingredients;
  int preparationTime;
  std::string procedure;

 public:
  Recipe();
  Recipe(const Recipe&);
  ~Recipe(); // Agregado destructor

  std::string getCategory() const;
  std::string getName() const;
  TAuthor getAuthor() const;
  ListDoble<TIngredient>& getIngredients();
  int getPreparationTime() const;
  std::string getProcedure() const;

  std::string toString() const;

  void setCategory(const std::string&);
  void setName(const std::string&);
  void setAuthor(const TAuthor&);
  void setPreparationTime(const int&);
  void setProcedure(const std::string&);

  bool operator==(const Recipe& e) const;
  bool operator!=(const Recipe& e) const;
  bool operator<(const Recipe& e) const;
  bool operator<=(const Recipe& e) const;
  bool operator>(const Recipe& e) const;
  bool operator>=(const Recipe& e) const;

  static int compareByName(const Recipe& e1, const Recipe& e2);
  static int compareByPreparationTime(const Recipe& e1, const Recipe& e2);
  static int compareByCategory(const Recipe& e1, const Recipe& e2);

  template <class UAuthor, class UIngredient>
  friend std::ostream& operator<<(std::ostream&, const Recipe<UAuthor, UIngredient>&);
  template <class UAuthor, class UIngredient>
  friend std::istream& operator>>(std::istream&, Recipe<UAuthor, UIngredient>&);

};

// Implementación

template <class TAuthor, class TIngredient>
Recipe<TAuthor, TIngredient>::Recipe() : preparationTime(0) { }

template <class TAuthor, class TIngredient>
Recipe<TAuthor, TIngredient>::Recipe(const Recipe& m)
  : category(m.category),
    name(m.name),
    author(m.author),
    preparationTime(m.preparationTime),
    procedure(m.procedure) {
  auto pos = m.ingredients.getFirstPos();
  while (pos != nullptr) {
    ingredients.insertData(ingredients.getLastPos(), *m.ingredients.retrieve(pos));
    pos = m.ingredients.getNextPos(pos);
  }
}

template <class TAuthor, class TIngredient>
Recipe<TAuthor, TIngredient>::~Recipe() {
  ingredients.deleteAll();
}

template<class TAuthor, class TIngredient>
std::string Recipe<TAuthor, TIngredient>::getCategory() const
{
  return category;
}

template<class TAuthor, class TIngredient>
std::string Recipe<TAuthor, TIngredient>::getName() const
{
  return name;
}

template<class TAuthor, class TIngredient>
TAuthor Recipe<TAuthor, TIngredient>::getAuthor() const
{
  return author;
}

template<class TAuthor, class TIngredient>
ListDoble<TIngredient>& Recipe<TAuthor, TIngredient>::getIngredients() {
  return ingredients;
}

template<class TAuthor, class TIngredient>
int Recipe<TAuthor, TIngredient>::getPreparationTime() const{
  return preparationTime;
}

template<class TAuthor, class TIngredient>
std::string Recipe<TAuthor, TIngredient>::getProcedure() const{
  return procedure;
}

template<class TAuthor, class TIngredient>
std::string Recipe<TAuthor, TIngredient>::toString() const {
    std::ostringstream ss;
    
    // Agregar la cabecera antes de cada receta
    ss << "Categoria | Nombre | Autor | Tiempo de preparacion (minutos) | Procedimiento | " 
       << " -> " << " Lista de ingredientes " << " -> " << "\n\n";

    // Información general de la receta
    ss << category << " | " << name << " | " << author.toString() 
       << " | " << preparationTime << "s | " << procedure << "\n";

    // Lista de ingredientes
    ss << "Lista de ingredientes:\n";
    bool hasIngredients = false;
    auto pos = ingredients.getFirstPos();
    while (pos != nullptr) {
      ss << "- " << ingredients.retrieve(pos)->toString() << "\n";
      hasIngredients = true;
      pos = ingredients.getNextPos(pos);
    }

    // Si no hay ingredientes
    if (!hasIngredients) {
        ss << "(No hay ingporredientes registrados)\n";
    }

    // Separador para mejorar la legibilidad
    ss << "--------------------------------------\n";

    return ss.str();
}




template<class TAuthor, class TIngredient>
void Recipe<TAuthor, TIngredient>::setCategory(const std::string& c){
  category = c;
}

template<class TAuthor, class TIngredient>
void Recipe<TAuthor, TIngredient>::setName(const std::string& n){
  name = n;
}

template<class TAuthor, class TIngredient>
void Recipe<TAuthor, TIngredient>::setAuthor(const TAuthor& a) {
    author = a;
}

template<class TAuthor, class TIngredient>
void Recipe<TAuthor, TIngredient>::setPreparationTime(const int& p){
  preparationTime = p;
}

template<class TAuthor, class TIngredient>
void Recipe<TAuthor, TIngredient>::setProcedure(const std::string& pr){
  procedure = pr;
}

template<class TAuthor, class TIngredient>
bool Recipe<TAuthor, TIngredient>::operator==(const Recipe& e) const
{
  return this->name == e.name && this->preparationTime == e.preparationTime;
}

template<class TAuthor, class TIngredient>
bool Recipe<TAuthor, TIngredient>::operator!=(const Recipe& e) const
{
  return !(*this == e);
}

template<class TAuthor, class TIngredient>
bool Recipe<TAuthor, TIngredient>::operator<(const Recipe& e) const {
    return this->name < e.name && this->preparationTime < e.preparationTime;
}

template<class TAuthor, class TIngredient>
bool Recipe<TAuthor, TIngredient>::operator<=(const Recipe& e) const{
  return *this < e || *this == e;
}

template<class TAuthor, class TIngredient>
bool Recipe<TAuthor, TIngredient>::operator>(const Recipe& e) const
{
  return this->name > e.name && this->preparationTime > e.preparationTime;
}

template<class TAuthor, class TIngredient>
bool Recipe<TAuthor, TIngredient>::operator>=(const Recipe& e) const
{
  return !(*this < e);
}

template<class TAuthor, class TIngredient>
int Recipe<TAuthor, TIngredient>::compareByName(const Recipe& a, const Recipe& b)
{
  if (a.name < b.name) return -1;
  if (a.name == b.name) return 0;
  if (a.name > b.name) return 1;
}

template<class TAuthor, class TIngredient>
int Recipe<TAuthor, TIngredient>::compareByPreparationTime(const Recipe& a, const Recipe& b)
{
  if (a.preparationTime < b.preparationTime) return -1;
  if (a.preparationTime == b.preparationTime) return 0;
  if (a.preparationTime > b.preparationTime) return 1;
}

template<class TAuthor, class TIngredient>
int Recipe<TAuthor, TIngredient>::compareByCategory(const Recipe& a, const Recipe& b) {
    if (a.category < b.category) return -1;
    if (a.category == b.category) return 0;
    if (a.category > b.category) return 1;
}

template <class TAuthor, class TIngredient>
std::istream& operator>>(std::istream& is, Recipe<TAuthor, TIngredient>& r) {
    try {
        getline(is, r.category, '*');
        getline(is, r.name, '*');
        is >> r.author;
        std::string prepTimeStr;
        getline(is, prepTimeStr, '*');
        r.preparationTime = std::stoi(prepTimeStr);
        getline(is, r.procedure, '*');
        std::string ingredientCountStr;
        getline(is, ingredientCountStr, '*');
        int ingredientCount = std::stoi(ingredientCountStr);
        r.ingredients.deleteAll();
        for (int i = 0; i < ingredientCount; ++i) {
            TIngredient ingredient;
            is >> ingredient;
            r.ingredients.insertData(r.ingredients.getLastPos(), ingredient);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error al leer la receta: " << e.what() << std::endl;
        throw;
    }
    return is;
}

template <class TAuthor, class TIngredient>
std::ostream& operator<<(std::ostream& os, const Recipe<TAuthor, TIngredient>& r) {
    os << r.category << '*' << r.name << '*' << r.author
       << r.preparationTime << '*' << r.procedure << '*';
    // Contar ingredientes
    int ingredientCount = 0;
    auto pos = r.ingredients.getFirstPos();
    while (pos != nullptr) {
        ++ingredientCount;
        pos = r.ingredients.getNextPos(pos);
    }
    os << ingredientCount << '*';
    // Escribir ingredientes
    pos = r.ingredients.getFirstPos();
    while (pos != nullptr) {
        os << *r.ingredients.retrieve(pos);
        pos = r.ingredients.getNextPos(pos);
    }
    return os;
}

#endif // __RECIPE_HPP__