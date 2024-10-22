#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <memory>  // For smart pointers

class Ship {
private:
    int x, y;
    bool sunk;

    // Static variables to track total and sunk ships
    static int totalShips;
    static int sunkShips;

public:
    // Default constructor
    Ship() : x(0), y(0), sunk(false) {
        totalShips++;  // Increment totalShips when a Ship is created
    }

    // Parameterized constructor
    Ship(int x, int y) : x(x), y(y), sunk(false) {
        totalShips++;  // Increment totalShips when a Ship is created
    }

    // Accessor (getter) for x
    int getX() const { return x; }

    // Mutator (setter) for x
    void setX(int newX) { x = newX; }

    // Accessor (getter) for y
    int getY() const { return y; }

    // Mutator (setter) for y
    void setY(int newY) { y = newY; }

    // Accessor (getter) for sunk
    bool isSunk() const { return sunk; }

    // Mutator (method) to sink the ship
    void sink() {
        if (!sunk) {  // Only increment sunkShips if it's the first time sinking this ship
            sunk = true;
            sunkShips++;  // Increment sunkShips when a Ship is sunk
        }
    }

    // Static function to get the total number of ships
    static int getTotalShips() {
        return totalShips;
    }

    // Static function to get the number of sunk ships
    static int getSunkShips() {
        return sunkShips;
    }
};

// Initialize static variables
int Ship::totalShips = 0;
int Ship::sunkShips = 0;

class Board {
private:
    std::vector<std::vector<char>> grid;
    std::vector<std::unique_ptr<Ship>> ships;  // Now using smart pointers to manage Ship objects
    int size;

public:
    Board(int size) : size(size), grid(size, std::vector<char>(size, '-')) {}

    // Accessor (getter) for size
    int getSize() const { return size; }

    // Mutator (method) to add a ship to the board
    bool placeShip(std::unique_ptr<Ship> ship) {
        int x = ship->getX();
        int y = ship->getY();

        if (grid[x][y] == 'S') {
            return false;  // Ship already placed at this location
        }

        this->ships.push_back(std::move(ship));
        this->grid[x][y] = 'S';
        return true;
    }

    // Mutator (method) to handle an attack on the board
    bool attack(int x, int y) {
        if (x < 0 || x >= size || y < 0 || y >= size) {
            std::cout << "Out of bounds!\n";
            return false;
        }

        if (grid[x][y] == 'S') {
            grid[x][y] = 'X';
            std::cout << "Hit at (" << x << ", " << y << ")!\n";
            for (auto& ship : ships) {
                if (ship->getX() == x && ship->getY() == y) {
                    ship->sink();
                }
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

    // Accessor (getter) to check if all ships are sunk
    bool allShipsSunk() const {
        return Ship::getSunkShips() == Ship::getTotalShips();  // Check if all ships are sunk
    }

    // Print the current state of the board
    void printBoard() const {
        for (const auto& row : grid) {
            for (char cell : row) {
                std::cout << cell << ' ';
            }
            std::cout << '\n';
        }
    }
};

void playGame(Board& board) {
    int x, y;
    while (!board.allShipsSunk()) {
        board.printBoard();
        std::cout << "Enter coordinates to attack (x y): ";
        std::cin >> x >> y;
        board.attack(x, y);
        std::cout << "Ships remaining: " << Ship::getTotalShips() - Ship::getSunkShips() << "\n";
    }
    std::cout << "All ships sunk! You win!\n";
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int boardSize = 5;  // Initialize boardSize
    int numShips = 3;

    Board board(boardSize);  // Only one instance of Board

    // Dynamically allocate memory for Ship objects and use accessors/mutators
    for (int i = 0; i < numShips; ++i) {
        bool placed = false;
        while (!placed) {
            int x = rand() % boardSize;
            int y = rand() % boardSize;
            // Use parameterized constructor
            auto newShip = std::make_unique<Ship>(x, y);  
            placed = board.placeShip(std::move(newShip));  // Only place ship if the spot is free
        }
    }

    playGame(board);

    std::cout << "Total ships created: " << Ship::getTotalShips() << "\n";
    std::cout << "Total ships sunk: " << Ship::getSunkShips() << "\n";

    return 0;
}
