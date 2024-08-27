#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Class to represent a Ship
class Ship {
private:
    int x, y;
    bool sunk;

public:
    Ship(int x, int y) : x(x), y(y), sunk(false) {}

    int getX() const { return x; }
    int getY() const { return y; }
    bool isSunk() const { return sunk; }

    void sink() { sunk = true; }
};

// Class to represent the Game Board
class Board {
private:
    std::vector<std::vector<char>> grid;
    std::vector<Ship> ships;
    int size;

public:
    Board(int size) : size(size) {
        grid.resize(size, std::vector<char>(size, '-'));
    }

    void placeShip(int x, int y) {
        ships.emplace_back(x, y);
        grid[x][y] = 'S';
    }

    bool attack(int x, int y) {
        if (grid[x][y] == 'S') {
            grid[x][y] = 'X';
            for (auto& ship : ships) {
                if (ship.getX() == x && ship.getY() == y) {
                    ship.sink();
                    std::cout << "Hit! Ship at (" << x << ", " << y << ") has been sunk!\n";
                    return true;
                }
            }
        } else {
            grid[x][y] = 'O';
            std::cout << "Miss at (" << x << ", " << y << ")\n";
        }
        return false;
    }

    void printBoard() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                std::cout << grid[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    bool allShipsSunk() const {
        for (const auto& ship : ships) {
            if (!ship.isSunk()) return false;
        }
        return true;
    }
};

// Function to play the game
void playGame(Board& board) {
    int x, y;
    while (!board.allShipsSunk()) {
        board.printBoard();
        std::cout << "Enter coordinates to attack (x y): ";
        std::cin >> x >> y;
        board.attack(x, y);
    }
    std::cout << "Congratulations! You've sunk all the ships!\n";
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    const int boardSize = 5;
    const int numShips = 3;

    Board board(boardSize);

    // Randomly place ships
    for (int i = 0; i < numShips; ++i) {
        int x = rand() % boardSize;
        int y = rand() % boardSize;
        board.placeShip(x, y);
    }

    playGame(board);

    return 0;
}
