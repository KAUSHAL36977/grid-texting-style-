#include <iostream>
#include <map>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

// Grid size
const int GRID_SIZE = 10;

// Define a structure to represent grid coordinates
struct GridPosition {
    char col;  // Columns from A to J
    int row;   // Rows from 1 to 10

    // Custom comparison for std::map ordering
    bool operator<(const GridPosition& other) const {
        if (col == other.col)
            return row < other.row;
        return col < other.col;
    }
};

// Function to display the grid
void displayGrid(const map<GridPosition, string>& grid) {
    cout << "   ";
    for (char col = 'A'; col < 'A' + GRID_SIZE; col++) {
        cout << col << "   ";
    }
    cout << "\n";

    for (int row = 1; row <= GRID_SIZE; row++) {
        cout << setw(2) << row << " ";
        for (char col = 'A'; col < 'A' + GRID_SIZE; col++) {
            GridPosition pos = {col, row};
            if (grid.count(pos)) {
                cout << "[X] ";
            } else {
                cout << "[ ] ";
            }
        }
        cout << endl;
    }
    cout << "Your grid\n";
}

int main() {
    map<GridPosition, string> grid;  // Map to store messages at (col, row)
    int choice;

    cout << "Welcome to the 10x10 Grid Messaging System!\n";

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add a message\n";
        cout << "2. View a message\n";
        cout << "3. Display the grid\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            char col;
            int row;
            string message;
            cout << "Enter column (A-J): ";
            cin >> col;
            cout << "Enter row (1-10): ";
            cin >> row;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear input buffer
            cout << "Enter your message: ";
            getline(cin, message);

            if (col < 'A' || col > 'J' || row < 1 || row > 10) {
                cout << "Invalid coordinates! Please try again.\n";
            } else {
                grid[{col, row}] = message;
                cout << "Message stored at (" << col << ", " << row << ").\n";
            }
        } 
        
        else if (choice == 2) {
            char col;
            int row;
            cout << "Enter column (A-J) to view: ";
            cin >> col;
            cout << "Enter row (1-10) to view: ";
            cin >> row;

            auto it = grid.find({col, row});
            if (it != grid.end()) {
                cout << "Message at (" << col << ", " << row << "): " << it->second << endl;
            } else {
                cout << "No message found at the specified location.\n";
            }
        } 
        
        else if (choice == 3) {
            displayGrid(grid);
        } 
        
        else if (choice == 4) {
            cout << "Exiting the program.\n";
            break;
        } 
        
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
