#include <iostream>
#include <map>
#include <string>
#include <iomanip>
#include <limits>
#include <vector>

using namespace std;

// ------------------------------------------------------------
// Configuration
// ------------------------------------------------------------
static const bool USE_COLOR = true;     // Set to false to disable colored output
static const bool USE_ASCII_ART = false; // Set to true to use ASCII borders instead of Unicode

// Grid size
const int GRID_SIZE = 10;

// ------------------------------------------------------------
// Utility: ANSI Color Codes
// ------------------------------------------------------------
namespace Color {
    const string RESET  = "\033[0m";
    const string RED    = "\033[31m";
    const string GREEN  = "\033[32m";
    const string YELLOW = "\033[33m";
    const string BLUE   = "\033[34m";
    const string CYAN   = "\033[36m";
    const string WHITE  = "\033[37m";
}

// ------------------------------------------------------------
// Box/ASCII Drawing Characters
// ------------------------------------------------------------
struct BoxChars {
    string topLeft;
    string topRight;
    string bottomLeft;
    string bottomRight;
    string topT;
    string bottomT;
    string leftT;
    string rightT;
    string cross;
    string horizontal;
    string vertical;
};

BoxChars unicodeBox = {
    "┌", "┐", "└", "┘", "┬", "┴", "├", "┤", "┼", "─", "│"
};

BoxChars asciiBox = {
    "+", "+", "+", "+", "+", "+", "+", "+", "+", "-", "|"
};

// ------------------------------------------------------------
// Define a structure to represent grid coordinates
// Columns: A-J, Rows: 1-10
// ------------------------------------------------------------
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

// ------------------------------------------------------------
// Function to get the current box characters (Unicode or ASCII)
// ------------------------------------------------------------
BoxChars getBoxChars() {
    return (USE_ASCII_ART ? asciiBox : unicodeBox);
}

// ------------------------------------------------------------
// Function to colorize text (if USE_COLOR is true)
// ------------------------------------------------------------
string colorize(const string& text, const string& colorCode) {
    if (USE_COLOR) {
        return colorCode + text + Color::RESET;
    }
    return text;
}

// ------------------------------------------------------------
// Function to display the grid with box-drawing characters
// ------------------------------------------------------------
void displayGrid(const map<GridPosition, string>& grid) {
    BoxChars box = getBoxChars();

    // Print column headers
    cout << "    ";
    for (char c = 'A'; c < 'A' + GRID_SIZE; c++) {
        cout << setw(3) << c << " ";
    }
    cout << "\n";

    // Top border
    cout << "   " << box.topLeft;
    for (int col = 0; col < GRID_SIZE; col++) {
        cout << string(3, box.horizontal[0]);
        if (col < GRID_SIZE - 1) cout << box.topT;
    }
    cout << box.topRight << "\n";

    // Each row
    for (int row = 1; row <= GRID_SIZE; row++) {
        // Print row number
        cout << setw(2) << row << " " << box.vertical;

        // Cells
        for (int colIndex = 0; colIndex < GRID_SIZE; colIndex++) {
            char colLetter = 'A' + colIndex;
            GridPosition pos = {colLetter, row};
            if (grid.count(pos)) {
                // Mark occupied cells
                cout << colorize(" X ", Color::GREEN);
            } else {
                cout << "   ";
            }
            cout << box.vertical;
        }
        cout << "\n";

        // Horizontal separator (bottom border if last row)
        if (row < GRID_SIZE) {
            cout << "   " << box.leftT;
            for (int col = 0; col < GRID_SIZE; col++) {
                cout << string(3, box.horizontal[0]);
                if (col < GRID_SIZE - 1) cout << box.cross;
            }
            cout << box.rightT << "\n";
        } else {
            // Bottom border
            cout << "   " << box.bottomLeft;
            for (int col = 0; col < GRID_SIZE; col++) {
                cout << string(3, box.horizontal[0]);
                if (col < GRID_SIZE - 1) cout << box.bottomT;
            }
            cout << box.bottomRight << "\n";
        }
    }

    cout << "Your grid\n";
}

// ------------------------------------------------------------
// Function to add a message
// ------------------------------------------------------------
void addMessage(map<GridPosition, string>& grid) {
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

    // Convert to uppercase if user typed a-j
    if (col >= 'a' && col <= 'j') {
        col = static_cast<char>(col - 'a' + 'A');
    }

    if (col < 'A' || col > 'J' || row < 1 || row > 10) {
        cout << colorize("Invalid coordinates! Please try again.\n", Color::RED);
    } else {
        grid[{col, row}] = message;
        cout << colorize("Message stored at (", Color::CYAN)
             << col << ", " << row << ").\n";
    }
}

// ------------------------------------------------------------
// Function to view a message
// ------------------------------------------------------------
void viewMessage(const map<GridPosition, string>& grid) {
    char col;
    int row;
    cout << "Enter column (A-J) to view: ";
    cin >> col;
    cout << "Enter row (1-10) to view: ";
    cin >> row;

    // Convert to uppercase if user typed a-j
    if (col >= 'a' && col <= 'j') {
        col = static_cast<char>(col - 'a' + 'A');
    }

    auto it = grid.find({col, row});
    if (it != grid.end()) {
        cout << colorize("Message at (", Color::CYAN)
             << col << ", " << row << "): " 
             << colorize(it->second, Color::YELLOW) << endl;
    } else {
        cout << colorize("No message found at the specified location.\n", Color::RED);
    }
}

// ------------------------------------------------------------
// Function to update an existing message
// ------------------------------------------------------------
void updateMessage(map<GridPosition, string>& grid) {
    char col;
    int row;
    cout << "Enter column (A-J) to update: ";
    cin >> col;
    cout << "Enter row (1-10) to update: ";
    cin >> row;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear input buffer

    // Convert to uppercase if user typed a-j
    if (col >= 'a' && col <= 'j') {
        col = static_cast<char>(col - 'a' + 'A');
    }

    auto it = grid.find({col, row});
    if (it != grid.end()) {
        cout << "Current message at (" << col << ", " << row << "): "
             << it->second << "\n";
        cout << "Enter new message: ";
        string newMessage;
        getline(cin, newMessage);
        it->second = newMessage;
        cout << colorize("Message updated!\n", Color::GREEN);
    } else {
        cout << colorize("No message found at the specified location.\n", Color::RED);
    }
}

// ------------------------------------------------------------
// Function to remove a message
// ------------------------------------------------------------
void removeMessage(map<GridPosition, string>& grid) {
    char col;
    int row;
    cout << "Enter column (A-J) to remove: ";
    cin >> col;
    cout << "Enter row (1-10) to remove: ";
    cin >> row;

    // Convert to uppercase if user typed a-j
    if (col >= 'a' && col <= 'j') {
        col = static_cast<char>(col - 'a' + 'A');
    }

    auto it = grid.find({col, row});
    if (it != grid.end()) {
        grid.erase(it);
        cout << colorize("Message removed from (", Color::CYAN)
             << col << ", " << row << ").\n";
    } else {
        cout << colorize("No message found at the specified location.\n", Color::RED);
    }
}

// ------------------------------------------------------------
// Function to list all messages
// ------------------------------------------------------------
void listAllMessages(const map<GridPosition, string>& grid) {
    if (grid.empty()) {
        cout << colorize("No messages stored.\n", Color::RED);
        return;
    }
    cout << colorize("All stored messages:\n", Color::CYAN);
    for (const auto& entry : grid) {
        cout << "(" << entry.first.col << ", " << entry.first.row << "): "
             << colorize(entry.second, Color::YELLOW) << "\n";
    }
}

// ------------------------------------------------------------
// Main function
// ------------------------------------------------------------
int main() {
    map<GridPosition, string> grid;  // Map to store messages at (col, row)
    int choice;

    cout << colorize("Welcome to the 10x10 Grid Messaging System!\n", Color::BLUE);

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add a message\n";
        cout << "2. View a message\n";
        cout << "3. Display the grid\n";
        cout << "4. Update a message\n";
        cout << "5. Remove a message\n";
        cout << "6. List all messages\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (!cin) {
            // Handle invalid input (non-integer)
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << colorize("Invalid choice. Please try again.\n", Color::RED);
            continue;
        }

        switch (choice) {
            case 1:
                addMessage(grid);
                break;
            case 2:
                viewMessage(grid);
                break;
            case 3:
                displayGrid(grid);
                break;
            case 4:
                updateMessage(grid);
                break;
            case 5:
                removeMessage(grid);
                break;
            case 6:
                listAllMessages(grid);
                break;
            case 7:
                cout << colorize("Exiting the program.\n", Color::BLUE);
                return 0;
            default:
                cout << colorize("Invalid choice. Please try again.\n", Color::RED);
        }
    }

    return 0;
}
