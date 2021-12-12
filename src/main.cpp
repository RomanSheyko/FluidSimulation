#include <SFML/Graphics.hpp>
#include <iostream>
#define GLM_FORCE_RADIANS
#include "RenderSystem.hpp"
#include "FluidGrid.hpp"

int main() {
   RenderSystem render(1400, 1000, "Fluid Simulation");
   render.dbgDrawVectorField = true;
   render.Start();
   
   return 0;
}
