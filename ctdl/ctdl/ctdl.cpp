#include <iostream>
#include <conio.h>
#include <algorithm>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include "screen.h"
#include "userfile.h"
#include <cstdio>

using namespace std;

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
        if (ch == 13) { // Enter key
            break;
        }
        else if (ch == 8 && password.length() > 0) { // Backspace key
            password.pop_back();
            cout << "\b \b"; // Erase the last character
        }
        else if (ch != 8) {
            password += ch;
            cout << "*"; // Display an asterisk for each character
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

// Kiểm tra email hợp lệ
bool isValidEmail(const string& email) {
    size_t atPos = email.find('@');
    size_t dotPos = email.find('.', atPos);
    return atPos != string::npos && dotPos != string::npos && atPos < dotPos;
}

// Kiểm tra số điện thoại hợp lệ
bool isValidPhoneNumber(const string& phone) {
    return phone.length() == 10 && all_of(phone.begin(), phone.end(), ::isdigit);
}

bool ktUser(string user) {
    if (dsEmployee.timUser(user) == nullptr) return true;
    return false;
}

string getInput(int x, int y, const string& prompt, bool (*validate)(const string& input), int maxLength) {
    gotoxy(x, y);
    cout << prompt;
    string input;
    char ch;

    while (true) {
        ch = _getch();
        if (ch == 27) { // ESC để thoát
            input.clear();
            break;
        }
        else if (ch == 13) { // Enter để xác nhận
            if (!validate || validate(input)) break;
            else {
                gotoxy(55,  20);
                cout << "So dien thoai khong hop le";
                input.clear();
                gotoxy(x + prompt.size(), y);
                cout << string(maxLength, ' '); // Xóa dòng
                gotoxy(x + prompt.size(), y);
            }
        }
        else if (ch == 8) { // Backspace
            if (!input.empty()) {
                input.pop_back();
                cout << "\b \b";
            }
        }
        else if (input.size() < maxLength) { // Thêm ký tự mới
            input += ch;
            cout << ch;
        }
    }
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
            int x = ThemEmployee.Move(); // Gọi hàm Move() từ đối tượng menu
            switch (x) {
            case 1: // Xuống
                line = (line + 1) % ThemEmployee.numberOfItem();
                break;
            case 2: // Lên
                line = (line - 1 + ThemEmployee.numberOfItem()) % ThemEmployee.numberOfItem();
                break;
            case 5: {

                switch (line) {
                case 0: // Nhập username
                    userNem = getInput(48, 8, "", nullptr, 20);
                    break;
                case 1: // Nhập họ tên
                    hoTen = getInput(49, 9, "", nullptr, 50);
                    break;
                case 2: // Nhập địa chỉ
                    Address = getInput(47, 10, "", nullptr, 100);
                    break;
                case 3: // Nhập số điện thoại
                    sdt = getInput(53, 11, "", isValidPhoneNumber, 10);
                    break;
                case 4: // Nhập email
                    mail = getInput(45, 12, "", isValidEmail, 50);
                    break;
                case 5: // Thoát
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
            // In menu
            ThemEmployee.printMenu(line);

            // Hiển thị lại các giá trị nhập
            if (!userNem.empty()) gotoxy(48, 8), cout << userNem;
            if (!hoTen.empty()) gotoxy(49, 9), cout << hoTen;
            if (!Address.empty()) gotoxy(47, 10), cout << Address;
            if (!sdt.empty()) gotoxy(53, 11), cout << sdt;
            if (!mail.empty()) gotoxy(45, 12), cout << mail;

            // Nếu tất cả thông tin đã nhập, tạo đối tượng Info
            if (!userNem.empty() && !hoTen.empty() && !Address.empty() && !sdt.empty() && !mail.empty()) {
                // Set thông tin cho employee
                employee.setUsername(userNem);
                employee.setPassword(pass);
                Info eInfo;
                eInfo.setTen(hoTen);
                eInfo.setDiaChi(Address);
                eInfo.setDienThoai(sdt);
                eInfo.setEmail(mail);
                employee.setThongTin(eInfo);
                dsEmployee.Them(employee);

                // Tạo file [username].txt chứa thông tin nhân viên
                ofstream employeeFile(file + "\\Employee\\" + userNem + ".txt");
                if (employeeFile.is_open()) {
                    employeeFile<< hoTen << endl;
                    employeeFile << Address << endl;
                    employeeFile << sdt << endl;
                    employeeFile << mail << endl;
                    employeeFile.close();
                }
                else {
                    gotoxy(55, 20);
                    cout << "Khong the tao file cho nhan vien!" << endl;
                }

                // Cập nhật file Employee.txt
                ofstream empFile("Employee.txt", ios::app);
                if (empFile.is_open()) {
                    empFile << userNem <<" 111111"; // Ghi username của nhân viên mới vào Employee.txt
                    empFile.close();
                }
                else {
                    gotoxy(55, 20);
                    cout << "Khong the cap nhat file Employee.txt!" << endl;
                }

                gotoxy(35, 17);
                cout << "Luu Nhan vien moi thanh cong";
            }
        }
    }
}

// Hàm tìm và hiển thị thông tin nhân viên
void runTimEmployee() {
    system("cls");
    string inputUsername;

    while (true) {
        // Tạo menu yêu cầu nhập username
        Menu nhapUsernameMenu(1, { "Nhap Username: " }, "Tim Nhan Vien", 35, 5, 40, 8);
        nhapUsernameMenu.printMenu(0);

        // Kiểm tra phím ESC ngay khi menu hiển thị, không cần đợi nhập
        if (_kbhit()) {
            char key = _getch();
            if (key == 27) {  // Nếu nhấn ESC, thoát về menu chính
                runAmenu();
                return;
            }
        }

        gotoxy(55, 8);
        getline(cin, inputUsername);

        // Kiểm tra nếu username rỗng
        if (inputUsername.empty()) {
            continue;  // Nếu chưa nhập username, yêu cầu nhập lại
        }

        // Kiểm tra nếu username không tồn tại
        if (!checkUserExists(inputUsername)) {
            gotoxy(35, 10);
            cout << "    Employee khong ton tai! Vui long nhap lai.";
            gotoxy(55, 8);
            inputUsername.clear();  // Xóa giá trị cũ của inputUsername để người dùng có thể nhập lại
            continue;  // Quay lại vòng lặp để người dùng nhập lại username
        }

        // Lấy thông tin nhân viên
        Info thongTin;
        thongTin.setThongTin(inputUsername);
        string ten = thongTin.getTen();
        string dienThoai = thongTin.getDienThoai();
        string diaChi = thongTin.getDiaChi();
        string email = thongTin.getEmail();

        // Tạo menu hiển thị thông tin nhân viên
        Menu thongTinMenu(5, {
            "Thong tin cua " + inputUsername + ":",
            "Ten: " + ten,
            "Dien Thoai: " + dienThoai,
            "Dia Chi: " + diaChi,
            "Email: " + email
            }, "Thong Tin Nhan Vien", 35, 5, 35, 10);

        thongTinMenu.printMenu(0);

        // Chờ người dùng nhấn phím để thoát hoặc tiếp tục
        while (true) {
            if (_kbhit()) {
                char key = _getch();
                if (key == 27) {  // Nếu nhấn ESC, thoát về menu chính
                    runAmenu();
                    return;
                }
                if (key == 13) {  // Nếu nhấn Enter, quay lại nhập lại username
                    break;  // Quay lại vòng lặp và yêu cầu nhập lại username
                }
            }
        }
    }
}




void runXoaEmployee() {
    system("cls");
    string inputUsername;

    while (true) {
        // Tạo menu yêu cầu nhập username
        Menu nhapUsernameMenu(1, { "Nhap Username: " }, "Xoa Nhan Vien", 35, 5, 40, 8);
        nhapUsernameMenu.printMenu(0);
        gotoxy(55, 8);
        getline(cin, inputUsername);

        // Kiểm tra nếu username rỗng
        if (inputUsername.empty()) {
            continue;  // Nếu chưa nhập username, yêu cầu nhập lại
        }

        // Kiểm tra nếu username không tồn tại
        if (!checkUserExists(inputUsername)) {
            gotoxy(35, 17);
            cout << "    Employee khong ton tai! Vui long nhap lai.";
            gotoxy(55, 8);
            inputUsername.clear();  // Xóa giá trị cũ của inputUsername để người dùng có thể nhập lại
            while (true) {
                if (_kbhit()) {
                    char key = _getch();  // Chờ người dùng nhấn phím
                    break;  // Khi người dùng nhấn phím, thoát khỏi vòng lặp và yêu cầu nhập lại username
                }
            }
            continue;  // Quay lại vòng lặp để người dùng nhập lại username
        }

        // Xác nhận xóa nhân viên
        gotoxy(35, 17);
        cout << "Ban co chac chan muon xoa Employee nay? (Y/N)";
        char confirm = _getch();

        if (confirm == 'Y' || confirm == 'y') {
            if (dsEmployee.xoa(inputUsername)) {
                // Xóa file [username].txt tương ứng
                string fileName = inputUsername + ".txt";
                if (remove(fileName.c_str()) == 0) {
                    gotoxy(35, 18);
                    cout << "Employee da duoc xoa thanh cong va file " << fileName << " da duoc xoa.";
                }
                else {
                    gotoxy(35, 18);
                    cout << "Employee da duoc xoa thanh cong, nhung khong the xoa file " << fileName << ".";
                    dsEmployee = DanhSach<Employee>();
                    dsEmployee.docDanhSach(file + "\\Employee");
                }

                while (true) {
                    if (_kbhit()) {
                        char key = _getch();
                        if (key == 27) {  // ESC to exit and return to menu
                            runAmenu();
                            return;
                        }
                        if (key == 13) {  // Enter to continue entering username
                            break;  // Exit the loop and go back to entering username
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
                        if (key == 27) {  // ESC to exit and return to menu
                            runAmenu();
                            return;
                        }
                        if (key == 13) {  // Enter to continue entering username
                            break;  // Exit the loop and go back to entering username
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
                    if (key == 27) {  // ESC to exit and return to menu
                        runAmenu();
                        return;
                    }
                    if (key == 13) {  // Enter to continue entering username
                        break;  // Exit the loop and go back to entering username
                    }
                }
            }
            continue;  // Nếu người dùng không muốn xóa, quay lại bước nhập username
        }
    }
}




void runChonDangNhap() {
    int x;
    int line = 0;
    bool thoat = false;

    system("cls");

    // In menu lần đầu
    ChonDangNhap.printMenu(line);
    gotoxy(40, 15);
    while (!thoat) {
        if (_kbhit()) {
            x = ChonDangNhap.Move(); // Gọi hàm Move() từ đối tượng menu

            switch (x) {
            case 1: // xuống
                line++;
                if (line >= ChonDangNhap.numberOfItem()) line = 0;
                break;
            case 2: // lên
                line--;
                if (line < 0) line = ChonDangNhap.numberOfItem() - 1;
                break;
            case 5: // enter
                if (line == 0) {
                    runADangNhap();
                }
                else runEDangNhap();
                return;
            case 8: // esc
                thoat = true;
                break;
            }
            ChonDangNhap.printMenu(line); // In lại menu với dòng được chọn mới
            gotoxy(40, 15);
        }
    }
}

void runXemThongTin() {
    // Nếu người dùng tồn tại, tạo đối tượng Info để lưu thông tin người dùng
    Info thongTin = employee.getThongTin();

    // Cố gắng đọc thông tin từ file tương ứng với username

    // Lấy thông tin từ đối tượng Info
    string ten = thongTin.getTen();
    string dienThoai = thongTin.getDienThoai();
    string diaChi = thongTin.getDiaChi();
    string email = thongTin.getEmail();

    // Tạo danh sách các mục để hiển thị thông tin qua Menu
    Menu thongTinMenu(5, {
        "Thong tin cua " + employee.getUsername() + ":",
        "Ten: " + ten,             // Không bị chia cắt bởi khoảng trắng
        "Dien Thoai: " + dienThoai,
        "Dia Chi: " + diaChi,      // Không bị chia cắt bởi khoảng trắng
        "Email: " + email         // Không bị chia cắt bởi khoảng trắng
        }, "Thong Tin Employee", 35, 5, 35, 10);

    // In thông tin bằng cách gọi printMenu của Menu
    thongTinMenu.printMenu(0);

    // Chờ người dùng nhấn phím ESC để thoát
    while (true) {
        if (_kbhit()) {
            char key = _getch();  // Lấy mã phím nhấn
            if (key == 27) {  // Kiểm tra nếu phím ESC được nhấn
                Thoat();  // Gọi hàm Thoat() để thoát
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

    // Kiểm tra mật khẩu cũ
    if (!employee.kiemTraMatKhau(oldPassword)) {
        gotoxy(40, 17);
        cout << "Mat khau hien tai khong chinh xac!!" << endl;
        _getch();
        return;
    }

    // Nhập mật khẩu mới
    gotoxy(40, 17);
    cout << "Nhap mat khau moi: ";
    string newPassword1 = nhapPassword();

    gotoxy(40, 19);
    cout << "Nhap lai mat khau moi: ";
    string newPassword2 = nhapPassword();

    // Kiểm tra sự khớp của mật khẩu mới
    if (newPassword1 != newPassword2) {
        gotoxy(40, 23);
        cout << "Mat khau moi khong khop!!" << endl;
        _getch();
        return;
    }

    // Cập nhật mật khẩu
    employee.setPassword(newPassword1);
    gotoxy(40, 23);
    cout << "Mat khau da duoc thay doi thanh cong" << endl;

    // Cập nhật file employee.txt
    ifstream infile("employee.txt");
    ofstream outfile("employee_temp.txt");

    if (!infile) {
        gotoxy(40, 25);
        cout << "Khong the mo file!" << endl;
        _getch();
        return;
    }

    string lines;
    while (getline(infile, lines)) {
        // Tách username và password
        istringstream iss(lines);
        string username, password;
        iss >> username >> password;

        if (username == employee.getUsername()) {
            // Cập nhật mật khẩu của nhân viên trong file
            outfile << username << " " << newPassword1 << endl;  // Ghi lại username với mật khẩu mới
        }
        else {
            // Nếu không phải nhân viên này, ghi lại thông tin không thay đổi
            outfile << lines << endl;
        }
    }

    infile.close();
    outfile.close();

    // Xóa file cũ và đổi tên file tạm thời thành file chính
    remove("employee.txt");
    rename("employee_temp.txt", "employee.txt");

    // Chờ người dùng nhấn phím ESC để thoát
    while (true) {
        if (_kbhit()) {
            char key = _getch();
            if (key == 27) { // Kiểm tra nếu phím ESC được nhấn
                Thoat();  // Gọi hàm Thoat() để thoát
                return;
            }
        }
    }
}



// Hàm cập nhật tên người dùng trong file
void updateName(const string& username, const string& newName) {
    string filename = username + ".txt";  // Tạo tên file theo username
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
        if (lineIndex == 1) {  // Cập nhật tên
            outfile << newName << endl;
        }
        else {
            outfile << line << endl;
        }
    }
    infile.close();
    outfile.close();
    remove(filename.c_str());  // Xóa file cũ
    rename("temp.txt", filename.c_str());  // Đổi tên file tạm thành file gốc
}

// Hàm cập nhật số điện thoại người dùng trong file
void updatePhoneNumber(const string& username, const string& newPhoneNumber) {
    string filename = username + ".txt";  // Tạo tên file theo username
    ifstream infile(filename);
    ofstream outfile("temp.txt");


    string line;
    int lineIndex = 0;
    while (getline(infile, line)) {
        lineIndex++;
        if (lineIndex == 2) {  // Cập nhật số điện thoại
            outfile << newPhoneNumber << endl;
        }
        else {
            outfile << line << endl;
        }
    }
    infile.close();
    outfile.close();
    remove(filename.c_str());  // Xóa file cũ
    rename("temp.txt", filename.c_str());  // Đổi tên file tạm thành file gốc
}

// Hàm cập nhật địa chỉ người dùng trong file
void updateAddress(const string& username, const string& newAddress) {
    string filename = username + ".txt";  // Tạo tên file theo username
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
        if (lineIndex == 3) {  // Cập nhật địa chỉ
            outfile << newAddress << endl;
        }
        else {
            outfile << line << endl;
        }
    }
    infile.close();
    outfile.close();
    remove(filename.c_str());  // Xóa file cũ
    rename("temp.txt", filename.c_str());  // Đổi tên file tạm thành file gốc
}

// Hàm cập nhật email người dùng trong file
void updateEmail(const string& username, const string& newEmail) {
    string filename = username + ".txt";  // Tạo tên file theo username
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
        if (lineIndex == 4) {  // Cập nhật email
            outfile << newEmail << endl;
        }
        else {
            outfile << line << endl;
        }
    }
    infile.close();
    outfile.close();
    remove(filename.c_str());  // Xóa file cũ
    rename("temp.txt", filename.c_str());  // Đổi tên file tạm thành file gốc
}



void runCapNhatEmployee() {
    string inputUsername;

    // Tạo menu yêu cầu nhập username
    Menu nhapUsernameMenu(1, { "Nhap Username: " }, "Nhap Username", 35, 5, 40, 8);
    nhapUsernameMenu.printMenu(0);  // In menu nhập username
    gotoxy(55, 8);  // Di chuyển con trỏ đến vị trí nhập username

    // Nhập username từ người dùng
    getline(cin, inputUsername);

    // Kiểm tra xem người dùng có tồn tại không
    if (!checkUserExists(inputUsername)) {
        gotoxy(35, 10);
        cout << "    Nguoi dung khong ton tai!" << endl;
        while (true) {
            char key = _getch();  // Đọc phím nhấn
            if (key == 27) {  // ESC để thoát về menu chính
                runAmenu();  // Quay lại menu chính
                return;
            }
        }
    }

    // Tạo menu cập nhật thông tin
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

    // Vẽ lại menu cập nhật thông tin mà không xóa màn hình
    capNhatMenu.printMenu(line);  // Vẽ menu cập nhật thông tin

    while (!thoat) {
        // Đọc phím nhấn trực tiếp từ bàn phím
        char c = _getch();
        if ((int)c == -32) c = _getch();  // Nếu là mã ASCII đặc biệt (mũi tên lên/xuống)

        switch ((int)c) {
        case 80:  // Mũi tên xuống
            line = (line == 4) ? 0 : line + 1;  // Quay lại đầu nếu đến cuối
            break;
        case 72:  // Mũi tên lên
            line = (line == 0) ? 4 : line - 1;  // Quay lại cuối nếu lên quá đầu
            break;
        case 13:  // Enter
        {
            string newInput;
            valid = false;  // Reset lại trạng thái valid

            switch (line) {
            case 0:  // Cập nhật tên
                gotoxy(35, 20);
                cout << "Nhap ten moi: ";
                getline(cin, newInput);
                if (!newInput.empty() && newInput.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") == string::npos) {
                    updateName(inputUsername, newInput);
                    valid = true;
                }
                else {
                    cout << "Thong tin khong hop le!" << endl;  // Thông báo không hợp lệ
                }
                break;
            case 1:  // Cập nhật số điện thoại
                gotoxy(35, 20);
                cout << "Nhap so dien thoai moi: ";
                getline(cin, newInput);
                if (newInput.length() == 10 && newInput[0] == '0' && std::all_of(newInput.begin(), newInput.end(), ::isdigit)) {
                    updatePhoneNumber(inputUsername, newInput);
                    valid = true;
                }
                else {
                    cout << "Thong tin khong hop le!" << endl;  // Thông báo không hợp lệ
                }
                break;
            case 2:  // Cập nhật địa chỉ
                gotoxy(35, 20);
                cout << "Nhap dia chi moi: ";
                getline(cin, newInput);
                if (!newInput.empty()) {
                    updateAddress(inputUsername, newInput);
                    valid = true;
                }
                else {
                    cout << "Thong tin khong hop le!" << endl;  // Thông báo không hợp lệ
                }
                break;
            case 3:  // Cập nhật email
                gotoxy(35, 20);
                cout << "Nhap email moi: ";
                getline(cin, newInput);
                if (newInput.find("@gmail.com") != string::npos) {
                    updateEmail(inputUsername, newInput);
                    valid = true;
                }
                else {
                    cout << "Thong tin khong hop le!" << endl;  // Thông báo không hợp lệ
                }
                break;
            case 4:  // Thoát
                thoat = true;
                break;
            }

            // Nếu cập nhật thành công, hiển thị thông báo và yêu cầu nhấn ESC để thoát
            if (valid) {
                // Thông báo thành công
                Menu thongBaoMenu(1, { "Cap Nhat Thong Tin Thanh Cong! Nhap ESC de thoat." }, "Thong Bao", 35, 5, 55, 10);
                dsEmployee = DanhSach<Employee>();
                dsEmployee.docDanhSach(file + "\\Employee");
                thongBaoMenu.printMenu(0);
            }
            else {
                // Thông báo lỗi nếu thông tin không hợp lệ
                Menu thongBaoMenu(1, { "Thong Tin Khong Hop Le! Nhap ESC de thoat." }, "Thong Bao", 35, 5, 50, 10);
                thongBaoMenu.printMenu(0);
            }

            // Chờ người dùng nhấn ESC để thoát
            while (true) {
                char key = _getch();  // Đọc phím nhấn
                if (key == 27) {  // ESC để thoát về menu chính
                    runAmenu();  // Quay lại menu chính
                    return;
                }
            }

            break;
        }
        case 27:  // ESC để thoát về menu chính
            runAmenu();  // Quay lại menu chính
            return;
        }

        // Vẽ lại menu cập nhật sau khi chọn mà không cần xóa màn hình
        capNhatMenu.printMenu(line);  // Vẽ lại menu mỗi khi có sự thay đổi
    }
}



void runHienThiEmployee() {
    system("cls");

    // Tạo menu hiển thị danh sách thông tin nhân viên
    vector<string> displayData;

    // Thêm tiêu đề vào vector displayData
    displayData.push_back("Danh Sach Employee:");
    displayData.push_back("Ten\tDien Thoai\tDia Chi\tEmail");

    // Duyệt qua danh sách nhân viên (linked list)
    Node<Employee>* current = dsEmployee.getDau();  // Truy cập đầu danh sách nhân viên

    // Lặp qua tất cả các phần tử trong danh sách liên kết
    while (current != nullptr) {
        Employee emp = current->getNode();  // Lấy dữ liệu nhân viên từ node
        Info info = emp.getThongTin();

        // Tạo chuỗi thông tin nhân viên
        string employeeData = info.getTen() + "\t"  // Tên
            + info.getDienThoai() + "\t"  // Điện thoại
            + info.getDiaChi() + "\t"  // Địa chỉ
            + info.getEmail();  // Email
        displayData.push_back(employeeData);  // Thêm thông tin vào danh sách hiển thị

        current = current->getnextNode();  // Di chuyển đến phần tử tiếp theo trong danh sách
    }

    // Tạo menu hiển thị danh sách nhân viên
    Menu thongTinMenu(displayData.size(), displayData, "Thong Tin Employee", 35, 5, 35, 10);

    // In thông tin bằng cách gọi printMenu của Menu
    thongTinMenu.printMenu(0);

    // Chờ người dùng nhấn phím ESC để thoát
    while (true) {
        if (_kbhit()) {
            char key = _getch();  // Lấy mã phím nhấn
            if (key == 27) {  // Kiểm tra nếu phím ESC được nhấn
                Thoat();  // Gọi hàm Thoat() để thoát
                return;   // Thoát khỏi hàm
            }
        }
    }
}




void runADangNhap() {
    int x;
    int line = 0;
    bool thoat = false;
    int wrong = 0;
    bool timthay = true;
    bool saimatKhau = true;

    ADangNhap.printMenu(line);  // Initial menu print (no system("cls") here)

    while (!thoat) {
        if (_kbhit()) {
            x = ADangNhap.Move();  // Call Move() from menu object

            if (!Ausername.empty()) {
                gotoxy(55, 8);
                cout << Ausername;
            }

            switch (x) {
            case 1:  // down
                line++;
                if (line >= ADangNhap.numberOfItem()) line = 0;
                break;
            case 2:  // up
                line--;
                if (line < 0) line = ADangNhap.numberOfItem() - 1;
                break;
            case 5:  // enter
                if (!Ausername.empty() && !Apassword.empty()) {
                    if (dsAdmin.timUser(Ausername) != nullptr) {
                        admin = *dsAdmin.timUser(Ausername);
                        if (admin.kiemTraMatKhau(Apassword)) {
                            Ausername.clear();
                            Apassword.clear();
                            runAmenu();
                            return;
                        }
                        else {
                            saimatKhau = false;
                            wrong++;
                            if (wrong >= 3) {
                                runChonDangNhap();  // Run the main menu after 3 wrong attempts
                                return;  // Exit the function to avoid further attempts
                            }
                            Ausername.clear();
                            Apassword.clear();
                        }
                    }
                    else {
                        // Username not found
                        timthay = false;
                        wrong++;
                        if (wrong >= 3) {
                            runChonDangNhap();  // Run the main menu after 3 wrong attempts
                            return;  // Exit the function to avoid further attempts
                        }
                        Ausername.clear();
                        Apassword.clear();
                    }
                }
                else {
                    switch (line) {
                    case 0: {
                        gotoxy(55, 8);  // Position for username input
                        string input;
                        cin >> input;  // Allow full username input
                        Ausername = input;
                        break;
                    }
                    case 1: {
                        gotoxy(55, 9);  // Position for password input
                        Apassword = nhapPassword();  // Secure password input
                        break;
                    }
                    }
                }
                break;
            case 8:  // esc
                thoat = true;  // Exit the loop
                break;
            }

            ADangNhap.printMenu(line);  // Print menu after each action

            if (!Ausername.empty()) {
                gotoxy(55, 8);
                cout << Ausername;
            }
            if (!Apassword.empty()) {
                gotoxy(55, 9);
                for (int i = 0; i < Apassword.size(); i++)
                    cout << '*';
            }

            if (Ausername.empty() && Apassword.empty()) {
                if (!timthay) {
                    gotoxy(38, 22);
                    cout << "Khong tim thay username";
                }
                else {
                    gotoxy(38, 22);
                    cout << "Sai mat khau";
                }
            }
            gotoxy(40, 15);
        }
    }
}


void runEDangNhap() {
    int x;
    int line = 0;
    bool thoat = false;
    int wrong = 0;
    bool timthay = true, saimatkhau = true;

    EDangNhap.printMenu(line);  // Initial menu print (no system("cls") here)

    while (!thoat) {
        if (_kbhit()) {
            x = EDangNhap.Move();  // Call Move() from menu object

            if (!Eusername.empty()) {
                gotoxy(55, 8);
                cout << Eusername;
            }

            switch (x) {
            case 1:  // down
                line++;
                if (line >= EDangNhap.numberOfItem()) line = 0;
                break;
            case 2:  // up
                line--;
                if (line < 0) line = EDangNhap.numberOfItem() - 1;
                break;
            case 5:  // enter
                if (!Eusername.empty() && !Epassword.empty()) {
                    if (dsEmployee.timUser(Eusername) != nullptr) {
                        employee = *dsEmployee.timUser(Eusername);
                        if (employee.kiemTraMatKhau(Epassword)) {
                            Eusername.clear();
                            Epassword.clear();
                            runEmenu();
                            return;
                        }
                        else {
                            // Incorrect password
                            saimatkhau = false;
                            wrong++;
                            if (wrong >= 3) {
                                runChonDangNhap();  // Run the main menu after 3 wrong attempts
                                return;  // Exit the function to avoid further attempts
                            }
                            Eusername.clear();
                            Epassword.clear();
                        }
                    }
                    else {
                        // Username not found
                        timthay = false;
                        wrong++;
                        if (wrong >= 3) {
                            runChonDangNhap();  // Run the main menu after 3 wrong attempts
                            return;  // Exit the function to avoid further attempts
                        }
                        Eusername.clear();
                        Epassword.clear();
                    }
                }
                else {
                    switch (line) {
                    case 0: {
                        gotoxy(55, 8);  // Position for username input
                        string input;
                        cin >> input;  // Allow full username input
                        Eusername = input;
                        break;
                    }
                    case 1: {
                        gotoxy(55, 9);  // Position for password input
                        Epassword = nhapPassword();  // Secure password input
                        break;
                    }
                    }
                }
                break;
            case 8:  // esc
                thoat = true;  // Exit the loop
                break;
            }

            EDangNhap.printMenu(line);  // Print menu after each action

            if (!Eusername.empty()) {
                gotoxy(55, 8);
                cout << Eusername;
            }
            if (!Epassword.empty()) {
                gotoxy(55, 9);
                for (int i = 0; i < Epassword.size(); i++)
                    cout << '*';
            }

            if (Eusername.empty() && Epassword.empty()) {
                if (!timthay) {
                    gotoxy(38, 22);
                    cout << "Khong tim thay username";
                }
                else {
                    gotoxy(38, 22);
                    cout << "Sai mat khau";
                }
            }
            gotoxy(40, 15);
        }
    }
}


void runAmenu() {
    int x;
    int line = 0;
    bool thoat = false;

    system("cls");

    // In menu lần đầu
    Amenu.printMenu(line);
    gotoxy(40, 15);
    while (!thoat) {
        if (_kbhit()) {
            x = Amenu.Move(); // Gọi hàm Move() từ đối tượng menu

            switch (x) {
            case 1: // xuống
                line++;
                if (line >= Amenu.numberOfItem()) line = 0;
                break;
            case 2: // lên
                line--;
                if (line < 0) line = Amenu.numberOfItem() - 1;
                break;
            case 5: // enter
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
            case 8: // esc
                thoat = true;
                break;
            }
            Amenu.printMenu(line); // In lại menu với dòng được chọn mới
            gotoxy(40, 15);
        }
    }
}

void runEmenu() {
    int x;
    int line = 0;
    bool thoat = false;

    system("cls");

    // In menu lần đầu
    Emenu.printMenu(line);
    gotoxy(40, 15);
    while (!thoat) {
        if (_kbhit()) {
            x = Emenu.Move(); // Gọi hàm Move() từ đối tượng menu

            switch (x) {
            case 1: // xuống
                line++;
                if (line >= Emenu.numberOfItem()) line = 0;
                break;
            case 2: // lên
                line--;
                if (line < 0) line = Emenu.numberOfItem() - 1;
                break;
            case 5: // enter
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

            case 8: // esc
                thoat = true;
                break;
            }
            Emenu.printMenu(line); // In lại menu với dòng được chọn mới
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
    Emenu = Menu(3, { "Xem thong tin tai lhoan", "Doi password", "Thoat" }, "Menu employee", 35, 5, 35, 9);
    ChonDangNhap = Menu(2, { "Admin", "Employee" }, "Chon Dang Nhap", 35, 5, 30, 8);
    ThemEmployee = Menu(5, { "Username: ", "Ho va ten: ", "Dia chi: ", "So dien thoai: ", "Email: " }, "THEM EMPLOYEE", 35, 5, 50, 16);

    runChonDangNhap();
    return 0;
}