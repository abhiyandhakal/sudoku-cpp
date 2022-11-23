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

void Stopwatch::Reset() {
  m_clock.restart();
  m_runTime = 0;
  m_isPaused = false;
}

void Stopwatch::Resume() {
  if (m_isPaused) {
    m_clock.restart();
  }
  m_isPaused = false;
}

void Stopwatch::Pause() {
  if (!m_isPaused) {
    m_runTime += m_clock.getElapsedTime().asSeconds();
  }
  m_isPaused = true;
}

float Stopwatch::getElapsedSeconds() {
  if (!m_isPaused) {
    return m_runTime + m_clock.getElapsedTime().asSeconds();
  }
  return m_runTime;
}

std::string Stopwatch::Format(int time) {
  if (time >= 10)
    return std::to_string(time);
  else
    return "0" + std::to_string(time);
}

std::string Stopwatch::getElapsedTime() {
  int seconds = int(getElapsedSeconds());
  int minutes = seconds / 60;
  int hours = minutes / 60;
  minutes = (seconds - hours * 3600) / 60;
  seconds -= (minutes * 60 + hours * 3600);

  return Format(minutes) + ":" + Format(seconds);
}

#endif