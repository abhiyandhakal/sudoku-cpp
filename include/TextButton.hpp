#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>

class TextButton {
 public:
  TextButton(std::string myState);

  void Render(sf::RenderWindow &window);

  // setter functions
  void setText(std::string text);
  void setSize(sf::Vector2f size);
  void setPosition(sf::Vector2f position);
  void setFont(std::string fontPath);
  void setColor(sf::Color color);
  void setBg(sf::Color color);
  void setFontSize(int fontSize);

  // button actions
  void Hover(sf::RenderWindow &window, sf::Color color = sf::Color::Black,
             sf::Color bg = sf::Color::Cyan);
  void Clicked(sf::RenderWindow &window, std::string &activeState,
               std::string id);

  // mouse actions (booleans)
  bool IsMouseOver(sf::RenderWindow &window);  // hover
  bool m_clickedOnce;
  bool IsMouseDown(sf::RenderWindow &window);
  bool IsMouseUp(sf::RenderWindow &window);

 private:
  sf::RectangleShape m_container;
  sf::RectangleShape m_middle;
  sf::CircleShape m_left;
  sf::CircleShape m_right;
  sf::Text m_text;
  sf::Font m_font;
  std::string m_myState;

  // set values
  sf::Color m_setColor;
  sf::Color m_setBg;

  // set positions
  void setTextPosition();
  void setShapesPosition();
};

TextButton::TextButton(std::string myState) : m_myState(myState) {
  // set values
  m_setColor = sf::Color(50, 50, 50);
  m_setBg = sf::Color(187, 185, 225);

  // initialize font
  m_font.loadFromFile("assets/fonts/Inter/static/Inter-Bold.ttf");

  // initialize text
  m_text.setString("hello world");
  m_text.setFont(m_font);
  m_text.setFillColor(m_setColor);
  m_text.setCharacterSize(20);

  // initialize container
  m_container.setFillColor(sf::Color::Transparent);

  // initialize left circle
  m_left.setFillColor(m_setBg);

  // initialize middle rectangle
  m_middle.setFillColor(m_setBg);

  // initialize left circle
  m_right.setFillColor(m_setBg);

  // set positions
  setTextPosition();
  setShapesPosition();
}

void TextButton::setTextPosition() {
  float btnPosX = m_container.getPosition().x;
  float btnPosY = m_container.getPosition().y;

  float textPosX = btnPosX + m_container.getGlobalBounds().width / 2 -
                   m_text.getGlobalBounds().width / 2;
  float textPosY = btnPosY + m_container.getGlobalBounds().height / 2 -
                   m_text.getGlobalBounds().height;

  m_text.setPosition(textPosX, textPosY);
}

void TextButton::setShapesPosition() {
  m_left.setPosition(m_container.getPosition());

  m_middle.setPosition(
      {m_container.getPosition().x + m_container.getSize().y / 2,
       m_container.getPosition().y});

  m_right.setPosition({m_container.getPosition().x + m_container.getSize().x -
                           m_container.getSize().y,
                       m_container.getPosition().y});
}

void TextButton::Render(sf::RenderWindow &window) {
  window.draw(m_left);
  window.draw(m_middle);
  window.draw(m_right);
  window.draw(m_container);
  window.draw(m_text);
}

// ===========================================
// SETTER FUNCTIONS
// ===========================================
void TextButton::setText(std::string text) { m_text.setString(text); }

void TextButton::setColor(sf::Color color) {
  m_text.setFillColor(color);

  m_setColor = color;
}

void TextButton::setBg(sf::Color color) {
  m_left.setFillColor(color);
  m_middle.setFillColor(color);
  m_right.setFillColor(color);

  m_setBg = color;
}

void TextButton::setFontSize(int fontSize) {
  m_text.setCharacterSize(fontSize);
}

void TextButton::setSize(sf::Vector2f size) {
  m_container.setSize(size);
  m_left.setRadius(size.y / 2);
  m_middle.setSize({size.x - size.y, size.y});
  m_right.setRadius(size.y / 2);
}

void TextButton::setPosition(sf::Vector2f position) {
  m_container.setPosition(position);
  setTextPosition();
  setShapesPosition();
}

void TextButton::setFont(std::string fontPath) {
  m_font.loadFromFile(fontPath);
}

// ===========================================
// MOUSE ACTIONS (BOOLEANS)
// ===========================================
// is mouse over the button?
bool TextButton::IsMouseOver(sf::RenderWindow &window) {
  float mousePosX = sf::Mouse::getPosition(window).x;
  float mousePosY = sf::Mouse::getPosition(window).y;

  float btnPosX = m_container.getPosition().x;
  float btnPosY = m_container.getPosition().y;

  float btnSizeX = m_container.getSize().x;
  float btnSizeY = m_container.getSize().y;

  bool isHoveringX = mousePosX <= (btnPosX + btnSizeX) && mousePosX >= btnPosX;
  bool isHoveringY = mousePosY <= (btnPosY + btnSizeY) && mousePosY >= btnPosY;

  return isHoveringX && isHoveringY;
}

// ===========================================
// BUTTON ACTIONS
// ===========================================
void TextButton::Hover(sf::RenderWindow &window, sf::Color color,
                       sf::Color bg) {
  if (IsMouseOver(window)) {
    m_text.setFillColor(color);

    m_left.setFillColor(bg);
    m_middle.setFillColor(bg);
    m_right.setFillColor(bg);
  }
  if (!IsMouseOver(window)) {
    m_text.setFillColor(m_setColor);
    m_left.setFillColor(m_setBg);
    m_middle.setFillColor(m_setBg);
    m_right.setFillColor(m_setBg);
  }
}

bool TextButton::IsMouseDown(sf::RenderWindow &window) {
  return IsMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

bool TextButton::IsMouseUp(sf::RenderWindow &window) {
  return IsMouseOver(window) && !IsMouseDown(window) && m_clickedOnce;
}

void TextButton::Clicked(sf::RenderWindow &window, std::string &activeState,
                         std::string id) {
  if (IsMouseDown(window)) {
    m_clickedOnce = true;
  }

  if (IsMouseUp(window)) {
    m_clickedOnce = false;

    if (id == "exit")
      window.close();

    else
      activeState = id;
  }
}

#endif