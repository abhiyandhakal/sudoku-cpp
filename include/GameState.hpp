#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "LoseState.hpp"
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

  std::string MY_PATH;

  int m_clickedNum;

  // font
  sf::Font m_font;

  // stopwatch
  Stopwatch& m_stopwatch;

  // sudoku grid position
  sf::Vector2f m_gridPos;

  // for the functionality when window loses and gains focus
  bool m_lostFocus, m_gainedFocus;

  // sudoku generator object
  SudokuGenerator* m_sudokuGenerator;

  // stores int sudoku
  int** m_generatedSudoku;

  // sudoku solved by the solver
  int m_solvedSudoku[NUM][NUM];

  // display of numbers and interactive buttons
  SudokuButton m_sudokuTexts[NUM][NUM];

  // current selected element's position in grid
  int m_activeX;
  int m_activeY;

  int m_mistakesCount;

  // check for mistakes
  bool CheckIfSolved();
  bool CheckIfCorrect(int i, int j);

  bool m_isClickedOnce = false;

  // for mistakes visual representation and mistakes count
  std::string m_wrongNumArr[NUM][NUM];

  // clicked number
  std::string m_highlightedNum;

  // for keyboard navigation
  sf::RectangleShape m_navRect;
  int m_rectX, m_rectY;

  // highscore
  int StringToSeconds(std::string time);
  void setHighscore();

  // images
  sf::Texture m_bgTexture;
  sf::Sprite m_bgSprite;

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

  void PauseStopwatch();
  void ResumeStopwatch();

  void Update(WinState& winState, LoseState& loseState);
  void Render();

  ////////////////////////////////////
  // SUDOKU SOLVER
  ////////////////////////////////////
  bool IsSafe(int grid[NUM][NUM], int row, int col, int num);
  bool SolveSudoku(int grid[NUM][NUM], int row, int col);
};

#endif