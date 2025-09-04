#include "name.hpp"

using namespace std;

Name::Name(){}

Name::Name(const Name &n) : lastName(n.lastName), firstName(n.firstName){}

string Name::getLastName() const{
    return this->lastName;
}

string Name::getFirstName() const{
    return this->firstName;
}

string Name::toString() const{
    return this->firstName + " " + this->lastName;
}

void Name::setLastName(const string& l){
    this->lastName = l;
}

void Name::setFirstName(const string& f){
    this->firstName = f;
}

std::istream& operator>>(std::istream& is, Name& n) {
    getline(is, n.firstName, '*');
    getline(is, n.lastName, '*');
    return is;
}

std::ostream& operator<<(std::ostream& os, const Name& n) {
    os << n.firstName << '*' << n.lastName << '*';
    return os;
}
