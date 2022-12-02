#ifndef LEVELS_HPP
#define LEVELS_HPP

#include "GameState.hpp"
#include "ImageButton.hpp"
#include "TextButton.hpp"

class LevelsState {
 private:
  sf::RenderWindow* m_window;
  std::string* m_activeState;

  std::string MY_PATH;

  sf::Font m_font;

  // image
  sf::Texture m_bgTexture;
  sf::Sprite m_bgSprite;

  // text
  sf::Text m_title;

  // buttons
  ImageButton m_backBtn;
  TextButton m_easyBtn, m_mediumBtn, m_hardBtn, m_expertBtn;

  // load stuff
  void LoadStatic();
  void LoadBtns();

 public:
  LevelsState();

  // setters
  void setWindow(sf::RenderWindow* window);
  void setActiveState(std::string* activeState);

  void Update(GameState& gameState, WinState& winState, LoseState& LoseState);
  void Render();
};

#endif