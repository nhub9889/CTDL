#include "screen.h"
#include <initializer_list>
// Move cursor to specific position in the console
void gotoxy(int column, int line) {
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Change text color
void textColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Reset text color to default
void resetColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Default color (white)
}

// Draw a rectangular border around the menu
void veKhung(int x, int y, int chieuDai, int chieuRong) {
    textColor(6); // Choose color for border

    gotoxy(x, y);
    cout << char(201);  // Top-left corner
    for (int i = 0; i < chieuDai; i++) cout << char(205);  // Top horizontal line
    cout << char(187);  // Top-right corner

    for (int i = 1; i < chieuRong; i++) {
        gotoxy(x, y + i); cout << char(186);  // Left vertical line
        gotoxy(x + chieuDai + 1, y + i); cout << char(186);  // Right vertical line
    }

    gotoxy(x, y + chieuRong);
    cout << char(200);  // Bottom-left corner
    for (int i = 0; i < chieuDai; i++) cout << char(205);  // Bottom horizontal line
    cout << char(188);  // Bottom-right corner

    resetColor();  // Reset color after drawing
}

// Constructor: initializes the menu with items


Menu::Menu(int n,vector<string> arr, string t, int X, int Y, int D, int R):_numberOfItem(n), item(arr), title(t), x(X), y(Y), chieuDai(D), chieuRong(R) {}




// Destructor


// Get the number of items in the menu
int Menu::numberOfItem() {
    return _numberOfItem;
}



// Print the menu with the selected line highlighted
void Menu::printMenu(int selectedLine) {
    system("cls");
    veKhung(x - 1, y - 1, chieuDai, chieuRong); // Draw border around menu

    // Print title inside the border
    gotoxy(x + chieuDai/2 - title.size()/2, y);
    textColor(12);
    cout << title;
    resetColor(); // Reset to default color

    // Draw horizontal line below title
    gotoxy(x + chieuDai / 2 - 13, y + 1);
    for (int i = 0; i < 26; i++) {
        cout << "-";
    }

    // Print menu items, highlighting the selected item
    for (int i = 0; i < _numberOfItem; i++) {
        gotoxy(x, y + 3 + i);
        if (i == selectedLine) {
            textColor(14);  // Highlight color for selected item
            cout << ">> " << item[i];
            resetColor();
        }
        else {
            cout << "   " << item[i];
        }
    }
}

// Handle menu movement input
int Menu::Move() {
    char c = _getch();
    if ((int)c == -32) c = _getch();
    switch ((int)c) {
    case 80:
        return 1; // Down arrow
    case 72:
        return 2; // Up arrow
    case 27:
        return 8; // Escape
    case 13:
        return 5; // Enter
    default:
        return 0; // Invalid input
    }
}




