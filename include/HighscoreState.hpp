#ifndef HIGHSCORE_STATE_HPP
#define HIGHSCORE_STATE_HPP

#include "DEFINITIONS.hpp"
#include "ImageButton.hpp"
#include "fstream"

class HighScoreState {
 private:
  sf::RenderWindow* m_window;
  std::string *m_activeState, m_highscore[4];

  sf::Font m_font, m_fontBold;

  // shapes
  sf::RectangleShape m_line;

  // IMAGES
  // background image
  sf::Texture m_bgTexture;
  sf::Sprite m_bgSprite;

  // title caption
  sf::Texture m_captionTexture;
  sf::Sprite m_captionSprite;

  // buttons
  ImageButton m_backBtn, m_resetBtns[4];

  // text
  sf::Text m_title, m_levelsTextStatic, m_levelsText[4], m_highscoreText[4],
      m_highscoreTextStatic;

  // load stuff
  void LoadStatic();
  void LoadBtns();

  // file handling
  std::string ReadScore(std::string file);
  void ResetScore(std::string file);

 public:
  HighScoreState();

  // setters
  void setWindow(sf::RenderWindow* window);
  void setActiveState(std::string* activeState);

  void Update();
  void Render();
};

#endif