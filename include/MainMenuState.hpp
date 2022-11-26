#ifndef MAIN_MENU_STATE_HPP
#define MAIN_MENU_STATE_HPP

#include "DEFINITIONS.hpp"
#include "TextButton.hpp"

class MainMenuState {
 private:
  sf::RenderWindow* m_window;
  std::string* m_activeState;

  // =================================
  // IMAGES
  // =================================
  // background
  sf::Texture m_bgTexture;
  sf::Sprite m_bgSprite;

  // logo
  sf::Texture m_logoTexture;
  sf::Sprite m_logoSprite;
  // =================================

  // buttons
  TextButton m_newGameBtn, m_howToPlayBtn, m_highScoreBtn, m_exitBtn;

  // load stuff
  void LoadStatic();
  void LoadBtns();

 public:
  MainMenuState();

  // setters
  void setWindow(sf::RenderWindow* window);
  void setActiveState(std::string* activeState);

  void Update();
  void Render();
};

#endif