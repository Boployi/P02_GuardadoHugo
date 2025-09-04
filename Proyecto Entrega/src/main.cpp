#include "userinterfaces.hpp"
#include "list.hpp"
#include "listdoble.hpp"
#include "recipe.hpp"
#include "name.hpp"
#include "ingredients.hpp"
//MODIFICACION INTENSA

int main() {
    List<Recipe<Name, Ingredients>> myListRecipe;
    
    UserInterfaces myInterfaces(myListRecipe);
    return 0;
}
