#include "Simulation.hpp"
#include <cassert>


void SimpleRules::Update(float dt) {
   // velocity step
//   for (int y = 0; y < grid.GetHeight(); y++) {
//      for (int x = 0; x < grid.GetWigth(); x++) {
//
//         grid.SetVelocityAt({x, y}, grid.GetVelocityAt({x, y}) + glm::vec2(0.f, 9.8f) * 0.00001f);
//      }
//   }
   std::swap(grid, prev_grid);
   DiffuseVel(dt, 0.0001f, 1);
   Project();
   std::swap(grid, prev_grid);
   AdvectVel(dt, 1);
   Project();
   
   // density step
   std::swap(grid, prev_grid);
   Diffuse(dt, 0.0005f);
   std::swap(grid, prev_grid);
   Advect(dt, 0);
   
}


void SimpleRules::Diffuse(float dt, float diffusion, int b) {
   float a = dt * diffusion * (grid.GetWigth() - 1) * (grid.GetHeight() - 1);
   
   for (int k = 0; k < 5; k++) {
      for (int y = 1; y < grid.GetHeight() - 1; y++) {
         for (int x = 1; x < grid.GetWigth() - 1; x++) {
            glm::ivec2 pos {x, y};
            float pressure = (prev_grid.GetPressureAt(pos) + a * (grid.GetPressureAt({x - 1, y}) + grid.GetPressureAt({x + 1, y}) + grid.GetPressureAt({x, y - 1}) + grid.GetPressureAt({x, y + 1}))) / (1 + 4 * a);
            grid.SetPressureAt(pos, pressure);
         }
      }
      SetBndPressure(b);
   }
}


void SimpleRules::DiffuseVel(float dt, float diffusion, int b) {
   float a = dt * diffusion * (grid.GetWigth() - 1) * (grid.GetHeight() - 1);
   
   for (int k = 0; k < 5; k++) {
      for (int y = 1; y < grid.GetHeight() - 1; y++) {
         for (int x = 1; x < grid.GetWigth() - 1; x++) {
            glm::ivec2 pos {x, y};
            auto vel = (prev_grid.GetVelocityAt(pos) + a * (grid.GetVelocityAt({x - 1, y}) + grid.GetVelocityAt({x + 1, y}) + grid.GetVelocityAt({x, y - 1}) + grid.GetVelocityAt({x, y + 1}))) / (1 + 4 * a);
            grid.SetVelocityAt(pos, vel);
         }
      }
      SetBndVelocity(b);
   }
}


void SimpleRules::Advect(float dt, int b) {
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
   
   SetBndPressure(b);
}


void SimpleRules::AdvectVel(float dt, int b) {
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
         
         auto vel = s0 * (t0 * prev_grid.GetVelocityAt(ipos0) + t1 * prev_grid.GetVelocityAt({ipos1.x, ipos0.y})) + s1 * (t0 * prev_grid.GetVelocityAt({ipos0.x, ipos1.y}) + t1 * prev_grid.GetVelocityAt(ipos1));
         grid.SetVelocityAt({x, y}, vel);
      }
   }
   
   SetBndVelocity(b);
}


void SimpleRules::Project() {
   
   float h = 1.0 / grid.GetHeight();
   for (int y = 1; y < grid.GetHeight() - 1; y++) {
      for (int x = 1; x < grid.GetWigth() - 1; x++) {
         prev_grid.SetVelocityAt({x, y}, {0, -0.5f * h * (grid.GetVelocityAt({x + 1, y}).x - grid.GetVelocityAt({x - 1, y}).x + grid.GetVelocityAt({x, y + 1}).y - grid.GetVelocityAt({x, y - 1}).y)});
      }
   }
   
   SetBndVelocityPrev(0);
   
   for (int k = 0; k < 5; k++) {
      for (int y = 1; y < grid.GetHeight() - 1; y++) {
         for (int x = 1; x < grid.GetWigth() - 1; x++) {
            auto oldVel = prev_grid.GetVelocityAt({x, y});
            prev_grid.SetVelocityAt({x, y}, {(oldVel.y + prev_grid.GetVelocityAt({x - 1, y}).x + prev_grid.GetVelocityAt({x + 1, y}).x + prev_grid.GetVelocityAt({x, y - 1}).x + prev_grid.GetVelocityAt({x, y + 1}).x) / 4.f, oldVel.y});
         }
      }
      SetBndVelocityPrev(0);
   }
   
   for (int y = 1; y < grid.GetHeight() - 1; y++) {
      for (int x = 1; x < grid.GetWigth() - 1; x++) {
         auto oldVel = grid.GetVelocityAt({x, y});
         glm::vec2 newVel = {0.5f * (prev_grid.GetVelocityAt({x + 1, y}).x - prev_grid.GetVelocityAt({x - 1, y}).x) / h, 0.5f * (prev_grid.GetVelocityAt({x, y + 1}).x - prev_grid.GetVelocityAt({x, y - 1}).x) / h};
         grid.SetVelocityAt({x, y}, oldVel - newVel);
      }
   }
   
   SetBndVelocity(1);
}


void SimpleRules::SetBndPressure(int b) {
   
   for (int y = 1; y < grid.GetHeight() - 1; y++) {
      grid.SetPressureAt({0, y}, (b == 1 ? -1 : 1) * grid.GetPressureAt({1, y}));
      grid.SetPressureAt({grid.GetWigth() - 1, y}, (b == 1 ? -1 : 1) * grid.GetPressureAt({grid.GetWigth() - 2, y}));
   }
   
   for (int x = 1; x < grid.GetWigth() - 1; x++) {
      grid.SetPressureAt({x, 0}, (b == 2 ? -1 : 1) * grid.GetPressureAt({x, 1}));
      grid.SetPressureAt({x, grid.GetHeight() - 1}, (b == 2 ? -1 : 1) * grid.GetPressureAt({x, grid.GetHeight() - 2}));
   }
   
   grid.SetPressureAt({0, 0}, 0.5f * (grid.GetPressureAt({1, 0}) + grid.GetPressureAt({0, 1})));
   grid.SetPressureAt({0, grid.GetHeight() - 1}, 0.5f * (grid.GetPressureAt({1, grid.GetHeight() - 1}) + grid.GetPressureAt({0, grid.GetHeight() - 2})));
   grid.SetPressureAt({grid.GetWigth() - 1, 0}, 0.5f * (grid.GetPressureAt({grid.GetWigth() - 2, 0}) + grid.GetPressureAt({grid.GetWigth() - 1, 1})));
   grid.SetPressureAt({grid.GetWigth() - 1, grid.GetHeight() - 1}, 0.5f * (grid.GetPressureAt({grid.GetWigth() - 2, grid.GetHeight() - 1}) + grid.GetPressureAt({grid.GetWigth() - 1, grid.GetHeight() - 2})));
}


void SimpleRules::SetBndVelocity(int b) {
   
   for (int y = 1; y < grid.GetHeight() - 1; y++) {
      grid.SetVelocityAt({0, y}, static_cast<float>(b == 1 ? -1 : 1) * grid.GetVelocityAt({1, y}));
      grid.SetVelocityAt({grid.GetWigth() - 1, y}, static_cast<float>(b == 1 ? -1 : 1) * grid.GetVelocityAt({grid.GetWigth() - 2, y}));
   }
   
   for (int x = 1; x < grid.GetWigth() - 1; x++) {
      grid.SetVelocityAt({x, 0}, static_cast<float>(b == 2 ? -1 : 1) * grid.GetVelocityAt({x, 1}));
      grid.SetVelocityAt({x, grid.GetHeight() - 1}, static_cast<float>(b == 2 ? -1 : 1) * grid.GetVelocityAt({x, grid.GetHeight() - 2}));
   }
   
   grid.SetVelocityAt({0, 0}, 0.5f * (grid.GetVelocityAt({1, 0}) + grid.GetVelocityAt({0, 1})));
   grid.SetVelocityAt({0, grid.GetHeight() - 1}, 0.5f * (grid.GetVelocityAt({1, grid.GetHeight() - 1}) + grid.GetVelocityAt({0, grid.GetHeight() - 2})));
   grid.SetVelocityAt({grid.GetWigth() - 1, 0}, 0.5f * (grid.GetVelocityAt({grid.GetWigth() - 2, 0}) + grid.GetVelocityAt({grid.GetWigth() - 1, 1})));
   grid.SetVelocityAt({grid.GetWigth() - 1, grid.GetHeight() - 1}, 0.5f * (grid.GetVelocityAt({grid.GetWigth() - 2, grid.GetHeight() - 1}) + grid.GetVelocityAt({grid.GetWigth() - 1, grid.GetHeight() - 2})));
}


void SimpleRules::SetBndVelocityPrev(int b) {
   for (int y = 1; y < prev_grid.GetHeight() - 1; y++) {
      prev_grid.SetVelocityAt({0, y}, static_cast<float>(b == 1 ? -1 : 1) * prev_grid.GetVelocityAt({1, y}));
      prev_grid.SetVelocityAt({prev_grid.GetWigth() - 1, y}, static_cast<float>(b == 1 ? -1 : 1) * prev_grid.GetVelocityAt({grid.GetWigth() - 2, y}));
   }
   
   for (int x = 1; x < prev_grid.GetWigth() - 1; x++) {
      prev_grid.SetVelocityAt({x, 0}, static_cast<float>(b == 2 ? -1 : 1) * prev_grid.GetVelocityAt({x, 1}));
      prev_grid.SetVelocityAt({x, prev_grid.GetHeight() - 1}, static_cast<float>(b == 2 ? -1 : 1) * prev_grid.GetVelocityAt({x, prev_grid.GetHeight() - 2}));
   }
   
   prev_grid.SetVelocityAt({0, 0}, 0.5f * (prev_grid.GetVelocityAt({1, 0}) + prev_grid.GetVelocityAt({0, 1})));
   prev_grid.SetVelocityAt({0, prev_grid.GetHeight() - 1}, 0.5f * (prev_grid.GetVelocityAt({1, prev_grid.GetHeight() - 1}) + prev_grid.GetVelocityAt({0, prev_grid.GetHeight() - 2})));
   prev_grid.SetVelocityAt({prev_grid.GetWigth() - 1, 0}, 0.5f * (prev_grid.GetVelocityAt({prev_grid.GetWigth() - 2, 0}) + prev_grid.GetVelocityAt({grid.GetWigth() - 1, 1})));
   prev_grid.SetVelocityAt({prev_grid.GetWigth() - 1, prev_grid.GetHeight() - 1}, 0.5f * (prev_grid.GetVelocityAt({prev_grid.GetWigth() - 2, prev_grid.GetHeight() - 1}) + prev_grid.GetVelocityAt({prev_grid.GetWigth() - 1, prev_grid.GetHeight() - 2})));
}
