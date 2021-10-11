#include "RenderSystem.hpp"

RenderSystem::RenderSystem(unsigned int width, unsigned int height,
                           const std::string &windowName)
    : window(sf::VideoMode(width, height), sf::String(windowName)) {}

void RenderSystem::Update() {
  window.clear(sf::Color::Black);

  sf::RectangleShape rectangle(sf::Vector2f(120.f, 50.f));
  rectangle.setPosition(120.f, 20.f);
  rectangle.setFillColor(sf::Color(150, 50, 250));

  window.draw(rectangle);

  window.display();
}

void RenderSystem::Start() {
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    Update();
  }
}

RenderSystem::~RenderSystem() {}
