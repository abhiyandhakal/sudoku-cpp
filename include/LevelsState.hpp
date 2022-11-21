#ifndef LEVELS_HPP
#define LEVELS_HPP

#include "DEFINITIONS.hpp"
#include "ImageButton.hpp"
#include "TextButton.hpp"

class LevelsState {
 private:
  sf::RenderWindow* m_window;
  std::string* m_activeState;

  // image
  sf::Texture m_bgTexture;
  sf::Sprite m_bgSprite;

  // text
  sf::Text m_title;
  sf::Font m_font;

  // buttons
  ImageButton m_backBtn{LEVELS_ID};
  TextButton m_easyBtn{LEVELS_ID}, m_mediumBtn{LEVELS_ID}, m_hardBtn{LEVELS_ID},
      m_expertBtn{LEVELS_ID};

  // load stuff
  void LoadStatic();
  void LoadBtns();

 public:
  LevelsState();

  // setters
  void setWindow(sf::RenderWindow* window);
  void setActiveState(std::string* activeState);

  void Update();
  void Render();
};

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
// images
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

void LevelsState::Update() {
  // hovering the buttons
  m_backBtn.Hover(*m_window);
  m_easyBtn.Hover(*m_window);
  m_mediumBtn.Hover(*m_window);
  m_hardBtn.Hover(*m_window);
  m_expertBtn.Hover(*m_window);

  sf::Event event;

  while (m_window->pollEvent(event)) {
    if (event.type == sf::Event::MouseButtonPressed) {
      if (m_easyBtn.IsMouseOver(*m_window)) *m_activeState = GAME_ID;
    }
  }

  // clicking the buttons
  m_backBtn.Clicked(*m_window, *m_activeState, MAIN_MENU_ID);
  // m_easyBtn.Clicked(*m_window, *m_activeState, GAME_ID);
  m_mediumBtn.Clicked(*m_window, *m_activeState, GAME_ID);
  m_hardBtn.Clicked(*m_window, *m_activeState, GAME_ID);
  m_expertBtn.Clicked(*m_window, *m_activeState, GAME_ID);
}

void LevelsState::Render() {
  m_window->clear();

  m_window->draw(m_bgSprite);
  m_window->draw(m_title);

  // render buttons
  m_backBtn.Render(*m_window);
  m_easyBtn.Render(*m_window);
  m_mediumBtn.Render(*m_window);
  m_hardBtn.Render(*m_window);
  m_expertBtn.Render(*m_window);
}

#endif