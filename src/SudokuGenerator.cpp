#include "SudokuGenerator.hpp"

// Constructor
SudokuGenerator::SudokuGenerator(int n, int numOfMissing) {
  m_n = n;
  m_numOfEmpty = numOfMissing;

  // Compute square root of N
  double SRNd = sqrt(n);
  m_sqrtN = (int)SRNd;
  m_matrix = new int*[n];

  // Create a row for every pointer
  for (int i = 0; i < n; i++) {
    // Note : Rows may not be contiguous
    m_matrix[i] = new int[n];

    // Initialize all entries as false to indicate
    // that there are no edges initially
    memset(m_matrix[i], 0, n * sizeof(int));
  }

  fillValues();
}

// Sudoku Generator
void SudokuGenerator::fillValues() {
  // Fill the diagonal of SRN x SRN matrices
  fillDiagonal();

  // Fill remaining blocks
  fillRemaining(0, m_sqrtN);

  // Remove Randomly K digits to make game
  removeKDigits();
}

// Fill the diagonal SRN number of SRN x SRN matrices
void SudokuGenerator::fillDiagonal() {
  for (int i = 0; i < m_n; i = i + m_sqrtN) {
    // for diagonal box, start coordinates->i==j
    fillBox(i, i);
  }
}

// Returns false if given 3 x 3 block contains num.
bool SudokuGenerator::unUsedInBox(int rowStart, int colStart, int num) {
  for (int i = 0; i < m_sqrtN; i++) {
    for (int j = 0; j < m_sqrtN; j++) {
      if (m_matrix[rowStart + i][colStart + j] == num) {
        return false;
      }
    }
  }
  return true;
}

// Fill a 3 x 3 matrix.
void SudokuGenerator::fillBox(int row, int col) {
  int num;
  for (int i = 0; i < m_sqrtN; i++) {
    for (int j = 0; j < m_sqrtN; j++) {
      do {
        num = randomGenerator(m_n);
      } while (!unUsedInBox(row, col, num));
      m_matrix[row + i][col + j] = num;
    }
  }
}

// Random generator
int SudokuGenerator::randomGenerator(int num) {
  return (int)floor((float)(rand() / double(RAND_MAX) * num + 1));
}

// Check if safe to put in cell
bool SudokuGenerator::CheckIfSafe(int i, int j, int num) {
  return (unUsedInRow(i, num) && unUsedInCol(j, num) &&
          unUsedInBox(i - i % m_sqrtN, j - j % m_sqrtN, num));
}

// check in the row for existence
bool SudokuGenerator::unUsedInRow(int i, int num) {
  for (int j = 0; j < m_n; j++) {
    if (m_matrix[i][j] == num) {
      return false;
    }
  }
  return true;
}

// check in the row for existence
bool SudokuGenerator::unUsedInCol(int j, int num) {
  for (int i = 0; i < m_n; i++) {
    if (m_matrix[i][j] == num) {
      return false;
    }
  }
  return true;
}

// A recursive function to fill remaining
// matrix
bool SudokuGenerator::fillRemaining(int i, int j) {
  // System.out.println(i+" "+j);
  if (j >= m_n && i < m_n - 1) {
    i = i + 1;
    j = 0;
  }
  if (i >= m_n && j >= m_n) {
    return true;
  }
  if (i < m_sqrtN) {
    if (j < m_sqrtN) {
      j = m_sqrtN;
    }
  } else if (i < m_n - m_sqrtN) {
    if (j == (int)(i / m_sqrtN) * m_sqrtN) {
      j = j + m_sqrtN;
    }
  } else {
    if (j == m_n - m_sqrtN) {
      i = i + 1;
      j = 0;
      if (i >= m_n) {
        return true;
      }
    }
  }
  for (int num = 1; num <= m_n; num++) {
    if (CheckIfSafe(i, j, num)) {
      m_matrix[i][j] = num;
      if (fillRemaining(i, j + 1)) {
        return true;
      }
      m_matrix[i][j] = 0;
    }
  }
  return false;
}

// Remove the K no. of digits to
// complete game
void SudokuGenerator::removeKDigits() {
  int count = m_numOfEmpty;
  while (count != 0) {
    int cellId = randomGenerator(m_n * m_n) - 1;
    // System.out.println(cellId);
    // extract coordinates i and j
    int i = (cellId / m_n);
    int j = cellId % 9;
    if (j != 0) {
      j = j - 1;
    }
    // System.out.println(i+" "+j);
    if (m_matrix[i][j] != 0) {
      count--;
      m_matrix[i][j] = 0;
    }
  }
}
