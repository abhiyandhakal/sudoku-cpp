#include "Game.hpp"

Game::Game(sf::Vector2f winSize, std::string title, int framerateLimit)
    : m_activeState(MAIN_MENU_ID), MY_PATH(PATH) {
  // smooth shapes
  m_settings.antialiasingLevel = 8;

  m_window.create(sf::VideoMode(winSize.x, winSize.y), title, sf::Style::Close,
                  m_settings);

  m_window.setFramerateLimit(framerateLimit);

  // set icon
  /////////////////////////////////////////////////////////
  auto image = sf::Image{};
  if (!image.loadFromFile(MY_PATH + "assets/images/icon.png")) {
    std::cout << "Error loading icon\n";
  }

  m_window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
  /////////////////////////////////////////////////////////

  LoadStates();
}

void Game::LoadStates() {
  m_mainMenuState.setActiveState(&m_activeState);
  m_mainMenuState.setWindow(&m_window);

  m_levelsState.setActiveState(&m_activeState);
  m_levelsState.setWindow(&m_window);

  m_gameState.setActiveState(&m_activeState);
  m_gameState.setWindow(&m_window);

  m_winState.setActiveState(&m_activeState);
  m_winState.setWindow(&m_window);

  m_loseState.setActiveState(&m_activeState);
  m_loseState.setWindow(&m_window);

  m_pauseState.setActiveState(&m_activeState);
  m_pauseState.setWindow(&m_window);

  m_highscoreState.setActiveState(&m_activeState);
  m_highscoreState.setWindow(&m_window);

  m_howToPlayState.setActiveState(&m_activeState);
  m_howToPlayState.setWindow(&m_window);
}

void Game::HandleInputs() {
  sf::Event event;

  while (m_window.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed:
        m_window.close();
        break;

      case sf::Event::LostFocus:
        m_gameState.PauseStopwatch();
        break;

      case sf::Event::GainedFocus:
        if (m_activeState == GAME_ID) m_gameState.ResumeStopwatch();
        break;

      default:
        break;
    }
  }
}

void Game::Update() {
  if (m_activeState == MAIN_MENU_ID) m_mainMenuState.Update();
  if (m_activeState == LEVELS_ID)
    m_levelsState.Update(m_gameState, m_winState, m_loseState);
  if (m_activeState == GAME_ID) m_gameState.Update(m_winState, m_loseState);
  if (m_activeState == WIN_ID) m_winState.Update();
  if (m_activeState == LOSE_ID) m_loseState.Update();
  if (m_activeState == PAUSE_ID) m_pauseState.Update();
  if (m_activeState == HIGHSCORE_ID) m_highscoreState.Update();
  if (m_activeState == HOW_TO_PLAY_ID) m_howToPlayState.Update();
}

void Game::Render() {
  m_window.clear();

  if (m_activeState == MAIN_MENU_ID) m_mainMenuState.Render();
  if (m_activeState == LEVELS_ID) m_levelsState.Render();
  if (m_activeState == GAME_ID) m_gameState.Render();
  if (m_activeState == WIN_ID) m_winState.Render();
  if (m_activeState == LOSE_ID) m_loseState.Render();
  if (m_activeState == PAUSE_ID) m_pauseState.Render();
  if (m_activeState == HIGHSCORE_ID) m_highscoreState.Render();
  if (m_activeState == HOW_TO_PLAY_ID) m_howToPlayState.Render();

  m_window.display();
}

void Game::Run() {
  while (m_window.isOpen()) {
    HandleInputs();
    Render();
    Update();
  }
}