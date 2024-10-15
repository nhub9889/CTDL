
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

    Node* timNhanVien(string username) {
        return danhSach.timNhanVien(username);
    }
    
    void Thoat() {return EXIT_SUCCESS;}
    

};
