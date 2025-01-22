
#include <iostream>
#include <map>
#include <string>
#include <limits>

using namespace std;

// Define a structure to represent grid coordinates
struct GridPosition {
    long long x, y;

    // Custom comparison for std::map ordering
    bool operator<(const GridPosition& other) const {
        if (x == other.x)
            return y < other.y;
        return x < other.x;
    }
};

int main() {
    map<GridPosition, string> grid;  // Map to store messages at (x, y)
    int choice;
    
    cout << "Welcome to the 10^10 Grid Messaging System!\n";
    
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add a message\n";
        cout << "2. View a message\n";
        cout << "3. Display all messages\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            long long x, y;
            string message;
            cout << "Enter X coordinate (0 to 10^10): ";
            cin >> x;
            cout << "Enter Y coordinate (0 to 10^10): ";
            cin >> y;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear input buffer
            cout << "Enter your message: ";
            getline(cin, message);

            if (x < 0 || y < 0 || x >= 1e10 || y >= 1e10) {
                cout << "Invalid coordinates! Please try again.\n";
            } else {
                grid[{x, y}] = message;
                cout << "Message stored at (" << x << ", " << y << ").\n";
            }
        } 
        
        else if (choice == 2) {
            long long x, y;
            cout << "Enter X coordinate to view: ";
            cin >> x;
            cout << "Enter Y coordinate to view: ";
            cin >> y;

            auto it = grid.find({x, y});
            if (it != grid.end()) {
                cout << "Message at (" << x << ", " << y << "): " << it->second << endl;
            } else {
                cout << "No message found at the specified location.\n";
            }
        } 
        
        else if (choice == 3) {
            if (grid.empty()) {
                cout << "No messages stored.\n";
            } else {
                cout << "Stored messages:\n";
                for (const auto& entry : grid) {
                    cout << "Location (" << entry.first.x << ", " << entry.first.y << "): " 
                         << entry.second << endl;
                }
            }
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
