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
  int m_solvedSudoku[NUM][NUM];
  SudokuButton m_sudokuTexts[NUM][NUM];
  int m_activeX;
  int m_activeY;
  bool CheckIfSolved();

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

  void Update();
  void Render();

  ////////////////////////////////////
  // SUDOKU SOLVER
  ////////////////////////////////////
  // Checks whether it will be legal to assign num to the given row, col
  bool isSafe(int grid[NUM][NUM], int row, int col, int num);

  /* Takes a partially filled-in grid and attempts to assign values to all
   * unassigned locations in such a way to meet the requirements for Sudoku
   * solution (non-duplication across rows, columns, and boxes) */
  bool solveSudoku(int grid[NUM][NUM], int row, int col);

  /* A utility function to print grid */
  void print(int arr[NUM][NUM]) {
    for (int i = 0; i < NUM; i++) {
      for (int j = 0; j < NUM; j++) {
        cout << arr[i][j] << " ";
      }
      cout << endl;
    }
  }
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
  m_eraseBtn.setImage("assets/images/eraser.png");
  m_eraseBtn.setPosition({534, 15});

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

      m_solvedSudoku[j][i] = num;

      m_sudokuTexts[i][j].setNumber(num);
      m_sudokuTexts[i][j].setStatus(num == 0 ? "not-active" : "untouchable");
      m_sudokuTexts[i][j].setSize({50, 50});
      m_sudokuTexts[i][j].setPosition({i * 50 + 75, j * 50 + 100});
    }
  }

  print(m_solvedSudoku);
  std::cout << std::endl;
  solveSudoku(m_solvedSudoku, 0, 0);
  print(m_solvedSudoku);
}

// ===========================================
bool GameState::CheckIfSolved() {
  bool isSolved = true;

  for (int i = 0; i < NUM; i++) {
    for (int j = 0; j < NUM; j++) {
      if (std::to_string(m_solvedSudoku[j][i]) !=
          m_sudokuTexts[i][j].getNumber()) {
        isSolved = false;
      }
    }
  }
  return isSolved;
}
// ===========================================

void GameState::Update() {
  // has number button been clicked once?
  bool isClickedOnce = false;

  // starting the stopwatch
  m_stopwatch.Resume();

  // hovering the buttons
  m_pauseBtn.Hover(*m_window);
  m_eraseBtn.Hover(*m_window);
  for (int i = 0; i < NUM; i++) {
    m_numBtns[i].Hover(*m_window);
  }

  // clicking the buttons
  m_pauseBtn.Clicked(*m_window, *m_activeState, PAUSE_ID);
  if (m_eraseBtn.Clicked(*m_window, *m_activeState)) {
    m_clickedNum = 0;
    isClickedOnce = true;
    std::cout << "erased\n";
  }

  // keyboard insertion of numbers
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0)) {
    m_clickedNum = 0;
    isClickedOnce = true;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
    m_clickedNum = 1;
    isClickedOnce = true;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) {
    m_clickedNum = 2;
    isClickedOnce = true;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)) {
    m_clickedNum = 3;
    isClickedOnce = true;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)) {
    m_clickedNum = 4;
    isClickedOnce = true;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)) {
    m_clickedNum = 5;
    isClickedOnce = true;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)) {
    m_clickedNum = 6;
    isClickedOnce = true;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7)) {
    m_clickedNum = 7;
    isClickedOnce = true;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)) {
    m_clickedNum = 8;
    isClickedOnce = true;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9)) {
    m_clickedNum = 9;
    isClickedOnce = true;
  }

  for (int i = 0; i < NUM; i++) {
    for (int j = 0; j < NUM; j++) {
      if (m_numBtns[i].Clicked(*m_window, *m_activeState)) {
        m_clickedNum = i + 1;
        isClickedOnce = true;
      }

      if (m_sudokuTexts[i][j].getStatus() != "untouchable") {
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
      }

      // hover
      m_sudokuTexts[i][j].Hover(*m_window);
    }
  }

  // check if solved
  if (CheckIfSolved()) {
    m_stopwatch.Reset();
    m_stopwatch.Pause();
    *m_activeState = MAIN_MENU_ID;
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
  m_eraseBtn.Render(*m_window);
  for (int i = 0; i < NUM; i++) {
    m_numBtns[i].Render(*m_window);
  }
}

// ===========================================
// SUDOKU SOLVER
// ===========================================
// Checks whether it will be legal to assign num to the given row, col
bool GameState::isSafe(int grid[NUM][NUM], int row, int col, int num) {
  // Check if we find the same num
  // in the similar row , we
  // return false
  for (int x = 0; x <= 8; x++)
    if (grid[row][x] == num) return false;

  // Check if we find the same num in
  // the similar column , we
  // return false
  for (int x = 0; x <= 8; x++)
    if (grid[x][col] == num) return false;

  // Check if we find the same num in
  // the particular 3*3 matrix,
  // we return false
  int startRow = row - row % 3, startCol = col - col % 3;

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (grid[i + startRow][j + startCol] == num) return false;

  return true;
}

/* Takes a partially filled-in grid and attempts to assign values to all
 * unassigned locations in such a way to meet the requirements for Sudoku
 * solution (non-duplication across rows, columns, and boxes) */
bool GameState::solveSudoku(int grid[NUM][NUM], int row,
                            int col) {  // Check if we have reached the 8th
  // row and 9th column (0
  // indexed matrix) , we are
  // returning true to avoid
  // further backtracking
  if (row == NUM - 1 && col == NUM) return true;

  // Check if column value becomes 9 ,
  // we move to next row and
  // column start from 0
  if (col == NUM) {
    row++;
    col = 0;
  }

  // Check if the current position of
  // the grid already contains
  // value >0, we iterate for next column
  if (grid[row][col] > 0) return solveSudoku(grid, row, col + 1);

  for (int num = 1; num <= NUM; num++) {
    // Check if it is safe to place
    // the num (1-9) in the
    // given row ,col ->we
    // move to next column
    if (isSafe(grid, row, col, num)) {
      /* Assigning the num in
              the current (row,col)
              position of the grid
              and assuming our assigned
              num in the position
              is correct	 */
      grid[row][col] = num;

      // Checking for next possibility with next
      // column
      if (solveSudoku(grid, row, col + 1)) return true;
    }

    // Removing the assigned num ,
    // since our assumption
    // was wrong , and we go for
    // next assumption with
    // diff num value
    grid[row][col] = 0;
  }
  return false;
}

#endif