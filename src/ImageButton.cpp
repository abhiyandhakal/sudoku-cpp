#include "ImageButton.hpp"

ImageButton::ImageButton() : MY_PATH(PATH) {
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

// mouse actions
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

bool ImageButton::IsMouseDown(sf::RenderWindow &window) {
  return IsMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

bool ImageButton::IsMouseUp(sf::RenderWindow &window) {
  return IsMouseOver(window) && !IsMouseDown(window) && m_clickedOnce;
}

// button actions
void ImageButton::Hover(sf::RenderWindow &window) {
  if (IsMouseOver(window)) m_overlay.setFillColor(sf::Color(225, 225, 225, 50));
  if (!IsMouseOver(window)) m_overlay.setFillColor(sf::Color::Transparent);
}

bool ImageButton::Clicked(sf::RenderWindow &window, std::string &activeState,
                          std::string id) {
  if (IsMouseDown(window)) {
    m_clickedOnce = true;
    m_overlay.setFillColor(sf::Color(0, 0, 0, 50));
  }

  if (IsMouseUp(window)) {
    m_clickedOnce = false;

    if (id == EXIT_ID) {
      window.close();
    } else if (id != "") {
      activeState = id;
    }
    return true;
  } else {
    return false;
  }
}
