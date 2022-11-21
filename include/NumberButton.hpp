#ifndef NUMBER_BUTTON_HPP
#define NUMBER_BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class NumberButton {
 public:
  NumberButton();

  void Render(sf::RenderWindow &window);

  // setter functions
  void setNumber(std::string number);
  void setFontSize(int fontSize);
  void setColor(sf::Color color);
  void setFont(std::string fontPath);
  void setPosition(sf::Vector2f position);

  // button actions
  void Hover(sf::RenderWindow &window, sf::Color color = sf::Color::Black);
  void Clicked(sf::RenderWindow &window, std::string &activeState,
               std::string id);

 private:
  sf::Text m_text;
  sf::Font m_font;

  // mouse actions
  bool IsMouseOver(sf::RenderWindow &window);  // hover
  bool m_clickedOnce;
  bool IsMouseDown(sf::RenderWindow &window);
  bool IsMouseUp(sf::RenderWindow &window);

  // set value
  sf::Color m_setColor;
};

NumberButton::NumberButton() {
  // set value
  m_setColor = sf::Color(0, 0, 85);

  // load font
  m_font.loadFromFile("assets/fonts/Nerko_One/NerkoOne-Regular.ttf");

  // load text
  m_text.setString("0");
  m_text.setFont(m_font);
  m_text.setFillColor(m_setColor);
  m_text.setCharacterSize(88);
}

void NumberButton::Render(sf::RenderWindow &window) { window.draw(m_text); }

// ===========================================
// SETTER FUNCTIONS
// ===========================================
void NumberButton::setNumber(std::string number) { m_text.setString(number); }

void NumberButton::setFontSize(int fontSize) {
  m_text.setCharacterSize(fontSize);
}

void NumberButton::setColor(sf::Color color) {
  m_text.setFillColor(color);
  m_setColor = color;
}

void NumberButton::setFont(std::string fontPath) {
  m_font.loadFromFile(fontPath);
  m_text.setFont(m_font);
}

void NumberButton::setPosition(sf::Vector2f position) {
  m_text.setPosition(position);
}

// ===========================================
// MOUSE ACTIONS
// ===========================================
bool NumberButton::IsMouseOver(sf::RenderWindow &window) {
  float mousePosX = sf::Mouse::getPosition(window).x;
  float mousePosY = sf::Mouse::getPosition(window).y;

  float btnPosX = m_text.getPosition().x;
  float btnPosY = m_text.getPosition().y;

  float btnSizeX = m_text.getGlobalBounds().width;
  float btnSizeY = m_text.getGlobalBounds().height;

  bool isHoveringX = mousePosX <= (btnPosX + btnSizeX) && mousePosX >= btnPosX;
  bool isHoveringY = mousePosY <= (btnPosY + btnSizeY) && mousePosY >= btnPosY;

  return isHoveringX && isHoveringY;
}

bool NumberButton::IsMouseDown(sf::RenderWindow &window) {
  return IsMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

bool NumberButton::IsMouseUp(sf::RenderWindow &window) {
  return IsMouseOver(window) && !IsMouseDown(window) && m_clickedOnce;
}

// ===========================================
// BUTTON ACTIONS
// ===========================================
void NumberButton::Hover(sf::RenderWindow &window, sf::Color color) {
  if (IsMouseOver(window)) {
    m_text.setFillColor(color);
  }
  if (!IsMouseOver(window)) {
    m_text.setFillColor(m_setColor);
  }
}

void NumberButton::Clicked(sf::RenderWindow &window, std::string &activeState,
                           std::string id) {
  if (IsMouseDown(window)) {
    m_clickedOnce = true;
  }

  if (IsMouseUp(window)) {
    m_clickedOnce = false;

    m_text.setFillColor(sf::Color(0, 0, 0, 150));
  }
}

#endif