#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>

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
    gotoxy(x, y); cout << char(201);  // Góc trên trái
    for (int i = 0; i < chieuDai; i++) cout << char(205);  // Đường ngang trên
    cout << char(187);  // Góc trên phải

    for (int i = 1; i < chieuRong; i++) {
        gotoxy(x, y + i); cout << char(186);  // Đường dọc trái
        gotoxy(x + chieuDai + 1, y + i); cout << char(186);  // Đường dọc phải
    }

    gotoxy(x, y + chieuRong); cout << char(200);  // Góc dưới trái
    for (int i = 0; i < chieuDai; i++) cout << char(205);  // Đường ngang dưới
    cout << char(188);  // Góc dưới phải
}

// Hàm vẽ màn hình đăng nhập cho Admin
void veManHinhDangNhap() {
    system("cls");  // Xóa màn hình
    int x = 30, y = 5;  // Tọa độ vị trí khung
    int chieuDai = 40, chieuRong = 2;

    // Tiêu đề
    textColor(4);  // Màu đỏ
    gotoxy(x + 10, y - 2); cout << "Dang nhap Admin";

    // Vẽ khung nhập Username
    veKhung(x, y, chieuDai, chieuRong);
    gotoxy(x + 5, y + 1); cout << "Username: ";

    // Vẽ khung nhập Password
    veKhung(x, y + 4, chieuDai, chieuRong);
    gotoxy(x + 5, y + 5); cout << "Password: ";

    // Vẽ nút đăng nhập
    veKhung(x, y + 8, chieuDai, chieuRong);
    textColor(11);  // Màu xanh dương
    gotoxy(x + 15, y + 9); cout << "Dang nhap";

    // Di chuyển con trỏ đến vị trí nhập Username
    gotoxy(x + 16, y + 1);
}

// Hàm nhập mật khẩu với ẩn ký tự
string nhapPassword() {
    string password = "";
    char ch;
    while (true) {
        ch = _getch();  // Lấy ký tự người dùng nhập, không hiển thị trên màn hình
        if (ch == 13) {  // Nhấn Enter
            break;
        }
        else if (ch == 8 && password.length() > 0) {  // Nhấn Backspace
            password.pop_back();
            cout << "\b \b";  // Xóa ký tự trên màn hình
        }
        else if (ch != 8) {
            password += ch;
            cout << "*";  // Hiển thị dấu "*" thay vì ký tự thực tế
        }
    }
    return password;
}

// Hàm kiểm tra đăng nhập
bool kiemTraDangNhap(string username, string password) {
    string adminUsername = "phanthanh";
    string adminPassword = "123";

    if (username == adminUsername && password == adminPassword) {
        return true;
    }
    return false;
}

// Lớp Thông Tin
class ThongTin {
public:
    string ten;
    string diaChi;
    string soDienThoai;

    ThongTin() {}
    ThongTin(string ten, string diaChi, string soDienThoai)
        : ten(ten), diaChi(diaChi), soDienThoai(soDienThoai) {}

    void capNhatThongTin(ThongTin thongTinMoi) {
        this->ten = thongTinMoi.ten;
        this->diaChi = thongTinMoi.diaChi;
        this->soDienThoai = thongTinMoi.soDienThoai;
    }
};

// Lớp Nhân Viên
class NhanVien {
public:
    string username;
    ThongTin thongTin;

    NhanVien(string username, ThongTin thongTin) : username(username), thongTin(thongTin) {}

    ThongTin getThongTin() {
        return thongTin;
    }

    void capNhatThongTin(ThongTin thongTinMoi) {
        thongTin.capNhatThongTin(thongTinMoi);
    }
};

// Lớp Node lưu trữ nhân viên
class Node {
public:
    NhanVien* nhanVien;
    Node* next;

    Node(NhanVien* nhanVien) {
        this->nhanVien = nhanVien;
        this->next = nullptr;
    }
};

// Lớp Danh Sách Nhân Viên
class DanhSachNhanVien {
public:
    Node* head;

    DanhSachNhanVien() {
        head = nullptr;
    }

    // Hàm thêm nhân viên
    void themNhanVien(NhanVien* nhanVien) {
        Node* newNode = new Node(nhanVien);
        newNode->next = head;
        head = newNode;
    }

    // Hàm tìm nhân viên
    Node* timNhanVien(string username) {
        Node* current = head;
        while (current != nullptr) {
            if (current->nhanVien->username == username) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    // Hàm xóa nhân viên
    bool xoaNhanVien(string username) {
        Node* current = head;
        Node* previous = nullptr;

        while (current != nullptr) {
            if (current->nhanVien->username == username) {
                if (previous == nullptr) {
                    head = current->next;
                }
                else {
                    previous->next = current->next;
                }
                delete current;
                return true;
            }
            previous = current;
            current = current->next;
        }
        return false;
    }
};

// Lớp quản trị viên
class QuanTriVien {
public:
    string username, password;
    DanhSachNhanVien danhSachNhanVien;

    // Thêm nhân viên
    bool themNhanVien(NhanVien* nhanVien) {
        if (danhSachNhanVien.timNhanVien(nhanVien->username) != nullptr) {
            return false;
        }
        danhSachNhanVien.themNhanVien(nhanVien);
        return true;
    }

    // Tìm nhân viên
    Node* timNhanVien(string username) {
        return danhSachNhanVien.timNhanVien(username);
    }

    // Xóa nhân viên
    bool xoaNhanVien(string username) {
        return danhSachNhanVien.xoaNhanVien(username);
    }

    // Cập nhật thông tin nhân viên
    bool capNhatNhanVien(string username, ThongTin thongTinMoi) {
        Node* nodeNhanVien = danhSachNhanVien.timNhanVien(username);
        if (nodeNhanVien != nullptr) {
            nodeNhanVien->nhanVien->capNhatThongTin(thongTinMoi);
            return true;
        }
        return false;
    }

    // Hiển thị thông tin nhân viên
    ThongTin hienThiNhanVien(string username) {
        Node* nodeNhanVien = danhSachNhanVien.timNhanVien(username);
        if (nodeNhanVien != nullptr) {
            return nodeNhanVien->nhanVien->getThongTin();
        }
        return ThongTin();
    }
};

// Hàm vẽ trang chủ admin với khung
void veTrangChuAdmin(QuanTriVien& admin) {
    int chon;
    int x = 30, y = 5;  // Tọa độ vẽ khung cho menu chính
    do {
        system("cls");
        veKhung(x, y, 40, 12);  // Vẽ khung cho các chức năng

        gotoxy(x + 15, y + 1); cout << "Quan ly Admin";
        gotoxy(x + 5, y + 3); cout << "1. Them nhan vien";
        gotoxy(x + 5, y + 4); cout << "2. Tim nhan vien";
        gotoxy(x + 5, y + 5); cout << "3. Xoa nhan vien";
        gotoxy(x + 5, y + 6); cout << "4. Cap nhat nhan vien";
        gotoxy(x + 5, y + 7); cout << "5. Hien thi nhan vien";
        gotoxy(x + 5, y + 8); cout << "6. Thoat";
        gotoxy(x + 5, y + 10); cout << "Nhap lua chon: ";
        cin >> chon;

        if (chon == 1) {
            string username, ten, diaChi, soDienThoai;
            cout << "Nhap username: "; cin >> username;
            cout << "Nhap ten: "; cin.ignore(); getline(cin, ten);
            cout << "Nhap dia chi: "; getline(cin, diaChi);
            cout << "Nhap so dien thoai: "; getline(cin, soDienThoai);

            NhanVien* nv = new NhanVien(username, ThongTin(ten, diaChi, soDienThoai));
            if (admin.themNhanVien(nv)) {
                cout << "Them nhan vien thanh cong!\n";
            }
            else {
                cout << "Nhan vien da ton tai!\n";
            }
        }
        else if (chon == 2) {
            string username;
            cout << "Nhap username can tim: "; cin >> username;
            Node* nv = admin.timNhanVien(username);
            if (nv != nullptr) {
                ThongTin tt = nv->nhanVien->getThongTin();
                cout << "Ten: " << tt.ten << "\n";
                cout << "Dia chi: " << tt.diaChi << "\n";
                cout << "So dien thoai: " << tt.soDienThoai << "\n";
            }
            else {
                cout << "Nhan vien khong ton tai!\n";
            }
        }
        else if (chon == 3) {
            string username;
            cout << "Nhap username can xoa: "; cin >> username;
            if (admin.xoaNhanVien(username)) {
                cout << "Xoa nhan vien thanh cong!\n";
            }
            else {
                cout << "Nhan vien khong ton tai!\n";
            }
        }
        else if (chon == 4) {
            string username, ten, diaChi, soDienThoai;
            cout << "Nhap username can cap nhat: "; cin >> username;
            Node* nv = admin.timNhanVien(username);
            if (nv != nullptr) {
                cout << "Nhap ten moi: "; cin.ignore(); getline(cin, ten);
                cout << "Nhap dia chi moi: "; getline(cin, diaChi);
                cout << "Nhap so dien thoai moi: "; getline(cin, soDienThoai);

                admin.capNhatNhanVien(username, ThongTin(ten, diaChi, soDienThoai));
                cout << "Cap nhat thong tin nhan vien thanh cong!\n";
            }
            else {
                cout << "Nhan vien khong ton tai!\n";
            }
        }
        else if (chon == 5) {
            string username;
            cout << "Nhap username can hien thi: "; cin >> username;
            ThongTin tt = admin.hienThiNhanVien(username);
            if (!tt.ten.empty()) {
                cout << "Ten: " << tt.ten << "\n";
                cout << "Dia chi: " << tt.diaChi << "\n";
                cout << "So dien thoai: " << tt.soDienThoai << "\n";
            }
            else {
                cout << "Nhan vien khong ton tai!\n";
            }
        }

        if (chon != 6) {
            system("pause");
        }
    } while (chon != 6);
}

int main() {
    string username, password;

    // Vẽ màn hình đăng nhập
    veManHinhDangNhap();

    // Nhập Username
    cin >> username;

    // Di chuyển con trỏ đến vị trí nhập Password
    gotoxy(46, 10);
    password = nhapPassword();

    // Kiểm tra thông tin đăng nhập
    if (kiemTraDangNhap(username, password)) {
        system("cls");
        textColor(10);  // Màu xanh lá cây
        gotoxy(40, 12);
        cout << "Dang nhap thanh cong!\n";
        system("pause");

        // Sau khi đăng nhập thành công, hiển thị trang chủ admin
        QuanTriVien admin;
        veTrangChuAdmin(admin);
    }
    else {
        system("cls");
        textColor(12);  // Màu đỏ
        gotoxy(40, 12);
        cout << "Sai thong tin dang nhap!\n";
        system("pause");
    }

    return 0;
}
