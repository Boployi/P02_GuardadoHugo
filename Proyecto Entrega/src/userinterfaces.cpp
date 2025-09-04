#include "userinterfaces.hpp"

UserInterfaces::UserInterfaces(List<Recipe<Name, Ingredients>>& l) : listRef(&l) {
    mainMenu();
}


void UserInterfaces::mainMenu() {
    int op = 0;
    do {
        system("cls");
        cout << "|----------------------------------------|" << endl;
        cout << "|----Bienvenido al recetario digital-----|" << endl;
        cout << "|----------------------------------------|" << endl << endl;
        cout << "Que desea hacer?" << endl;
        cout << "1.- Mostrar recetas" << endl;
        cout << "2.- Agregar receta" << endl;
        cout << "3.- Encontrar receta" << endl;
        cout << "4.- Eliminar receta" << endl;
        cout << "5.- Eliminar todas las recetas" << endl;
        cout << "6.- Ordenar recetas" << endl;
        cout << "7.- Agregar ingrediente a una receta" << endl;
        cout << "8.- Eliminar ingrediente de una receta" << endl;
        cout << "9.- Eliminar todos los ingredientes de una receta" << endl;
        cout << "10.- Modificar cantidad de un ingrediente de una receta" << endl;
        cout << "11.- Modificar procedimiento de una receta" << endl;
        cout << "12.- Guardar recetario a disco" << endl;
        cout << "13.- Leer recetario del disco" << endl;
        cout << "14.- Salir del programa" << endl << endl;
        cout << "Respuesta: " ;
        cin >> op;
        cin.ignore();
        switch (op) {
            case 1:
                mostrarReceta();
                system("pause");
                break;
            case 2:
                agregar();
                break;
            case 3:
            {
                cout << "Como desea buscar la receta?" << endl;
                cout << "1.- Por nombre de la receta" << endl;
                cout << "2.- Por categoria de la receta" << endl;
                int tipoBuscar(0);
                cout << "Respuesta: ";
                cin.clear();
                cin >> tipoBuscar;
                if(tipoBuscar != 1 && tipoBuscar != 2){
                    std::cout << "Opcion no valida, por favor intente de nuevo." << std::endl;
                    cin.clear();
                    cin.ignore();
                    system("pause");
                    break;
                }
                buscar(tipoBuscar);
                break;
            }
            case 4:
            {
                eliminar();
                break;
            }
            case 5:
            {
                listRef->deleteAll();
                cout << "Se han eliminado todas las recetas." << endl;
                system("pause");
                break;
            }
            case 6:
            {
                cout << "Como desea ordenar la lista?" << endl;
                cout << "1.- Ordenar por nombre de la receta" << endl;
                cout << "2.- Ordenar por tiempo de preparacion" << endl;
                int tipoSort(0); // Inicializar la variable
                cout << "Respuesta: ";
                cin >> tipoSort; // Leer el valor de tipoSort
                cin.ignore();
            
                if(tipoSort != 1 && tipoSort != 2){
                    std::cout << "Opcion no valida, por favor intente de nuevo." << std::endl;
                    cin.clear();
                    cin.ignore();
                    system("pause");
                    break;
                }
                ordenar(tipoSort);
                cout << "Lista ordenada." << endl;
                mostrarReceta();
                system("pause");
                break;
            }
            case 7:
            {
                agregarIngrediente();
                break;
            }
            case 8:
            {
                eliminarIngrediente();
                break;
            }
            case 9:
            {
                eliminarIngredientes();
                break;
            }
            case 10:
            {
                modificarIngrediente();
                break;
            }
            case 11:
            {
                modificarProcedimiento();
                break;
            }
            case 12:
            {
                guardarReceta();
                break;
            }
            case 13:
            {
                leerReceta();
                break;
            }
            case 14:
            {
                cout << "Gracias por usar el recetario digital." << endl;
                system("pause");
                break;
            }
            default:
            {
                cout << "Opcion no valida, por favor intente de nuevo." << endl;
                cin.clear();
                cin.ignore();
                system("pause");
                break;
            }
            }
    } while (op != 14);
}


void UserInterfaces::agregar() {
    Recipe<Name, Ingredients> myRecipe;
    std::string myString;
    int intCant;
    float cant;

    cout << "Digame la categoria de la receta " << endl;
    cout << "1.- Desayuno" << endl;
    cout << "2.- Almuerzo" << endl;
    cout << "3.- Cena" << endl;
    cout << "4.- Navide" << "\xA4" << "o" << endl;
    cout << "Respuesta: ";
    int tipo;
    cin >> tipo;
    if (tipo == 1) {
        myString = "Desayuno";
    } else if (tipo == 2) {
        myString = "Almuerzo";
    } else if (tipo == 3) {
        myString = "Cena";
    } else if (tipo == 4) {
        myString = "Navideno";
    } else {
        myString = "Navideno";
    }
    cin.ignore();
    myRecipe.setCategory(myString);

    cout << "Digame el nombre de la receta: ";
    getline(cin, myString);
    myRecipe.setName(myString);

    Name author;
    cout << "Digame el nombre del autor: ";
    getline(cin, myString);
    author.setFirstName(myString);
    cout << "Digame el apellido del autor: ";
    getline(cin, myString);
    author.setLastName(myString);
    myRecipe.setAuthor(author);

    cout << "Digame la cantidad de ingredientes: ";
    cin >> intCant;
    cin.ignore();

    // Creamos una lista auxiliar ligada para ordenar los ingredientes
    struct NodoAux {
        Ingredients ingrediente;
        NodoAux* sig;
        NodoAux(const Ingredients& ing) : ingrediente(ing), sig(nullptr) {}
    };
    NodoAux* head = nullptr;
    for (int i = 0; i < intCant; ++i) {
        Ingredients ingredient;
        cout << "Digame el nombre del ingrediente " << i + 1 << ": ";
        getline(cin, myString);
        ingredient.setName(myString);

        cout << "Digame la cantidad del ingrediente " << i + 1 << " en gramos o mililitros: ";
        cin >> cant;
        cin.ignore();
        ingredient.setQuantity(cant);
        
        // Insertar en la lista auxiliar en orden alfabético
        NodoAux* nuevo = new NodoAux(ingredient);
        if (!head || nuevo->ingrediente.getName() < head->ingrediente.getName()) {
            nuevo->sig = head;
            head = nuevo;
        } else {
            NodoAux* actual = head;
            while (actual->sig && actual->sig->ingrediente.getName() < nuevo->ingrediente.getName()) {
                actual = actual->sig;
            }
            nuevo->sig = actual->sig;
            actual->sig = nuevo;
        }
    }
    // Pasar los ingredientes ordenados a ingredientsList
    ListDoble<Ingredients> ingredientsList;
    NodoAux* aux = head;
    while (aux) {
        try {
            ingredientsList.insertData(ingredientsList.getLastPos(), aux->ingrediente);
        } catch (const typename ListDoble<Ingredients>::Exception& ex) {
            cout << "Hubo un error al agregar el ingrediente: " << ex.what() << endl;
        }
        NodoAux* borrar = aux;
        aux = aux->sig;
        delete borrar;
    }
    myRecipe.getIngredients() = ingredientsList; // Asigna la lista de ingredientes al índice 0

    cout << "Digame el tiempo de preparacion (en minutos): ";
    cin >> intCant;
    myRecipe.setPreparationTime(intCant);

    cin.ignore();
    cout << "Digame el procedimiento: ";
    getline(cin, myString);
    myRecipe.setProcedure(myString);

    try {
        typename List<Recipe<Name, Ingredients>>::Position pos = nullptr;
        if (!listRef->isEmpty()) {
            pos = listRef->getLastPos(); // Obtener la última posición si la lista no está vacía
        }
        listRef->insertData(pos, myRecipe); // Inserta la receta en la posición adecuada
    } catch (const typename List<Recipe<Name, Ingredients>>::Exception& ex) {
        cout << "Hubo un error: " << ex.what() << endl;
    }
}

void UserInterfaces::eliminar() {
    std::string recipeName;
    cout << "Digame el nombre de la receta que desea eliminar: ";
    getline(cin, recipeName);

    int idx = buscarPorNombre(recipeName);
    if (idx == -1) {
        cout << "Receta no encontrada." << endl;
        system("pause");
        return;
    }
    try {
        auto pos = listRef->getFirstPos();
        int currentIndex = 1;
        while (pos != nullptr && currentIndex < idx) {
            pos = listRef->getNextPos(pos);
            currentIndex++;
        }
        if (pos != nullptr) {
            listRef->deleteData(pos);
            cout << "Receta eliminada exitosamente." << endl;
        } else {
            cout << "Receta no encontrada." << endl;
        }
    } catch (const typename List<Recipe<Name, Ingredients>>::Exception& ex) {
        cout << "Hubo un error: " << ex.what() << endl;
    }
    system("pause");
}

void UserInterfaces::encontrar() {
    int posIndex;
    cout << "Digame la posicion de la receta que desea imprimir: ";
    cin >> posIndex;
    
    if (posIndex <= 0) {
        cout << "Posición inválida." << endl;
        system("pause");
        return;
    }

    try {
        auto pos = listRef->getFirstPos();
        int currentIndex = 1;
        while(pos != nullptr) {
            if(currentIndex == posIndex) {
                Recipe<Name, Ingredients>* recipe = listRef->retrieve(pos);
                cout << recipe->toString() << endl;
                system("pause");
                return;
            }
            pos = listRef->getNextPos(pos); // Avanzar a la siguiente posición
            currentIndex++;
        };
        cout << "Posición inválida." << endl;
        } catch (const typename List<Recipe<Name, Ingredients>>::Exception& ex) {
        cout << "Hubo un error: " << ex.what() << endl;
        }
    system("pause");
}

void UserInterfaces::encontrar(const int& pos) {
    int posIndex(pos);
    
    if (posIndex <= 0) {
        cout << "Posición inválida." << endl;
        system("pause");
        return;
    }

    try {
        auto pos = listRef->getFirstPos();
        int currentIndex = 1;
        while(pos != nullptr) {
            if(currentIndex == posIndex) {
                Recipe<Name, Ingredients>* recipe = listRef->retrieve(pos);
                cout << recipe->toString() << endl;
                system("pause");
                return;
            }
            pos = listRef->getNextPos(pos); // Avanzar a la siguiente posición
            currentIndex++;
        };
        cout << "Posición inválida." << endl;
        } catch (const typename List<Recipe<Name, Ingredients>>::Exception& ex) {
        cout << "Hubo un error: " << ex.what() << endl;
        }
    system("pause");
}

void UserInterfaces::mostrarReceta()
{
    cout<<listRef->toString();
}

void UserInterfaces::agregarIngrediente() {
    std::string recipeName;
    cout << "Digame el nombre de la receta a la que desea agregar un ingrediente: ";
    getline(cin, recipeName); 

    int idx = buscarPorNombre(recipeName);
    if (idx == -1) {
        cout << "Receta no encontrada." << endl;
        system("pause");
        return;
    }
    try {
        auto pos = listRef->getFirstPos();
        int currentIndex = 1;
        while (pos != nullptr && currentIndex < idx) {
            pos = listRef->getNextPos(pos);
            currentIndex++;
        }
        if (pos != nullptr) {
            Recipe<Name, Ingredients>* recipe = listRef->retrieve(pos);
            Ingredients ingredient;
            std::string ingredientName;
            float quantity;

            cout << "Nombre del ingrediente: ";
            getline(cin, ingredientName);
            ingredient.setName(ingredientName);

            cout << "Cantidad del ingrediente: ";
            cin >> quantity;
            cin.ignore();
            ingredient.setQuantity(quantity);

            // Insertar en orden alfabético en la lista doblemente ligada
            auto ingPos = recipe->getIngredients().getFirstPos();
            // Si la lista está vacía o el nuevo ingrediente va al principio
            if (ingPos == nullptr || ingredient.getName() < recipe->getIngredients().retrieve(ingPos)->getName()) {
                recipe->getIngredients().insertData(nullptr, ingredient);
            } else {
                // Buscar la posición donde el siguiente sea mayor o igual, o final
                while (recipe->getIngredients().getNextPos(ingPos) != nullptr && recipe->getIngredients().retrieve(recipe->getIngredients().getNextPos(ingPos))->getName() < ingredient.getName()) {
                    ingPos = recipe->getIngredients().getNextPos(ingPos);
                }
                // Si el nuevo ingrediente es mayor que todos, agregar al final
                if (recipe->getIngredients().getNextPos(ingPos) == nullptr && recipe->getIngredients().retrieve(ingPos)->getName() < ingredient.getName()) {
                    recipe->getIngredients().insertData(ingPos, ingredient);
                } else {
                    recipe->getIngredients().insertData(ingPos, ingredient);
                }
            }

            cout << "Ingrediente agregado exitosamente." << endl;
        } else {
            cout << "Receta no encontrada." << endl;
        }
    } catch (const typename List<Recipe<Name, Ingredients>>::Exception& ex) {
        cout << "Hubo un error: " << ex.what() << endl;
    }
    system("pause");

}

void UserInterfaces::eliminarIngrediente() {
    std::string recipeName;
    cout << "Digame el nombre de la receta de la que desea eliminar un ingrediente: ";
    getline(cin, recipeName); 

    int idx = buscarPorNombre(recipeName);
    if (idx == -1) {
        cout << "Receta no encontrada." << endl;
        system("pause");
        return;
    }
    auto pos = listRef->getFirstPos();
    int currentIndex = 1;
    while (pos != nullptr && currentIndex < idx) {
        pos = listRef->getNextPos(pos);
        currentIndex++;
    }
    if (pos != nullptr) {
        Recipe<Name, Ingredients>* recipe = listRef->retrieve(pos);
        std::string ingredientName;
        cout << "Nombre del ingrediente a eliminar: ";
        getline(cin, ingredientName);

        auto ingredientPos = recipe->getIngredients().getFirstPos();
        while (ingredientPos != nullptr) {
            if (recipe->getIngredients().retrieve(ingredientPos)->getName() == ingredientName) {
                recipe->getIngredients().deleteData(ingredientPos);
                cout << "Ingrediente eliminado exitosamente." << endl;
                system("pause");
                return;
            }
            ingredientPos = recipe->getIngredients().getNextPos(ingredientPos);
        }
        cout << "Ingrediente no encontrado." << endl;
    } else {
        cout << "Receta no encontrada." << endl;
    }
    system("pause");
}

void UserInterfaces::eliminarIngredientes() {
    std::string recipeName;
    cout << "Digame el nombre de la receta de la que desea eliminar todos los ingredientes: ";
    getline(cin, recipeName); 

    int idx = buscarPorNombre(recipeName);
    if (idx == -1) {
        cout << "Receta no encontrada." << endl;
        system("pause");
        return;
    }
    auto pos = listRef->getFirstPos();
    int currentIndex = 1;
    while (pos != nullptr && currentIndex < idx) {
        pos = listRef->getNextPos(pos);
        currentIndex++;
    }
    if (pos != nullptr) {
        Recipe<Name, Ingredients>* recipe = listRef->retrieve(pos);
        recipe->getIngredients().deleteAll();
        cout << "Todos los ingredientes han sido eliminados." << endl;
    } else {
        cout << "Receta no encontrada." << endl;
    }
    system("pause");
}

void UserInterfaces::modificarIngrediente() {
    std::string recipeName;
    cout << "Digame el nombre de la receta en la que desea modificar un ingrediente: ";
    getline(cin, recipeName); 

    int idx = buscarPorNombre(recipeName);
    if (idx == -1) {
        cout << "Receta no encontrada." << endl;
        system("pause");
        return;
    }
    auto pos = listRef->getFirstPos();
    int currentIndex = 1;
    while (pos != nullptr && currentIndex < idx) {
        pos = listRef->getNextPos(pos);
        currentIndex++;
    }
    if (pos != nullptr) {
        Recipe<Name, Ingredients>* recipe = listRef->retrieve(pos);
        std::string ingredientName;
        cout << "Nombre del ingrediente a modificar: ";
        getline(cin, ingredientName);

        auto ingredientPos = recipe->getIngredients().getFirstPos();
        while (ingredientPos != nullptr) {
            if (recipe->getIngredients().retrieve(ingredientPos)->getName() == ingredientName) {
                Ingredients* ingredient = recipe->getIngredients().retrieve(ingredientPos);
                float newQuantity;
                cout << "Nueva cantidad del ingrediente: ";
                cin >> newQuantity;
                cin.ignore();
                ingredient->setQuantity(newQuantity);
                cout << "Ingrediente modificado exitosamente." << endl;
                system("pause");
                return;
            }
            ingredientPos = recipe->getIngredients().getNextPos(ingredientPos);
        }
        cout << "Ingrediente no encontrado." << endl;
    } else {
        cout << "Receta no encontrada." << endl;
    }
    system("pause");
}

void UserInterfaces::modificarProcedimiento() {

    std::string recipeName;
    cout << "Digame el nombre de la receta en la que desea modificar el procedimiento: ";
    getline(cin, recipeName); 

    int idx = buscarPorNombre(recipeName);
    if (idx == -1) {
        cout << "Receta no encontrada." << endl;
        system("pause");
        return;
    }
    try {
        auto pos = listRef->getFirstPos();
        int currentIndex = 1;
        while (pos != nullptr && currentIndex < idx) {
            pos = listRef->getNextPos(pos);
            currentIndex++;
        }
        if (pos != nullptr) {
            Recipe<Name, Ingredients>* recipe = listRef->retrieve(pos);
            std::string newProcedure;
            cout << "Nuevo procedimiento: ";
            getline(cin, newProcedure);
            recipe->setProcedure(newProcedure);
            cout << "Procedimiento modificado exitosamente." << endl;
        } else {
            cout << "Receta no encontrada." << endl;
        }
    } catch (const typename List<Recipe<Name, Ingredients>>::Exception& ex) {
        cout << "Hubo un error: " << ex.what() << endl;
    }
    system("pause");
}

void UserInterfaces::guardarReceta() {
    
    std::string fileName;
    std::cout << "Ingrese el nombre del archivo para guardar las recetas: ";
    std::cin >> fileName;
    try {
        listRef->writeToDisk(fileName);
        std::cout << "Recetas guardadas exitosamente en " << fileName << std::endl;
    } catch (const List<Recipe<Name, Ingredients>>::Exception& ex) {
        std::cerr << "Error al guardar las recetas: " << ex.what() << std::endl;
    }
    system("pause");
    
}

void UserInterfaces::leerReceta() {
    
    std::string fileName;
    std::cout << "Ingrese el nombre del archivo para leer las recetas: ";
    std::cin >> fileName;
    try {
        listRef->readFromDisk(fileName);
        std::cout << "Recetas leídas exitosamente desde " << fileName << std::endl;
    } catch (const List<Recipe<Name, Ingredients>>::Exception& ex) {
        std::cerr << "Error al leer las recetas: " << ex.what() << std::endl;
    }
    system("pause");
    
}

void UserInterfaces::ordenar(int op) {
    cout << "Que tipo de ordenamiento recursivo quiere? (sino sabe que es responder cualquier cosa)" << endl;
    cout << "1.- MergeSort" << endl;
    cout << "2.- QuickSort" << endl;
    cout << "Respuesta:" << endl;
    int typeSort;
    cin >> typeSort;
    cin.ignore();

    if(op == 1)
    {
        if (typeSort == 1) {
            listRef->sortDataMerge(Recipe<Name, Ingredients>::compareByName);
        } else  {
            listRef->sortDataQuick(Recipe<Name, Ingredients>::compareByName);
        }
    }

    else
    {
        if (typeSort == 1) {
            listRef->sortDataMerge(Recipe<Name, Ingredients>::compareByPreparationTime);
        }
        else {
            listRef->sortDataQuick(Recipe<Name, Ingredients>::compareByPreparationTime);
        }
    }
}

int UserInterfaces::buscar(int op) {
    std::string myString;
    Recipe<Name, Ingredients> tempRecipe;

    if (op == 1) {
        cout << "Digame el nombre de la receta que desea buscar: ";
        cin.ignore();
        getline(cin, myString);
        tempRecipe.setName(myString);

        auto pos = listRef->getFirstPos();
        int idx = 1;
        while (pos != nullptr) {
            if (Recipe<Name, Ingredients>::compareByName(*listRef->retrieve(pos), tempRecipe) == 0) {
                cout << "Receta encontrada." << endl;
                encontrar(idx); // Llama a encontrar con la posición encontrada
                return idx;
            }
            pos = listRef->getNextPos(pos);
            idx++;
        }
        cout << "Receta no encontrada." << endl;
    } else {
        cout << "Digame la categoria de la receta que desea buscar (sino dice una valida se tomara la ultima):" << endl;
        cout << "1.- Desayuno" << endl;
        cout << "2.- Almuerzo" << endl;
        cout << "3.- Cena" << endl;
        cout << "4.- Navideno" << endl;
        int tipo;
        cin >> tipo;
        cin.ignore();

        if (tipo == 1) {
            myString = "Desayuno";
        } else if (tipo == 2) {
            myString = "Almuerzo";
        } else if (tipo == 3) {
            myString = "Cena";
        } else if (tipo == 4) {
            myString = "Navideno";
        } else {
            myString = "Navideno";
        }
        tempRecipe.setCategory(myString);

        auto pos = listRef->getFirstPos();
        int idx = 1;
        while (pos != nullptr) {
            if (Recipe<Name, Ingredients>::compareByCategory(*listRef->retrieve(pos), tempRecipe) == 0) {
                cout << "Receta encontrada." << endl;
                encontrar(idx);
                return idx;
            }
            pos = listRef->getNextPos(pos);
            idx++;
        }
        cout << "Receta no encontrada." << endl;
    }
    return -1; 
}

int UserInterfaces::buscarPorNombre(const std::string& nombre) {
    Recipe<Name, Ingredients> tempRecipe;
    tempRecipe.setName(nombre);
    auto pos = listRef->getFirstPos();
    int idx = 1;
    while (pos != nullptr) {
        if (Recipe<Name, Ingredients>::compareByName(*listRef->retrieve(pos), tempRecipe) == 0) {
            return idx;
        }
        pos = listRef->getNextPos(pos);
        idx++;
    }
    return -1;
}

void UserInterfaces::writeToDisk(const std::string& fileName) {
    try {
        listRef->writeToDisk(fileName);
        std::cout << "Recetas guardadas exitosamente en " << fileName << std::endl;
    } catch (const List<Recipe<Name, Ingredients>>::Exception& ex) {
        std::cerr << "Error al guardar las recetas: " << ex.what() << std::endl;
    }
}

void UserInterfaces::readFromDisk(const std::string& fileName) {
    try {
        listRef->readFromDisk(fileName);
        std::cout << "Recetas leidas exitosamente desde " << fileName << std::endl;
    } catch (const List<Recipe<Name, Ingredients>>::Exception& ex) {
        std::cerr << "Error al leer las recetas: " << ex.what() << std::endl;
    }
}