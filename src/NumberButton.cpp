#include "NumberButton.hpp"

NumberButton::NumberButton() : MY_PATH(PATH) {
  // set value
  m_setColor = sf::Color(0, 0, 85);

  // load font
  m_font.loadFromFile(MY_PATH + "assets/fonts/Nerko_One/NerkoOne-Regular.ttf");

  // load text
  m_text.setString("0");
  m_text.setFont(m_font);
  m_text.setFillColor(m_setColor);
  m_text.setCharacterSize(88);

  // load container
  setContainer();
}

void NumberButton::setContainer() {
  m_container.setFillColor(sf::Color::Transparent);
  m_container.setSize({m_text.getGlobalBounds().width + 10,
                       m_text.getGlobalBounds().height + 10});
  m_container.setPosition(
      {m_text.getPosition().x - 5, m_text.getPosition().y + 5});
}

void NumberButton::Render(sf::RenderWindow &window) {
  window.draw(m_text);
  window.draw(m_container);
}

// ===========================================
// SETTER FUNCTIONS
// ===========================================
void NumberButton::setNumber(std::string number) { m_text.setString(number); }

void NumberButton::setFontSize(int fontSize) {
  m_text.setCharacterSize(fontSize);
  setContainer();
}

void NumberButton::setColor(sf::Color color) {
  m_text.setFillColor(color);
  m_setColor = color;
}

void NumberButton::setFont(std::string fontPath) {
  m_font.loadFromFile(fontPath);
  m_text.setFont(m_font);
  setContainer();
}

void NumberButton::setPosition(sf::Vector2f position) {
  m_text.setPosition(position);
  setContainer();
}

// ===========================================
// MOUSE ACTIONS
// ===========================================
bool NumberButton::IsMouseOver(sf::RenderWindow &window) {
  float mousePosX = sf::Mouse::getPosition(window).x;
  float mousePosY = sf::Mouse::getPosition(window).y;

  float btnPosX = m_container.getPosition().x;
  float btnPosY = m_container.getPosition().y;

  float btnSizeX = m_container.getGlobalBounds().width;
  float btnSizeY = m_container.getGlobalBounds().height;

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

bool NumberButton::Clicked(sf::RenderWindow &window, std::string &activeState,
                           std::string id) {
  if (IsMouseDown(window)) {
    m_clickedOnce = true;
    m_text.setFillColor(sf::Color(0, 0, 0, 150));
  }

  if (IsMouseUp(window)) {
    m_clickedOnce = false;

    return true;
  } else {
    return false;
  }
}
