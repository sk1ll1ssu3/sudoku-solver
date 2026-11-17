#include <cassert>
#include <iostream>

class Sudoku {
private:
  int board[9][9] = {0};
  bool isValid{false};

  bool solveHelper(int i, int j) {
    if (i == 9)
      return true;
    if (j == 9)
      return solveHelper(i + 1, 0);
    if (board[i][j] != 0)
      return solveHelper(i, j + 1);
    for (int elem{1}; elem <= 9; ++elem) {
      if (canPlace(i, j, elem)) {
        board[i][j] = elem;
        if (solveHelper(i, j + 1))
          return true;
        board[i][j] = 0;
      }
    }
    return false;
  }

  static bool validateBoard(const int board[9][9]) {
    for (int i{0}; i < 9; ++i) {
      for (int j{0}; j < 9; ++j) {
        int v{board[i][j]};
        if (v == 0)
          continue;
        if (v < 1 || v > 9)
          return false;
        bool cp{true};
        for (int row{0}; row < 9; ++row) {
          if (row == i)
            continue;
          if (board[row][j] == v) {
            cp = false;
            break;
          }
        }
        for (int col{0}; col < 9; ++col) {
          if (col == j)
            continue;
          if (board[i][col] == v) {
            cp = false;
            break;
          }
        }
        int startRow{(i / 3) * 3}, startCol{(j / 3) * 3};
        for (int r{startRow}; r < startRow + 3; ++r) {
          for (int c{startCol}; c < startCol + 3; ++c) {
            if (r == i && c == j)
              continue;
            if (board[r][c] == v) {
              cp = false;
              break;
            }
          }
          if (!cp)
            break;
        }
        if (!cp) {
          return false;
        }
      }
    }
    return true;
  }

public:
  Sudoku(const int board[9][9]) {
    isValid = validateBoard(board);
    if (isValid)
      for (int i{0}; i < 9; ++i) {
        for (int j{0}; j < 9; ++j)
          this->board[i][j] = board[i][j];
      }
  }

  bool canPlace(int x, int y, int v) const {
    assert(v >= 1 && v <= 9);
    assert(x >= 0 && y >= 0);
    assert(x < 9 && y < 9);
    for (int row{0}; row < 9; ++row) {
      if (board[row][y] == v)
        return false;
    }
    for (int col{0}; col < 9; ++col) {
      if (board[x][col] == v)
        return false;
    }
    int startRow{(x / 3) * 3}, startCol{(y / 3) * 3};
    for (int i{startRow}; i < startRow + 3; ++i) {
      for (int j{startCol}; j < startCol + 3; ++j) {
        if (board[i][j] == v)
          return false;
      }
    }
    return true;
  }

  bool solve() { return isValid && solveHelper(0, 0); }

  void printBoard() const {
    for (int i{0}; i < 9; ++i) {
      for (int j{0}; j < 9; ++j) {
        std::cout << board[i][j] << ' ';
      }
      std::cout << '\n';
    }
  }
};

int main() {
  std::cout << "Sudoku Solver!\n";
  std::cout << "Enter the board with blank places marked with 0:\n";
  int board[9][9];
  for (int i{0}; i < 9; ++i) {
    for (int j{0}; j < 9; ++j)
      std::cin >> board[i][j];
  }
  Sudoku sudokuBoard(board);
  if (sudokuBoard.solve()) {
    std::cout << "The Solved Board:\n";
    sudokuBoard.printBoard();
  } else
    std::cerr << "The board could not be solved.\n";
}
