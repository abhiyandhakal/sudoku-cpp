#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <sstream>

#include "NumberButton.hpp"
#include "Stopwatch.hpp"
#include "SudokuButton.hpp"
#include "SudokuGenerator.hpp"
#include "TextButton.hpp"
#include "WinState.hpp"

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
  int m_solvedSudoku[NUM][NUM];
  SudokuButton m_sudokuTexts[NUM][NUM];
  int m_activeX;
  int m_activeY;
  int m_mistakesCount;
  bool CheckIfSolved();
  bool CheckIfCorrect(int i, int j);
  bool m_isClickedOnce = false;
  std::string m_wrongNumArr[NUM][NUM];
  std::string m_highlightedNum;

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
  ImageButton m_pauseBtn, m_eraseBtn;
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

  void Update(WinState& winState);
  void Render();

  ////////////////////////////////////
  // SUDOKU SOLVER
  ////////////////////////////////////
  bool isSafe(int grid[NUM][NUM], int row, int col, int num);
  bool solveSudoku(int grid[NUM][NUM], int row, int col);

  /* A utility function to print grid */
  void print(int arr[NUM][NUM]);
};

#endif