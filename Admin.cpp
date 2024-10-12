class QuanTriVien {
public:
    string username, password;
    DanhSachNhanVien danhSachNhanVien;

    bool themNhanVien(NhanVien* nhanVien) {
        if (danhSachNhanVien.timNhanVien(nhanVien->username) != nullptr) {
            return false; 
        }
        danhSachNhanVien.themNhanVien(nhanVien);
        return true;
    }

    Node* timNhanVien(string username) {
        return danhSachNhanVien.timNhanVien(username);
    }

    bool xoaNhanVien(string username) {
        return danhSachNhanVien.xoaNhanVien(username);
    }

    bool capNhatNhanVien(string username, ThongTin thongTinMoi) {
        Node* nodeNhanVien = danhSachNhanVien.timNhanVien(username);
        if (nodeNhanVien != nullptr) {
            nodeNhanVien->nhanVien->capNhatThongTin(thongTinMoi); 
            return true;
        }
        return false;
    }

    ThongTin hienThiNhanVien(string username) {
        Node* nodeNhanVien = danhSachNhanVien.timNhanVien(username);
        if (nodeNhanVien != nullptr) {
            return nodeNhanVien->nhanVien->getThongTin();
        }
        return ThongTin();  
    }
};
