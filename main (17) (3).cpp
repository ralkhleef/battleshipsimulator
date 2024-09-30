#include <iostream>
#include <vector>
#include <limits>  // For std::numeric_limits
#include "Board.h"
#include "Boat.h"

using namespace std; // Simplifies code by removing the need to prefix std:: everywhere

void printHelp() {
    cout << "Welcome to Battleship!\n";
    cout << "Instructions:\n";
    cout << "- Enter coordinates directly (e.g., 2 3) to attack.\n";
    cout << "- Type 'c' to clear and show the game board again.\n";
    cout << "- Type 'h' for help.\n";
    cout << "- Type 'q' to quit the game.\n";
}

void getCoordinates(int& row, int& col) {
    cout << "Enter attack coordinates (row col): ";
    cin >> row >> col;
}

int main() {
    Board board; // Create a game board instance.
    vector<Boat> boatList; // List to store the boats.

    board.initGrid(); // Initialize the game grid.
    board.setBoat(5, "Aircraft Carrier", boatList);
    board.setBoat(4, "Battleship", boatList);
    board.setBoat(3, "Destroyer", boatList);
    board.setBoat(3, "Submarine", boatList);
    board.setBoat(2, "Frigate", boatList);

    cout << "Welcome to Battleship!\n";
    printHelp();
    board.printGameBoard();

    string input;
    int row, col;
    bool gameOver = false;

    while (!gameOver) {
        cout << "\nEnter command or coordinates (row col): ";
        cin >> input;
        if (input == "c") {
            board.printGameBoard();
        } else if (input == "h") {
            printHelp();
        } else if (input == "q") {
            cout << "Thanks for playing! See you next time.\n";
            break;
        } else {
            cin.putback(input[0]);  // Put the first character back into the input stream
            if (cin >> row >> col) {
                if (!board.attack(row, col, boatList)) {
                    cout << "Miss! Try again.\n";
                } else {
                    cout << "Hit! You struck the " << boatList.back().getName() << "!\n";
                    if (boatList.back().checkSunk()) {
                        cout << "You've sunk the " << boatList.back().getName() << "!\n";
                    }
                }
                gameOver = board.checkGameOver(boatList);
                if (gameOver) {
                    cout << "Victory! All enemy ships have been destroyed!\n";
                }
            } else {
                cout << "Invalid input. Please enter two numbers for row and column.\n";
                cin.clear(); // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Skip to the next line
            }
        }
    }

    return 0;
}
