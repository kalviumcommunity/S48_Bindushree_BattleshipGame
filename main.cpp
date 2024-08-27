#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Ship {
public:
    int x, y;
    bool sunk;

<<<<<<< HEAD
public:
    Ship(int x = 0, int y = 0) : x(x), y(y), sunk(false) {}

    int getX() const { return this->x; }
    int getY() const { return this->y; }
    bool isSunk() const { return this->sunk; }

    void sink() { this->sunk = true; }

    void setPosition(int newX, int newY) {
        this->x = newX;
        this->y = newY;
    }
=======
    Ship(int x, int y) : x(x), y(y), sunk(false) {}
>>>>>>> 383aaa0746ab520918a0b727de79c5b2b7406a9c
};

class Board {
private:
    std::vector<std::vector<char>> grid;
    std::vector<Ship> ships;
    int size;

public:
    Board(int size) : size(size), grid(size, std::vector<char>(size, '-')) {}

<<<<<<< HEAD
    void placeShip(Ship& ship) {
        int x = ship.getX();
        int y = ship.getY();
        this->ships.push_back(ship);
        this->grid[x][y] = 'S';
=======
    void placeShip(int x, int y) {
        ships.emplace_back(x, y);
        grid[x][y] = 'S';
>>>>>>> 383aaa0746ab520918a0b727de79c5b2b7406a9c
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

<<<<<<< HEAD
    Board board(boardSize);

    // Create an array of Ship objects
    Ship ships[numShips];

    // Randomly assign positions to the ships
    for (int i = 0; i < numShips; ++i) {
        int x = rand() % boardSize;
        int y = rand() % boardSize;
        ships[i].setPosition(x, y);
        board.placeShip(ships[i]);
=======
    for (int i = 0; i < numShips; ++i) {
        int x, y;
        do {
            x = rand() % 5;
            y = rand() % 5;
        } while (board.attack(x, y)); // Use attack to check if the cell is already occupied
        board.placeShip(x, y);
>>>>>>> 383aaa0746ab520918a0b727de79c5b2b7406a9c
    }

    playGame(board);

    return 0;
}
