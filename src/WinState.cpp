#include "WinState.hpp"

// ===========================================
// CONSTRUCTOR
// ===========================================
WinState::WinState() : m_highscoreTime("59:59"), m_elapsedTime("00:00") {
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

void WinState::setHighscoreTime() {
  std::fstream highscoreFile;

  // easy level score
  if (m_level == "Easy") {
    // reading text file to get highscore
    highscoreFile.open("db/highscore-easy.txt", std::ios::in);

    if (highscoreFile.is_open()) {
      getline(highscoreFile, m_highscoreTime);
      highscoreFile.close();
    }
  }
  // medium level score
  else if (m_level == "Medium") {
    // reading text file to get highscore
    highscoreFile.open("db/highscore-medium.txt", std::ios::in);

    if (highscoreFile.is_open()) {
      getline(highscoreFile, m_highscoreTime);
      highscoreFile.close();
    }
  }
  // hard level score
  else if (m_level == "Hard") {
    // reading text file to get highscore
    highscoreFile.open("db/highscore-hard.txt", std::ios::in);

    if (highscoreFile.is_open()) {
      getline(highscoreFile, m_highscoreTime);
      highscoreFile.close();
    }
  }
  // expert level score
  else if (m_level == "Expert") {
    // reading text file to get highscore
    highscoreFile.open("db/highscore-expert.txt", std::ios::in);

    if (highscoreFile.is_open()) {
      getline(highscoreFile, m_highscoreTime);
      highscoreFile.close();
    }
  }
}

void WinState::setLevel(std::string level) {
  m_level = level;
  setHighscoreTime();
}

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
  m_congratsSprite.setPosition({80, 110});

  // fonts
  m_font1.loadFromFile("assets/fonts/Inter/static/Inter-Bold.ttf");
  m_font2.loadFromFile("assets/fonts/Nerko_One/NerkoOne-Regular.ttf");

  // TEXT
  // you won text
  m_winText.setString("You Won !!!");
  m_winText.setFont(m_font1);
  m_winText.setFillColor(sf::Color(6, 17, 75));
  m_winText.setCharacterSize(32);
  m_winText.setPosition({203, 213});

  // elapsed time static
  m_timeTextStatic.setString("Elapsed Time:");
  m_timeTextStatic.setFont(m_font1);
  m_timeTextStatic.setFillColor(sf::Color(0, 0, 0));
  m_timeTextStatic.setCharacterSize(24);
  m_timeTextStatic.setPosition({154, 286});

  // elapsed time dynamic
  m_timeTextDynamic.setString(m_elapsedTime);
  m_timeTextDynamic.setFont(m_font1);
  m_timeTextDynamic.setFillColor(sf::Color(100, 64, 64));
  m_timeTextDynamic.setCharacterSize(32);
  m_timeTextDynamic.setPosition({340, 280});

  // highscore time static
  m_highScoreTextStatic.setString("Shortest Time:");
  m_highScoreTextStatic.setFont(m_font1);
  m_highScoreTextStatic.setFillColor(sf::Color(0, 0, 0));
  m_highScoreTextStatic.setCharacterSize(24);
  m_highScoreTextStatic.setPosition({150, 325});

  // highscore time dynamic
  m_highScoreTextDynamic.setString(m_highscoreTime);
  m_highScoreTextDynamic.setFont(m_font1);
  m_highScoreTextDynamic.setFillColor(sf::Color(100, 64, 64));
  m_highScoreTextDynamic.setCharacterSize(32);
  m_highScoreTextDynamic.setPosition({340, 320});

  // level static
  m_levelTextStatic.setString("Level");
  m_levelTextStatic.setFont(m_font2);
  m_levelTextStatic.setFillColor(sf::Color(0, 0, 0));
  m_levelTextStatic.setCharacterSize(24);
  m_levelTextStatic.setPosition({239, 371});

  // level dynamic
  m_levelTextDynamic.setString(m_level);
  m_levelTextDynamic.setFont(m_font2);
  m_levelTextDynamic.setFillColor(sf::Color(100, 64, 64));
  m_levelTextDynamic.setCharacterSize(24);
  m_levelTextDynamic.setPosition({311, 371});
}

void WinState::LoadBtns() {
  // back to home button
  m_returnToHomeBtn.setImage("assets/images/home-icon.png");
  m_returnToHomeBtn.setPosition({265, 425});
}
// ===========================================

void WinState::Update() {
  // dynamic texts
  m_timeTextDynamic.setString(m_elapsedTime);
  m_highScoreTextDynamic.setString(m_highscoreTime);
  m_levelTextDynamic.setString(m_level);

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
  m_window->draw(m_levelTextStatic);
  m_window->draw(m_levelTextDynamic);

  // render buttons
  m_returnToHomeBtn.Render(*m_window);
}
