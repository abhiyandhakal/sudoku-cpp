#ifndef LOSE_STATE_HPP
#define LOSE_STATE_HPP

#include "DEFINITIONS.hpp"
#include "ImageButton.hpp"
#include "TextButton.hpp"

class LoseState {
 private:
  sf::RenderWindow* m_window;
  std::string* m_activeState;
  std::string m_level;

  // fonts
  sf::Font m_font1;
  sf::Font m_font2;

  // =================================
  // IMAGES
  // =================================
  // background
  sf::Texture m_bgTexture;
  sf::Sprite m_bgSprite;

  // you lose
  sf::Texture m_lostTexture;
  sf::Sprite m_lostSprite;
  // =================================

  // text
  sf::Text m_loseText;
  sf::Text m_levelTextStatic;
  sf::Text m_levelTextDynamic;

  // buttons
  ImageButton m_homeBtn, m_testBtn;

  // load stuff
  void LoadStatic();
  void LoadBtns();

 public:
  LoseState();

  // setters
  void setWindow(sf::RenderWindow* window);
  void setActiveState(std::string* activeState);
  void setLevel(std::string level);

  void Update();
  void Render();
};

#endif