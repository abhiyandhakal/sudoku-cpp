#ifndef GAME_HPP
#define GAME_HPP

#include "GameState.hpp"
#include "HighscoreState.hpp"
#include "HowToPlayState.hpp"
#include "LevelsState.hpp"
#include "LoseState.hpp"
#include "MainMenuState.hpp"
#include "PauseState.hpp"
#include "WinState.hpp"

class Game {
 private:
  sf::RenderWindow m_window;
  std::string m_activeState;

  std::string MY_PATH;

  sf::ContextSettings m_settings;

  void HandleInputs();
  void Update();
  void Render();
  void LoadStates();

  Stopwatch m_stopwatch;

  // states
  MainMenuState m_mainMenuState;
  LevelsState m_levelsState;
  GameState m_gameState{m_stopwatch};
  PauseState m_pauseState{m_stopwatch};
  WinState m_winState;
  LoseState m_loseState;
  HighScoreState m_highscoreState;
  HowToPlayState m_howToPlayState;

 public:
  Game(sf::Vector2f winSize = {200, 200}, std::string title = "",
       int framerateLimit = 60);

  void Run();
};

#endif