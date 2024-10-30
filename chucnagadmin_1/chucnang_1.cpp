#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <fstream>
#include <regex> // Thêm thư viện để kiểm tra email

using namespace std;

// Hàm di chuyển con trỏ đến tọa độ cần vẽ
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Hàm thay đổi màu chữ
void textColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Hàm vẽ khung hình chữ nhật
void veKhung(int x, int y, int chieuDai, int chieuRong) {
    gotoxy(x, y); cout << char(201);
    for (int i = 0; i < chieuDai; i++) cout << char(205);
    cout << char(187);

    for (int i = 1; i < chieuRong; i++) {
        gotoxy(x, y + i); cout << char(186);
        gotoxy(x + chieuDai + 1, y + i); cout << char(186);
    }

    gotoxy(x, y + chieuRong); cout << char(200);
    for (int i = 0; i < chieuDai; i++) cout << char(205);
    cout << char(188);
}

// Lớp Thông Tin
class ThongTin {
public:
    string ten;
    string diaChi;
    string soDienThoai;
    string email;

    ThongTin() {}
    ThongTin(string ten, string diaChi, string soDienThoai, string email)
        : ten(ten), diaChi(diaChi), soDienThoai(soDienThoai), email(email) {}
};

// Cấu trúc Nút trong danh sách liên kết
struct Node {
    string username;
    string password;
    ThongTin thongTin;
    Node* next;

    Node(string username, string password, ThongTin thongTin)
        : username(username), password(password), thongTin(thongTin), next(nullptr) {}
};

// Lớp Danh Sách
class DanhSach {
private:
    Node* head;

public:
    DanhSach() : head(nullptr) {}

    // Hàm kiểm tra username trong tệp
    bool kiemTraUsernameTrung(string username) {
        ifstream inFile("Employees.txt");
        string line;

        while (getline(inFile, line)) {
            size_t pos = line.find(',');
            if (pos != string::npos) {
                string existingUsername = line.substr(0, pos);
                if (existingUsername == username) {
                    inFile.close();
                    return true; // Username đã tồn tại
                }
            }
        }

        inFile.close();
        return false; // Username không tồn tại
    }

    // Sửa đổi hàm themNhanVien
    bool themNhanVien(string username, string password, ThongTin thongTin) {
        if (kiemTraUsernameTrung(username) || timNhanVien(username) != nullptr) {
            return false; // Username đã tồn tại
        }

        Node* newNode = new Node(username, password, thongTin);
        newNode->next = head;
        head = newNode;
        return true;
    }


    // Tìm nhân viên theo username
    Node* timNhanVien(string username) {
        Node* current = head;
        while (current != nullptr) {
            if (current->username == username) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    // Lưu danh sách vào tệp
    void luuDanhSach() {
        ofstream outFile("Employees.txt", ios::trunc);
        Node* current = head;
        while (current != nullptr) {
            outFile << current->username << "," << current->password << ","
                << current->thongTin.ten << "," << current->thongTin.diaChi << ","
                << current->thongTin.soDienThoai << "," << current->thongTin.email << endl;
            current = current->next;
        }
        outFile.close();
    }

    // Tạo tệp [username].txt cho mỗi nhân viên
    void taoTepChoNhanVien(Node* nv) {
        ofstream userFile(nv->username + ".txt");
        userFile << nv->thongTin.ten << endl;
        userFile << nv->thongTin.diaChi << endl;
        userFile << nv->thongTin.soDienThoai << endl;
        userFile << nv->thongTin.email << endl;
        userFile.close();
    }

    // Ghi dữ liệu vào tệp khi thêm nhân viên
    void ghiNhanVien(Node* nv) {
        luuDanhSach();
        taoTepChoNhanVien(nv);
    }

    // Hàm kiểm tra số điện thoại
    bool kiemTraSoDienThoai(string soDienThoai) {
        return (soDienThoai.length() == 10 && all_of(soDienThoai.begin(), soDienThoai.end(), ::isdigit));
    }

    // Hàm kiểm tra email
    bool kiemTraEmail(string email) {
        regex pattern("^[a-zA-Z0-9._%+-]+@gmail\\.com$");
        return regex_match(email, pattern);
    }
};

// Hàm vẽ màn hình chính
void veManHinhChinh(int selected) {
    system("cls");
    int x = 30, y = 5; // Tọa độ khung
    veKhung(x, y, 40, 10);

    gotoxy(x + 10, y + 1); textColor(5); cout << "QUAN LY NHAN VIEN";

    for (int i = 0; i < 2; i++) {
        gotoxy(x + 5, y + 3 + i);
        if (i == selected) {
            textColor(12); // Màu cho mục đã chọn
        }
        else {
            textColor(10); // Màu cho các mục khác
        }
        cout << (i + 1) << ". " << (i == 0 ? "Them nhan vien" : "Thoat");
    }
}

// Hàm vẽ màn hình thêm nhân viên
void veManHinhThemNhanVien(DanhSach& ds) {
    system("cls");
    int x = 30, y = 5; // Tọa độ khung
    veKhung(x, y, 40, 14); // Thay đổi chiều cao khung

    string username, ten, diaChi, soDienThoai, email;

    gotoxy(x + 10, y + 1); textColor(5); cout << "THEM NHAN VIEN";
    // Nhập username và kiểm tra tính duy nhất
    while (true) {
        gotoxy(x + 5, y + 3); textColor(10); cout << "Nhap username: "; textColor(9); cin >> username;
        cin.ignore(); // Xóa bộ nhớ đệm
        if (ds.timNhanVien(username) != nullptr) {
            gotoxy(x + 5, y + 5); textColor(12); cout << "Username da ton tai! nhap lai!";
            gotoxy(x + 5, y + 6); textColor(10); system("pause");
            system("cls");
            veKhung(x, y, 40, 14); // Vẽ lại khung
            gotoxy(x + 10, y + 1); textColor(5); cout << "THEM NHAN VIEN";
        }
        else {
            break; // Username hợp lệ
        }
    }

    // Nhập tên
    while (true) {
        gotoxy(x + 5, y + 4); textColor(10); cout << "Nhap ten: "; textColor(9); getline(cin, ten);
        if (!ten.empty()) {
            break; // Tên hợp lệ
        }
        else {
            gotoxy(x + 5, y + 5); textColor(12); cout << "Ten khong duoc de trong!";
            gotoxy(x + 5, y + 6); textColor(10); system("pause");
            system("cls");
            veKhung(x, y, 40, 14); // Vẽ lại khung
            gotoxy(x + 10, y + 1); textColor(5); cout << "THEM NHAN VIEN";
            gotoxy(x + 5, y + 3); textColor(10); cout << "Nhap username: "; textColor(9); cout << username;
        }
    }

    // Nhập địa chỉ
    while (true) {
        gotoxy(x + 5, y + 5); textColor(10); cout << "Nhap dia chi: "; textColor(9); getline(cin, diaChi);
        if (!diaChi.empty()) {
            break; // Địa chỉ hợp lệ
        }
        else {
            gotoxy(x + 5, y + 6); textColor(12); cout << "Dia chi khong duoc de trong!";
            gotoxy(x + 5, y + 7); textColor(10); system("pause");
            system("cls");
            veKhung(x, y, 40, 14); // Vẽ lại khung
            gotoxy(x + 10, y + 1); textColor(5); cout << "THEM NHAN VIEN";
            gotoxy(x + 5, y + 3); textColor(10); cout << "Nhap username: "; textColor(9); cout << username;
            gotoxy(x + 5, y + 4); textColor(10); cout << "Nhap ten: "; textColor(9); cout << ten;
        }
    }

    // Nhập số điện thoại và kiểm tra
    while (true) {
        gotoxy(x + 5, y + 6); textColor(10); cout << "Nhap so dien thoai: "; textColor(9); getline(cin, soDienThoai);
        if (ds.kiemTraSoDienThoai(soDienThoai)) {
            break; // Số điện thoại hợp lệ
        }
        else {
            gotoxy(x + 5, y + 7); textColor(12); cout << "So dien thoai co 10 so!!!";
            gotoxy(x + 5, y + 8); textColor(10); system("pause");
            system("cls");
            veKhung(x, y, 40, 14); // Vẽ lại khung
            gotoxy(x + 10, y + 1); textColor(5); cout << "THEM NHAN VIEN";
            gotoxy(x + 5, y + 3); textColor(10); cout << "Nhap username: "; textColor(9); cout << username;
            gotoxy(x + 5, y + 4); textColor(10); cout << "Nhap ten: "; textColor(9); cout << ten;
            gotoxy(x + 5, y + 5); textColor(10); cout << "Nhap dia chi: "; textColor(9); cout << diaChi;
        }
    }

    // Nhập email và kiểm tra
    while (true) {
        gotoxy(x + 5, y + 7); textColor(10); cout << "Nhap email: "; textColor(9); getline(cin, email);
        if (ds.kiemTraEmail(email)) {
            break; // Email hợp lệ
        }
        else {
            gotoxy(x + 5, y + 8); textColor(12); cout << "Email phai co dinh dang @gmail.com!!";
            gotoxy(x + 5, y + 9); textColor(10); system("pause");
            system("cls");
            veKhung(x, y, 40, 14); // Vẽ lại khung
            gotoxy(x + 10, y + 1); textColor(5); cout << "THEM NHAN VIEN";
            gotoxy(x + 5, y + 3); textColor(10); cout << "Nhap username: "; textColor(9); cout << username;
            gotoxy(x + 5, y + 4); textColor(10); cout << "Nhap ten: "; textColor(9); cout << ten;
            gotoxy(x + 5, y + 5); textColor(10); cout << "Nhap dia chi: "; textColor(9); cout << diaChi;
            gotoxy(x + 5, y + 6); textColor(10); cout << "Nhap so dien thoai: "; textColor(9); cout << soDienThoai; // In lại dòng nhập
        }
    }


    // Tạo nhân viên mới
    Node* nv = new Node(username, "111111", ThongTin(ten, diaChi, soDienThoai, email));
    if (ds.themNhanVien(nv->username, nv->password, nv->thongTin)) {
        ds.ghiNhanVien(nv);
        gotoxy(x + 5, y + 9); textColor(12); cout << "Them nhan vien thanh cong!";
    }
    else {
        gotoxy(x + 5, y + 9); textColor(12); cout << "Username da ton tai!";
    }
    gotoxy(x + 5, y + 10); textColor(10); system("pause");
}

// Hàm chạy chương trình
void chayChuongTrinh() {
    DanhSach ds;
    int selected = 0;

    while (true) {
        veManHinhChinh(selected);
        char key = _getch(); // Nhận phím từ người dùng
        if (key == 80) { // Mũi tên xuống
            selected = (selected + 1) % 2; // Chọn mục tiếp theo
        }
        else if (key == 72) { // Mũi tên lên
            selected = (selected - 1 + 2) % 2; // Chọn mục trước
        }
        else if (key == '\r') { // Phím Enter
            if (selected == 0) {
                veManHinhThemNhanVien(ds);
            }
            else if (selected == 1) {
                break; // Thoát chương trình
            }
        }
    }
}

int main() {
    DanhSach ds;
    ds.luuDanhSach(); // Tải danh sách nhân viên từ tệp
    chayChuongTrinh();
    return 0;
}
