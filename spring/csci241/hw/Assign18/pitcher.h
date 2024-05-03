#include "player.h"
class pitcher : public player {
private:
  int earned_runs = 0;
  int innings_pitched = 0;
public:
  pitcher() = default;
  pitcher(const std::string&, int, int, int);

  void print() const;
  double average() const;
};

