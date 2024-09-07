#include "hitter.h"

hitter::hitter(const std::string &name, int number, int hits,int at_bats) : player(name, number) {
  this->hits = hits;
  this->at_bats = at_bats;
}
void hitter::print() const {
  player::print();
  std::cout << std::right << std::setw(7) << hits
            << std::right << std::setw(7) << at_bats 
            << std::right << std::setprecision(3) << std::fixed << std::setw(9) << average();
}
double hitter::average() const {
  return (at_bats > 0) ? (static_cast<double>(hits) / at_bats) : 0.0;
}

