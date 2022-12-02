#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>

#include "DEFINITIONS.hpp"

class TextButton {
 public:
  TextButton();

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
  bool Clicked(sf::RenderWindow &window, std::string &activeState,
               std::string id = "");

 private:
  sf::RectangleShape m_container;
  sf::RectangleShape m_middle;
  sf::CircleShape m_left;
  sf::CircleShape m_right;
  sf::Text m_text;
  sf::Font m_font;

  std::string MY_PATH;

  // mouse actions (booleans)
  bool IsMouseOver(sf::RenderWindow &window);  // hover
  bool m_clickedOnce;
  bool IsMouseDown(sf::RenderWindow &window);
  bool IsMouseUp(sf::RenderWindow &window);

  // set values
  sf::Color m_setColor;
  sf::Color m_setBg;

  // set positions
  void setTextPosition();
  void setShapesPosition();
};

#endif