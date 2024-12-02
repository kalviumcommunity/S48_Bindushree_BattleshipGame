#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <memory>

// Base class: Ship
class Ship {
private:
    int x, y;
    bool sunk;
    static int totalShips;
    static int sunkShips;

public:
    Ship() : x(0), y(0), sunk(false) { totalShips++; }
    Ship(int x, int y) : x(x), y(y), sunk(false) { totalShips++; }

    int getX() const { return x; }
    void setX(int newX) { x = newX; }
    int getY() const { return y; }
    void setY(int newY) { y = newY; }
    bool isSunk() const { return sunk; }

    // Method Overloading: sink method with and without damage
    void sink() {
        if (!sunk) {
            sunk = true;
            sunkShips++;
            std::cout << "Ship at (" << x << ", " << y << ") is sunk.\n";
        }
    }
    void sink(int damage) {
        if (!sunk) {
            sunk = true;
            sunkShips++;
            std::cout << "Ship at (" << x << ", " << y << ") is sunk due to " << damage << " damage!\n";
        }
    }

    // Static methods to track ship statistics
    static int getTotalShips() { return totalShips; }
    static int getSunkShips() { return sunkShips; }
};

// Initialize static variables
int Ship::totalShips = 0;
int Ship::sunkShips = 0;

// Derived class: Submarine
class Submarine : public Ship {
private:
    bool submerged;

public:
    Submarine(int x, int y) : Ship(x, y), submerged(false) {}
    void dive() {
        submerged = true;
        std::cout << "Submarine dove underwater.\n";
    }
    bool isSubmerged() const { return submerged; }
};

// Auxiliary class: Armored
class Armored {
private:
    int armor;

public:
    Armored(int armor = 100) : armor(armor) {}
    int getArmor() const { return armor; }
    void takeDamage(int damage) {
        armor -= damage;
        if (armor < 0) armor = 0;
        std::cout << "Armor reduced to " << armor << "\n";
    }
};

// Derived class: Battleship
class Battleship : public Ship, public Armored {
public:
    Battleship(int x, int y, int armor) : Ship(x, y), Armored(armor) {}
    void fire() { std::cout << "Battleship fired its cannons!\n"; }
};

// Game Board class
class Board {
private:
    std::vector<std::vector<char>> grid;
    std::vector<std::unique_ptr<Ship>> ships;
    int size;

public:
    Board(int size) : size(size), grid(size, std::vector<char>(size, '-')) {}

    int getSize() const { return size; }

    bool placeShip(std::unique_ptr<Ship> ship) {
        int x = ship->getX();
        int y = ship->getY();
        if (grid[x][y] == 'S') return false;
        ships.push_back(std::move(ship));
        grid[x][y] = 'S';
        return true;
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
                if (ship->getX() == x && ship->getY() == y) ship->sink(50); // Demonstrating overloaded sink
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

    bool allShipsSunk() const { return Ship::getSunkShips() == Ship::getTotalShips(); }

    void printBoard() const {
        for (const auto& row : grid) {
            for (char cell : row) std::cout << cell << ' ';
            std::cout << '\n';
        }
    }
};

// Gameplay function
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

// Main function
int main() {
    srand(static_cast<unsigned int>(time(0)));
    int boardSize = 5;
    int numShips = 3;

    Board board(boardSize);

    // Place a Battleship (Multiple Inheritance)
    auto battleship = std::make_unique<Battleship>(rand() % boardSize, rand() % boardSize, 200);
    board.placeShip(std::move(battleship));

    // Place Submarines (Single Inheritance)
    for (int i = 0; i < numShips; ++i) {
        bool placed = false;
        while (!placed) {
            int x = rand() % boardSize;
            int y = rand() % boardSize;
            auto newSub = std::make_unique<Submarine>(x, y);
            placed = board.placeShip(std::move(newSub));
        }
    }

    playGame(board);

    std::cout << "Total ships created: " << Ship::getTotalShips() << "\n";
    std::cout << "Total ships sunk: " << Ship::getSunkShips() << "\n";

    return 0;
}
