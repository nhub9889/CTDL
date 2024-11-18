#include "userfile.h"
#include <fstream>
#include <string>

// Info Class Methods
Info::Info() : ten(""), dienThoai(""), diaChi(""), email("") {}
Info::Info(string _ten, string _dienThoai, string _diaChi, string _email) : ten(_ten), dienThoai(_dienThoai), diaChi(_diaChi), email(_email){}
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
    in >> dienThoai >> diaChi >> email;
    in.close();
}

void Info::doiThongTin(string t, string dt, string dc, string e) {
    ten = t;
    dienThoai = dt;
    diaChi = dc;
    email = e;
}

// Employee Class Methods
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

// Admin Class Methods
string Admin::getUsername() { return username; }
string Admin::getPassword() { return password; }
Info Admin::getThongTin() { return thongtin; }

void Admin::setUsername(string _username) { username = _username; }
void Admin::setPassword(string _password) { password = _password; }

bool Admin::kiemTraMatKhau(string mk) { return mk == password; }

// Node Class Methods
template <typename T>
Node<T>::Node() : user(T()), nextNode(nullptr) {}

template <typename T>
Node<T>::Node(T user) : user(user), nextNode(nullptr) {}

template <typename T>
T& Node<T>::getUser() {
    return user;  // Return the user by reference
}

template <typename T>
Node<T>* Node<T>::getNext() { return nextNode; }

template <typename T>
void Node<T>::setNext(Node<T>* next) { nextNode = next; }

// DanhSach Class Methods
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
            string fileInfo = s +"\\" + name;
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
            return &(cur->getUser()); // Now we can return the address of the user
        cur = cur->getNext();
    }
    return nullptr; // User not found
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

// Explicit template instantiations
template class DanhSach<Employee>;
template class DanhSach<Admin>;
