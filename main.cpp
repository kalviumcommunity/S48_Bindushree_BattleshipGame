#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Ship {
public:
    int x, y;
    bool sunk;

    // Static variables to track total and sunk ships
    static int totalShips;
    static int sunkShips;

public:
    // Constructor with default parameters
    Ship(int x = 0, int y = 0) : x(x), y(y), sunk(false) {
        totalShips++;  // Increment totalShips when a Ship is created
    }

    int getX() const { return this->x; }
    int getY() const { return this->y; }
    bool isSunk() const { return this->sunk; }

    void sink() {
        if (!this->sunk) {  // Only increment sunkShips if it's the first time sinking this ship
            this->sunk = true;
            sunkShips++;  // Increment sunkShips when a Ship is sunk
        }
    }

    void setPosition(int newX, int newY) {
        this->x = newX;
        this->y = newY;
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
    std::vector<Ship*> ships;  // Now storing pointers to Ship objects
    int size;

public:
    Board(int size) : size(size), grid(size, std::vector<char>(size, '-')) {}

    // Add ship to the board using a pointer to Ship
    void placeShip(Ship* ship) {
        int x = ship->getX();
        int y = ship->getY();
        this->ships.push_back(ship);
        this->grid[x][y] = 'S';
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
                if (ship->getX() == x && ship->getY() == y) ship->sink();
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
        return Ship::getSunkShips() == Ship::getTotalShips();  // Check if all ships are sunk
    }

    // Destructor to free dynamically allocated ships
    ~Board() {
        for (auto ship : ships) {
            delete ship;
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

    // Dynamically allocate memory for Ship objects
    for (int i = 0; i < numShips; ++i) {
        int x = rand() % boardSize;
        int y = rand() % boardSize;
        Ship* newShip = new Ship(x, y);  // Allocate new Ship
        board.placeShip(newShip);
    }

    playGame(board);

    std::cout << "Total ships created: " << Ship::getTotalShips() << "\n";
    std::cout << "Total ships sunk: " << Ship::getSunkShips() << "\n";

    return 0;
}


