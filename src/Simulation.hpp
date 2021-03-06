#ifndef Simulation_hpp
#define Simulation_hpp
#include "FluidGrid.hpp"
#include <GLM/gtc/random.hpp>

// Simulation from http://graphics.cs.cmu.edu/nsp/course/15-464/Fall09/papers/StamFluidforGames.pdf article
class SimpleRules {
public:
   SimpleRules(FluidGrid& grid) : grid(grid), prev_grid(grid) {
//      for (int y = 0; y < grid.GetHeight(); y++) {
//         for (int x = 0; x < grid.GetWigth(); x++) {
//
//            if (y == grid.GetHeight() - 2 && x != 0 && x != grid.GetWigth() - 1) {
//               grid.SetVelocityAt({x, y}, {0.f, -0.1f});
//               grid.SetPressureAt({x, y}, 1.f);
//            }
//         }
//      }
      
      prev_grid = grid;
   }
   
   void Update(float dt);
   
   void Diffuse(float dt, float diffusion, int b = 0);
   void DiffuseVel(float dt, float diffusion, int b = 0);
   void Advect(float dt, int b);
   void AdvectVel(float dt, int b);
   void Project();
   void SetBndPressure(int b);
   void SetBndVelocity(int b);
   void SetBndVelocityPrev(int b);
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
   
   FluidGrid& GetGrid() { return grid; };
private:
   FluidGrid grid;
   SimulationRules rules;
};

#endif /* Simulation_hpp */
