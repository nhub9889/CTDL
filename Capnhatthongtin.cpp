#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <string>
#include <algorithm>

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
    textColor(14); // Chọn màu vàng cho khung

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

//Hàm trim sẽ loại bỏ tất cả các dấu cách và ký tự xuống dòng (\n, \r) ở đầu và cuối chuỗi:
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \n\r\t\f\v");
    if (first == string::npos)
        return "";  // Chuỗi chỉ chứa dấu cách hoặc rỗng

    size_t last = str.find_last_not_of(" \n\r\t\f\v");
    return str.substr(first, (last - first + 1));
}

// Hàm thoát khỏi chương trình và đóng cửa sổ console
void thoatChuongTrinh() {
    cout << "Dang thoat chuong trinh..." << endl; // Thông báo trước khi thoát
    Sleep(1000); // Đợi 1 giây để người dùng thấy thông báo
    ExitProcess(0); // Kết thúc chương trình và đóng cửa sổ console
}

template <typename T>
class Node {
private:
    T user;
    Node* nextNode;

public:
    Node() : nextNode(nullptr) {}
    Node(T user) : user(user), nextNode(nullptr) {}

    T& getUser() { return user; }
    Node* getNext() { return nextNode; }
    void setNext(Node* next) { nextNode = next; }
};

template<class T>
class DanhSach {
private:
    Node<T>* Dau;
    Node<T>* Cuoi;
    int SoLuong;

public:
    DanhSach() : Dau(nullptr), Cuoi(nullptr), SoLuong(0) {}
    ~DanhSach();
    //void xayDanhSach(T a);
    T* timUser(string user);
    bool Them(T user);
    //bool xoa(string user);
    void hienThiDanhSach();
};

// Hàm hủy để giải phóng bộ nhớ
template<class T>
DanhSach<T>::~DanhSach() {
    Node<T>* current = Dau;
    while (current) {
        Node<T>* next = current->getNext();
        delete current;
        current = next;
    }
}

// Hàm thêm nhân viên vào danh sách
template<class T>
bool DanhSach<T>::Them(T user) {
    Node<T>* newNode = new Node<T>(user);
    if (!Dau) {
        Dau = newNode;
        Cuoi = newNode;
    }
    else {
        Cuoi->setNext(newNode);
        Cuoi = newNode;
    }
    SoLuong++;
    return true;
}

// Hàm tìm nhân viên theo tên
template<class T>
T* DanhSach<T>::timUser(string user) {
    string trimmedUser = trim(user);
    std::transform(trimmedUser.begin(), trimmedUser.end(), trimmedUser.begin(), ::tolower);

    Node<T>* current = Dau;
    while (current) {
        string tenNV = current->getUser().getTen();
        std::transform(tenNV.begin(), tenNV.end(), tenNV.begin(), ::tolower);

        // In ra tên nhân viên và tên cần tìm để so sánh
        cout << "Dang so sanh: [" << tenNV << "] voi [" << trimmedUser << "]" << endl;

        if (tenNV == trimmedUser) {
            return &current->getUser(); // Nếu trùng thì trả về đối tượng Info
        }
        current = current->getNext();
    }
    return nullptr; // Trả về nullptr nếu không tìm thấy
}

// Hàm hiển thị danh sách nhân viên
template<class T>
void DanhSach<T>::hienThiDanhSach() {
    Node<T>* current = Dau;
    int index = 0;
    while (current) {
        current->getUser().hienThi(index++, false);
        current = current->getNext();
    }
}

class Info {
private:
    string ten, dienThoai, diaChi, email;

public:
    Info(string t = "", string dt = "", string dc = "", string em = "")
        : ten(t), dienThoai(dt), diaChi(dc), email(em) {}

    string getTen() { return ten; }
    string getDienThoai() { return dienThoai; }
    string getDiaChi() { return diaChi; }
    string getEmail() { return email; }

    void setTen(const string& t) { ten = t; }
    void setDienThoai(const string& dt) { dienThoai = dt; }
    void setDiaChi(const string& dc) { diaChi = dc; }
    void setEmail(const string& em) { email = em; }

    void hienThi(int index, bool isSelected) {
        if (isSelected) textColor(14);  // Màu vàng cho mục đang chọn
        cout << (isSelected ? ">> " : "   ") << index + 1 << ". Ho ten: " << ten
            << " | Dia chi: " << diaChi
            << " | So dien thoai: " << dienThoai
            << " | Email: " << email << endl;
        resetColor();
    }
};

class Menu {
public:
    Menu();
    ~Menu();
    void printMenu(int selectedLine, int x, int y, Info& info); // Thêm x, y để in mục ở đúng vị trí trong khung
    int numberOfItem() {
        return _numberOfItem;
    }
    string* getItem() {
        return item;
    }
    int Move();

private:
    string* item; // mảng lưu tên của các menu
    int _numberOfItem; // số lượng menu    
};

Menu::Menu() {
    _numberOfItem = 4;
    item = new string[_numberOfItem];
    item[0] = "Ho ten: ";
    item[1] = "Dia chi: ";
    item[2] = "So dien thoai: ";
    item[3] = "Dia chi email: ";
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

void Menu::printMenu(int selectedLine, int x, int y, Info& info) {
    veKhung(x - 1, y - 1, 50, 14); // Vẽ khung bao quanh menu với chiều cao lớn hơn để chứa nút

    gotoxy(x + 15, y);
    textColor(12);
    cout << "THONG TIN NHAN VIEN";
    resetColor();

    gotoxy(x + 10, y + 1);
    textColor(14);
    for (int i = 0; i < 29; i++) {
        cout << "-";
    }
    resetColor();

    gotoxy(x + 1, y + 3);
    for (int i = 0; i < _numberOfItem; i++) {
        gotoxy(x + 1, y + 3 + i);
        if (i == selectedLine) {
            textColor(14);
            cout << ">> ";
        }
        else {
            cout << "   ";
        }

        cout << item[i];
        if (i == 0) cout << info.getTen();
        else if (i == 1) cout << info.getDiaChi();
        else if (i == 2) cout << info.getDienThoai();
        else if (i == 3) cout << info.getEmail();

        resetColor();
    }

    // Vẽ nút "Cập nhật" ở góc dưới khung
    gotoxy(x + 35, y + 12);
    if (selectedLine == _numberOfItem) {
        textColor(14);
        cout << "[CAP NHAT]";
        resetColor();
    }
    else {
        cout << " CAP NHAT ";
    }
}

// Hàm nhập thông tin từ người dùng với khả năng xử lý phím Backspace và Enter
string nhapThongTinMoi() {
    string newInfo;
    char ch;

    // Đọc từng ký tự đến khi gặp Enter
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') { // Xử lý phím Backspace
            if (!newInfo.empty()) {
                newInfo.pop_back();
                cout << "\b \b"; // Xóa ký tự cuối trên màn hình
            }
        }
        else {
            newInfo += ch;
            cout << ch; // Hiển thị ký tự vừa nhập
        }
    }
    cout << endl;

    // Loại bỏ dấu cách hoặc ký tự xuống dòng ở đầu và cuối
    return trim(newInfo);
}

// Hàm kiểm tra tính hợp lệ của số điện thoại
bool laSoDienThoaiHopLe(const string& sdt) {
    // Kiểm tra độ dài có phải là 10 và chỉ chứa ký tự số không
    if (sdt.length() == 10 && all_of(sdt.begin(), sdt.end(), ::isdigit)) {
        return true;
    }
    return false;
}

// Hàm để chạy menu
void runMenu(Menu& menu, Info& info) {
    int x;
    int line = 0;
    bool thoat = false;

    int menuX = 35, menuY = 5;

    menu.printMenu(line, menuX, menuY, info);

    while (!thoat) {
        if (_kbhit()) {
            x = menu.Move();
            string newInfo;
            string previousInput;
            switch (x) {
            case 1: // xuống
                line++;
                if (line > menu.numberOfItem()) line = 0;
                break;
            case 2: // lên
                line--;
                if (line < 0) line = menu.numberOfItem();
                break;
            case 5: // enter
                if (line == menu.numberOfItem()) {  // Nếu chọn nút "Cập nhật"
                    gotoxy(menuX, menuY + 15); // Vị trí để in thông báo dưới menu
                    cout << "Thong tin da duoc cap nhat thanh cong!";
                    Sleep(1000); // Đợi 1 giây để người dùng nhìn thấy thông báo
                    gotoxy(menuX, menuY + 15); // Xóa thông báo sau khi hiển thị
                    cout << string(50, ' ');
                    thoat = true;  // Thoát khỏi vòng lặp sau khi cập nhật
                    break;
                }

                gotoxy(0, 20);
                cout << string(50, ' '); // Xóa dòng trước khi hiển thị nội dung mới
                gotoxy(0, 20);
                cout << "Cap nhat " << menu.getItem()[line];

                previousInput = "";
                while (true) {
                    gotoxy(0, 21);
                    cout << string(50, ' ');
                    gotoxy(0, 21);

                    newInfo = nhapThongTinMoi();

                    if (line == 2 && !laSoDienThoaiHopLe(newInfo)) {
                        gotoxy(0, 22);
                        cout << "So dien thoai khong hop le! Nhap lai.";
                        previousInput = newInfo;
                    }
                    else {
                        if (line == 0) info.setTen(newInfo);
                        else if (line == 1) info.setDiaChi(newInfo);
                        else if (line == 2) info.setDienThoai(newInfo);
                        else if (line == 3) info.setEmail(newInfo);

                        gotoxy(0, 22);
                        cout << string(100, ' ');
                        break;
                    }
                }
                break;
            case 8: // esc
                thoatChuongTrinh(); // Gọi hàm thoát khi nhấn ESC
                break;
            }
            menu.printMenu(line, menuX, menuY, info);
        }
    }
}

int main() {
    DanhSach<Info> danhSachNhanVien;

    // Thêm một số nhân viên vào danh sách
    danhSachNhanVien.Them(Info("Nguyen Van A", "0123456789", "Ha Noi", "a@gmail.com"));
    danhSachNhanVien.Them(Info("Tran Thi B", "0987654321", "Hai Phong", "b@gmail.com"));

   // Tìm nhân viên và hiển thị menu chỉnh sửa thông tin
    string tenCanTim;
    cout << "Nhap ten nhan vien can tim: ";
    getline(cin, tenCanTim); // Sử dụng getline để lấy tên đầy đủ
    Info* userFound = danhSachNhanVien.timUser(tenCanTim);

    if (userFound) {
        // Tạo menu chỉnh sửa và truyền thông tin của nhân viên tìm được vào
        Menu menu;
        runMenu(menu, *userFound);
    }
    else {
        cout << "Khong tim thay nhan vien!" << endl;
    }

    return 0;
}

