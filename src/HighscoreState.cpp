#include "HighscoreState.hpp"

HighScoreState::HighScoreState()
    : m_highscore({"59:59", "59:59", "59:59", "59:59"}) {
  LoadStatic();
  LoadBtns();
}

// ===========================================
// LOAD STUFFS
// ===========================================
void HighScoreState::LoadStatic() {
  // IMAGES
  // background image
  m_bgTexture.loadFromFile("assets/images/background.png");
  m_bgSprite.setTexture(m_bgTexture);

  m_captionTexture.loadFromFile("assets/images/highscore-subtitle.png");
  m_captionSprite.setTexture(m_captionTexture);
  m_captionSprite.setPosition(99, 159);

  // font
  m_font.loadFromFile("assets/fonts/Inter/static/Inter-Regular.ttf");
  m_fontBold.loadFromFile("assets/fonts/Inter/static/Inter-Bold.ttf");

  // shapes
  m_line.setSize({275, 2});
  m_line.setFillColor(sf::Color(51, 0, 0));
  m_line.setPosition(79, 325);

  // ===========================================
  // TEXT
  // ===========================================
  // state title
  m_title.setString("Highscore");
  m_title.setFont(m_fontBold);
  m_title.setFillColor(sf::Color::Black);
  m_title.setCharacterSize(48);
  m_title.setPosition({169, 94});

  // "levels" text
  m_levelsTextStatic.setString("Levels");
  m_levelsTextStatic.setFont(m_fontBold);
  m_levelsTextStatic.setCharacterSize(24);
  m_levelsTextStatic.setPosition({99, 282});
  m_levelsTextStatic.setFillColor(sf::Color(51, 0, 0));

  // "time" text
  m_highscoreTextStatic.setString("Time");
  m_highscoreTextStatic.setFont(m_fontBold);
  m_highscoreTextStatic.setCharacterSize(24);
  m_highscoreTextStatic.setPosition({269, 282});
  m_highscoreTextStatic.setFillColor(sf::Color(51, 0, 0));

  // LEVELS
  // setting common properties of level texts
  for (int i = 0; i < 4; i++) {
    m_levelsText[i].setFont(m_font);
    m_levelsText[i].setCharacterSize(24);
    m_levelsText[i].setFillColor(sf::Color::Black);
  }

  // levels' text
  m_levelsText[0].setString("Easy");
  m_levelsText[1].setString("Medium");
  m_levelsText[2].setString("Hard");
  m_levelsText[3].setString("Expert");

  // levels' position
  m_levelsText[0].setPosition({112, 344});
  m_levelsText[1].setPosition({92, 406});
  m_levelsText[2].setPosition({111, 468});
  m_levelsText[3].setPosition({100, 530});

  // TIME
  for (int i = 0; i < 4; i++) {
    m_highscoreText[i].setString(m_highscore[i]);
    m_highscoreText[i].setFont(m_font);
    m_highscoreText[i].setCharacterSize(24);
    m_highscoreText[i].setFillColor(sf::Color::Black);
    m_highscoreText[i].setPosition({262, 344 + i * 62});
  }
}

void HighScoreState::LoadBtns() {
  // reset buttons
  for (int i = 0; i < 4; i++) {
    m_resetBtns[i].setImage("assets/images/reset.png");
    m_resetBtns[i].setPosition({395, 338 + 62 * i});
  }

  // back button
  m_backBtn.setImage("assets/images/back.png");
  m_backBtn.setPosition({25, 25});
}

// ===========================================
// FILE HANDLING
// ===========================================
std::string HighScoreState::ReadScore(std::string file) {
  std::fstream highscoreFile;
  std::string highscore;

  highscoreFile.open("db/" + file, std::ios::in);

  if (highscoreFile.is_open()) {
    getline(highscoreFile, highscore);
    highscoreFile.close();
  }

  return highscore;
}

void HighScoreState::ResetScore(std::string file) {
  std::fstream highScoreFile;

  highScoreFile.open("db/" + file, std::ios::out);

  if (highScoreFile.is_open()) {
    highScoreFile << "59:59";
    highScoreFile.close();
  }
}
// ===========================================

// setter functions
void HighScoreState::setWindow(sf::RenderWindow* window) { m_window = window; }

void HighScoreState::setActiveState(std::string* activeState) {
  m_activeState = activeState;
}

void HighScoreState::Update() {
  // read highscore
  m_highscore[0] = ReadScore("highscore-easy.txt");
  m_highscore[1] = ReadScore("highscore-medium.txt");
  m_highscore[2] = ReadScore("highscore-hard.txt");
  m_highscore[3] = ReadScore("highscore-expert.txt");

  // update highscore text
  for (int i = 0; i < 4; i++) {
    m_highscoreText[i].setString(m_highscore[i]);
  }

  // hover
  m_backBtn.Hover(*m_window);
  for (int i = 0; i < 4; i++) {
    m_resetBtns[i].Hover(*m_window);
  }

  // click
  m_backBtn.Clicked(*m_window, *m_activeState, MAIN_MENU_ID);

  // reset
  if (m_resetBtns[0].Clicked(*m_window, *m_activeState))
    ResetScore("highscore-easy.txt");
  if (m_resetBtns[1].Clicked(*m_window, *m_activeState))
    ResetScore("highscore-medium.txt");
  if (m_resetBtns[2].Clicked(*m_window, *m_activeState))
    ResetScore("highscore-hard.txt");
  if (m_resetBtns[3].Clicked(*m_window, *m_activeState))
    ResetScore("highscore-expert.txt");
}

void HighScoreState::Render() {
  // images
  m_window->draw(m_bgSprite);
  m_window->draw(m_captionSprite);

  // text
  m_window->draw(m_title);
  m_window->draw(m_levelsTextStatic);
  m_window->draw(m_highscoreTextStatic);

  // shapes
  m_window->draw(m_line);

  // buttons
  m_backBtn.Render(*m_window);

  // texts and buttons in array
  for (int i = 0; i < 4; i++) {
    // text
    m_window->draw(m_levelsText[i]);
    m_window->draw(m_highscoreText[i]);

    // button
    m_resetBtns[i].Render(*m_window);
  }
}
