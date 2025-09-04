#include "ingredients.hpp"
using namespace std;
#include <iomanip>
#include <sstream>

Ingredients::Ingredients() : quantity(0) {}

Ingredients::Ingredients(const Ingredients& i) : name(i.name), quantity(i.quantity){}

std::string Ingredients::getName() const {
    return name;
}

float Ingredients::getQuantity() const {
    return quantity;
}

std::string Ingredients::toString() const {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << quantity;
    return "- " + name + " con " + ss.str();
}

void Ingredients::setName(const std::string& n) {
    name = n;
}

void Ingredients::setQuantity(const float& q) {
    quantity = q;
}

std::istream& operator>>(std::istream& is, Ingredients& i) {
    getline(is, i.name, '*');
    std::string quantityStr;
    getline(is, quantityStr, '*');
    i.quantity = std::stof(quantityStr);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Ingredients& i) {
    os << i.name << '*' << i.quantity << '*';
    return os;
}
