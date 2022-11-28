#include "Game.hpp"

int main() {
  Game game{{600, 648}, "Sudoku", 60};
  game.Run();

  return 0;
}