#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Info {
private:
    string ten;
    string dienThoai;
    string diaChi;
    string email;

public:
    string getTen() const {
        return ten;
    }

    void setTen(const string& tenMoi) {
        ten = tenMoi;
    }

    string getDienThoai() const {
        return dienThoai;
    }

    void setDienThoai(const string& soDienThoaiMoi) {
        dienThoai = soDienThoaiMoi;
    }

    string getDiaChi() const {
        return diaChi;
    }

    void setDiaChi(const string& diaChiMoi) {
        diaChi = diaChiMoi;
    }

    string getEmail() const {
        return email;
    }

    void setEmail(const string& emailMoi) {
        email = emailMoi;
    }
};

class Employee {
private:
    string username;
    string password;
    Info thongtin;

public:
    string getUsername() const {
        return username;
    }

    void setUsername(const string& _username) {
        username = _username;
    }

    void setPassword(const string& _password) {
        password = _password;
    }

    Info getThongTin() const {
        return thongtin;
    }

    void setThongTin(const Info& _thongtin) {
        thongtin = _thongtin;
    }

    void XemThongTin() const {
        cout << "Thong tin nhan vien:" << endl;
        cout << "Ten: " << thongtin.getTen() << endl;
        cout << "Dien thoai: " << thongtin.getDienThoai() << endl;
        cout << "Dia chi: " << thongtin.getDiaChi() << endl;
        cout << "Email: " << thongtin.getEmail() << endl;
    }
    string getPassword() const { return password; }
};

class Admin {
public:
    void ThemEmployee(vector<Employee>& employees) {
        Employee emp;
        Info info;

        string username;
        cout << "Nhap username nhan vien: ";
        cin >> username;

        for (const auto& e : employees) {
            if (e.getUsername() == username) {
                cout << "Username da ton tai. Vui long thu lai." << endl;
                return;
            }
        }

        emp.setUsername(username);
        emp.setPassword("111111");

        cin.ignore();

        cout << "Nhap ten nhan vien: ";
        string ten;
        getline(cin, ten);
        info.setTen(ten);

        cout << "Nhap so dien thoai: ";
        string dienThoai;
        getline(cin, dienThoai);
        info.setDienThoai(dienThoai);

        cout << "Nhap dia chi: ";
        string diaChi;
        getline(cin, diaChi);
        info.setDiaChi(diaChi);

        cout << "Nhap email: ";
        string email;
        getline(cin, email);
        info.setEmail(email);

        emp.setThongTin(info);
        employees.push_back(emp);

        ofstream employeeFile("Employees.txt", ios::app);
        if (employeeFile.is_open()) {
            employeeFile << username << " 111111\n";
            employeeFile.close();
        }
        else {
            cout << "Khong the mo file Employees.txt de ghi." << endl;
        }

        ofstream userFile(username + ".txt");
        if (userFile.is_open()) {
            userFile << ten << endl;
            userFile << diaChi << endl;
            userFile << dienThoai << endl;
            userFile << email << endl;
            userFile.close();
        }
        else {
            cout << "Khong the tao file " << username << ".txt de ghi." << endl;
        }

        cout << "Them nhan vien thanh cong!" << endl;
    }

    void XoaEmployee(vector<Employee>& employees) {
        string username;
        int attempts = 0;

        while (attempts < 3) {
            cout << "Nhap username nhan vien can xoa: ";
            cin >> username;

            for (auto it = employees.begin(); it != employees.end(); ++it) {
                if (it->getUsername() == username) {
                    employees.erase(it);

                    ofstream employeeFile("Employees.txt");
                    for (const auto& e : employees) {
                        employeeFile << e.getUsername() << " " << e.getPassword() << endl;
                    }
                    employeeFile.close();

                    remove((username + ".txt").c_str());

                    cout << "Xoa nhan vien thanh cong!" << endl;
                    return;
                }
            }

            attempts++;
            cout << "Khong tim thay nhan vien voi username: " << username << ". Vui long thu lai." << endl;

            if (attempts == 3) {
                cout << "Ban da nhap sai qua 3 lan. Thoat chuc nang." << endl;
            }
        }
    }

    void TimEmployee(const vector<Employee>& employees) const {
        string username;
        int attempts = 0;

        while (attempts < 3) {
            cout << "Nhap username nhan vien can tim: ";
            cin >> username;

            for (const auto& emp : employees) {
                if (emp.getUsername() == username) {
                    emp.XemThongTin();
                    return;
                }
            }

            attempts++;
            cout << "Khong tim thay nhan vien voi username: " << username << ". Vui long thu lai." << endl;

            if (attempts == 3) {
                cout << "Ban da nhap sai qua 3 lan. Thoat chuc nang." << endl;
            }
        }
    }

    void CapNhatEmployee(vector<Employee>& employees) {
        string username;
        int attempts = 0;

        while (attempts < 3) {
            cout << "Nhap username nhan vien can cap nhat: ";
            cin >> username;

            for (auto& emp : employees) {
                if (emp.getUsername() == username) {
                    Info currentInfo = emp.getThongTin();
                    Info newInfo = currentInfo;

                    string input;
                    cout << "Nhap ten moi: ";
                    cin.ignore();
                    getline(cin, input);
                    if (!input.empty()) {
                        newInfo.setTen(input);
                    }

                    cout << "Nhap so dien thoai moi: ";
                    getline(cin, input);
                    if (!input.empty()) {
                        newInfo.setDienThoai(input);
                    }

                    cout << "Nhap dia chi moi: ";
                    getline(cin, input);
                    if (!input.empty()) {
                        newInfo.setDiaChi(input);
                    }

                    cout << "Nhap email moi: ";
                    getline(cin, input);
                    if (!input.empty()) {
                        newInfo.setEmail(input);
                    }

                    emp.setThongTin(newInfo);
                    ofstream userFile(username + ".txt");
                    if (userFile.is_open()) {
                        userFile << newInfo.getTen() << endl;
                        userFile << newInfo.getDiaChi() << endl;
                        userFile << newInfo.getDienThoai() << endl;
                        userFile << newInfo.getEmail() << endl;
                        userFile.close();
                    }
                    else {
                        cout << "Khong the cap nhat file " << username << ".txt." << endl;
                    }

                    cout << "Cap nhat thong tin nhan vien thanh cong!" << endl;
                    return;
                }
            }
            attempts++;
            cout << "Khong tim thay nhan vien voi username: " << username << ". Vui long thu lai." << endl;
            if (attempts == 3) {
                cout << "Ban da nhap sai qua 3 lan. Thoat chuc nang." << endl;
            }
        }
    }

    void HienThiEmployee(const vector<Employee>& employees) const {
        if (employees.empty()) {
            cout << "Khong co nhan vien nao trong danh sach." << endl;
            return;
        }

        cout << "Danh sach nhan vien:" << endl;
        for (const auto& emp : employees) {
            cout << "Username: " << emp.getUsername() << endl;
            emp.XemThongTin();
            cout << "---------------------" << endl;
        }
    }

    void DocEmployeeTuFile(const string& username, Employee& emp) {
        ifstream userFile(username + ".txt");
        if (userFile.is_open()) {
            Info info;
            string ten, diaChi, dienThoai, email;
            getline(userFile, ten);
            getline(userFile, diaChi);
            getline(userFile, dienThoai);
            getline(userFile, email);

            info.setTen(ten);
            info.setDiaChi(diaChi);
            info.setDienThoai(dienThoai);
            info.setEmail(email);

            emp.setThongTin(info);
            userFile.close();
        }
        else {
            cout << "Khong the mo file " << username << ".txt de doc." << endl;
        }
    }
};

int main() {
    vector<Employee> employees;
    Admin admin;

    
    ifstream employeeFile("Employees.txt");
    if (employeeFile.is_open()) {
        string username, password;
        while (employeeFile >> username >> password) {
            Employee emp;
            emp.setUsername(username);
            emp.setPassword(password);
            admin.DocEmployeeTuFile(username, emp);
            employees.push_back(emp);
        }
        employeeFile.close();
    }
    else {
        cout << "Khong the mo file Employees.txt de doc." << endl;
    }

    
    int choice;
    do {
        cout << "Chuc nang:" << endl;
        cout << "1. Them nhan vien" << endl;
        cout << "2. Xoa nhan vien" << endl;
        cout << "3. Tim nhan vien" << endl;
        cout << "4. Cap nhat nhan vien" << endl;
        cout << "5. Hien thi danh sach nhan vien" << endl;
        cout << "6. Thoat" << endl;
        cout << "Nhap lua chon: ";
        cin >> choice;

        switch (choice) {
        case 1:
            admin.ThemEmployee(employees);
            break;
        case 2:
            admin.XoaEmployee(employees);
            break;
        case 3:
            admin.TimEmployee(employees);
            break;
        case 4:
            admin.CapNhatEmployee(employees);
            break;
        case 5:
            admin.HienThiEmployee(employees);
            break;
        case 6:
            cout << "Thoat." << endl;
            break;
        default:
            cout << "Lua chon khong hop le." << endl;
            break;
        }

        char continueChoice;
        do {
            cout << "Ban co muon chon chuc nang khac? (y/n): ";
            cin >> continueChoice;


            if (cin.fail() || (continueChoice != 'y' && continueChoice != 'n')) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Lua chon khong hop le. Vui long nhap 'y' hoac 'n': ";
            }
        } while (cin.fail() || (continueChoice != 'y' && continueChoice != 'n'));


        if (continueChoice == 'n') {
            choice = 6;
        }
    } while (choice != 6);

    return 0;
}
