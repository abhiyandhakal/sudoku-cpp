#ifndef TIMER_HPP
#define TIMER_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Stopwatch {
 private:
  sf::Clock m_clock;
  float m_runTime;
  bool m_isPaused;

  float getElapsedSeconds();
  std::string Format(int time);

 public:
  Stopwatch() {
    m_isPaused = true;
    m_runTime = 0;
    m_clock.restart();
    Pause();
  }

  void Reset();
  void Resume();
  void Pause();
  std::string getElapsedTime();
};

#endif