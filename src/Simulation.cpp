#include "Simulation.hpp"
#include <cassert>

void SimpleRules::Update(float dt) {
   for (int y = 0; y < grid.GetHeight(); y++) {
      for (int x = 0; x < grid.GetWigth(); x++) {
         if (y == grid.GetHeight() - 2 && x != 0 && x != grid.GetWigth() - 1) {
            grid.SetPressureAt({x, y}, 1.f);
         }
      }
   }
   std::swap(grid, prev_grid);
   Diffuse(dt, 0.02f);
   std::swap(grid, prev_grid);
   Addvect(dt);
   //std::swap(grid, prev_grid);
}

void SimpleRules::Diffuse(float dt, float diffusion) {
   float a = dt * diffusion * (grid.GetWigth() - 1) * (grid.GetHeight() - 1);
   
   for (int k = 0; k < 20; k++) {
      for (int y = 1; y < grid.GetHeight() - 1; y++) {
         for (int x = 1; x < grid.GetWigth() - 1; x++) {
            glm::ivec2 pos {x, y};
            float pressure = (prev_grid.GetPressureAt(pos) + a * (grid.GetPressureAt({x - 1, y}) + grid.GetPressureAt({x + 1, y}) + grid.GetPressureAt({x, y - 1}) + grid.GetPressureAt({x, y + 1}))) / (1 + 4 * a);
            grid.SetPressureAt(pos, pressure);
         }
      }
   }
}

void SimpleRules::Addvect(float dt) {
   float dt0 = dt * (grid.GetHeight() - 1);
   
   for (int y = 1; y < grid.GetHeight() - 1; y++) {
      for (int x = 1; x < grid.GetWigth() - 1; x++) {
         float x0 = x - dt0 * grid.GetVelocityAt({x, y}).x;
         float y0 = y - dt0 * grid.GetVelocityAt({x, y}).y;
         
         if (x0 < 0.5f) x0 = 0.5f;
         if (x0 > (grid.GetWigth() - 1) + 0.5) x0 = (grid.GetWigth() - 1) + 0.5;
         if (y0 < 0.5f) y0 = 0.5f;
         if (y0 > (grid.GetHeight() - 1) + 0.5) y0 = (grid.GetHeight() - 1) + 0.5;
         
         glm::ivec2 ipos0 {(int)x0, (int)y0};
         glm::ivec2 ipos1 = ipos0 + 1;
         
         float s1 = y0 - ipos0.y;
         float s0 = 1 - s1;
         float t1 = x0 - ipos0.x;
         float t0 = 1 - t1;
         
         float pressure = s0 * (t0 * prev_grid.GetPressureAt(ipos0) + t1 * prev_grid.GetPressureAt({ipos1.x, ipos0.y})) + s1 * (t0 * prev_grid.GetPressureAt({ipos0.x, ipos1.y}) + t1 * prev_grid.GetPressureAt(ipos1));
         grid.SetPressureAt({x, y}, pressure);
      }
   }
}
