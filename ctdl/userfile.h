#ifndef EMPLOYEE_MANAGEMENT_H
#define EMPLOYEE_MANAGEMENT_H

#include <iostream>
#include <fstream>
using namespace std;

class Info {
private:
    string ten, dienThoai, diaChi, email;

public:
    Info();
    string getTen();
    string getDienThoai();
    string getDiaChi();
    string getEmail();
    void setThongTin(string username);
    void doiThongTin(string t, string dt, string dc, string e);
};

class Employee {
private:
    string username, password;
    Info thongtin;

public:
    string getUsername();
    string getPassword();
    Info getThongTin();
    void setUsername(string _username);
    void setPassword(string _password);
    void setThongTin(string username);
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
    Info getThongTin();
    void setUsername(string _username);
    void setPassword(string _password);
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
};

#endif // EMPLOYEE_MANAGEMENT_H
