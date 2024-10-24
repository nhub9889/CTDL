#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>

using namespace std;

class Info {
private:
    string ten;
    string dienThoai;
    string diaChi;
    string email;

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

    void XemThongTin() const {
        cout << "Ho ten: " << ten << endl;
        cout << "Dien thoai: " << dienThoai << endl;
        cout << "Dia chi: " << diaChi << endl;
        cout << "Email: " << email << endl;
    }
};

class Employee {
private:
    string username;
    string password;
    Info thongtin;

public:
    Employee(string user = "", string pass = "", Info i = Info())
        : username(user), password(pass), thongtin(i) {}

    string getUsername() const { return username; }
    string getPassword() const { return password; }

    void setUsername(const string& _username) { username = _username; }
    void setPassword(const string& _password) { password = _password; }

    void setThongTin(Info _thongtin) { thongtin = _thongtin; }

    // Add const qualifier so this method can be called on const objects
    Info getThongTin() const { return thongtin; }

    bool KiemTraMatKhau(const string& matKhauNhap) const {
        return matKhauNhap == password;
    }

    int DoiMatKhau(const string& matKhauCu, const string& newPassword, const string& xacNhanMatKhauMoi) {
        if (!KiemTraMatKhau(matKhauCu)) return -1;  // Sai mật khẩu cũ
        if (newPassword != xacNhanMatKhauMoi) return 0;  // Mật khẩu mới không khớp

        // Cập nhật mật khẩu
        password = newPassword;
        return 1;  // Đổi mật khẩu thành công
    }

    void XemThongTinNhanVien() const {
        thongtin.XemThongTin();
    }
};

// Di chuyển con trỏ đến tọa độ x, y trên màn hình console
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Màu cho văn bản
void textColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Tạo khung hình chữ nhật có kích thước chiều dài và chiều rộng
void veKhung(int x, int y, int chieuDai, int chieuRong) {
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
}

// Vẽ menu với các lựa chọn và tô màu theo vị trí chọn hiện tại
void veMenu(int viTriChon) {
    system("cls");  // Xóa màn hình
    int x = 30, y = 3;  // Tọa độ vẽ khung chính
    int chieuDai = 60, chieuRong = 14;

    // Vẽ khung bao ngoài menu
    veKhung(x, y, chieuDai, chieuRong);

    // Vẽ tiêu đề menu
    gotoxy(x + 23, y + 1); textColor(14); cout << "MENU CHINH";  // Tiêu đề màu vàng

    // Các mục menu, tô màu đỏ khi được chọn
    textColor(viTriChon == 0 ? 4 : 7);  // Nếu chọn, màu đỏ, nếu không, màu trắng
    gotoxy(x + 10, y + 3); cout << "1. Xem thong tin tai khoan";

    textColor(viTriChon == 1 ? 4 : 7);
    gotoxy(x + 10, y + 5); cout << "2. Doi password";

    textColor(viTriChon == 2 ? 4 : 7);
    gotoxy(x + 10, y + 7); cout << "3. Thoat";
}

// Hiển thị thông tin tài khoản
void hienThiThongTin(const Employee& user) {
    system("cls");
    int x = 30, y = 3;  // Tọa độ vẽ khung hiển thị thông tin
    veKhung(x, y, 60, 10);  // Tạo khung cho thông tin

    gotoxy(x + 20, y + 1);  // In "Thong tin tai khoan"
    textColor(14);  cout << "THONG TIN TAI KHOAN:" << endl;

    Info info = user.getThongTin();

    gotoxy(x + 2, y + 3);  // Canh chỉnh cho thông tin bên trong khung
    textColor(12); cout << "[+] Ho ten: ";
    textColor(13); cout << info.getTen() << endl;

    gotoxy(x + 2, y + 4);  // In số điện thoại
    textColor(12); cout << "[+] Dien thoai: ";
    textColor(13); cout << info.getDienThoai() << endl;

    gotoxy(x + 2, y + 5);  // In địa chỉ
    textColor(12); cout << "[+] Dia chi: ";
    textColor(13); cout << info.getDiaChi() << endl;

    gotoxy(x + 2, y + 6);  // In email
    textColor(12); cout << "[+] Email: ";
    textColor(13); cout << info.getEmail() << endl;

    gotoxy(x + 2, y + 8);  // Hướng dẫn quay lại menu
    textColor(10); cout << "Nhan phim bat ky de quay lai menu.";

    _getch();  // Dừng chờ người dùng nhấn phím để quay lại
}


// Hàm nhập mật khẩu với ký tự *
void nhapMatKhau(string& matKhau) {
    matKhau.clear();  // Xóa chuỗi mật khẩu
    char ch;
    while (true) {
        ch = _getch();  // Nhập từng ký tự
        if (ch == 13) break;  // Nếu nhấn Enter, dừng lại
        if (ch == 8) {  // Nếu nhấn Backspace
            if (!matKhau.empty()) {
                matKhau.pop_back();  // Xóa ký tự cuối
                cout << "\b \b";  // Xóa ký tự trên màn hình
            }
        }
        else {
            matKhau.push_back(ch);  // Thêm ký tự vào mật khẩu
            cout << "*";  // Hiển thị *
        }
    }
}

// Đổi mật khẩu
void doiMatKhau(Employee& user) {
    system("cls");
    int x = 30, y = 3;  // Tọa độ vẽ khung đổi mật khẩu
    veKhung(x, y, 60, 10);  // Tạo khung cho đổi mật khẩu
    gotoxy(x + 23, y + 1); textColor(14); cout << "DOI MAT KHAU";
    string matKhauCu, matKhauMoi, xacNhanMatKhauMoi;

    int soLanNhap = 0;  // Đếm số lần nhập mật khẩu
    const int maxNhap = 3;  // Số lần nhập tối đa

    // Vòng lặp cho phép nhập mật khẩu cũ tối đa 3 lần
    while (soLanNhap < maxNhap) {
        gotoxy(x + 2, y + 2.5); textColor(12); cout << "[+] Nhap mat khau cu: ";
        nhapMatKhau(matKhauCu);  // Nhập mật khẩu cũ
        if (user.KiemTraMatKhau(matKhauCu)) {  // Kiểm tra mật khẩu cũ
            gotoxy(x + 2, y + 3.5); textColor(12); cout << "[+] Nhap mat khau moi: ";
            nhapMatKhau(matKhauMoi);  // Nhập mật khẩu mới

            gotoxy(x + 2, y + 4.5); textColor(12); cout << "[+] Xac nhan mat khau moi: ";
            nhapMatKhau(xacNhanMatKhauMoi);  // Nhập xác nhận mật khẩu mới

            int ketQua = user.DoiMatKhau(matKhauCu, matKhauMoi, xacNhanMatKhauMoi);
            if (ketQua == -1) {
            gotoxy(x + 2, y + 6); textColor(12); cout << "Sai mat khau cu!" << endl;
            }
            else if (ketQua == 0) {
                gotoxy(x + 2, y + 6); textColor(12); cout << "Mat khau moi khong khop!" << endl;
            }
            else {
                gotoxy(x + 2, y + 6); textColor(5); cout << "Doi mat khau thanh cong!" << endl;
            }

            gotoxy(x + 2, y + 8); textColor(10); cout << "Nhan phim bat ky de quay lai menu.";
            _getch();  // Dừng chờ người dùng nhấn phím để quay lại
            return;
        }
        else {
            soLanNhap++;  // Tăng số lần nhập
            gotoxy(x + 2, y + 6); textColor(5); cout << "Sai mat khau cu! (Lan thu " << soLanNhap << "/" << maxNhap << ")" << endl;
        }

        if (soLanNhap == maxNhap) {
            gotoxy(x + 2, y + 8); textColor(10); cout << "Ban da nhap sai qua 3 lan, quay lai menu." << endl;
            _getch();  // Dừng chờ người dùng nhấn phím để quay lại
            return;  // Thoát khỏi hàm
        }
    }
}

// Xử lý di chuyển qua lại và chọn menu
void xuLyMenu(Employee& user) {
    int viTriChon = 0;  // Vị trí mục được chọn (0, 1, hoặc 2)
    char phim;  // Biến để lưu phím người dùng nhấn

    veMenu(viTriChon);  // Vẽ menu lần đầu tiên

    while (true) {
        phim = _getch();  // Lấy phím người dùng nhấn
        if (phim == -32) {  // Nếu là phím điều hướng (mã -32)
            phim = _getch();  // Lấy mã phím điều hướng tiếp theo
            if (phim == 72) {  // Phím mũi tên lên
                viTriChon = (viTriChon - 1 + 3) % 3;  // Quay lại mục trước
            }
            else if (phim == 80) {  // Phím mũi tên xuống
                viTriChon = (viTriChon + 1) % 3;  // Chọn mục tiếp theo
            }
        }
        else if (phim == '\r') {  // Nếu nhấn Enter
            switch (viTriChon) {
            case 0: hienThiThongTin(user); break;  // Xem thông tin
            case 1: doiMatKhau(user); break;  // Đổi mật khẩu
            case 2: return;  // Thoát
            }
        }

        veMenu(viTriChon);  // Vẽ lại menu sau mỗi lựa chọn
    }
}

int main() {
    // Tạo một nhân viên để thử nghiệm
    Info thongTin("Nguyen Van A", "0123456789", "123 Nguyen Trai", "example@example.com");
    Employee user("user123", "pass123", thongTin);

    xuLyMenu(user);  // Bắt đầu chương trình

    return 0;
}
