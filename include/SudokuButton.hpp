#ifndef SUDOKU_BUTTON_HPP
#define SUDOKU_BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <cstring>

class SudokuButton {
 public:
  SudokuButton();

  void Render(sf::RenderWindow &window);

  // setter functions
  void setNumber(int num);
  void setSize(sf::Vector2f size);
  void setPosition(sf::Vector2f position);
  void setFont(std::string fontPath);
  void setColor(sf::Color color);
  void setFontSize(int fontSize);
  void setStatus(std::string status);
  void setTextPosition();

  // button actions
  void Hover(sf::RenderWindow &window, sf::Color color = sf::Color::Black);
  bool Clicked(sf::RenderWindow &window);

 private:
  sf::RectangleShape m_container;
  sf::RectangleShape m_overlay;
  sf::Text m_text;
  std::string m_status;
  sf::Font m_font;

  // mouse actions (booleans)
  bool IsMouseOver(sf::RenderWindow &window);  // hover
  bool m_clickedOnce;
  bool IsMouseDown(sf::RenderWindow &window);
  bool IsMouseUp(sf::RenderWindow &window);

  // set values
  sf::Color m_setColor;
  int m_setNum;

  // set stuffs
  void setText();
};

SudokuButton::SudokuButton() : m_status("not-active") {
  m_setColor = sf::Color::Black;
  m_setNum = 0;

  // load font
  m_font.loadFromFile("assets/fonts/Inter/static/Inter-Bold.ttf");

  // load overlay
  m_overlay.setFillColor(sf::Color::Transparent);

  // load container
  m_container.setFillColor(sf::Color::Transparent);

  // load text
  setText();
  m_text.setFont(m_font);
  m_text.setFillColor(m_setColor);
  m_text.setCharacterSize(30);

  setTextPosition();
}

void SudokuButton::setText() {
  if (m_setNum == 0)
    m_text.setString("");
  else
    m_text.setString(std::to_string(m_setNum));
}

void SudokuButton::setTextPosition() {
  float btnPosX = m_container.getPosition().x;
  float btnPosY = m_container.getPosition().y;

  float textPosX = btnPosX + m_container.getGlobalBounds().width / 2 -
                   m_text.getGlobalBounds().width / 2;
  float textPosY = btnPosY + m_container.getGlobalBounds().height / 2 -
                   m_text.getGlobalBounds().height;

  m_text.setPosition(textPosX, textPosY);
}

void SudokuButton::Render(sf::RenderWindow &window) {
  window.draw(m_container);
  window.draw(m_text);
  window.draw(m_overlay);
}

// ===========================================
// SETTER FUNCTIONS
// ===========================================
void SudokuButton::setStatus(std::string status) {
  m_status = status;
  if (m_status == "not-active") {
    m_container.setFillColor(sf::Color::Transparent);
    m_container.setOutlineThickness(0);
  } else if (m_status == "active") {
    m_container.setFillColor(sf::Color(0, 165, 225));
    m_container.setOutlineColor(sf::Color(100, 100, 100));
    m_container.setOutlineThickness(2);
  } else if (m_status == "semi-active") {
    m_container.setFillColor(sf::Color(0, 0, 225, 70));
    m_container.setOutlineThickness(1);
  }
}

void SudokuButton::setNumber(int num) {
  m_setNum = num;
  setText();
}

void SudokuButton::setSize(sf::Vector2f size) {
  m_container.setSize(size);
  m_overlay.setSize(size);
}

void SudokuButton::setPosition(sf::Vector2f position) {
  m_container.setPosition(position);
  m_overlay.setPosition(position);
  setTextPosition();
}

void SudokuButton::setFont(std::string fontPath) {
  m_font.loadFromFile(fontPath);
}

void SudokuButton::setColor(sf::Color color) { m_text.setFillColor(color); }

void SudokuButton::setFontSize(int fontSize) {
  m_text.setCharacterSize(fontSize);
}

// ===========================================
// MOUSE ACTIONS (BOOLEANS)
// ===========================================
// is mouse over the button?
bool SudokuButton::IsMouseOver(sf::RenderWindow &window) {
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

bool SudokuButton::IsMouseDown(sf::RenderWindow &window) {
  return IsMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

bool SudokuButton::IsMouseUp(sf::RenderWindow &window) {
  return IsMouseOver(window) && !IsMouseDown(window) && m_clickedOnce;
}

// ===========================================
// BUTTON ACTIONS
// ===========================================
void SudokuButton::Hover(sf::RenderWindow &window, sf::Color color) {
  if (IsMouseOver(window)) {
    m_text.setFillColor(color);
    m_overlay.setFillColor(sf::Color(0, 0, 0, 50));
  }
  if (!IsMouseOver(window)) {
    m_overlay.setFillColor(sf::Color::Transparent);
  }
}

bool SudokuButton::Clicked(sf::RenderWindow &window) {
  if (IsMouseDown(window)) {
    // m_clickedOnce = true;
    return true;
  } else
    return false;

  // if (IsMouseUp(window)) {
  //   m_clickedOnce = false;

  // } else {
  //   return false;
  // }
}

#endif