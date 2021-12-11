#include "FluidGrid.hpp"


FluidGrid::FluidGrid(int gridWidth, int gridHeight) : gridHeight(gridHeight), gridWidth(gridWidth) {
   grid.resize(gridHeight);
   grid_prev.resize(gridHeight);
   
   for (auto& line : grid) {
      line.resize(gridWidth);
   }
   
   for (auto& line : grid_prev) {
      line.resize(gridWidth);
   }
}

void FluidGrid::SetCellInfoAt(const glm::ivec2 &pos, const FluidGrid::CellInfo &cellInfo) {
   grid[glm::clamp(pos.y, 0, gridHeight)][glm::clamp(pos.x, 0, gridWidth)].pressure = cellInfo.pressure;
   grid[glm::clamp(pos.y, 0, gridHeight)][glm::clamp(pos.x, 0, gridWidth)].velocity = cellInfo.velocity;
}


void FluidGrid::SetPressureAt(const glm::ivec2 &pos, float pressure) {
   grid[glm::clamp(pos.y, 0, gridHeight)][glm::clamp(pos.x, 0, gridWidth)].pressure = glm::clamp(pressure, 0.f, 1.f);
}


void FluidGrid::SetVelocityAt(const glm::ivec2 &pos, const glm::vec2& velocity) {
   grid[glm::clamp(pos.y, 0, gridHeight)][glm::clamp(pos.x, 0, gridWidth)].velocity = velocity;
}


void FluidGrid::Update(float dt) {
   
}
