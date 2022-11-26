#ifndef SUDOKU_GENERATOR_HPP
#define SUDOKU_GENERATOR_HPP

#include <cmath>
#include <cstring>
#include <iostream>

class SudokuGenerator {
 public:
  int** m_matrix;
  int m_n;

  // number of columns/rows.
  int m_sqrtN;

  // square root of N
  int m_numOfEmpty;
  // No. Of missing digits

  // Constructor
  SudokuGenerator(int n, int numOfMissing);

  // Sudoku Generator
  void fillValues();

  // Fill the diagonal SRN number of SRN x SRN matrices
  void fillDiagonal();

  // Returns false if given 3 x 3 block contains num.
  bool unUsedInBox(int rowStart, int colStart, int num);

  // Fill a 3 x 3 matrix.
  void fillBox(int row, int col);

  // Random generator
  int randomGenerator(int num);

  // Check if safe to put in cell
  bool CheckIfSafe(int i, int j, int num);

  // check in the row for existence
  bool unUsedInRow(int i, int num);

  // check in the row for existence
  bool unUsedInCol(int j, int num);

  // A recursive function to fill remaining
  // matrix
  bool fillRemaining(int i, int j);

  // Remove the K no. of digits to
  // complete game
  void removeKDigits();

  int** getSudoku();
};

inline int** SudokuGenerator::getSudoku() { return m_matrix; }

#endif