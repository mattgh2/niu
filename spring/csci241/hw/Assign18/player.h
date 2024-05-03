#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <iostream>
#include <iomanip>
class player {
private:
  std::string name = "";
  int number = 0;
public:
  player() = default;
  player(const std::string&, const int&);
  virtual ~player();
  int get_number();
  virtual void print() const;
  virtual double average() const = 0;
};

#endif
