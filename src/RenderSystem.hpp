#ifndef RenderSystem_hpp
#define RenderSystem_hpp
#include <SFML/Graphics.hpp>

class RenderSystem {
public:
   RenderSystem(unsigned int width, unsigned int height, const std::string &windowName);
   ~RenderSystem();
   void Start();

protected:
   virtual void Update();

private:
   sf::RenderWindow window;
};

#endif /* RenderSystem_hpp */
