#ifndef __INGREDIENTS_HPP__
#define __INGREDIENTS_HPP__

#include <string>

class Ingredients {
 private:
  std::string name;
  float quantity;

 public:
  Ingredients();
  Ingredients(const Ingredients&);

  std::string getName() const;
  float getQuantity() const;

  std::string toString() const;

  void setName(const std::string&);
  void setQuantity(const float&);

  friend std::ostream& operator<<(std::ostream&, const Ingredients&);
  friend std::istream& operator>>(std::istream&, Ingredients&);
};

#endif // __INGREDIENTS_HPP__
