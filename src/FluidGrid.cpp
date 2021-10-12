#include "FluidGrid.hpp"


FluidGrid::FluidGrid(int gridWidth, int gridHeight) { 
   grid.resize(gridHeight);
   
   for (auto& line : grid) {
      line.resize(gridWidth);
   }
}

void FluidGrid::SetCellInfoAt(const glm::vec2 &pos, const FluidGrid::CellInfo &cellInfo) { 
   grid[pos.y][pos.x].pressure = cellInfo.pressure;
   grid[pos.y][pos.x].velocity = cellInfo.velocity;
}


void FluidGrid::SetPressureAt(const glm::vec2 &pos, float pressure) { 
   grid[pos.y][pos.x].pressure = pressure;
}


void FluidGrid::SetVelocityAt(const glm::vec2 &pos, const glm::vec2& velocity) {
   grid[pos.y][pos.x].velocity = velocity;
}
