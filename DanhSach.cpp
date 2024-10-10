#include <iostream>
using namespace std;
class Info {
    public:
        string ten, dienThoai, diaChi, email;

    public:
        Info(string _ten, string _dienthoai, string _diachi, string _email) {
            ten = _ten;
            dienThoai = _dienthoai;
            diaChi = _diachi;
            email = _email;
        }
        string getTen() {
            return ten;
        }

        void setTen(string _ten) {
            ten = _ten;
        }

        string getDienThoai() {
            return dienThoai;
        }

        void setDienThoai(string _dienThoai) {
            dienThoai = _dienThoai;
        }

        string getDiaChi() {
            return diaChi;
        

        void setDiaChi(string _diaChi) {
            diaChi = _diaChi;
        }

        string getEmail() {
            return email;
        }

        void setEmail(string _email) {
            email = _email;
        }
};

class Employee {
    public:
        string username, password;

    public:
        Employee(string _user, string _pass) {
            username = _user;
            password = _pass;
        }
        void XemThongTin() {
        
        }

        void DoiPassWord(string newPassword) {
            password = newPassword;
        }
};
class Danh_Sach {
    private:
        int SoLuong;
    private:
        void DocDanhSach();
        void XayDanhSach(user);
        void HuyDanhSach();
        void Them(T);
        void Xoa(T);
        void CapNhat(T);
};
int main() {
    return 0;
}