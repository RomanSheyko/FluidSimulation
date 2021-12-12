#include "Simulation.hpp"
#include <cassert>

void SimpleRules::Update(float dt) {
   
   std::swap(grid, prev_grid);
}
