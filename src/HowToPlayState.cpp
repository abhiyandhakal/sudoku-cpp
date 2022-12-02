#include "HowToPlayState.hpp"

// load stuff
void HowToPlayState::LoadStatic() {
  std::string path = MY_PATH + "assets/images/how-to-play/";

  for (int i = 0; i < 3; i++) {
    m_textures[i].loadFromFile(path + std::to_string(i + 1) + ".png");
    m_sprites[i].setTexture(m_textures[i]);
  }
}

void HowToPlayState::LoadBtns() {
  // load images
  m_backBtn.setImage(MY_PATH + "assets/images/back.png");
  m_forwardBtn.setImage(MY_PATH + "assets/images/forward.png");

  // set position
  m_backBtn.setPosition({42, 19});
  m_forwardBtn.setPosition({508, 19});
}

// constructor
HowToPlayState::HowToPlayState() : m_activeImageNum(0), MY_PATH(PATH) {
  LoadStatic();
  LoadBtns();
}

// setters
void HowToPlayState::setWindow(sf::RenderWindow* window) { m_window = window; }

void HowToPlayState::setActiveState(std::string* activeState) {
  m_activeState = activeState;
}

void HowToPlayState::Update() {
  // hover
  m_backBtn.Hover(*m_window);
  m_forwardBtn.Hover(*m_window);

  // CLICK

  // previous btn
  // preventing activeImageNum = -1 and changing state to main menu
  if (m_activeImageNum == 0)
    m_backBtn.Clicked(*m_window, *m_activeState, MAIN_MENU_ID);
  else {
    // changing active image num
    if (m_backBtn.Clicked(*m_window, *m_activeState)) {
      m_activeImageNum--;
    }
  }

  if (m_activeImageNum < sizeof(m_sprites) / sizeof(*m_sprites) - 1) {
    // forward btn
    if (m_forwardBtn.Clicked(*m_window, *m_activeState)) {
      m_activeImageNum++;
    }
  }
}

void HowToPlayState::Render() {
  m_window->draw(m_sprites[m_activeImageNum]);

  m_backBtn.Render(*m_window);

  if (m_activeImageNum != 2) m_forwardBtn.Render(*m_window);
}
