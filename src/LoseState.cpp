#include "LoseState.hpp"

// ===========================================
// CONSTRUCTORS
// ===========================================
LoseState::LoseState() : MY_PATH(PATH) {
  LoadStatic();
  LoadBtns();
}
// ===========================================

// ===========================================
// SETTER FUNCTIONS
// ===========================================
void LoseState::setWindow(sf::RenderWindow* window) { m_window = window; }

void LoseState::setActiveState(std::string* activeState) {
  m_activeState = activeState;
}

void LoseState::setLevel(std::string level) { m_level = level; }

// ===========================================
// LOAD STUFFS
// ===========================================
// images
void LoseState::LoadStatic() {
  // IMAGES
  // load textures
  m_bgTexture.loadFromFile(MY_PATH + "assets/images/background.png");
  m_lostTexture.loadFromFile(MY_PATH + "assets/images/lost.png");

  // sprites
  m_bgSprite.setTexture(m_bgTexture);
  m_lostSprite.setTexture(m_lostTexture);

  // set position
  m_lostSprite.setPosition({115, 148});

  // fonts
  m_font1.loadFromFile(MY_PATH + "assets/fonts/Inter/static/Inter-Bold.ttf");
  m_font2.loadFromFile(MY_PATH + "assets/fonts/Nerko_One/NerkoOne-Regular.ttf");

  // TEXT
  // better luck next time text
  m_loseText.setString("Better Luck Next Time!");
  m_loseText.setFont(m_font1);
  m_loseText.setFillColor(sf::Color(6, 17, 75));
  m_loseText.setCharacterSize(32);
  m_loseText.setPosition({104, 258});

  // level static
  m_levelTextStatic.setString("Level");
  m_levelTextStatic.setFont(m_font2);
  m_levelTextStatic.setFillColor(sf::Color(0, 0, 0));
  m_levelTextStatic.setCharacterSize(24);
  m_levelTextStatic.setPosition({239, 321});

  // level dynamic
  m_levelTextDynamic.setString(m_level);
  m_levelTextDynamic.setFont(m_font2);
  m_levelTextDynamic.setFillColor(sf::Color(100, 64, 64));
  m_levelTextDynamic.setCharacterSize(24);
  m_levelTextDynamic.setPosition({311, 321});
}

void LoseState::LoadBtns() {
  // back to home button
  m_homeBtn.setImage(MY_PATH + "assets/images/home-icon.png");
  m_homeBtn.setPosition({265, 422});
}
// ===========================================

void LoseState::Update() {
  // dynamic text
  m_levelTextDynamic.setString(m_level);

  // hovering the buttons
  m_homeBtn.Hover(*m_window);

  // clicking the buttons
  m_homeBtn.Clicked(*m_window, *m_activeState, MAIN_MENU_ID);
}

void LoseState::Render() {
  // images
  m_window->draw(m_bgSprite);
  m_window->draw(m_lostSprite);

  // text
  m_window->draw(m_loseText);
  m_window->draw(m_levelTextStatic);
  m_window->draw(m_levelTextDynamic);

  // render buttons
  m_homeBtn.Render(*m_window);
}