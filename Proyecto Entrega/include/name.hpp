#ifndef __NAME_HPP__
#define __NAME_HPP__
#include <iostream>
#include <string>

class Name {
 private:
  std::string lastName;
  std::string firstName;

 public:
  Name();
  Name(const Name&);

  std::string getLastName() const;
  std::string getFirstName() const;

  std::string toString() const;

  void setLastName(const std::string&);
  void setFirstName(const std::string&);

  friend std::ostream& operator<<(std::ostream&, const Name&);
  friend std::istream& operator>>(std::istream&, Name&);
};

#endif // __NAME_HPP__