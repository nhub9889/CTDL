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

#endif // EMPLOYEE_MANAGEMENT_H
