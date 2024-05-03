#include "player.h"

player::player(const std::string& name, const int& number) {
    this->name = name;
    this->number = number;
}
player::~player() {}

int player::get_number() {
 return number;
}
void player::print() const {
    int numw;
    std::string padding;
  if (number < 10) {
    padding = " ";
    numw = 5;
  } else {
    numw = 6;
    padding = "";
  }

  std::cout << padding << std::setw(numw) << std::left 
            << number
            << std::left << std::setw(20)
            << name;
}
