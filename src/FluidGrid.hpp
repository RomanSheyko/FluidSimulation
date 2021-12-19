#ifndef FluidGrid_hpp
#define FluidGrid_hpp
#include <vector>
#include <iostream>
#define GLM_FORCE_RADIANS
#include <GLM/GLM.hpp>

class FluidGrid {
public:
   FluidGrid(int gridWidth, int gridHeight);
   FluidGrid(const FluidGrid& other);
   
   struct CellInfo {
      glm::vec2 velocity;
      float pressure = 0.f;
   };
   
   void SetVelocityAt(const glm::ivec2& pos, const glm::vec2& velocity);
   void SetPressureAt(const glm::ivec2& pos, float pressure);
   void SetCellInfoAt(const glm::ivec2& pos, const CellInfo& cellInfo);
   
   CellInfo GetCellInfoAt(const glm::ivec2& pos) const { return grid[glm::clamp(pos.y, 0, gridHeight - 1)][glm::clamp(pos.x, 0, gridWidth - 1)]; };
   glm::vec2 GetVelocityAt(const glm::ivec2& pos) const { return GetCellInfoAt(pos).velocity; };
   float GetPressureAt(const glm::ivec2& pos) const { return GetCellInfoAt(pos).pressure; };
   
   int GetHeight() const { return gridHeight; };
   int GetWigth() const { return gridWidth; };
   
   FluidGrid& operator=(const FluidGrid& other)
   {
      if (this == &other) {
         return *this;
      }
      
      grid = other.grid;
      gridWidth = other.gridWidth;
      gridHeight = other.gridHeight;
      return *this;
   }
   
   FluidGrid& operator=(FluidGrid&& other) noexcept
   {
      if (this == &other)
         return *this;
      
      grid = std::move(other.grid);
      return *this;
   }
   std::vector<std::vector<CellInfo>> grid;
private:
   
   int gridWidth;
   int gridHeight;
};

#endif /* FluidGrid_hpp */
