#ifndef PAUSE_STATE_HPP
#define PAUSE_STATE_HPP

#include "Stopwatch.hpp"
#include "TextButton.hpp"

class PauseState {
 private:
  sf::RenderWindow* m_window;
  std::string* m_activeState;

  std::string MY_PATH;

  // font
  sf::Font m_font;

  // stopwatch
  Stopwatch& m_stopwatch;

  // image
  sf::Texture m_bgTexture;
  sf::Sprite m_bgSprite;

  // text
  sf::Text m_title;

  // buttons
  TextButton m_resumeBtn, m_quitBtn;

  // load stuff
  void LoadStatic();
  void LoadBtns();

 public:
  PauseState(Stopwatch& stopwatch);

  // setters
  void setWindow(sf::RenderWindow* window);
  void setActiveState(std::string* activeState);

  void Update();
  void Render();
};

#endif