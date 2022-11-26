#ifndef WIN_STATE_HPP
#define WIN_STATE_HPP

#include <fstream>
#include <sstream>

#include "DEFINITIONS.hpp"
#include "ImageButton.hpp"

class WinState {
 private:
  sf::RenderWindow* m_window;
  std::string* m_activeState;
  std::string m_level;

  // fonts
  sf::Font m_font1;
  sf::Font m_font2;

  // time
  std::string m_elapsedTime;
  std::string m_highscoreTime;

  void setHighscoreTime();

  // =================================
  // IMAGES
  // =================================
  // background
  sf::Texture m_bgTexture;
  sf::Sprite m_bgSprite;

  // CONGRATS
  sf::Texture m_congratsTexture;
  sf::Sprite m_congratsSprite;
  // =================================

  // text
  sf::Text m_winText;
  sf::Text m_timeTextStatic;
  sf::Text m_timeTextDynamic;
  sf::Text m_highScoreTextStatic;
  sf::Text m_highScoreTextDynamic;
  sf::Text m_levelTextStatic;
  sf::Text m_levelTextDynamic;

  // buttons
  ImageButton m_returnToHomeBtn;
  ImageButton m_testBtn;

  // load stuff
  void LoadStatic();
  void LoadBtns();

 public:
  WinState();

  // setters
  void setWindow(sf::RenderWindow* window);
  void setActiveState(std::string* activeState);
  void setElapsedTime(std::string time);
  void setLevel(std::string level);

  void Update();
  void Render();
};

#endif