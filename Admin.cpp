
using namespace std;

class Admin{
    private :
    string username, password;
    Info thongtin;
    public :
    string getUsername() {return username;}
    string getPassword() {return password;}
    Info getThongTin() {return thongtin;}
    void setUsername(string _username) { username = _username;}
    void setPassword (string _password) {password = _password;}
    void setThongTin(Info _thongtin) { thongtin = _thongtin;}

    Node* timEmployee(string user) {
        return danhSachEmployee.tim(user);
    }

    bool KiemTraMatKhau(string pass){
        return pass == password;
    }

    void CapNhatEmployee(){
        
    }
    
    Info hienThiEmployee(string user) {
        Node* nodeNhanVien = danhSachEmployee.tim(user);
        if (nodeNhanVien != nullptr) {
            return nodeNhanVien->Employee->getThongTin();
        }
        return nullptr;  
    }
    
    bool ThemEmployee(string user){
        if (!timEmployee(user)==nullptr){
            DanhSachEmployee.Them(emp);
            return true;
        }
        return false;
    }
    
    void XoaEmployee(){
        danhSachEmployee.Xoa();
    }
    void Thoat() {return EXIT_SUCCESS;}
    

};
