#include "SudokuButton.hpp"

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
    // m_container.setFillColor(sf::Color::Transparent);
    m_container.setOutlineThickness(0);
    m_text.setFillColor(m_setColor);
  }
  if (m_status == "active") {
    m_container.setFillColor(sf::Color(0, 165, 225));
    m_container.setOutlineColor(sf::Color(100, 100, 100));
    m_container.setOutlineThickness(2);
    m_text.setFillColor(m_setColor);
  }
  if (m_status == "untouchable") {
    m_text.setFillColor(sf::Color(0, 0, 85));
    // m_container.setFillColor(sf::Color::Transparent);
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

void SudokuButton::setColor(sf::Color color) {
  m_text.setFillColor(color);
  m_setColor = color;
}

void SudokuButton::setBg(sf::Color bg) { m_container.setFillColor(bg); }

void SudokuButton::setFontSize(int fontSize) {
  m_text.setCharacterSize(fontSize);
}

// ===========================================
// GETTER FUNCTIONS
// ===========================================
std::string SudokuButton::getStatus() { return m_status; }
std::string SudokuButton::getNumber() { return m_text.getString(); }

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
void SudokuButton::Hover(sf::RenderWindow &window) {
  if (IsMouseOver(window)) {
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
}

void SudokuButton::Mistake(bool isCorrect) {
  if (!isCorrect)
    m_text.setFillColor(sf::Color(150, 0, 0));
  else
    setStatus(m_status);
}

void SudokuButton::Highlight() {
  m_container.setFillColor(sf::Color(0, 0, 225, 70));
}
