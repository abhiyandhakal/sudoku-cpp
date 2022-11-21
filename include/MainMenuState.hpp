#ifndef MAIN_MENU_STATE_HPP
#define MAIN_MENU_STATE_HPP

// #include "DEFINITIONS.hpp"
// #include "TextButton.hpp"
#include "LevelsState.hpp"

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
  TextButton m_newGameBtn{MAIN_MENU_ID}, m_howToPlayBtn{MAIN_MENU_ID},
      m_highScoreBtn{MAIN_MENU_ID}, m_exitBtn{MAIN_MENU_ID};

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

// ===========================================
// CONSTRUCTORS
// ===========================================
MainMenuState::MainMenuState() {
  LoadStatic();
  LoadBtns();
}
// ===========================================

// ===========================================
// SETTER FUNCTIONS
// ===========================================
void MainMenuState::setWindow(sf::RenderWindow* window) { m_window = window; }

void MainMenuState::setActiveState(std::string* activeState) {
  m_activeState = activeState;
}

// ===========================================
// LOAD STUFFS
// ===========================================
// images
void MainMenuState::LoadStatic() {
  // load textures
  m_bgTexture.loadFromFile("assets/images/background.png");
  m_logoTexture.loadFromFile("assets/images/logo.png");

  // sprites
  m_bgSprite.setTexture(m_bgTexture);
  m_logoSprite.setTexture(m_logoTexture);

  // set position
  m_logoSprite.setPosition({96, 67});
}

void MainMenuState::LoadBtns() {
  // new game button
  m_newGameBtn.setText("NEW GAME");
  m_newGameBtn.setSize({160, 64});
  m_newGameBtn.setPosition({220, 264});

  // how to play button
  m_howToPlayBtn.setText("HOW TO PLAY");
  m_howToPlayBtn.setSize({190, 64});
  m_howToPlayBtn.setPosition({204, 344});

  // high score button
  m_highScoreBtn.setText("HIGH SCORE");
  m_highScoreBtn.setSize({190, 64});
  m_highScoreBtn.setPosition({204, 424});

  // exit button
  m_exitBtn.setText("EXIT");
  m_exitBtn.setSize({89, 64});
  m_exitBtn.setPosition({255, 504});
}
// ===========================================

void MainMenuState::Update() {
  // hovering the buttons
  m_newGameBtn.Hover(*m_window);
  m_howToPlayBtn.Hover(*m_window);
  m_highScoreBtn.Hover(*m_window);
  m_exitBtn.Hover(*m_window);

  // clicking the buttons
  m_newGameBtn.Clicked(*m_window, *m_activeState, LEVELS_ID);
  m_howToPlayBtn.Clicked(*m_window, *m_activeState, HOW_TO_PLAY_ID);
  m_highScoreBtn.Clicked(*m_window, *m_activeState, HIGH_SCORE_ID);
  m_exitBtn.Clicked(*m_window, *m_activeState, EXIT_ID);
}

void MainMenuState::Render() {
  m_window->clear();

  m_window->draw(m_bgSprite);
  m_window->draw(m_logoSprite);

  // render buttons
  m_newGameBtn.Render(*m_window);
  m_howToPlayBtn.Render(*m_window);
  m_highScoreBtn.Render(*m_window);
  m_exitBtn.Render(*m_window);

  m_window->display();
}

#endif