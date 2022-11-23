#ifndef GAME_HPP
#define GAME_HPP

#include "GameState.hpp"
#include "LevelsState.hpp"
#include "MainMenuState.hpp"

class Game {
 private:
  sf::RenderWindow m_window;
  std::string m_activeState;

  sf::ContextSettings m_settings;

  void HandleInputs();
  void Update();
  void Render();
  void LoadStates();

  // states
  MainMenuState m_mainMenuState;
  LevelsState m_levelsState;
  GameState m_gameState;

  // stopwatch
  Stopwatch m_stopwatch;

 public:
  Game(sf::Vector2f winSize = {200, 200}, std::string title = "",
       int framerateLimit = 60);

  void Run();
};

Game::Game(sf::Vector2f winSize, std::string title, int framerateLimit) {
  // smooth shapes
  m_settings.antialiasingLevel = 8;

  m_activeState = MAIN_MENU_ID;

  m_window.create(sf::VideoMode(winSize.x, winSize.y), title, sf::Style::Close,
                  m_settings);
  m_window.setFramerateLimit(framerateLimit);

  LoadStates();
}

void Game::LoadStates() {
  m_mainMenuState.setActiveState(&m_activeState);
  m_mainMenuState.setWindow(&m_window);

  m_levelsState.setActiveState(&m_activeState);
  m_levelsState.setWindow(&m_window);

  m_gameState.setActiveState(&m_activeState);
  m_gameState.setWindow(&m_window);
  m_gameState.setStopwatch(m_stopwatch);
}

void Game::HandleInputs() {
  sf::Event event;

  while (m_window.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed:
        m_window.close();
        break;

      default:
        break;
    }
  }
}

void Game::Update() {
  if (m_activeState == MAIN_MENU_ID) m_mainMenuState.Update();
  if (m_activeState == LEVELS_ID) m_levelsState.Update(m_gameState);
  if (m_activeState == GAME_ID) m_gameState.Update();
}

void Game::Render() {
  m_window.clear();

  if (m_activeState == MAIN_MENU_ID) m_mainMenuState.Render();
  if (m_activeState == LEVELS_ID) m_levelsState.Render();
  if (m_activeState == GAME_ID) m_gameState.Render();

  m_window.display();
}

void Game::Run() {
  while (m_window.isOpen()) {
    HandleInputs();
    Render();
    Update();
  }
}

#endif