#include <iostream>
#include <SFML/Graphics.hpp>
#define GLM_FORCE_RADIANS
#include <GLM/GLM.hpp>
#include "RenderSystem.hpp"

int main()
{
    RenderSystem render(800, 600, "Fluid Simulation");
    
    render.Start();
    
    return 0;
}
