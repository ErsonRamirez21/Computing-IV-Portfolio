// Copyright [2022] <Erson Ramirez Mendoza>
// Graphics
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main() {
  int x = 0, y = 0;

  // Window Settings
  sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML window");
  window.setFramerateLimit(120);

  // Load Texture
  sf::Texture texture;
  if (!texture.loadFromFile("sprite.png"))
    return EXIT_FAILURE;
  sf::Sprite sprite(texture);

  // Load Font & Set Color
  sf::Font font;
  if (!font.loadFromFile("BROADW.TTF"))
    return EXIT_FAILURE;
  sf::Text text("YOU FOUND THE SECRET BUTTON!", font, 50);
  text.setFillColor(sf::Color::Red);

  // Create a circle
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  // Main Window Loop
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    window.clear();

    // Draw both Shape and Sprite
    sprite.setPosition(x, y);
    window.draw(shape);
    window.draw(sprite);

    // If spacebar is pressed, display the secret text
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
      text.setPosition(200, 0);
      window.draw(text);
    }
    window.display();

    // Movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      x += 8;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      x -= 8;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      y -= 8;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
      y += 8;
    }
  }
  return 0;
}
