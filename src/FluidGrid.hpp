#ifndef FluidSimulation_hpp
#define FluidSimulation_hpp
#include <vector>
#include <iostream>
#define GLM_FORCE_RADIANS
#include <GLM/GLM.hpp>

class FluidGrid {
public:
   FluidGrid(int gridWidth, int gridHeight);
   
   struct CellInfo {
      glm::vec2 velocity;
      float pressure = 0.f;
   };
   
   void SetVelocityAt(const glm::vec2& pos, const glm::vec2& velocity);
   void SetPressureAt(const glm::vec2& pos, float pressure);
   void SetCellInfoAt(const glm::vec2& pos, const CellInfo& cellInfo);
private:
   std::vector<std::vector<CellInfo>> grid;
};

#endif /* FluidSimulation_hpp */
