#ifndef IMAGE_BUTTON_HPP
#define IMAGE_BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class ImageButton {
 public:
  ImageButton();

  void Render(sf::RenderWindow &window);

  // setter functions
  void setImage(std::string imagePath);
  void setPosition(sf::Vector2f position);

  // button actions
  void Hover(sf::RenderWindow &window);
  bool Clicked(sf::RenderWindow &window, std::string &activeState,
               std::string id = "");

 private:
  sf::RectangleShape m_overlay;
  // image
  sf::Texture m_texture;
  sf::Sprite m_sprite;

  // mouse actions (boolean)
  bool IsMouseOver(sf::RenderWindow &window);
  bool IsMouseDown(sf::RenderWindow &window);
  bool IsMouseUp(sf::RenderWindow &window);
  bool m_clickedOnce;

  void setOverlay();
};

#endif