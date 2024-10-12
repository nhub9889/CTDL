#include <iostream>
#include <fstream>
#include <string>
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
};

class Employee {
private:
    string username, password;
    Info thongtin;
    bool firstLogin;

public:
    Employee(string user = "", string pass = "", Info i = Info(), bool isFirstLogin = true)
        : username(user), password(pass), thongtin(i), firstLogin(isFirstLogin) {}

    string getUsername() { return username; }
    string getPassword() { return password; }

    void setUsername(const string& _username) { username = _username; }
    void setPassword(const string& _password) { password = _password; }

    void setThongTin(Info _thongtin) { thongtin = _thongtin; }
    Info getThongTin() { return thongtin; }

    Info XemThongTin() const {
        thongtin.XemThongTin();  
    }

    bool KiemTraMatKhau(string& matKhauNhap)  {
        return matKhauNhap == password; 
    }

    int DoiMatKhau(string& password, const string& newPassword, const string& xacNhanMatKhauMoi) {
        if (!KiemTraMatKhau(password)) { return -1; }  // Sai mật khẩu cũ

        if (newPassword != xacNhanMatKhauMoi) { return 0; }  // Mật khẩu mới không khớp

        // Cập nhật mật khẩu
        password = newPassword;
        return 1;  // Đổi mật khẩu thành công
    }
};
