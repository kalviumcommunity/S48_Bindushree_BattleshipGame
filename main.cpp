#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Ship {
public:
    int x, y;
    bool sunk;

    Ship(int x, int y) : x(x), y(y), sunk(false) {}
};

class Board {
private:
    std::vector<std::vector<char>> grid;
    std::vector<Ship> ships;
    int size;

public:
    Board(int size) : size(size), grid(size, std::vector<char>(size, '-')) {}

    void placeShip(int x, int y) {
        ships.emplace_back(x, y);
        grid[x][y] = 'S';
    }

    bool attack(int x, int y) {
        if (x < 0 || x >= size || y < 0 || y >= size) {
            std::cout << "Out of bounds!\n";
            return false;
        }

        if (grid[x][y] == 'S') {
            grid[x][y] = 'X';
            std::cout << "Hit at (" << x << ", " << y << ")!\n";
            for (auto& ship : ships) {
                if (ship.x == x && ship.y == y) ship.sunk = true;
            }
            return true;
        }

        if (grid[x][y] == 'X' || grid[x][y] == 'O') {
            std::cout << "Already attacked (" << x << ", " << y << ").\n";
        } else {
            grid[x][y] = 'O';
            std::cout << "Miss at (" << x << ", " << y << ").\n";
        }
        return false;
    }

    void printBoard() const {
        for (const auto& row : grid) {
            for (char cell : row) {
                std::cout << cell << ' ';
            }
            std::cout << '\n';
        }
    }

    bool allShipsSunk() const {
        for (const auto& ship : ships) {
            if (!ship.sunk) return false;
        }
        return true;
    }
};

void playGame(Board& board) {
    int x, y;
    while (!board.allShipsSunk()) {
        board.printBoard();
        std::cout << "Enter coordinates to attack (x y): ";
        std::cin >> x >> y;
        board.attack(x, y);
    }
    std::cout << "All ships sunk! You win!\n";
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    Board board(5);
    int numShips = 3;

    for (int i = 0; i < numShips; ++i) {
        int x, y;
        do {
            x = rand() % 5;
            y = rand() % 5;
        } while (board.attack(x, y)); // Use attack to check if the cell is already occupied
        board.placeShip(x, y);
    }

    playGame(board);

    return 0;
}
