#include <iostream>
using namespace std;

template <class T>
class Danh_Sach {
    private:
        int SoLuong;
        Node <T> Dau;
        Node <T> Cuoi;
    public:
        void DocDanhSach();
        void XayDanhSach(user);
        void HuyDanhSach();
        void Them(T);
        void Xoa(T);
        void CapNhat(T);
        void DangNhap();
};
