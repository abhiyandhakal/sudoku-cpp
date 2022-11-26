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
  bool Clicked(sf::RenderWindow &window, std::string &activeState,
               std::string id = "");

 private:
  sf::Text m_text;
  sf::RectangleShape m_container;
  sf::Font m_font;

  // mouse actions
  bool IsMouseOver(sf::RenderWindow &window);  // hover
  bool m_clickedOnce;
  bool IsMouseDown(sf::RenderWindow &window);
  bool IsMouseUp(sf::RenderWindow &window);

  // set value
  sf::Color m_setColor;

  void setContainer();
};

#endif