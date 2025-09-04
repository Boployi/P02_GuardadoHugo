#ifndef __USERINTERFACES_HPP__
#define __USERINTERFACES_HPP__
#include <iostream>
#include <string>
#include "list.hpp"
#include "listdoble.hpp"
#include "recipe.hpp"
#include "name.hpp"
#include "ingredients.hpp"


class UserInterfaces {
 private:
  List<Recipe<Name, Ingredients>>* listRef;
  void encontrar(const int&);
  int buscarPorNombre(const std::string& nombre); // Declaración añadida

 public:
  UserInterfaces(List<Recipe<Name, Ingredients>>&);
  void mainMenu();
  void agregar();
  void eliminar();
  void ordenar(int op);
  int buscar(int op);
  void encontrar();
  void mostrarReceta();
  void agregarIngrediente();
  void eliminarIngrediente();
  void eliminarIngredientes();
  void modificarIngrediente();
  void modificarProcedimiento();
  void guardarReceta();
  void leerReceta();
  void writeToDisk(const std::string& fileName);
  void readFromDisk(const std::string& fileName);
};


#endif // __USERINTERFACES_HPP__