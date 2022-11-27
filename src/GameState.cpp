#include "GameState.hpp"

// constructor
GameState::GameState(Stopwatch& stopwatch)
    : m_stopwatch(stopwatch),
      m_level("Easy"),
      m_mistakesCount(0),
      m_highlightedNum("") {
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

  m_mistakesTextDynamic.setString(std::to_string(m_mistakesCount) + "/5");
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

      m_solvedSudoku[i][j] = num;

      m_sudokuTexts[i][j].setNumber(num);
      m_sudokuTexts[i][j].setStatus(num == 0 ? "not-active" : "untouchable");
      m_sudokuTexts[i][j].setSize({50, 50});
      m_sudokuTexts[i][j].setPosition({i * 50 + 75, j * 50 + 100});
    }
  }

  std::cout << std::endl;
  SolveSudoku(m_solvedSudoku, 0, 0);
}

// ===========================================
bool GameState::CheckIfCorrect(int i, int j) {
  bool isCorrect = true;

  if (std::to_string(m_solvedSudoku[i][j]) != m_sudokuTexts[i][j].getNumber())
    isCorrect = false;

  return isCorrect;
}
// ===========================================

int GameState::StringToSeconds(std::string time) {
  int mins, secs;

  std::string minsStr = time;
  minsStr.erase(2, 3);

  std::string secsStr = time;
  secsStr.erase(0, 3);

  std::stringstream ssoMins;
  ssoMins << minsStr;
  ssoMins >> mins;

  std::stringstream ssoSecs;
  ssoSecs << secsStr;
  ssoSecs >> secs;

  secs += mins * 60;

  return secs;
}

// ===========================================
void GameState::setHighscore() {
  std::fstream highscoreFile;
  std::string highscoreStr = "59:59";
  int highscore = 0;

  // easy level highscore
  if (m_level == "Easy") {
    // reading text file to get highscore
    highscoreFile.open("db/highscore-easy.txt", std::ios::in);

    if (highscoreFile.is_open()) {
      getline(highscoreFile, highscoreStr);

      highscore = StringToSeconds(highscoreStr);

      highscoreFile.close();
    }

    // check if new record is made
    if (StringToSeconds(m_timeTextDynamic.getString()) < highscore) {
      highscoreFile.open("db/highscore-easy.txt", std::ios::out);

      std::string newHighscoreStr = m_timeTextDynamic.getString();

      if (highscoreFile.is_open()) {
        highscoreFile << newHighscoreStr;  // set new highscore

        highscoreFile.close();
      }
    }
  }
  // medium level highscore
  if (m_level == "Medium") {
    // reading text file to get highscore
    highscoreFile.open("db/highscore-medium.txt", std::ios::in);

    if (highscoreFile.is_open()) {
      getline(highscoreFile, highscoreStr);

      highscore = StringToSeconds(highscoreStr);

      highscoreFile.close();
    }

    // check if new record is made
    if (StringToSeconds(m_timeTextDynamic.getString()) < highscore) {
      highscoreFile.open("db/highscore-medium.txt", std::ios::out);

      std::string newHighscoreStr = m_timeTextDynamic.getString();

      if (highscoreFile.is_open()) {
        highscoreFile << newHighscoreStr;  // set new highscore

        highscoreFile.close();
      }
    }
  }
  // hard level highscore
  if (m_level == "Hard") {
    // reading text file to get highscore
    highscoreFile.open("db/highscore-hard.txt", std::ios::in);

    if (highscoreFile.is_open()) {
      getline(highscoreFile, highscoreStr);

      highscore = StringToSeconds(highscoreStr);

      highscoreFile.close();
    }

    // check if new record is made
    if (StringToSeconds(m_timeTextDynamic.getString()) < highscore) {
      highscoreFile.open("db/highscore-hard.txt", std::ios::out);

      std::string newHighscoreStr = m_timeTextDynamic.getString();

      if (highscoreFile.is_open()) {
        highscoreFile << newHighscoreStr;  // set new highscore

        highscoreFile.close();
      }
    }
  }
  // expert level highscore
  if (m_level == "Expert") {
    // reading text file to get highscore
    highscoreFile.open("db/highscore-expert.txt", std::ios::in);

    if (highscoreFile.is_open()) {
      getline(highscoreFile, highscoreStr);

      highscore = StringToSeconds(highscoreStr);

      highscoreFile.close();
    }

    // check if new record is made
    if (StringToSeconds(m_timeTextDynamic.getString()) < highscore) {
      highscoreFile.open("db/highscore-expert.txt", std::ios::out);

      std::string newHighscoreStr = m_timeTextDynamic.getString();

      if (highscoreFile.is_open()) {
        highscoreFile << newHighscoreStr;  // set new highscore

        highscoreFile.close();
      }
    }
  }
}
// ===========================================

// ===========================================
bool GameState::CheckIfSolved() {
  bool isSolved = true;

  for (int i = 0; i < NUM; i++) {
    for (int j = 0; j < NUM; j++) {
      if (std::to_string(m_solvedSudoku[i][j]) !=
          m_sudokuTexts[i][j].getNumber()) {
        isSolved = false;
      }
    }
  }
  return isSolved;
}
// ===========================================

// ===========================================
void GameState::Update(WinState& winState, LoseState& loseState) {
  // starting the stopwatch
  m_stopwatch.Resume();
  m_timeTextDynamic.setString(m_stopwatch.getElapsedTime());

  // mistakes
  m_mistakesTextDynamic.setString(std::to_string(m_mistakesCount) + "/5");

  // hovering the buttons
  m_pauseBtn.Hover(*m_window);
  m_eraseBtn.Hover(*m_window);
  for (int i = 0; i < NUM; i++) {
    m_numBtns[i].Hover(*m_window);
  }

  // clicking the buttons
  if (m_pauseBtn.Clicked(*m_window, *m_activeState, PAUSE_ID))
    m_stopwatch.Pause();
  if (m_eraseBtn.Clicked(*m_window, *m_activeState)) {
    m_clickedNum = 0;
    m_isClickedOnce = true;
  }

  // keyboard insertion of numbers
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0)) {
    m_clickedNum = 0;
    m_isClickedOnce = true;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
    m_clickedNum = 1;
    m_highlightedNum = "1";
    m_isClickedOnce = true;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) {
    m_clickedNum = 2;
    m_highlightedNum = "2";
    m_isClickedOnce = true;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)) {
    m_clickedNum = 3;
    m_highlightedNum = "3";
    m_isClickedOnce = true;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)) {
    m_clickedNum = 4;
    m_highlightedNum = "4";
    m_isClickedOnce = true;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)) {
    m_clickedNum = 5;
    m_highlightedNum = "5";
    m_isClickedOnce = true;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)) {
    m_clickedNum = 6;
    m_highlightedNum = "6";
    m_isClickedOnce = true;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7)) {
    m_clickedNum = 7;
    m_highlightedNum = "7";
    m_isClickedOnce = true;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)) {
    m_clickedNum = 8;
    m_highlightedNum = "8";
    m_isClickedOnce = true;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9)) {
    m_clickedNum = 9;
    m_highlightedNum = "9";
    m_isClickedOnce = true;
  }

  for (int i = 0; i < NUM; i++) {
    for (int j = 0; j < NUM; j++) {
      if (m_numBtns[i].Clicked(*m_window, *m_activeState)) {
        m_clickedNum = i + 1;
        m_highlightedNum = std::to_string(i + 1);
        m_isClickedOnce = true;
      }

      // highlight same numbers
      if (m_sudokuTexts[i][j].getNumber() == m_highlightedNum &&
          m_sudokuTexts[i][j].getNumber() != "") {
        m_sudokuTexts[i][j].Highlight();
      } else {
        m_sudokuTexts[i][j].setBg(sf::Color::Transparent);
      }

      if (m_sudokuTexts[i][j].Clicked(*m_window)) {
        m_highlightedNum = m_sudokuTexts[i][j].getNumber();
      }

      // clicking sudoku boxes
      if (m_sudokuTexts[i][j].getStatus() != "untouchable") {
        if (m_sudokuTexts[i][j].Clicked(*m_window)) {
          m_sudokuTexts[m_activeX][m_activeY].setStatus("not-active");

          m_activeX = i;
          m_activeY = j;

          m_sudokuTexts[i][j].setStatus("active");
        }

        if (m_isClickedOnce) {
          // insert number
          m_sudokuTexts[m_activeX][m_activeY].setNumber(m_clickedNum);
          m_sudokuTexts[m_activeX][m_activeY].setTextPosition();

          // increase mistakes
          if (!CheckIfCorrect(m_activeX, m_activeY)) {
            if (m_wrongNumArr[m_activeX][m_activeY] !=
                    m_sudokuTexts[m_activeX][m_activeY].getNumber() &&
                m_sudokuTexts[m_activeX][m_activeY].getNumber() != "") {
              m_mistakesCount++;

              m_wrongNumArr[m_activeX][m_activeY] =
                  m_sudokuTexts[m_activeX][m_activeY].getNumber();
            }
          }

          m_isClickedOnce = false;
        }
      }

      m_sudokuTexts[i][j].Hover(*m_window);
      m_sudokuTexts[i][j].Mistake(CheckIfCorrect(i, j));
    }
  }

  // check if solved
  if (CheckIfSolved()) {
    // sending elapsed time to win state
    winState.setElapsedTime(m_stopwatch.getElapsedTime());

    // setting highscore if new high score is set
    setHighscore();

    // reseting the clock
    m_stopwatch.Reset();
    m_stopwatch.Pause();

    m_mistakesCount = 0;

    *m_activeState = WIN_ID;
  }

  if (m_mistakesCount >= 5) {
    // sending elapsed time to lose state
    winState.setElapsedTime(m_timeTextDynamic.getString());

    // reseting the clock
    m_stopwatch.Reset();
    m_stopwatch.Pause();

    // reseting the mistake
    m_mistakesCount = 0;

    // changing state
    *m_activeState = LOSE_ID;
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
  // time
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
bool GameState::IsSafe(int grid[NUM][NUM], int row, int col, int num) {
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
bool GameState::SolveSudoku(int grid[NUM][NUM], int row,
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
  if (grid[row][col] > 0) return SolveSudoku(grid, row, col + 1);

  for (int num = 1; num <= NUM; num++) {
    // Check if it is safe to place
    // the num (1-9) in the
    // given row ,col ->we
    // move to next column
    if (IsSafe(grid, row, col, num)) {
      /* Assigning the num in
              the current (row,col)
              position of the grid
              and assuming our assigned
              num in the position
              is correct	 */
      grid[row][col] = num;

      // Checking for next possibility with next
      // column
      if (SolveSudoku(grid, row, col + 1)) return true;
    }

    /* Removing the assigned num, since our assumption was wrong, and we go
     * for next assumption with diff num value */
    grid[row][col] = 0;
  }
  return false;
}