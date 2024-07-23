#include <iostream>
#include <iomanip>

#define SIZE 9

using namespace std;

class Sudoku {
private:
    int puzzle[SIZE][SIZE];

public:
    Sudoku() {
        // Initialize the puzzle with the initial values
        int initialPuzzle[SIZE][SIZE] = {
            {9, 8, 7, 4, 0, 3, 0, 2, 6},
            {0, 0, 0, 2, 0, 6, 9, 0, 0},
            {0, 0, 5, 0, 0, 0, 0, 0, 1},
            {0, 0, 1, 0, 0, 8, 0, 0, 7},
            {0, 9, 3, 0, 6, 0, 8, 4, 0},
            {8, 0, 0, 3, 0, 7, 6, 0, 0},
            {5, 0, 0, 0, 0, 2, 1, 6, 0},
            {0, 0, 9, 6, 0, 4, 0, 0, 0},
            {4, 7, 0, 5, 0, 0, 0, 9, 3}
        };

        // Copy the values to the puzzle
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                puzzle[i][j] = initialPuzzle[i][j];
            }
        }
    }

    void printPuzzle() {
        cout << endl;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                cout << setw(2) << puzzle[i][j] << " ";
                if ((j + 1) % 3 == 0 && j < SIZE - 1)
                    cout << "| ";
            }
            cout << endl;
            if ((i + 1) % 3 == 0 && i < SIZE - 1)
                cout << "-------------------------------" << endl;
        }
        cout << endl;
    }

    bool isValid(int row, int col, int num) {
        for (int i = 0; i < SIZE; i++) {
            if (puzzle[row][i] == num || puzzle[i][col] == num)
                return false;
        }

        int startRow = row - row % 3;
        int startCol = col - col % 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (puzzle[i + startRow][j + startCol] == num)
                    return false;
            }
        }

        return true;
    }

    bool solve() {
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                if (puzzle[row][col] == 0) {
                    for (int num = 1; num <= SIZE; num++) {
                        if (isValid(row, col, num)) {
                            puzzle[row][col] = num;
                            if (solve())
                                return true;
                            puzzle[row][col] = 0;
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

    bool isPuzzleSolved() {
        // Check if there are any empty cells
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (puzzle[i][j] == 0) {
                    return false; // Puzzle is not solved
                }
            }
        }
        return true; // Puzzle is solved
    }

    void playGame() {
        char c;
        int row, col, num;

        bool puzzleSolved = false;

        do {
            cout << "Enter row, column, and value (0 to quit): ";
            cin >> row >> col >> num;

            if (row == 0 || col == 0 || num == 0) {
                cout << "\nQuitting the game. Here's the solution:\n";
                solve();
                printPuzzle();
                break;
            }

            if (row < 1 || row > SIZE || col < 1 || col > SIZE || num < 1 || num > SIZE) {
                cout << "\nInvalid input. Please try again.\n";
            } else if (puzzle[row - 1][col - 1] == 0 && isValid(row - 1, col - 1, num)) {
                puzzle[row - 1][col - 1] = num;
                printPuzzle();

                puzzleSolved = isPuzzleSolved();
                if (puzzleSolved) {
                    cout << "Congratulations! You've completed the Sudoku puzzle!\n";
                    break;
                }
            } else {
                cout << "\nInvalid move. Please try again.\n";
            }

            // Clear the input buffer
            while ((c = getchar()) != '\n' && c != EOF);

        } while (1);
    }
};

int main() {
    cout << "SUDOKU GAME" << endl;
    cout << "RULES:" << endl;
    cout << "1. The objective of Sudoku is to fill a 9x9 grid made of small squares so that each row, each column, and each full 3x3 squares use the numbers 1-9." << endl;
    cout << "2. While solving the sudoku puzzle you can only use each number one time in the square, column, and row." << endl;
    cout << "3. You can only insert numbers in the squares that have value \"0\"" << endl;
    cout << "4. If you give up and want to see a solved puzzle please press \"q\" key" << endl;
    cout << "GOOD LUCK!\n";

    Sudoku sudoku;
    cout << "Initial Puzzle:\n";
    sudoku.printPuzzle();
    sudoku.playGame();

    return 0;}
