#include <SFML/Graphics.hpp>
#include <iostream>
#define GLM_FORCE_RADIANS
#include "RenderSystem.hpp"
// #include <GLM/GLM.hpp>

int main() {
  RenderSystem render(800, 600, "Fluid Simulation");

  render.Start();

  return 0;
}
