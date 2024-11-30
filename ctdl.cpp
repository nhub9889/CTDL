#include <iostream>
#include <conio.h>
#include <algorithm>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <initializer_list>
#include <string>
#include <iomanip>
#include <cstdio>
#include <vector>
using namespace std;

//Cac lop dinh nghia
class Info {
private:
    string ten, dienThoai, diaChi, email;

public:
    Info();
    Info(string _ten, string _dienthoai, string _diaChi, string _email);
    string getTen();
    string getDienThoai();
    string getDiaChi();
    string getEmail();
    void setThongTin(string username);
    void setTen(string _ten);
    void setDienThoai(string _dienthoai);
    void setDiaChi(string _diachi);
    void setEmail(string _email);
    void doiThongTin(string t, string dt, string dc, string e);
};

class Employee {
private:
    string username, password;
    Info thongtin;

public:
    string getUsername();
    string getPassword();
    string getType() { return "Employee"; }
    Info getThongTin();
    void setUsername(string _username);
    void setPassword(string _password);
    void setThongTin(string username);
    void setThongTin(Info info);
    bool kiemTraMatKhau(string mk);
    Info XemThongTin();
    void DoiPassWord(string s);
};

class Admin {
private:
    string username, password;
    Info thongtin;

public:
    string getUsername();
    string getPassword();
    string getType() { return "Admin"; }
    Info getThongTin();
    void setUsername(string _username);
    void setPassword(string _password);
    void setThongTin(string x) { return; }
    bool kiemTraMatKhau(string mk);
};

template <typename T>
class Node {
private:
    T user;
    Node* nextNode;

public:
    Node();
    Node(T user);
    T& getUser();
    Node* getNext();
    T getNode() { return user; }
    Node <T>* getnextNode() { return nextNode; }
    void setNext(Node* next);
};

template<class T>
class DanhSach {
private:
    Node<T>* Dau;
    Node<T>* Cuoi;
    int SoLuong;

public:
    DanhSach();
    ~DanhSach();
    void xayDanhSach(T a);
    void docDanhSach(string s);
    T* timUser(string user);
    bool Them(T user);
    bool xoa(string user);
    Node<T>* getDau() const { return Dau; }
    Node<T>* getCuoi() const { return Cuoi; }
};
Info::Info() : ten(""), dienThoai(""), diaChi(""), email("") {}
Info::Info(string _ten, string _dienThoai, string _diaChi, string _email) : ten(_ten), dienThoai(_dienThoai), diaChi(_diaChi), email(_email) {}
string Info::getTen() { return ten; }
string Info::getDienThoai() { return dienThoai; }
string Info::getDiaChi() { return diaChi; }
string Info::getEmail() { return email; }
void Info::setDiaChi(string _diachi) { diaChi = _diachi; }
void Info::setEmail(string _email) { email = _email; };
void Info::setTen(string _ten) { ten = _ten; }
void Info::setDienThoai(string _dienthoai) { dienThoai = _dienthoai; };

void Info::setThongTin(string username) {
    string fn = username + ".txt";
    ifstream in(fn);
    getline(in, ten);
    getline(in, dienThoai);
    getline(in, diaChi);
    getline(in, email);
    in.close();
}

void Info::doiThongTin(string t, string dt, string dc, string e) {
    ten = t;
    dienThoai = dt;
    diaChi = dc;
    email = e;
}


string Employee::getUsername() { return username; }
string Employee::getPassword() { return password; }
Info Employee::getThongTin() { return thongtin; }

void Employee::setUsername(string _username) { username = _username; }
void Employee::setPassword(string _password) { password = _password; }
void Employee::setThongTin(string username) { thongtin.setThongTin(username); }
void Employee::setThongTin(Info info) { thongtin = info; }


bool Employee::kiemTraMatKhau(string mk) { return mk == password; }
Info Employee::XemThongTin() { return thongtin; }
void Employee::DoiPassWord(string s) { setPassword(s); }


string Admin::getUsername() { return username; }
string Admin::getPassword() { return password; }
Info Admin::getThongTin() { return thongtin; }

void Admin::setUsername(string _username) { username = _username; }
void Admin::setPassword(string _password) { password = _password; }

bool Admin::kiemTraMatKhau(string mk) { return mk == password; }


template <typename T>
Node<T>::Node() : user(T()), nextNode(nullptr) {}

template <typename T>
Node<T>::Node(T user) : user(user), nextNode(nullptr) {}

template <typename T>
T& Node<T>::getUser() {
    return user;  
}

template <typename T>
Node<T>* Node<T>::getNext() { return nextNode; }

template <typename T>
void Node<T>::setNext(Node<T>* next) { nextNode = next; }


template <typename T>
DanhSach<T>::DanhSach() : SoLuong(0), Dau(nullptr), Cuoi(nullptr) {}

template <typename T>
DanhSach<T>::~DanhSach() {
    Node<T>* cur = Dau; 
    while (cur != nullptr) {
        Node<T>* p = cur->getNext();  
        delete cur;  
        cur = p; 
    }
    Dau = nullptr;  
}


template <typename T>
void DanhSach<T>::xayDanhSach(T a) {
    if (Dau == nullptr) {
        Dau = new Node<T>(a);
        Cuoi = Dau;
        return;
    }
    Node<T>* p = new Node<T>(a);
    Cuoi->setNext(p);
    Cuoi = p;
}

template <typename T>
void DanhSach<T>::docDanhSach(string s) {
    ifstream in(s + ".txt");

    string name, pass;
    while (in >> name >> pass) {
        T user;
        user.setUsername(name);
        user.setPassword(pass);
        if (user.getType() == "Employee") {
            string fileInfo = s + "\\" + name;
            user.setThongTin(fileInfo);
        }
        xayDanhSach(user);
        SoLuong++;
    }
    in.close();
}

template <typename T>
T* DanhSach<T>::timUser(string user) {
    Node<T>* cur = Dau;
    while (cur != nullptr) {
        if (cur->getUser().getUsername() == user)
            return &(cur->getUser()); 
        cur = cur->getNext();
    }
    return nullptr; 
}


template <typename T>
bool DanhSach<T>::Them(T user) {
    if (timUser(user.getUsername()) != nullptr)
        return false;
    xayDanhSach(user);
    return true;
}

template <typename T>
bool DanhSach<T>::xoa(string user) {
    if (Dau == nullptr)
        return false;

    if (Dau->getUser().getUsername() == user) {
        Node<T>* p = Dau->getNext();
        delete Dau;
        Dau = p;
        return true;
    }

    Node<T>* cur = Dau;
    while (cur->getNext() != nullptr && cur->getNext()->getUser().getUsername() != user)
        cur = cur->getNext();

    if (cur->getNext() == nullptr)
        return false;

    Node<T>* p = cur->getNext()->getNext();
    delete cur->getNext();
    cur->setNext(p);
    return true;
}

template class DanhSach<Employee>;
template class DanhSach<Admin>;


//Lam dep
void gotoxy(int column, int line);

void textColor(int color);

void resetColor();

void veKhung(int x, int y, int chieuDai, int chieuRong);

class Menu {
public:
    Menu() {};
    Menu(int n, vector<string> arr, string t, int X, int Y, int D, int R);
    void printMenu(int selectedLine);
    int numberOfItem();
    int Move();


private:
    vector <string> item;
    int _numberOfItem; 
    string title;
    int x; int y;
    int chieuDai;
    int chieuRong;
};

void gotoxy(int column, int line) {
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void textColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


void resetColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); 
}


void veKhung(int x, int y, int chieuDai, int chieuRong) {
    textColor(6); 

    gotoxy(x, y);
    cout << char(201);  
    for (int i = 0; i < chieuDai; i++) cout << char(205);  
    cout << char(187);  

    for (int i = 1; i < chieuRong; i++) {
        gotoxy(x, y + i); cout << char(186);  
        gotoxy(x + chieuDai + 1, y + i); cout << char(186); 
    }

    gotoxy(x, y + chieuRong);
    cout << char(200);  
    for (int i = 0; i < chieuDai; i++) cout << char(205);  
    cout << char(188);  

    resetColor();  
}


Menu::Menu(int n, vector<string> arr, string t, int X, int Y, int D, int R) :_numberOfItem(n), item(arr), title(t), x(X), y(Y), chieuDai(D), chieuRong(R) {}

int Menu::numberOfItem() {
    return _numberOfItem;
}




void Menu::printMenu(int selectedLine) {
    system("cls");
    veKhung(x - 1, y - 1, chieuDai, chieuRong); 


    gotoxy(x + chieuDai / 2 - title.size() / 2, y);
    textColor(12);
    cout << title;
    resetColor(); 

    
    gotoxy(x + chieuDai / 2 - 13, y + 1);
    for (int i = 0; i < 26; i++) {
        cout << "-";
    }


    for (int i = 0; i < _numberOfItem; i++) {
        gotoxy(x, y + 3 + i);
        if (i == selectedLine) {
            textColor(14);  
            cout << ">> " << item[i];
            resetColor();
        }
        else {
            cout << "   " << item[i];
        }
    }
}


int Menu::Move() {
    char c = _getch();
    if ((int)c == -32) c = _getch();
    switch ((int)c) {
    case 80:
        return 1; 
    case 72:
        return 2; 
    case 27:
        return 8; 
    case 13:
        return 5; 
    default:
        return 0; 
    }
}



void runADangNhap();
void runEDangNhap();
void runAmenu();
void runEmenu();
void runThemEmployee();
void runXoaEmployee();
void runTimEmployee();
void runCapNhatEmployee();
void runHienThiEmployee();
void runXemThongTin();
void runDoiPassword();

void Thoat();
string file = "C:\\Users\\Lenovo\\Desktop\\up\\VS\\ctdl\\ctdl";
DanhSach<Admin> dsAdmin;
DanhSach<Employee> dsEmployee;
Admin admin;
Employee employee;
string Ausername, Eusername, Apassword, Epassword;

Menu ChonDangNhap, ADangNhap, EDangNhap, Amenu, Emenu, ThemEmployee, XoaEmployee, TimEmployee, CapNhatEmployee, HienThiEmployee, XemThongTin, DoiPassword;


string nhapPassword() {
    string password = "";
    char ch;
    while (true) {
        ch = _getch();
        if (ch == 13) { 
            break;
        }
        else if (ch == 8 && password.length() > 0) { 
            password.pop_back();
            cout << "\b \b"; 
        }
        else if (ch != 8) {
            password += ch;
            cout << "*"; 
        }
    }
    return password;
}

void Thoat() {
    system("cls");
    gotoxy(0, 0);
    exit(0);
}

bool checkUserExists(const string& username) {
    Employee* user = dsEmployee.timUser(username);
    return user != nullptr;
}


bool isValidEmail(const string& email) {
    size_t atPos = email.find('@');
    size_t dotPos = email.find('.', atPos);
    return atPos != string::npos && dotPos != string::npos && atPos < dotPos && email.find('@')!=0;
}


bool isValidPhoneNumber(const string& phone) {
    return phone.length() == 10 && all_of(phone.begin(), phone.end(), ::isdigit);
}

bool ktUser(string user) {
    if (dsEmployee.timUser(user) == nullptr) return true;
    return false;
}

string getInput(int x, int y, const string& prompt, bool (*validator)(const string&), int maxLength) {
    gotoxy(x, y);
    cout << prompt;
    string input;
    char ch;

    while (true) {
        ch = _getch();
        if (ch == 27) { 
            input.clear();
            break;
        }
        else if (ch == 13) { 
            if (validator == nullptr || validator(input)) {
                break; 
            }
            else {
                gotoxy(55, 30); 
                cout << "Thong tin khong hop le. Vui long nhap lai.";
                input.clear();
                gotoxy(x + prompt.size(), y); 
                cout << string(maxLength, ' '); 
                gotoxy(x + prompt.size(), y);
            }
        }
        else if (ch == 8) { 
            if (!input.empty()) {
                input.pop_back();
                cout << "\b \b";
            }
        }
        else if (input.size() < maxLength) { 
            input += ch;
            cout << ch;
        }
    }

    gotoxy(x, y + 1);
    cout << string(50, ' '); 
    return input;
}


void runThemEmployee() {
    int line = 0;
    bool thoat = false;
    string userNem, hoTen, mail, Address, pass = "111111", sdt;
    system("cls");
    ThemEmployee.printMenu(line);

    while (!thoat) {
        if (_kbhit()) {
            int x = ThemEmployee.Move(); 
            switch (x) {
            case 1: 
                line = (line + 1) % ThemEmployee.numberOfItem();
                break;
            case 2: 
                line = (line - 1 + ThemEmployee.numberOfItem()) % ThemEmployee.numberOfItem();
                break;
            case 5: {

                switch (line) {
                case 0: 
                    userNem = getInput(48, 8, "", nullptr, 20);
                    break;
                case 1: 
                    hoTen = getInput(49, 9, "", nullptr, 50);
                    break;
                case 2: 
                    Address = getInput(47, 10, "", nullptr, 50);
                    break;
                case 3: 
                    sdt = getInput(53, 11, "", isValidPhoneNumber, 10);
                    break;
                case 4:
                    mail = getInput(45, 12, "", isValidEmail, 50);
                    break;
                case 5:
                    Thoat();
                    break;
                }
                break;
            }

            case 8: {
                runAmenu();
                break;
            }
            }

            ThemEmployee.printMenu(line);


            if (dsEmployee.timUser(userNem) != nullptr) {
                userNem = "";
                gotoxy(55,23);
                cout << "Username da ton tai";
                gotoxy(48, 8);
            }
            if (!userNem.empty()) gotoxy(48, 8), cout << userNem;
            if (!hoTen.empty()) gotoxy(49, 9), cout << hoTen;
            if (!Address.empty()) gotoxy(47, 10), cout << Address;
            if (!sdt.empty()) gotoxy(53, 11), cout << sdt;
            if (!mail.empty()) gotoxy(45, 12), cout << mail;

            if (!userNem.empty() && !hoTen.empty() && !Address.empty() && !sdt.empty() && !mail.empty()) {
                employee.setUsername(userNem);
                employee.setPassword(pass);
                Info eInfo;
                eInfo.setTen(hoTen);
                eInfo.setDiaChi(Address);
                eInfo.setDienThoai(sdt);
                eInfo.setEmail(mail);
                employee.setThongTin(eInfo);
                dsEmployee.Them(employee);

                ofstream employeeFile(file + "\\Employee\\" + userNem + ".txt");
                if (employeeFile.is_open()) {
                    employeeFile<< hoTen << endl;
                    employeeFile << sdt << endl;
                    employeeFile << Address << endl; 
                    employeeFile << mail << endl;
                    employeeFile.close();
                }
               
                ofstream empFile("Employee.txt", ios::app);
                if (empFile.is_open()) {
                    empFile << userNem << " 111111"<<'\n';
                    empFile.close();
                }
                

                gotoxy(35, 15);
                cout << "Luu Nhan vien moi thanh cong";
                dsEmployee.~DanhSach();
                dsEmployee.docDanhSach(file + "\\Employee");
                while (true) {
                    if (_kbhit()) {
                        char key = _getch();
                        if (key == 27) {  
                            runAmenu();
                            return;
                        }
                        if (key == 13) {  
                            runThemEmployee();
                        }
                    }
                }
            }
        }
    }
}


void runTimEmployee() {
    system("cls");
    string inputUsername;

    while (true) {
        Menu nhapUsernameMenu(1, { "Nhap Username: " }, "Tim Nhan Vien", 35, 5, 40, 8);
        nhapUsernameMenu.printMenu(0);
       
        gotoxy(55, 8);
        getline(cin, inputUsername);

        if (inputUsername.empty()) {
            gotoxy(35, 10);
            cout << "Username khong duoc de trong!";
            while (true) {
                if (_kbhit()) {
                    char key = _getch();
                    if (key == 27) {  
                        runAmenu();
                        return;
                    }
                    if (key == 13) {  
                        runTimEmployee();
                        break;
                    }
                }
            }
        }

        if (dsEmployee.timUser(inputUsername) == nullptr) {
            gotoxy(35, 10);
            cout << "Employee khong ton tai! Vui long nhap lai.";
            gotoxy(55, 8);
            cout << string(30, ' '); 
            while (true) {
                if (_kbhit()) {
                    char key = _getch();
                    if (key == 27) { 
                        runAmenu();
                        return;
                    }
                    if (key == 13) { 
                        runTimEmployee();
                        break;
                    }
                }
            }
        }


        Info thongTin = dsEmployee.timUser(inputUsername)->getThongTin();
        thongTin.setThongTin(inputUsername);
        string ten = thongTin.getTen();
        string dienThoai = thongTin.getDienThoai();
        string diaChi = thongTin.getDiaChi();
        string email = thongTin.getEmail();


        Menu thongTinMenu(5, {
            "Thong tin cua " + inputUsername + ":",
            "Ten: " + ten,
            "Dien Thoai: " + dienThoai,
            "Dia Chi: " + diaChi,
            "Email: " + email
            }, "Thong Tin Nhan Vien", 35, 5, 35, 10);
        thongTinMenu.printMenu(0);


        while (true) {
            if (_kbhit()) {
                char key = _getch();
                if (key == 27) { 
                    runAmenu();
                    return;
                }
                if (key == 13) { 
                    runTimEmployee();
                    break;
                }
            }
        }
    }
}




void runXoaEmployee() {
    system("cls");
    string inputUsername;

    while (true) {
        Menu nhapUsernameMenu(1, { "Nhap Username: " }, "Xoa Employee", 35, 5, 40, 8);
        nhapUsernameMenu.printMenu(0);
        gotoxy(55, 8);
        
        while (true) {
            if (_kbhit()) {
                char key = _getch();
                if (key == 27) {
                    runAmenu();
                    return;
                }
                break;  
            }
        }

        getline(cin, inputUsername);

        if (inputUsername.empty()) {
            continue;  
        }

        if (!checkUserExists(inputUsername)) {
            gotoxy(35, 17);
            cout << "    Employee khong ton tai! Vui long nhap lai.";
            gotoxy(55, 8);
            inputUsername.clear(); 
            while (true) {
                if (_kbhit()) {
                    char key = _getch();
                    if (key == 27) {  
                        runAmenu();
                        return;
                    }
                    break;  
                }
            }
            continue; 
        }


        gotoxy(35, 17);
        cout << "Ban co chac chan muon xoa Employee nay? (Y/N)";
        char confirm = _getch();

        if (confirm == 'Y' || confirm == 'y') {
            if (dsEmployee.xoa(inputUsername)) {
                string fileName = "Employee\\"+inputUsername + ".txt";
                ifstream infile("Employee.txt");
                ofstream outfile("employee_temp.txt");
                
                Node <Employee>* ds = dsEmployee.getDau();
                while (ds != NULL) {
                    Employee e = ds->getUser();
                    outfile << e.getUsername() << " " << e.getPassword() << '\n';
                    ds = ds->getnextNode();
                }
                infile.close();
                outfile.close();
                remove("Employee.txt");
                rename("employee_temp.txt", "Employee.txt");
                if (remove(fileName.c_str()) == 0) {
                    gotoxy(35, 18);
                    cout << "Employee da duoc xoa thanh cong va file " << fileName << " da duoc xoa.";
                }
               

                while (true) {
                    if (_kbhit()) {
                        char key = _getch();
                        if (key == 27) {  
                            runAmenu();
                            return;
                        }
                        if (key == 13) {  
                            break;  
                        }
                    }
                }
            }
            else {
                gotoxy(35, 18);
                cout << "Xoa that bai. Employee khong ton tai!";
                while (true) {
                    if (_kbhit()) {
                        char key = _getch();
                        if (key == 27) {  
                            runAmenu();
                            return;
                        }
                        if (key == 13) { 
                            break;  
                        }
                    }
                }
            }
        }
        else {
            gotoxy(35, 18);
            cout << "Xoa employee da bi huy. Vui long nhap username khac.";
            while (true) {
                if (_kbhit()) {
                    char key = _getch();
                    if (key == 27) { 
                        runAmenu();
                        return;
                    }
                    if (key == 13) {  
                        break;  
                    }
                }
            }
            continue;  
        }
        while (true) {
            if (_kbhit()) {
                char key = _getch();
                if (key == 27) { 
                    runAmenu();
                    return;
                }
                if (key == 13) {  
                    break;  
                }
            }
        }
    }
}




void runChonDangNhap() {
    int x;
    int line = 0;
    bool thoat = false;

    system("cls");

    ChonDangNhap.printMenu(line);
    gotoxy(40, 15);
    while (!thoat) {
        if (_kbhit()) {
            x = ChonDangNhap.Move(); 

            switch (x) {
            case 1: 
                line++;
                if (line >= ChonDangNhap.numberOfItem()) line = 0;
                break;
            case 2:
                line--;
                if (line < 0) line = ChonDangNhap.numberOfItem() - 1;
                break;
            case 5: 
                if (line == 0) {
                    runADangNhap();
                }
                else runEDangNhap();
                return;
            case 8: 
                thoat = true;
                break;
            }
            ChonDangNhap.printMenu(line); 
            gotoxy(40, 15);
        }
    }
}

void runXemThongTin() {
    Info thongTin = employee.getThongTin();
    string ten = thongTin.getTen();
    string dienThoai = thongTin.getDienThoai();
    string diaChi = thongTin.getDiaChi();
    string email = thongTin.getEmail();

    Menu thongTinMenu(5, {
        "Thong tin cua " + employee.getUsername() + ":",
        "Ten: " + ten,            
        "Dien Thoai: " + dienThoai,
        "Dia Chi: " + diaChi,      
        "Email: " + email        
        }, "Thong Tin Employee", 35, 5, 35, 10);
    thongTinMenu.printMenu(0);

    while (true) {
        if (_kbhit()) {
            char key = _getch(); 
            if (key == 27) {  
                runEmenu(); 
                return;
            }
        }
    }
}



void runDoiPassword() {
    system("cls");
    int line = 0;

    Menu doiPasswordMenu(1, { "Nhap mat khau hien tai: " }, "Doi Mat Khau", 35, 5, 40, 8);
    doiPasswordMenu.printMenu(line);
    string oldPassword = nhapPassword();

    if (!employee.kiemTraMatKhau(oldPassword)) {
        gotoxy(40, 17);
        cout << "Mat khau hien tai khong chinh xac!!" << endl;
        _getch();
        while (true) {
            if (_kbhit()) {
                char key = _getch();
                if (key == 27) { 
                    runEmenu();  
                    return;
                }
                if (key == 12) {
                    runDoiPassword();
                    return;
                }
            }
        }
    }

    gotoxy(40, 17);
    cout << "Nhap mat khau moi: ";
    string newPassword1 = nhapPassword();

    gotoxy(40, 19);
    cout << "Nhap lai mat khau moi: ";
    string newPassword2 = nhapPassword();

    if (newPassword1 != newPassword2) {
        gotoxy(40, 23);
        cout << "Mat khau moi khong khop!!" << endl;
        _getch();
        while (true) {
            if (_kbhit()) {
                char key = _getch();
                if (key == 27) { 
                    runEmenu(); 
                    return;
                }
                if (key == 12) {
                    runDoiPassword();
                    return;
                }
            }
        }
    }

    if (newPassword1 == "111111") {
        gotoxy(40, 23);
        cout << "Vi ly do bao mat ban hay chon mat khau khac" << endl;
        _getch();
        while (true) {
            if (_kbhit()) {
                char key = _getch();
                if (key == 27) {
                    runEmenu();
                    return;
                }
                if (key == 12) {
                    runDoiPassword();
                    return;
                }
            }
        }
    }

    employee.setPassword(newPassword1);
    gotoxy(40, 23);
    cout << "Mat khau da duoc thay doi thanh cong" << endl;

    ifstream infile("employee.txt");
    ofstream outfile("employee_temp.txt");



    string lines;
    while (getline(infile, lines)) {

        istringstream iss(lines);
        string username, password;
        iss >> username >> password;

        if (username == employee.getUsername()) {
            outfile << username << " " << newPassword1 << endl; 
        }
        else {
            outfile << lines << endl;
        }
    }

    infile.close();
    outfile.close();
    remove("employee.txt");
    rename("employee_temp.txt", "employee.txt");
    while (true) {
        if (_kbhit()) {
            char key = _getch();
            if (key == 27) {
                runEmenu(); 
                return;
            }
        }
    }
}

void runDoiPassword1() {
    system("cls");
    int line = 0;

    Menu doiPasswordMenu(1, { "Nhap mat khau hien tai: " }, "Doi Mat Khau", 35, 5, 40, 8);
    doiPasswordMenu.printMenu(line);
    string oldPassword = nhapPassword();
    if (!employee.kiemTraMatKhau(oldPassword)) {
        gotoxy(40, 17);
        cout << "Mat khau hien tai khong chinh xac!!" << endl;
        _getch();
        while (true) {
            if (_kbhit()) {
                char key = _getch();
                if (key == 27) { 
                    runEDangNhap(); 
                    return;
                }
                if (key == 12) {
                    runDoiPassword1();
                    return;
                }
            }
        }
    }
    gotoxy(40, 17);
    cout << "Nhap mat khau moi: ";
    string newPassword1 = nhapPassword();

    gotoxy(40, 19);
    cout << "Nhap lai mat khau moi: ";
    string newPassword2 = nhapPassword();
    if (newPassword1 != newPassword2) {
        gotoxy(40, 23);
        cout << "Mat khau moi khong khop!!" << endl;
        _getch();
        while (true) {
            if (_kbhit()) {
                char key = _getch();
                if (key == 27) { 
                    runEDangNhap();  
                    return;
                }
                if (key == 12) {
                    runDoiPassword1();
                    return;
                }
            }
        }
    }

    if (newPassword1 == "111111") {
        gotoxy(40, 23);
        cout << "Vi ly do bao mat ban hay chon mat khau khac" << endl;
        _getch();
        while (true) {
            if (_kbhit()) {
                char key = _getch();
                if (key == 27) {
                    runEmenu();
                    return;
                }
                if (key == 12) {
                    runDoiPassword();
                    return;
                }
            }
        }
    }

    employee.setPassword(newPassword1);
    gotoxy(40, 23);
    cout << "Mat khau da duoc thay doi thanh cong" << endl;
    ifstream infile("employee.txt");
    ofstream outfile("employee_temp.txt");



    string lines;
    while (getline(infile, lines)) {
        istringstream iss(lines);
        string username, password;
        iss >> username >> password;

        if (username == employee.getUsername()) {
            outfile << username << " " << newPassword1 << endl;
        }
        else {
            outfile << lines << endl;
        }
    }

    infile.close();
    outfile.close();

    remove("employee.txt");
    rename("employee_temp.txt", "employee.txt");

    while (true) {
        if (_kbhit()) {
            char key = _getch();
            if (key == 27) {
                runEmenu();  
                return;
            }
        }
    }
}


void updateName(const string& username, const string& newName) {
    string filename = file + "\\Employee\\" + username + ".txt";  
    ifstream infile(filename);
    ofstream outfile("temp.txt");


    string line;
    int lineIndex = 0;
    while (getline(infile, line)) {
        lineIndex++;
        if (lineIndex == 1) {  
            outfile << newName << endl;
        }
        else {
            outfile << line << endl;
        }
    }
    infile.close();
    outfile.close();
    remove(filename.c_str());  
    rename("temp.txt", filename.c_str());  
}


void updatePhoneNumber(const string& username, const string& newPhoneNumber) {
    string filename = file + "\\Employee\\" + username + ".txt"; 
    ifstream infile(filename);
    ofstream outfile("temp.txt");


    string line;
    int lineIndex = 0;
    while (getline(infile, line)) {
        lineIndex++;
        if (lineIndex == 2) { 
            outfile << newPhoneNumber << endl;
        }
        else {
            outfile << line << endl;
        }
    }
    infile.close();
    outfile.close();
    remove(filename.c_str());  
    rename("temp.txt", filename.c_str());  
}

void updateAddress(const string& username, const string& newAddress) {
    string filename = file + "\\Employee\\" + username + ".txt"; 
    ifstream infile(filename);
    ofstream outfile("temp.txt");


    string line;
    int lineIndex = 0;
    while (getline(infile, line)) {
        lineIndex++;
        if (lineIndex == 3) { 
            outfile << newAddress << endl;
        }
        else {
            outfile << line << endl;
        }
    }
    infile.close();
    outfile.close();
    remove(filename.c_str()); 
    rename("temp.txt", filename.c_str());  
}


void updateEmail(const string& username, const string& newEmail) {
    string filename =file+"\\Employee\\"+  username + ".txt";  
    ifstream infile(filename);
    ofstream outfile("temp.txt");

    if (!infile.is_open()) {
        cout << "Loi mo file!" << endl;
        return;
    }

    string line;
    int lineIndex = 0;
    while (getline(infile, line)) {
        lineIndex++;
        if (lineIndex == 4) {
            outfile << newEmail << endl;
        }
        else {
            outfile << line << endl;
        }
    }
    infile.close();
    outfile.close();
    remove(filename.c_str()); 
    rename("temp.txt", filename.c_str()); 
}



void runCapNhatEmployee() {
    string inputUsername;
    Menu nhapUsernameMenu(1, { "Nhap Username: " }, "Nhap Username", 35, 5, 40, 8);
    nhapUsernameMenu.printMenu(0);  
    gotoxy(55, 8); 
    getline(cin, inputUsername);
    if (inputUsername.empty()) {
        gotoxy(35, 10);
        cout << "    Username khong duoc de trong" << endl;
    }
    if (!checkUserExists(inputUsername)) {
        gotoxy(35, 10);
        cout << "    Nguoi dung khong ton tai!" << endl;
        while (true) {
            char key = _getch();  
            if (key == 27) {  
                runAmenu(); 
                return;
            }
            if (key == 13) {
                runCapNhatEmployee();
                return;
            }
        }
    }
    Menu capNhatMenu(5, {
        "Cap Nhat Ten",
        "Cap Nhat SDT",
        "Cap Nhat Dia Chi",
        "Cap Nhat Email",
        "Thoat"
        }, "Cap Nhat Thong Tin", 35, 5, 30, 9);

    int line = 0;
    bool thoat = false;
    bool valid = false;

    capNhatMenu.printMenu(line); 

    while (!thoat) {
        char c = _getch();
        if ((int)c == -32) c = _getch();  

        switch ((int)c) {
        case 80:  
            line = (line == 4) ? 0 : line + 1; 
            break;
        case 72: 
            line = (line == 0) ? 4 : line - 1; 
            break;
        case 13: 
        {
            string newInput;
            valid = false;  

            switch (line) {
            case 0:  
                gotoxy(35, 20);
                cout << "Nhap ten moi: ";
                getline(cin, newInput);
                if (!newInput.empty() && newInput.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") == string::npos) {
                    updateName(inputUsername, newInput);
                    valid = true;
                }
                else {
                    cout << "Thong tin khong hop le!" << endl; 
                }
                break;
            case 1: 
                gotoxy(35, 20);
                cout << "Nhap so dien thoai moi: ";
                getline(cin, newInput);
                if (newInput.length() == 10 && newInput[0] == '0' && std::all_of(newInput.begin(), newInput.end(), ::isdigit)) {
                    updatePhoneNumber(inputUsername, newInput);
                    valid = true;
                }
                else {
                    cout << "Thong tin khong hop le!" << endl; 
                }
                break;
            case 2:
                gotoxy(35, 20);
                cout << "Nhap dia chi moi: ";
                getline(cin, newInput);
                if (!newInput.empty()) {
                    updateAddress(inputUsername, newInput);
                    valid = true;
                }
                else {
                    cout << "Thong tin khong hop le!" << endl; 
                }
                break;
            case 3:  
                gotoxy(35, 20);
                cout << "Nhap email moi: ";
                getline(cin, newInput);
                if (newInput.find("@gmail.com") != string::npos) {
                    updateEmail(inputUsername, newInput);
                    valid = true;
                }
                else {
                    cout << "Thong tin khong hop le!" << endl; 
                }
                break;
            case 4: 
                thoat = true;
                break;
            }

            if (valid) {
                Menu thongBaoMenu(1, { "Cap Nhat Thong Tin Thanh Cong! Nhap ESC de thoat." }, "Thong Bao", 35, 5, 55, 10);
                dsEmployee = DanhSach<Employee>();
                dsEmployee.docDanhSach(file + "\\Employee");
                thongBaoMenu.printMenu(0);
            }
            else {
                Menu thongBaoMenu(1, { "Thong Tin Khong Hop Le! Nhap ESC de thoat." }, "Thong Bao", 35, 5, 50, 10);
                thongBaoMenu.printMenu(0);
            }

            while (true) {
                char key = _getch();  
                if (key == 27) {  
                    runAmenu(); 
                    return;
                }
            }

            break;
        }
        case 27:  
            runAmenu();  
            return;
        }

        capNhatMenu.printMenu(line);  
    }
}



void runHienThiEmployee() {
    system("cls");
    vector<string> displayData;

    string header =    "Ten               | Dien Thoai  | Dia Chi                    | Email           ";
    string separator = "------------------|-------------|----------------------------|-----------------";
    displayData.push_back("Danh Sach Employee:");
    displayData.push_back(header);
    displayData.push_back(separator);

    Node<Employee>* current = dsEmployee.getDau(); 
    while (current != nullptr) {
        Employee emp = current->getNode(); 
        Info info = emp.getThongTin();
        string ten = info.getTen().substr(0, 18);        
        string dienThoai = info.getDienThoai().substr(0, 15);
        string diaChi = info.getDiaChi().substr(0, 29); 
        string email = info.getEmail().substr(0, 23);    
        stringstream ss;
        ss << left << setw(18) << ten        
            << "| " << setw(12) << dienThoai 
            << "| " << setw(27) << diaChi   
            << "| " << setw(23) << email;    

        displayData.push_back(ss.str());  

        current = current->getnextNode();  
    }

    Menu thongTinMenu(displayData.size(), displayData, "Thong Tin Employee", 25, 5, 90, displayData.size()+5);

    thongTinMenu.printMenu(0);

    while (true) {
        if (_kbhit()) {
            char key = _getch(); 
            if (key == 27) { 
                runAmenu();  
                return;  
            }
        }
    }
}


int wrong = 0;
void runADangNhap() {
    int x;
    int line = 0;
    bool thoat = false;
    
    bool timthay = true;
    bool saimatKhau = true;  

    ADangNhap.printMenu(line);  

    while (!thoat) {
        if (_kbhit()) {
            x = ADangNhap.Move();

            switch (x) {
            case 1: 
                line++;
                if (line >= ADangNhap.numberOfItem()) line = 0;
                break;
            case 2: 
                line--;
                if (line < 0) line = ADangNhap.numberOfItem() - 1;
                break;
            case 5:  

                if (!Ausername.empty() && !Apassword.empty()) {
                    auto user = dsAdmin.timUser(Ausername);
                    if (user != nullptr) {
                        admin = *user;
                        if (admin.kiemTraMatKhau(Apassword)) {
                            timthay = true;
                            saimatKhau = true;
                            Ausername = "";
                            Apassword ="";
                            wrong = 0;
                            runAmenu();
                            return; 
                        }
                        else {
                            saimatKhau = false;
                            wrong++;
                            Apassword = "";  
                            gotoxy(55, 9);
                            cout << "                    "; 
                            if (wrong >= 3) {
                                Ausername = "";
                                Apassword = "";
                                wrong = 0;
                                runChonDangNhap(); 
                                return;
                            }
                        }
                    }
                    else {
                        timthay = false;
                        wrong++;
                        if (wrong >= 3) {
                            Ausername = "";
                            Apassword = "";
                            wrong = 0;
                            runChonDangNhap();  
                            return;
                        }
                    }
                }
                else if (line == 0 || line == 1) {
                    gotoxy(55, line == 0 ? 8 : 9);
                    if (line == 0) cin >> Ausername;
                    if (line == 1) Apassword = nhapPassword();
                }
                break;
            case 8: 
                runChonDangNhap();
                return;
            }
            ADangNhap.printMenu(line);  
            if (!Ausername.empty()) {
                gotoxy(55, 8);
                cout << Ausername;
            }
            if (!Apassword.empty()) {
                gotoxy(55, 9);
                for (int i = 0; i < Apassword.size(); i++)
                    cout << '*';
            }
            gotoxy(38, 22);
            if (!timthay) {
                ADangNhap.printMenu(line);
                gotoxy(55, 15);
                cout << "Khong tim thay username ";
                Ausername = "";
                Apassword = "";
                while (true) {
                    if (_kbhit()) {
                        char key = _getch(); 
                        if (key == 13) {  
                            runADangNhap();
                            return;   
                        }
                    }
                }
            }
            else if (!saimatKhau) {
                ADangNhap.printMenu(line);
                gotoxy(55, 15);
                cout << "Sai mat khau          "; 
                Apassword = ""; 
                Ausername = "";
                while (true) {
                    if (_kbhit()) {
                        char key = _getch(); 
                        if (key == 13) {  
                            runADangNhap();
                            return;  
                        }
                    }
                }               
                gotoxy(55, 9);
            }
        }
    }
}




void runEDangNhap() {
    int x;
    int line = 0;
    bool thoat = false;

    bool timthay = true, saimatkhau = true;
    if (dsEmployee.getDau() == nullptr) {
        system("cls");
        gotoxy(55, 8);
        cout << "Khong ton tai Employee";
        while (true) {
            if (_kbhit()) {
                char key = _getch();
                if (key == 27) {  
                    runChonDangNhap();
                    return;
                }
            }
        }
    }

    EDangNhap.printMenu(line); 

    while (!thoat) {
        if (_kbhit()) {
            x = EDangNhap.Move(); 

            switch (x) {
            case 1: 
                line++;
                if (line >= EDangNhap.numberOfItem()) line = 0;
                break;
            case 2: 
                line--;
                if (line < 0) line = EDangNhap.numberOfItem() - 1;
                break;
            case 5:  
                if (!Eusername.empty() && !Epassword.empty()) {
                    auto user = dsEmployee.timUser(Eusername);
                    if (user != nullptr) {
                        employee = *user;
                        if (employee.kiemTraMatKhau(Epassword)) {
                            timthay = true;
                            saimatkhau = true;
                            if (Epassword == "111111") {
                                Eusername.clear();
                                Epassword.clear();
                                runDoiPassword1(); 
                                return;
                            }

                            Eusername.clear();
                            Epassword.clear();
                            runEmenu();
                            return;
                        }
                        else {
                            saimatkhau = false;
                            wrong++;
                            Epassword.clear();
                            gotoxy(55, 9);
                            cout << "                    ";
                            if (wrong >= 3) {
                                Eusername.clear();
                                Epassword.clear();
                                wrong = 0;
                                runChonDangNhap();
                                return;
                            }
                        }
                    }
                    else {
                        timthay = false;
                        wrong++;
                        if (wrong >= 3) {
                            Eusername.clear();
                            Epassword.clear();
                            wrong = 0;
                            runChonDangNhap();
                            return;
                        }
                    }
                }
                else if (line == 0 || line == 1) {
                    gotoxy(55, line == 0 ? 8 : 9);
                    if (line == 0) cin >> Eusername;
                    if (line == 1) Epassword = nhapPassword();
                }
                break;
            case 8: 
                runChonDangNhap();
                return;
            }

            EDangNhap.printMenu(line); 
            if (!Eusername.empty()) {
                gotoxy(55, 8);
                cout << Eusername;
            }
            if (!Epassword.empty()) {
                gotoxy(55, 9);
                for (int i = 0; i < Epassword.size(); i++)
                    cout << '*';
            }
            gotoxy(38, 22);
            if (!timthay) {
                EDangNhap.printMenu(line);
                gotoxy(55, 15);
                cout << "Khong tim thay username ";
                Eusername.clear();
                Epassword.clear();
                while (true) {
                    if (_kbhit()) {
                        char key = _getch();
                        if (key == 13) { 
                            runEDangNhap();
                            return;
                        }
                    }
                }
            }
            else if (!saimatkhau) {
                EDangNhap.printMenu(line);
                gotoxy(55, 15);
                cout << "Sai mat khau          ";
                Epassword.clear();
                Eusername.clear();
                while (true) {
                    if (_kbhit()) {
                        char key = _getch();
                        if (key == 13) {  
                            runEDangNhap();
                            return;
                        }
                    }
                }
            }
        }
    }
}


void runAmenu() {
    int x;
    int line = 0;
    bool thoat = false;

    system("cls");
    Amenu.printMenu(line);
    gotoxy(40, 15);
    while (!thoat) {
        if (_kbhit()) {
            x = Amenu.Move(); 

            switch (x) {
            case 1: 
                line++;
                if (line >= Amenu.numberOfItem()) line = 0;
                break;
            case 2:
                line--;
                if (line < 0) line = Amenu.numberOfItem() - 1;
                break;
            case 5: 
                switch (line) {
                case 0: {
                    runThemEmployee();
                    return;
                }
                case 1: {
                    runXoaEmployee();
                    return;
                }
                case 2: {
                    runTimEmployee();
                    return;
                }
                case 3: {
                    runCapNhatEmployee();
                    return;
                }
                case 4: {
                    runHienThiEmployee();
                    return;
                }
                case 5: {
                    Thoat();
                    return;
                }
                }
                return;
            case 8:
                runADangNhap();
                break;
            }
            Amenu.printMenu(line); 
            gotoxy(40, 15);
        }
    }
}

void runEmenu() {
    int x;
    int line = 0;
    bool thoat = false;

    system("cls");
    Emenu.printMenu(line);
    gotoxy(40, 15);
    while (!thoat) {
        if (_kbhit()) {
            x = Emenu.Move();

            switch (x) {
            case 1: 
                line++;
                if (line >= Emenu.numberOfItem()) line = 0;
                break;
            case 2:
                line--;
                if (line < 0) line = Emenu.numberOfItem() - 1;
                break;
            case 5: 
                switch (line) {
                case 0: {
                    runXemThongTin();
                    return;
                }
                case 1: {
                    runDoiPassword();
                    return;
                }
                case 3: {
                    Thoat();
                    return;
                }
                }

            case 8: 
                thoat = true;
                break;
            }
            Emenu.printMenu(line); 
            gotoxy(40, 15);
        }
    }
}


int main() {

    dsAdmin.docDanhSach(file +"\\Admin");
    dsEmployee.docDanhSach(file +"\\Employee");
    EDangNhap = Menu (2, { "Nhap username : ", "Nhap password: " }, "Employee Login", 35, 5, 30, 8);
    ADangNhap = Menu (2, { "Nhap username : ", "Nhap password: " }, "Admin Login", 35, 5, 30, 8);
    Amenu = Menu(6, { "Them employee", "Xoa employee", "Tim employee", "Cap nhat employee", "Hien thi thong tin employee", "Thoat"}, "Menu admin", 35, 5, 35, 16);
    Emenu = Menu(3, { "Xem thong tin tai khoan", "Doi password", "Thoat" }, "Menu employee", 35, 5, 35, 9);
    ChonDangNhap = Menu(2, { "Admin", "Employee" }, "Chon Dang Nhap", 35, 5, 30, 8);
    ThemEmployee = Menu(5, { "Username: ", "Ho va ten: ", "Dia chi: ", "So dien thoai: ", "Email: " }, "THEM EMPLOYEE", 35, 5, 70, 13);

    runChonDangNhap();
    return 0;
}