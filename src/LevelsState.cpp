#include "LevelsState.hpp"

// constructor
LevelsState::LevelsState() {
  LoadStatic();
  LoadBtns();
}

// setter functions
void LevelsState::setWindow(sf::RenderWindow* window) { m_window = window; }

void LevelsState::setActiveState(std::string* activeState) {
  m_activeState = activeState;
}

// ===========================================
// LOAD STUFFS
// ===========================================
// static
void LevelsState::LoadStatic() {
  // background image
  m_bgTexture.loadFromFile("assets/images/background.png");
  m_bgSprite.setTexture(m_bgTexture);

  // font
  m_font.loadFromFile("assets/fonts/Inter/static/Inter-Bold.ttf");

  // text
  m_title.setString("Difficulty Level");
  m_title.setFont(m_font);
  m_title.setFillColor(sf::Color::Black);
  m_title.setCharacterSize(48);
  m_title.setPosition({106, 125});
}

void LevelsState::LoadBtns() {
  // back button
  m_backBtn.setImage("assets/images/back.png");
  m_backBtn.setPosition({54, 20});

  // easy button
  m_easyBtn.setText("EASY");
  m_easyBtn.setSize({98, 64});
  m_easyBtn.setPosition({249, 240});

  // medium button
  m_mediumBtn.setText("MEDIUM");
  m_mediumBtn.setSize({129, 64});
  m_mediumBtn.setPosition({235, 326});

  // hard button
  m_hardBtn.setText("HARD");
  m_hardBtn.setSize({101, 64});
  m_hardBtn.setPosition({246, 414});

  // expert button
  m_expertBtn.setText("EXPERT");
  m_expertBtn.setSize({124, 64});
  m_expertBtn.setPosition({235, 502});
}

void LevelsState::Update(GameState& gameState, WinState& winState,
                         LoseState& loseState) {
  // hovering the buttons
  m_backBtn.Hover(*m_window);
  m_easyBtn.Hover(*m_window);
  m_mediumBtn.Hover(*m_window);
  m_hardBtn.Hover(*m_window);
  m_expertBtn.Hover(*m_window);

  // clicking the buttons
  m_backBtn.Clicked(*m_window, *m_activeState, MAIN_MENU_ID);

  // levels buttons
  if (m_easyBtn.Clicked(*m_window, *m_activeState, GAME_ID)) {
    gameState.setLevel("Easy");
    winState.setLevel("Easy");
    loseState.setLevel("Easy");
  }
  if (m_mediumBtn.Clicked(*m_window, *m_activeState, GAME_ID)) {
    gameState.setLevel("Medium");
    winState.setLevel("Medium");
    loseState.setLevel("Medium");
  }
  if (m_hardBtn.Clicked(*m_window, *m_activeState, GAME_ID)) {
    gameState.setLevel("Hard");
    winState.setLevel("Hard");
    loseState.setLevel("Hard");
  }
  if (m_expertBtn.Clicked(*m_window, *m_activeState, GAME_ID)) {
    gameState.setLevel("Expert");
    winState.setLevel("Expert");
    loseState.setLevel("Hard");
  }
}

void LevelsState::Render() {
  m_window->draw(m_bgSprite);
  m_window->draw(m_title);

  // render buttons
  m_backBtn.Render(*m_window);
  m_easyBtn.Render(*m_window);
  m_mediumBtn.Render(*m_window);
  m_hardBtn.Render(*m_window);
  m_expertBtn.Render(*m_window);
}
