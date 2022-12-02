#include "PauseState.hpp"

// constructor
PauseState::PauseState(Stopwatch& stopwatch)
    : m_stopwatch(stopwatch), MY_PATH(PATH) {
  LoadStatic();
  LoadBtns();
}

// setter functions
void PauseState::setWindow(sf::RenderWindow* window) { m_window = window; }

void PauseState::setActiveState(std::string* activeState) {
  m_activeState = activeState;
}

// ===========================================
// LOAD STUFFS
// ===========================================
void PauseState::LoadStatic() {
  // background image
  m_bgTexture.loadFromFile(MY_PATH + "assets/images/background.png");
  m_bgSprite.setTexture(m_bgTexture);

  // font
  m_font.loadFromFile(MY_PATH + "assets/fonts/Inter/static/Inter-Bold.ttf");

  // text
  m_title.setString("Paused");
  m_title.setFont(m_font);
  m_title.setFillColor(sf::Color::Black);
  m_title.setCharacterSize(48);
  m_title.setPosition({207, 170});
}

void PauseState::LoadBtns() {
  // resume button
  m_resumeBtn.setText("RESUME");
  m_resumeBtn.setSize({129, 64});
  m_resumeBtn.setPosition({235, 291});

  // quit button
  m_quitBtn.setText("QUIT");
  m_quitBtn.setSize({93, 64});
  m_quitBtn.setPosition({253, 376});
}

void PauseState::Update() {
  // hovering the buttons
  m_resumeBtn.Hover(*m_window);
  m_quitBtn.Hover(*m_window);

  // clicking the buttons
  if (m_resumeBtn.Clicked(*m_window, *m_activeState, GAME_ID)) {
    m_stopwatch.Resume();
  }
  if (m_quitBtn.Clicked(*m_window, *m_activeState, MAIN_MENU_ID)) {
    m_stopwatch.Reset();
    m_stopwatch.Pause();
  }
}

void PauseState::Render() {
  m_window->draw(m_bgSprite);
  m_window->draw(m_title);

  // render buttons
  m_resumeBtn.Render(*m_window);
  m_quitBtn.Render(*m_window);
}