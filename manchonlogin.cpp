#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

// Hàm di chuyển con trỏ đến tọa độ cần vẽ
void gotoxy(int column, int line) {
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Hàm thay đổi màu chữ
void textColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Hàm reset màu về mặc định
void resetColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Màu mặc định (trắng)
}

// Tạo khung bao quanh menu
void veKhung(int x, int y, int chieuDai, int chieuRong) {
    textColor(6); // Chọn màu xanh cho khung

    gotoxy(x, y);
    cout << char(201);  // Góc trên trái
    for (int i = 0; i < chieuDai; i++) cout << char(205);  // Đường ngang trên
    cout << char(187);  // Góc trên phải

    for (int i = 1; i < chieuRong; i++) {
        gotoxy(x, y + i); cout << char(186);  // Đường dọc trái
        gotoxy(x + chieuDai + 1, y + i); cout << char(186);  // Đường dọc phải
    }

    gotoxy(x, y + chieuRong);
    cout << char(200);  // Góc dưới trái
    for (int i = 0; i < chieuDai; i++) cout << char(205);  // Đường ngang dưới
    cout << char(188);  // Góc dưới phải

    resetColor();  // Reset màu về mặc định sau khi vẽ khung
}

class Menu {
public:
    Menu();
    ~Menu();
    void printMenu(int selectedLine, int x, int y); // Thêm x, y để in mục ở đúng vị trí trong khung
    int numberOfItem() {
        return _numberOfItem;
    }
    string* getItem() {
        return item;
    }
    int Move(); // Đưa hàm Move vào trong class

private:
    string* item; // mảng lưu tên của các menu
    int _numberOfItem; // số lượng menu    
};

Menu::Menu() {
    _numberOfItem = 2;
    item = new string[_numberOfItem];  // Tạo mảng động đúng kích thước
    item[0] = "1. Admin";
    item[1] = "2. Employee";
}

Menu::~Menu() {
    delete[] item;
}

int Menu::Move() {
    char c = _getch();
    if ((int)c == -32) c = _getch();
    switch ((int)c) {
    case 80:
        return 1; // xuống
    case 72:
        return 2; // lên
    case 27:
        return 8; // esc
    case 13:
        return 5; // enter
    default:
        return 0; // sai
    }
}

void Menu::printMenu(int selectedLine, int x, int y) {
    veKhung(x - 1, y - 1, 30, 7); // Vẽ khung bao quanh menu

    // In tiêu đề "DANG NHAP" ngay bên trong khung
    gotoxy(x + 10, y);
    textColor(12);
    cout << "DANG NHAP";
    resetColor(); // Reset về màu mặc định

    // Vẽ đường gạch ngang dưới tiêu đề
    gotoxy(x + 2, y + 1); // Di chuyển xuống một dòng để vẽ đường gạch ngang
    for (int i = 0; i < 26; i++) { // Chiều dài của đường gạch ngang
        cout << "-";
    }

    // Tạo khoảng cách giữa tiêu đề và các mục menu
    for (int i = 0; i < _numberOfItem; i++) {
        gotoxy(x + 0.5, y + 3 + i);  // Tạo khoảng cách giữa tiêu đề và các mục
        if (i == selectedLine) {
            textColor(14);  // Màu vàng cho mục đang chọn
            cout << ">> " << item[i]; // In mục đang chọn
            resetColor();   // Reset về màu mặc định
        }
        else {
            cout << "   " << item[i]; // In các mục còn lại
        }
    }
}

// Hàm để chạy menu
void runMenu(Menu& menu) {
    int x;
    int line = 0;
    bool thoat = false;

    int menuX = 35, menuY = 5;   // Tọa độ menu

    // In menu lần đầu
    menu.printMenu(line, menuX, menuY);

    while (!thoat) {
        if (_kbhit()) {
            x = menu.Move(); // Gọi hàm Move() từ đối tượng menu

            switch (x) {
            case 1: // xuống
                line++;
                if (line >= menu.numberOfItem()) line = 0;
                break;
            case 2: // lên
                line--;
                if (line < 0) line = menu.numberOfItem() - 1;
                break;
            case 5: // enter
                gotoxy(0, 20);
                cout << "Ban chon: " << menu.getItem()[line];
                break;
            case 8: // esc
                thoat = true;
                break;
            }
            menu.printMenu(line, menuX, menuY); // In lại menu với dòng được chọn mới
        }
    }
}

int main() {
    Menu menu;
    runMenu(menu); // Gọi hàm runMenu để chạy menu
    return 0;
}
