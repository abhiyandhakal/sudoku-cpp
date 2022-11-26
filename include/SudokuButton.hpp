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
  void setBg(sf::Color bg);
  void setFontSize(int fontSize);
  void setStatus(std::string status);
  void setTextPosition();

  // getter function
  std::string getStatus();
  std::string getNumber();

  // button actions
  void Hover(sf::RenderWindow &window);
  bool Clicked(sf::RenderWindow &window);
  void Mistake(bool isCorrect);
  void Highlight();

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

#endif