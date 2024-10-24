#include <iostream>
#include "console.h"
#include <fstream>
#include <string>
#include <conio.h>
#include "userfile.h"
#define MAUNEN  176
#define MAUCHU  75
using namespace std;

enum TrangThai{UP, DOWN, LEFT, RIGHT, ENTER, BACK};
string thaotacEmployee[3] = { "Xem thong tin tai khoan", "Doi password", "Thoat" };
DanhSach<Employee> dsEmployee;
DanhSach<Admin> dsAdmin;
Employee e;
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
}


int menuEmployee(string thaotac[3], int n)
{
    int tt = 0;  // Trạng thái của lựa chọn hiện tại
    int* mau = new int[n];
    for (int i = 0; i < n; i++)
    {
        mau[i] = MAUCHU;  // Gán màu mặc định cho tất cả các dòng
    }


    while (1)
    {
        clrscr();  // Xóa màn hình để in menu mới

        box(10, 6, 60, 2, "Menu Employee", 22);

        for (int i = 0; i < n; i++)
        {
            // In từng mục menu với màu tương ứng
            box(10, 10 + i * 3, 60, 2, thaotac[i], mau[i]);
        }

        int z = _getch();  // Nhận phím điều khiển
        TrangThai trang_thai = key(z);  // Chuyển đổi trạng thái từ phím bấm
        mau[0] = MAUCHU;
        switch (trang_thai)
        {
        case UP:
            tt--;
            if (tt < 0) tt = n - 1;  // Quay về lựa chọn cuối nếu vượt qua đầu danh sách
            break;

        case DOWN:
            tt++;
            if (tt >= n) tt = 0;  // Quay về lựa chọn đầu nếu vượt qua cuối danh sách
            break;

        case ENTER:
            return tt;  // Trả về lựa chọn khi nhấn Enter
        }

        // Reset màu của tất cả lựa chọn về mặc định
        for (int i = 0; i < n; i++)
        {
            mau[i] = MAUCHU;  // Màu mặc định
        }

        // Đổi màu cho lựa chọn hiện tại
        mau[tt] = MAUNEN;  // Màu nổi bật cho lựa chọn hiện tại
    }
}

void xemThongtinEmployee()
{
    clrscr();  // Xóa màn hình để in menu mới

    box(10, 6, 60, 2, "Xem thong tin", 22);
    Info tt = e.XemThongTin();
    box(10, 10, 60, 2, tt.getTen(), 123);
    box(10, 13, 60, 2, tt.getDiaChi(), 123);
    box(10, 16, 60, 2, tt.getEmail(), 123);
    box(10, 19, 60, 2, tt.getDienThoai(), 123);

}



int main()
{
    dsAdmin.docDanhSach("Admin");
    dsEmployee.docDanhSach("Employee");
    e.setUsername("Ahsfjsfff");
    e.getThongTin();
	clrscr();
	int chose = menuEmployee(thaotacEmployee, 3);
    if (chose == 0) xemThongtinEmployee();
	system("pause");
}