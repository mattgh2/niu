#include <vector>
#include "player.h"
#include "hitter.h"
#include "pitcher.h"
void print_hitters(const std::vector<player*>& roster) {
  for (const auto& i : roster) {
    hitter* h = nullptr;
    if ((h = dynamic_cast<hitter*>(i))) {
      i->print(); std::cout << "\n";
    }
  }
}
void print_pitchers(const std::vector<player*>& roster) {
  for (const auto& i : roster) {
    pitcher* p = nullptr;
    if ((p = dynamic_cast<pitcher*>(i))) {
      i->print(); std::cout << "\n";
    }
  }
}
