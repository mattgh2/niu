#include "pitcher.h"
pitcher::pitcher(const std::string& name, int number, int earned_runs, int innings_pitched) : player(name, number) {
    this->earned_runs = earned_runs;
    this->innings_pitched = innings_pitched;
}
void pitcher::print() const {
    player::print();
 std::cout << std::right << std::setw(7) << earned_runs
           << std::right << std::setw(7) << innings_pitched
           << std::right << std::setprecision(2) << std::fixed << std::setw(9) << average();
 
}
double pitcher::average() const {
  return (innings_pitched > 0) ? (static_cast<double>(earned_runs * 9) / innings_pitched) : 0;
}

