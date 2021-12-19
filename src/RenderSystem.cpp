#include "RenderSystem.hpp"
#include <GLM/gtx/rotate_vector.hpp>
#include <GLM/gtc/random.hpp>
#include <array>

RenderSystem::RenderSystem(int width, int height,
                           const std::string &windowName)
    : window(sf::VideoMode(width, height), sf::String(windowName)), simulation(width / cellSize, height / cellSize)
{
   window.setVerticalSyncEnabled(true);
   
   window.setFramerateLimit(60);
}

void RenderSystem::Update(float dt) {
   window.clear(sf::Color::Black);
   
   if (mousePressed) {
      auto pos = sf::Mouse::getPosition(window);
      glm::ivec2 ipos {(int)(pos.x / cellSize), (int)(pos.y / cellSize)};
      
      for (int x = -1; x < 1; x++) {
         for (int y = -1; y < 1; y++) {
            simulation.GetGrid().SetPressureAt({ipos.x + x, ipos.y + y}, glm::clamp(simulation.GetGrid().GetPressureAt({ipos.x + x, ipos.y + y}) + 4.f, 0.f, 10.f));
         }
      }
      glm::vec2 fpos {(float)ipos.x, (float)ipos.y};
      simulation.GetGrid().SetVelocityAt(ipos, simulation.GetGrid().GetVelocityAt(ipos) + (fpos - prevPos) * 2.f);
      prevPos = fpos;
   }
   
   simulation.Update(dt);
   
   sf::RectangleShape rectangle(sf::Vector2f((float)cellSize, (float)cellSize));
   
   std::array<sf::Vertex, 2> line;
   std::array<sf::Vertex, 2> line2;
   std::array<sf::Vertex, 2> line3;
   
   auto grid = simulation.GetGrid();
   
   for (int y = 0; y < grid.GetHeight(); y++) {
      for (int x = 0; x < grid.GetWigth(); x++) {
         glm::vec2 pos {x, y};
         
         float pressure = grid.GetPressureAt(pos);
         glm::ivec3 color = GetColorByPressure(pressure);
         rectangle.setFillColor(sf::Color({static_cast<sf::Uint8>(color.x), static_cast<sf::Uint8>(color.y), static_cast<sf::Uint8>(color.z)}));
         
         rectangle.setPosition(x * cellSize, y * cellSize);
         
         window.draw(rectangle);
         
         glm::vec2 velocity = grid.GetVelocityAt(pos);
         
         if (dbgDrawVectorField) {
            DrawVector({x * cellSize + cellSize / 2, y * cellSize + cellSize / 2}, velocity, line, line2, line3);
         }
      }
   }

   window.display();
}

void RenderSystem::Start() {
   sf::Clock deltaClock;
   
   while (window.isOpen()) {
      sf::Event event;
      while (window.pollEvent(event)) {
         if (event.type == sf::Event::Closed) {
            window.close();
         }
         
         if (event.type == sf::Event::MouseButtonPressed) {
            mousePressed = true;
            
         }
         
         if (event.type == sf::Event::MouseButtonReleased) {
            mousePressed = false;
         }
      }
      
      sf::Time dt = deltaClock.restart();
      
      Update(dt.asSeconds());
      
      //sf::sleep(sf::milliseconds(1000));
   }
}

float Remap(float value, float from1, float to1, float from2, float to2) {
   return (value - from1) / (to1 - from1) * (to2 - from2) + from2;
}

void RenderSystem::DrawVector(const glm::vec2& pos, const glm::vec2& vec, std::array<sf::Vertex, 2>& line, std::array<sf::Vertex, 2>& line2, std::array<sf::Vertex, 2>& line3) {
   static constexpr float MAX_VELOCITY_LENGTH = 500.f;
   static constexpr float VEC_LENGTH_TO_DISPLAY = 30.f;
   static constexpr float ARROW_EDGE_LENGTH_TO_DISPLAY = 20.f;
   
   float len = glm::length(vec);
   if (len == 0.f) {
      return;
   }
   
   glm::vec2 vec_norm = glm::normalize(vec);
   glm::vec2 f_angle = glm::rotate(vec_norm, glm::pi<float>() / 6) * ARROW_EDGE_LENGTH_TO_DISPLAY;
   glm::vec2 s_angle = glm::rotate(vec_norm, glm::pi<float>() / -6) * ARROW_EDGE_LENGTH_TO_DISPLAY;
   
   vec_norm *= VEC_LENGTH_TO_DISPLAY;
   
   len = Remap(len, 0.f, MAX_VELOCITY_LENGTH, 0.f, 1.f);
   glm::ivec3 color = GetColorByVelocityLenth(len);
   line[0].color = sf::Color({static_cast<sf::Uint8>(color.x), static_cast<sf::Uint8>(color.y), static_cast<sf::Uint8>(color.z)});
   line[1].color = sf::Color({static_cast<sf::Uint8>(color.x), static_cast<sf::Uint8>(color.y), static_cast<sf::Uint8>(color.z)});
   
   line2[0].color = sf::Color({static_cast<sf::Uint8>(color.x), static_cast<sf::Uint8>(color.y), static_cast<sf::Uint8>(color.z)});
   line2[1].color = sf::Color({static_cast<sf::Uint8>(color.x), static_cast<sf::Uint8>(color.y), static_cast<sf::Uint8>(color.z)});
   
   line3[0].color = sf::Color({static_cast<sf::Uint8>(color.x), static_cast<sf::Uint8>(color.y), static_cast<sf::Uint8>(color.z)});
   line3[1].color = sf::Color({static_cast<sf::Uint8>(color.x), static_cast<sf::Uint8>(color.y), static_cast<sf::Uint8>(color.z)});
   
   line[0].position = sf::Vector2f(pos.x, pos.y);
   line[1].position = sf::Vector2f((pos + vec_norm).x, (pos + vec_norm).y);
   
   line2[0].position = sf::Vector2f((pos + vec_norm).x, (pos + vec_norm).y);
   line2[1].position = sf::Vector2f((pos + f_angle).x, (pos + f_angle).y);
   
   line3[0].position = sf::Vector2f((pos + vec_norm).x, (pos + vec_norm).y);
   line3[1].position = sf::Vector2f((pos + s_angle).x, (pos + s_angle).y);
   
   window.draw(line.data(), 2, sf::Lines);
   window.draw(line2.data(), 2, sf::Lines);
   window.draw(line3.data(), 2, sf::Lines);
}

RenderSystem::~RenderSystem() {}
