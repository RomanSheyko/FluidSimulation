#ifndef RenderSystem_hpp
#define RenderSystem_hpp
#include <SFML/Graphics.hpp>
#define GLM_FORCE_RADIANS
#include <GLM/GLM.hpp>
#include "Simulation.hpp"

float Remap(float value, float from1, float to1, float from2, float to2);

class RenderSystem {
public:
   RenderSystem(int width, int height, const std::string &windowName);
   ~RenderSystem();
   void Start();
   
   bool dbgDrawVectorField = false;

protected:
   virtual void Update(float dt);

private:
   glm::ivec3 GetColorByPressure(float pressure) { return glm::mix(lowPressureColor, hightPressureColor, Remap(pressure, 0.f, 10.f, 0.f, 1.f)); };
   glm::ivec3 GetColorByVelocityLenth(float length) { return glm::mix(shortVectorColor, longVectorColor, length); };
   void DrawVector(const glm::vec2& pos, const glm::vec2& vec, std::array<sf::Vertex, 2>& line, std::array<sf::Vertex, 2>& line2, std::array<sf::Vertex, 2>& line3);
   sf::RenderWindow window;
   
   const glm::ivec3 hightPressureColor {255, 0, 0};
   const glm::ivec3 lowPressureColor {0, 0, 255};
   
   const glm::ivec3 longVectorColor {255, 255, 255};
   const glm::ivec3 shortVectorColor {0, 0, 0};
   
   Simulation<SimpleRules> simulation;
   static const int cellSize = 10;
   
   bool mousePressed = false;
   glm::vec2 prevPos = {0.f, 0.f};
};

#endif /* RenderSystem_hpp */
