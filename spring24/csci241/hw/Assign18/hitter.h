#ifndef HITTER_H
#define HITTER_H
#include "player.h"

class hitter : public player {
private:
  int hits = 0;
  int at_bats = 0;
public:
  hitter() = default;
  hitter(const std::string&, int, int, int);
  double average() const;
  void print() const;
};
#endif
