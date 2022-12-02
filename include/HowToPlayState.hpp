#ifndef HOW_TO_PLAY_STATE
#define HOW_TO_PLAY_STATE

#include "ImageButton.hpp"

class HowToPlayState {
 private:
  sf::RenderWindow* m_window;
  std::string* m_activeState;
  int m_activeImageNum;

  std::string MY_PATH;

  // images
  sf::Texture m_textures[3];
  sf::Sprite m_sprites[3];

  // buttons
  ImageButton m_backBtn, m_forwardBtn;

  // load stuff
  void LoadStatic();
  void LoadBtns();

 public:
  HowToPlayState();

  // setters
  void setWindow(sf::RenderWindow* window);
  void setActiveState(std::string* activeState);

  void Update();
  void Render();
};

#endif