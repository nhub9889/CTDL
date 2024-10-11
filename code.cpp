#include <iostream>
using namespace std;
class Info{
    private :
    string  ten, dienThoai, diaChi, email;
    public :
    string getTen() {
        return ten;
    }

    void setTen(string tenMoi) {
        ten = tenMoi;
    }

    string getDienThoai() {
        return dienThoai;
    }

    void setDienThoai(string soDienThoaiMoi) {
        dienThoai = soDienThoaiMoi;
    }

    string getDiaChi() {
        return diaChi;
    }

    void setDiaChi(string diaChiMoi) {
        diaChi = diaChiMoi;
    }

    string getEmail() {
        return email;
    }

    void setEmail(string emailMoi) {
        email = emailMoi;
    }

};
class Employee{
    private :
    string username, password;
    Info thongtin;
    public :
    string getUsername() {return username;}
    string getPassword() {return password;}
    Info getThongTin() {return thongtin;}
    void setUsername(string _username) { username = _username;}
    void setPassword (string _password) {password = _password;}
    setThongTin(Info _thongtin) { thongtin = _thongtin;}
    void Thoat() {return EXIT_SUCCESS;}
    void XemThongTin();
    void DoiPassWord(string);

};
class Admin{
    private:
    Info thongtin;
    public :
    string getUsername() {return username;}
    string getPassword() {return password;}
    Info getThongTin() {return thongtin;}
    void setUsername(string _username) { username = _username;}
    void setPassword (string _password) {password = _password;}
    setThongTin(Info _thongtin) { thongtin = _thongtin;}
    void Thoat() {return EXIT_SUCCESS;}
    void ThemEmployee(Employee);
    bool TimEmployee(Info);
    void XoaEmployee(string, bool);
    void CapNhatEmployee(Employee);
    void HienThiEmployee();

};
class Man{
    public : 
    int vitriX;
    int vitriY;
    int dai, rong;
    string NoiDung;
    public :
    void xuLySuKien();
    void XuLyPhim(key_event_record);
    void ThongBao();

};
class ManDangNhap{
    public :
    void ChonDangNhap();
    string username(string);
    string password(string);


};
class ManAdmin{
    public : 
    void themEmployee();
    void xoaEmployee();
    void timEmployee();
    void capNhatEmployee();
    void hienThiThongTinEmployee();
    void Thoat();

};
class ManCapNhatEmployee{
    public :
    bool tonTai(string);
    void thongTinThayDoi(Info);

};
class ManHienThiThongTinEmployee{
    public :
    void hienThi();
};
class ManTimEmployee{
    public :
    void Tim(string);

};
class ManXoaEmployee{
    public :
    bool tonTai(string);
    void thongTin(Info);

};
class ManEmployee{
    public :
    void xemThongTin();
    void doiPassword();
    void Thoat();

};
class ManXemThongTin{

};
class ManDoiPassword{
    public : 
    bool nhapLaiMatKhau(string);
    void nhapMatKhauMoi(string);
};
