#include "FluidGrid.hpp"


FluidGrid::FluidGrid(int gridWidth, int gridHeight) : gridHeight(gridHeight), gridWidth(gridWidth) {
   grid.resize(gridHeight);
   
   for (auto& line : grid) {
      line.resize(gridWidth);
   }
}


FluidGrid::FluidGrid(const FluidGrid& other) {
   grid = other.grid;
   gridWidth = other.gridWidth;
   gridHeight = other.gridHeight;
}


void FluidGrid::SetCellInfoAt(const glm::ivec2 &pos, const FluidGrid::CellInfo &cellInfo) {
   grid[glm::clamp(pos.y, 0, gridHeight - 1)][glm::clamp(pos.x, 0, gridWidth - 1)].pressure = cellInfo.pressure;
   grid[glm::clamp(pos.y, 0, gridHeight - 1)][glm::clamp(pos.x, 0, gridWidth - 1)].velocity = cellInfo.velocity;
}


void FluidGrid::SetPressureAt(const glm::ivec2 &pos, float pressure) {
   grid[glm::clamp(pos.y, 0, gridHeight - 1)][glm::clamp(pos.x, 0, gridWidth - 1)].pressure = pressure;
}


void FluidGrid::SetVelocityAt(const glm::ivec2 &pos, const glm::vec2& velocity) {
   grid[glm::clamp(pos.y, 0, gridHeight - 1)][glm::clamp(pos.x, 0, gridWidth - 1)].velocity = velocity;
}
