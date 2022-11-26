#include "WinState.hpp"

// ===========================================
// CONSTRUCTOR
// ===========================================
WinState::WinState() : m_highscoreTime("00:00"), m_elapsedTime("00:00") {
  LoadStatic();
  LoadBtns();
}
// ===========================================

// ===========================================
// SETTER FUNCTIONS
// ===========================================
void WinState::setWindow(sf::RenderWindow* window) { m_window = window; }

void WinState::setActiveState(std::string* activeState) {
  m_activeState = activeState;
}

void WinState::setElapsedTime(std::string time) { m_elapsedTime = time; }

// ===========================================
// LOAD STUFFS
// ===========================================
// images
void WinState::LoadStatic() {
  // IMAGES
  // background image
  m_bgTexture.loadFromFile("assets/images/background.png");
  m_bgSprite.setTexture(m_bgTexture);

  // congrats image
  m_congratsTexture.loadFromFile("assets/images/congrats.png");
  m_congratsSprite.setTexture(m_congratsTexture);
  m_congratsSprite.setPosition({80, 120});

  // font
  m_font.loadFromFile("assets/fonts/Inter/static/Inter-Bold.ttf");

  // TEXT
  // you won text
  m_winText.setString("You Won !!!");
  m_winText.setFont(m_font);
  m_winText.setFillColor(sf::Color(6, 17, 75));
  m_winText.setCharacterSize(32);
  m_winText.setPosition({203, 223});

  // elapsed time static
  m_timeTextStatic.setString("Elapsed Time:");
  m_timeTextStatic.setFont(m_font);
  m_timeTextStatic.setFillColor(sf::Color(0, 0, 0));
  m_timeTextStatic.setCharacterSize(24);
  m_timeTextStatic.setPosition({154, 296});

  // elapsed time dynamic
  m_timeTextDynamic.setString(m_elapsedTime);
  m_timeTextDynamic.setFont(m_font);
  m_timeTextDynamic.setFillColor(sf::Color(151, 64, 64));
  m_timeTextDynamic.setCharacterSize(32);
  m_timeTextDynamic.setPosition({340, 290});

  // highscore time static
  m_highScoreTextStatic.setString("Shortest Time:");
  m_highScoreTextStatic.setFont(m_font);
  m_highScoreTextStatic.setFillColor(sf::Color(0, 0, 0));
  m_highScoreTextStatic.setCharacterSize(24);
  m_highScoreTextStatic.setPosition({150, 335});

  // highscore time dynamic
  m_highScoreTextDynamic.setString("00:00");
  m_highScoreTextDynamic.setFont(m_font);
  m_highScoreTextDynamic.setFillColor(sf::Color(100, 64, 64));
  m_highScoreTextDynamic.setCharacterSize(32);
  m_highScoreTextDynamic.setPosition({340, 330});
}

void WinState::LoadBtns() {
  // back to home button
  m_returnToHomeBtn.setImage("assets/images/home-icon.png");
  m_returnToHomeBtn.setPosition({265, 425});
}
// ===========================================

void WinState::Update() {
  m_timeTextDynamic.setString(m_elapsedTime);

  // hovering the buttons
  m_returnToHomeBtn.Hover(*m_window);

  // clicking the buttons
  m_returnToHomeBtn.Clicked(*m_window, *m_activeState, MAIN_MENU_ID);
}

void WinState::Render() {
  // images
  m_window->draw(m_bgSprite);
  m_window->draw(m_congratsSprite);

  // text
  m_window->draw(m_winText);
  m_window->draw(m_timeTextStatic);
  m_window->draw(m_timeTextDynamic);
  m_window->draw(m_highScoreTextStatic);
  m_window->draw(m_highScoreTextDynamic);

  // render buttons
  m_returnToHomeBtn.Render(*m_window);
}
