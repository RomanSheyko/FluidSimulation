#ifndef FluidGrid_hpp
#define FluidGrid_hpp
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
   
   void Update(float dt);
   
   void SetVelocityAt(const glm::ivec2& pos, const glm::vec2& velocity);
   void SetPressureAt(const glm::ivec2& pos, float pressure);
   void SetCellInfoAt(const glm::ivec2& pos, const CellInfo& cellInfo);
   
   CellInfo GetCellInfoAt(const glm::ivec2& pos) { return grid[glm::clamp(pos.y, 0, gridHeight)][glm::clamp(pos.x, 0, gridWidth)]; };
   glm::vec2 GetVelocityAt(const glm::ivec2& pos) { return GetCellInfoAt(pos).velocity; };
   float GetPressureAt(const glm::ivec2& pos) { return GetCellInfoAt(pos).pressure; };
   
   int GetHeight() { return gridHeight; };
   int GetWigth() { return gridWidth; };
private:
   std::vector<std::vector<CellInfo>> grid;
   std::vector<std::vector<CellInfo>> grid_prev;
   
   int gridWidth;
   int gridHeight;
};

#endif /* FluidGrid_hpp */
