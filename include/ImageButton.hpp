#ifndef IMAGE_BUTTON_HPP
#define IMAGE_BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class ImageButton {
 public:
  ImageButton(std::string myState);

  void Render(sf::RenderWindow &window);

  // setter functions
  void setImage(std::string imagePath);
  void setPosition(sf::Vector2f position);

  // mouse actions
  void Hover(sf::RenderWindow &window);
  void Clicked(sf::RenderWindow &window, std::string &activeState,
               std::string id);

 private:
  sf::RectangleShape m_overlay;
  // image
  sf::Texture m_texture;
  sf::Sprite m_sprite;
  std::string m_myState;

  // mouse actions (boolean)
  bool IsMouseOver(sf::RenderWindow &window);

  void setOverlay();
};

ImageButton::ImageButton(std::string myState) : m_myState(myState) {
  m_overlay.setFillColor(sf::Color::Transparent);
}

void ImageButton::setOverlay() {
  float sizeX = m_sprite.getGlobalBounds().width;
  float sizeY = m_sprite.getGlobalBounds().height;

  m_overlay.setSize({sizeX, sizeY});
  m_overlay.setPosition(m_sprite.getPosition());
}

void ImageButton::setImage(std::string imagePath) {
  m_texture.loadFromFile(imagePath);
  m_sprite.setTexture(m_texture);
}

void ImageButton::setPosition(sf::Vector2f position) {
  m_sprite.setPosition(position);
  setOverlay();
}

void ImageButton::Render(sf::RenderWindow &window) {
  window.draw(m_sprite);
  window.draw(m_overlay);
}

bool ImageButton::IsMouseOver(sf::RenderWindow &window) {
  float mousePosX = sf::Mouse::getPosition(window).x;
  float mousePosY = sf::Mouse::getPosition(window).y;

  float btnPosX = m_overlay.getPosition().x;
  float btnPosY = m_overlay.getPosition().y;

  float btnSizeX = m_overlay.getSize().x;
  float btnSizeY = m_overlay.getSize().y;

  bool isHoveringX = mousePosX <= (btnPosX + btnSizeX) && mousePosX >= btnPosX;
  bool isHoveringY = mousePosY <= (btnPosY + btnSizeY) && mousePosY >= btnPosY;

  return isHoveringX && isHoveringY;
}

void ImageButton::Hover(sf::RenderWindow &window) {
  if (IsMouseOver(window)) m_overlay.setFillColor(sf::Color(0, 0, 0, 50));
  if (!IsMouseOver(window)) m_overlay.setFillColor(sf::Color::Transparent);
}

void ImageButton::Clicked(sf::RenderWindow &window, std::string &activeState,
                          std::string id) {
  if (IsMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    if (id == "exit")
      window.close();

    else
      activeState = id;
  }
}

#endif