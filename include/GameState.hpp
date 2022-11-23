#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#define NUM 9

#include <sstream>

#include "DEFINITIONS.hpp"
#include "ImageButton.hpp"
#include "NumberButton.hpp"
#include "Stopwatch.hpp"
#include "SudokuButton.hpp"
#include "SudokuGenerator.hpp"
#include "TextButton.hpp"

class GameState {
 private:
  sf::RenderWindow* m_window;
  std::string* m_activeState;
  std::string m_level;

  int m_clickedNum;

  // font
  sf::Font m_font;

  // stopwatch
  Stopwatch& m_stopwatch;

  // images
  sf::Texture m_bgTexture;
  sf::Sprite m_bgSprite;

  // sudoku
  SudokuGenerator* m_sudokuGenerator;
  int** m_generatedSudoku;
  SudokuButton m_sudokuTexts[NUM][NUM];
  int m_activeX;
  int m_activeY;

  sf::Texture m_sudokuGridTexture;
  sf::Sprite m_sudokuGridSprite;

  sf::Texture m_titleTexture;
  sf::Sprite m_titleSprite;

  // text
  sf::Text m_levelText;
  sf::Text m_timeTextStatic;
  sf::Text m_timeTextDynamic;
  sf::Text m_mistakesTextStatic;
  sf::Text m_mistakesTextDynamic;

  // buttons
  ImageButton m_pauseBtn, m_undoBtn;
  NumberButton m_numBtns[NUM];

  // load stuff
  void LoadStatic();
  void LoadBtns();
  void LoadSudoku(int empty);

 public:
  GameState(Stopwatch& stopwatch);

  // setters
  void setWindow(sf::RenderWindow* window);
  void setActiveState(std::string* activeState);
  void setLevel(std::string level);

  void Update();
  void Render();
};

// constructor
GameState::GameState(Stopwatch& stopwatch)
    : m_stopwatch(stopwatch), m_level("Easy") {
  LoadStatic();
  LoadBtns();
}

// setter functions
void GameState::setWindow(sf::RenderWindow* window) { m_window = window; }

void GameState::setActiveState(std::string* activeState) {
  m_activeState = activeState;
}

void GameState::setLevel(std::string level) {
  m_level = level;
  m_levelText.setString(level);

  if (level == "Easy")
    LoadSudoku(20);
  else if (level == "Medium")
    LoadSudoku(25);
  else if (level == "Hard")
    LoadSudoku(30);
  else if (level == "Expert")
    LoadSudoku(40);
}

// ===========================================
// LOAD STUFFS
// ===========================================
// static
void GameState::LoadStatic() {
  // IMAGES
  // background image
  m_bgTexture.loadFromFile("assets/images/background.png");
  m_bgSprite.setTexture(m_bgTexture);

  // sudoku grid
  m_sudokuGridTexture.loadFromFile("assets/images/sudoku-grid.png");
  m_sudokuGridSprite.setTexture(m_sudokuGridTexture);
  m_sudokuGridSprite.setPosition({75, 100});

  m_titleTexture.loadFromFile("assets/images/SUDOKU.png");
  m_titleSprite.setTexture(m_titleTexture);
  m_titleSprite.setPosition({199, 15});

  // font
  m_font.loadFromFile("assets/fonts/Inter/static/Inter-Bold.ttf");

  // TEXTS
  m_levelText.setString(m_level);
  m_levelText.setFont(m_font);
  m_levelText.setFillColor(sf::Color::Black);
  m_levelText.setCharacterSize(12);
  m_levelText.setPosition(282, 79);

  m_timeTextStatic.setString("Time:");
  m_timeTextStatic.setFont(m_font);
  m_timeTextStatic.setFillColor(sf::Color::Black);
  m_timeTextStatic.setCharacterSize(20);
  m_timeTextStatic.setPosition(400, 75);

  m_timeTextDynamic.setString(m_stopwatch.getElapsedTime());
  m_timeTextDynamic.setFont(m_font);
  m_timeTextDynamic.setFillColor(sf::Color(151, 64, 64));
  m_timeTextDynamic.setCharacterSize(20);
  m_timeTextDynamic.setPosition(465, 75);

  m_mistakesTextStatic.setString("Mistakes:");
  m_mistakesTextStatic.setFont(m_font);
  m_mistakesTextStatic.setFillColor(sf::Color::Black);
  m_mistakesTextStatic.setCharacterSize(20);
  m_mistakesTextStatic.setPosition(75, 75);

  m_mistakesTextDynamic.setString("0/5");
  m_mistakesTextDynamic.setFont(m_font);
  m_mistakesTextDynamic.setFillColor(sf::Color(137, 0, 0));
  m_mistakesTextDynamic.setCharacterSize(20);
  m_mistakesTextDynamic.setPosition(175, 75);
}

void GameState::LoadBtns() {
  // pause button
  m_pauseBtn.setImage("assets/images/pause.png");
  m_pauseBtn.setPosition({15, 15});

  // undo button
  m_undoBtn.setImage("assets/images/undo.png");
  m_undoBtn.setPosition({534, 15});

  // number buttons
  for (int i = 0; i < NUM; i++) {
    m_numBtns[i].setNumber(std::to_string(i + 1));
    m_numBtns[i].setFontSize(64);
    m_numBtns[i].setPosition({(i * 50 + 75), 550});
  }
}

void GameState::LoadSudoku(int empty) {
  srand(time(NULL));

  m_sudokuGenerator = new SudokuGenerator(NUM, empty);
  m_generatedSudoku = m_sudokuGenerator->getSudoku();

  for (int i = 0; i < NUM; i++) {
    for (int j = 0; j < NUM; j++) {
      int num = m_generatedSudoku[i][j];

      m_sudokuTexts[i][j].setNumber(num);
      m_sudokuTexts[i][j].setSize({50, 50});
      m_sudokuTexts[i][j].setPosition({i * 50 + 75, j * 50 + 100});
    }
  }
}

// ===========================================

void GameState::Update() {
  // has number button been clicked once?
  bool isClickedOnce = false;

  // starting the stopwatch
  m_stopwatch.Resume();

  // hovering the buttons
  m_pauseBtn.Hover(*m_window);
  m_undoBtn.Hover(*m_window);
  for (int i = 0; i < NUM; i++) {
    m_numBtns[i].Hover(*m_window);
  }

  // clicking the buttons
  m_pauseBtn.Clicked(*m_window, *m_activeState, PAUSE_ID);
  m_undoBtn.Clicked(*m_window, *m_activeState);

  for (int i = 0; i < NUM; i++) {
    for (int j = 0; j < NUM; j++) {
      if (m_sudokuTexts[i][j].Clicked(*m_window)) {
        m_sudokuTexts[m_activeX][m_activeY].setStatus("not-active");

        m_activeX = i;
        m_activeY = j;

        m_sudokuTexts[i][j].setStatus("active");
      }

      // insert number
      if (isClickedOnce) {
        m_sudokuTexts[m_activeX][m_activeY].setNumber(m_clickedNum);
        m_sudokuTexts[m_activeX][m_activeY].setTextPosition();

        isClickedOnce = false;
      }

      if (m_numBtns[i].Clicked(*m_window, *m_activeState)) {
        m_clickedNum = i + 1;
        isClickedOnce = true;
      }

      // hover
      m_sudokuTexts[i][j].Hover(*m_window);
    }
  }
}

void GameState::Render() {
  // images
  m_window->draw(m_bgSprite);
  m_window->draw(m_sudokuGridSprite);
  m_window->draw(m_titleSprite);

  // text
  m_window->draw(m_levelText);
  m_window->draw(m_timeTextStatic);
  m_window->draw(m_mistakesTextDynamic);
  m_window->draw(m_mistakesTextStatic);

  // time
  m_timeTextDynamic.setString(m_stopwatch.getElapsedTime());
  m_window->draw(m_timeTextDynamic);

  // sudoku
  for (int i = 0; i < NUM; i++) {
    for (int j = 0; j < NUM; j++) {
      m_sudokuTexts[i][j].Render(*m_window);
    }
  }

  // render buttons
  m_pauseBtn.Render(*m_window);
  m_undoBtn.Render(*m_window);
  for (int i = 0; i < NUM; i++) {
    m_numBtns[i].Render(*m_window);
  }
}

#endif