#include "userinterfaces.hpp"
#include "list.hpp"
#include "listdoble.hpp"
#include "recipe.hpp"
#include "name.hpp"
#include "ingredients.hpp"


int main() {
    List<Recipe<Name, Ingredients>> myListRecipe;
    
    UserInterfaces myInterfaces(myListRecipe);
    return 0;
}