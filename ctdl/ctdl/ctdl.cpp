#include <iostream>
#include "console.h"
#include <fstream>
#include <string>
#include <conio.h>
#include <cstdlib>
#include "userfile.h"
#define MAUNEN  176
#define MAUCHU  75
using namespace std;


enum TrangThai{UP, DOWN, LEFT, RIGHT, ENTER, BACK};
string thaotac[3] = { "Xem thong tin tai khoan", "Doi password", "Thoat" };
DanhSach<Employee> dsEmployee;
DanhSach<Admin> dsAdmin;
Employee e;


void xemThongtinEmployee();
void menuEmployee();
void doiPassword();


void box(int x, int y, int w, int h, string s, int textcolor)
{

    TextColor(MAUCHU);
    for (int ix = x; ix < x + w; ix++)
    {
        gotoXY(ix, y);
        cout << '*';
        gotoXY(ix, y + h);
        cout << '*';
    }

    for (int iy = y + 1; iy <= y + h - 1; iy++)
    {
        gotoXY(x, iy);
        cout << '*';
        gotoXY(x + w - 1, iy);
        cout << '*';
    }

    TextColor(textcolor);
    int k = (w - s.size()) / 2;
    gotoXY(x + k, y + h / 2);
    cout << s;
    
}

TrangThai key(int k)
{
	if (k == 224)
	{
		char c = _getch();
		switch (c)
		{
		case 72: return UP;
		case 80: return DOWN;
		case 75: return LEFT;
		case 77: return RIGHT;
		}
	}
	else if (k == 13) return ENTER;
    else if (k == 27) return BACK;
}

 void xemThongtinEmployee()
{
    TextColor(7);
    clrscrA();  // Xóa màn hình để in menu mới

    // Thiết lập màu mặc định cho văn bản (ví dụ, trắng trên nền đen)


    // Tạo khung và in thông tin của Employee
    box(10, 6, 60, 2, "Xem thong tin", 22);

    Info tt = e.getThongTin();

    // In thông tin với màu mặc định
    TextColor(15);  // Màu trắng
    box(10, 10, 60, 2, tt.getTen(), 15);  // In tên nhân viên
    box(10, 13, 60, 2, tt.getDiaChi(), 15);  // In địa chỉ
    box(10, 16, 60, 2, tt.getEmail(), 15);  // In email
    box(10, 19, 60, 2, tt.getDienThoai(), 15);  // In số điện thoại

    gotoXY(0, 33);  // Đưa con trỏ về góc dưới cùng màn hình để tránh ghi đè
    int z = _getch();  // Nhận phím điều khiển
    TrangThai trang_thai = key(z);
    if (trang_thai) menuEmployee();
}

 string nhapPassword() {
     string password = "";
     char ch;
     while (true) {
         ch = _getch();
         if (ch == 13)
             break;// Lấy ký tự người dùng nhập, không hiển thị trên màn hình
         else if (ch == 27) {  // Nhấn Enter
             menuEmployee();
         }
         else if (ch == 8 && password.length() > 0) {  // Nhấn Backspace
             password.pop_back();
             cout << "\b \b";  // Xóa ký tự trên màn hình
         }
         else if (ch != 8) {
             password += ch;
             cout << "*";  // Hiển thị dấu "*" thay vì ký tự thực tế
         }
         
     }
     return password;
 }

void matkhaumoi()
{
    TextColor(7);
    clrscrA();  // Xóa màn hình để in menu mới

    // Thiết lập màu mặc định cho văn bản (ví dụ, trắng trên nền đen)

    // Tạo khung nhap mat khau
    box(10, 6, 60, 2, "Nhap password moi", 22);
    box(10, 10, 60, 2, "", 15);
    gotoXY(13, 11);
    string s = nhapPassword();
    e.DoiPassWord(s);
    menuEmployee();
}

void doiPassword()
{
    TextColor(7);
    clrscrA();  // Xóa màn hình để in menu mới

    // Thiết lập màu mặc định cho văn bản (ví dụ, trắng trên nền đen)

    // Tạo khung nhap mat khau
    box(10, 6, 60, 2, "Nhap password", 22);
    int dem = 0;
    box(10, 10, 60, 2, "", 15);
    gotoXY(13, 11);
    string s = nhapPassword();

    while(!e.kiemTraMatKhau(s)&&dem<3)
    {
        TextColor(7);
        clrscrA();  // Xóa màn hình để in menu mới

        // Thiết lập màu mặc định cho văn bản (ví dụ, trắng trên nền đen)

        // Tạo khung nhap mat khau
        box(10, 6, 60, 2, "Nhap password", 22);
        box(10, 10, 60, 2, "", 15);
        
        gotoXY(13, 11);
        box(10, 19, 60, 2, "Sai password", 22);
        gotoXY(13, 11);
        dem++;
		TextColor(7);
        s = nhapPassword();
    }
    if(dem>=3)
    {
        TextColor(7);
        clrscrA();
        return;
	    //Man dang nhap
    }
    else
    {
        matkhaumoi();
    }

}

void thoat()
{

    exit(0);
}

void menuEmployee()
{
    TextColor(7);
    clrscrA();
    int tt = 0;  // Trạng thái của lựa chọn hiện tại
    int* mau = new int[3];
    for (int i = 0; i < 3; i++)
    {
        mau[i] = MAUCHU;  // Gán màu mặc định cho tất cả các dòng
    }

    mau[0] = MAUNEN;
    while (1)
    {
        clrscr();  // Xóa màn hình để in menu mới

        box(10, 6, 60, 2, "Menu Employee", 22);
        
        for (int i = 0; i < 3; i++)
        {
            // In từng mục menu với màu tương ứng
            box(10, 10 + i * 3, 60, 2, thaotac[i], mau[i]);
        }
        int z = _getch();  // Nhận phím điều khiển
        TrangThai trang_thai = key(z);  // Chuyển đổi trạng thái từ phím bấm
       
        switch (trang_thai)
        {
        case UP:
            tt--;
            if (tt < 0) tt = 2;  // Quay về lựa chọn cuối nếu vượt qua đầu danh sách
            break;

        case DOWN:
            tt++;
            if (tt >= 3) tt = 0;  // Quay về lựa chọn đầu nếu vượt qua cuối danh sách
            break;

        case ENTER:
            clrscr();
            switch(tt)
            {
            case 0:
                xemThongtinEmployee();
                break;
            case 1:
                doiPassword();
                break;
            case 2:
                thoat();
                break;
            }
        }

        // Reset màu của tất cả lựa chọn về mặc định
        for (int i = 0; i < 3; i++)
        {
            mau[i] = MAUCHU;  // Màu mặc định
        }
        
        // Đổi màu cho lựa chọn hiện tại
        mau[tt] = MAUNEN;  // Màu nổi bật cho lựa chọn hiện tại
    }
   
}




int main()
{
    cout << e.getPassword();
    dsAdmin.docDanhSach("Admin");
    dsEmployee.docDanhSach("Employee");
    e.setThongTin("C:\\Users\\Lenovo\\Desktop\\up\\VS\\ctdl\\ctdl\\Ahsfjsfff");
    Info tt = e.getThongTin();
    e.DoiPassWord("123456789");
    menuEmployee();

    
}