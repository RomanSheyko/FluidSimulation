#ifndef Simulation_hpp
#define Simulation_hpp
#include "FluidGrid.hpp"

class SimpleRules {
public:
   SimpleRules(FluidGrid& grid) : grid(grid), prev_grid(grid) {
      for (int y = 0; y < grid.GetHeight(); y++) {
         for (int x = 0; x < grid.GetWigth(); x++) {
            grid.SetVelocityAt({x, y}, {0.f, -1.f});
         }
      }
      
      prev_grid = grid;
   }
   
   void Update(float dt);
private:
   FluidGrid& grid;
   FluidGrid prev_grid;
};

template<class SimulationRules>
class Simulation {
public:
   Simulation(int gridWidth, int gridHeight) : grid(gridWidth, gridHeight), rules(grid) {}
   
   void Update(float dt) {
      rules.Update(dt);
   }
   
   const FluidGrid& GetGrid() const { return grid; };
private:
   FluidGrid grid;
   SimulationRules rules;
};

#endif /* Simulation_hpp */
