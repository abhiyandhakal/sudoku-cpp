#include "TextButton.hpp"

TextButton::TextButton() : MY_PATH(PATH) {
  // set values
  m_setColor = sf::Color(50, 50, 50);
  m_setBg = sf::Color(187, 185, 225);

  // initialize font
  m_font.loadFromFile(MY_PATH + "assets/fonts/Inter/static/Inter-Bold.ttf");

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

bool TextButton::IsMouseDown(sf::RenderWindow &window) {
  return IsMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

bool TextButton::IsMouseUp(sf::RenderWindow &window) {
  return IsMouseOver(window) && !IsMouseDown(window) && m_clickedOnce;
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

bool TextButton::Clicked(sf::RenderWindow &window, std::string &activeState,
                         std::string id) {
  if (IsMouseDown(window)) {
    m_clickedOnce = true;
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
