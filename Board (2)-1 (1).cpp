#include "Board.h"
#include <iostream>
#include <cstdlib> 
#include <ctime>   

Board::Board() {
    srand(time(nullptr)); 
    initGrid();
}

void Board::initGrid() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            grid[i][j] = '.';  
        }
    }
}

bool Board::canPlaceBoat(int r, int c, int size, int dir) const {
    if ((dir == 0 && c + size > 10) || (dir == 1 && r + size > 10)) return false; 
    for (int i = 0; i < size; i++) {
        if (grid[r][c] != '.') return false;
        dir == 0 ? c++ : r++;
    }
    return true;
}

bool Board::setBoat(int size, const std::string& name, std::vector<Boat>& boats) {
    for (int attempts = 0; attempts < 100; attempts++) {
        int row = rand() % 10;
        int col = rand() % 10;
        int dir = rand() % 2;  

        if (canPlaceBoat(row, col, size, dir)) {
            std::vector<int> rows, cols;
            for (int i = 0; i < size; i++) {
                grid[row][col] = name[0];  
                rows.push_back(row);
                cols.push_back(col);
                dir == 0 ? col++ : row++;
            }
            boats.push_back(Boat(size, rows, cols, name, dir == 0 ? 'H' : 'V'));
            return true;
        }
    }
    return false;
}

void Board::printGameBoard() const {
    std::cout << "   ";
    for (int i = 0; i < 10; i++) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    std::cout << "  +-------------------------+\n";
    
    for (int i = 0; i < 10; i++) {
        std::cout << i << " |";  
        for (int j = 0; j < 10; j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << "|\n";
    }
    std::cout << "  +-------------------------+\n";
}


bool Board::attack(int row, int col, std::vector<Boat>& boats) {
    if (row < 0 || row >= 10 || col < 0 || col >= 10) {
        std::cout << "Attack out of bounds!\n";
        return false;
    }
    char& cell = grid[row][col];
    if (cell == 'X' || cell == 'O') {
        std::cout << "You already attacked here!\n";
        return false;
    }
    for (Boat& boat : boats) {
        if (boat.isHit(row, col)) {
            cell = 'X';
            boat.setHit();
            if (boat.checkSunk()) {
                std::cout << "Sunk " << boat.getName() << "!\n";
            }
            return true;
        }
    }
    cell = 'O'; 
    return false;
}

bool Board::checkGameOver(const std::vector<Boat>& boats) const {
    for (const Boat& boat : boats) {
        if (!boat.checkSunk()) {
            return false;
        }
    }
    return true;
}
