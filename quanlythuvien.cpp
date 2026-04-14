#include <iostream>
#include <string>
using namespace std;

// NGUYEN MANH CUONG
// Lớp cha sách
class Sach {
protected:
    string ma, ten, tacgia;
    int soluong;
public:
    Sach(string ma = "", string ten = "", string tacgia = "", int soluong = 0) {
        this->ma = ma;
        this->ten = ten;
        this->tacgia = tacgia;
        this->soluong = soluong;
    }
    virtual void nhap() {
        cin.ignore();
        cout << "Ma sach: ";
        getline(cin, ma);
        cout << "Ten sach: ";
        getline(cin, ten);
        cout << "Tac gia: ";
        getline(cin, tacgia);
        do {
            cout << "So luong: "; cin >> soluong;
            if (soluong <= 0)
                cout << "So luong phai > 0, nhap lai!\n";
        } while (soluong <= 0);
    }
    virtual void xuat() {
        cout << "- Ma: "       << ma
             << " - Ten: "     << ten
             << " - Tac gia: " << tacgia
             << " - SL: "      << soluong;
    }
    string getMa() {
         return ma; }
    string getTen() {
         return ten; }
    int getSoLuong(){
         return soluong; }
    void setSoLuong(int sl) { soluong = sl; }
    virtual ~Sach() {}
};

// NGUYEN HUY HOANG
// 3 lớp con kế thừa Sach
class SachGiaoKhoa : public Sach {
private:
    string monHoc, lop;
public:
    void nhap() override {
        Sach::nhap();
        cout << "Mon hoc: ";
        cin.ignore();
        getline(cin, monHoc);
        cout << "Lop: ";
        getline(cin, lop);
    }
    void xuat() override {
        Sach::xuat();
        cout << " - Mon: "  << monHoc
             << " - Lop: "  << lop
             << endl;
    }
};

class SachVanHoc : public Sach {
private:
    string theLoai;
public:
    void nhap() override {
        Sach::nhap();
        cin.ignore();
        cout << "The loai (tieu thuyet/tho/truyen ngan): ";
        getline(cin, theLoai);
    }
    void xuat() override {
        Sach::xuat();
        cout << " - The loai: " << theLoai
             << endl;
    }
};

class SachKhoaHoc : public Sach {
private:
    string linhVuc;
    int namXuatBan;
public:
    void nhap() override {
        Sach::nhap();
        cout << "Linh vuc: ";
        cin.ignore();
        getline(cin, linhVuc);
        do {
            cout << "Nam xuat ban: ";
            cin >> namXuatBan;
            if (namXuatBan <= 0)
                cout << "Nam xuat ban phai > 0, nhap lai!\n";
        } while (namXuatBan <= 0);
    }
    void xuat() override {
        Sach::xuat();
        cout << " - Linh vuc: " << linhVuc
             << " - Nam XB: "   << namXuatBan
             << endl;
    }
};

// LE QUANG HUY
// Lớp DocGia + Lớp Muon + Mảng + Hàm quản lý
class DocGia {
private:
    string ma, ten, sdt;
public:
    void nhap() {
        cin.ignore();
        cout << "Ma doc gia: ";
        getline(cin, ma);
        cout << "Ten: "; 
        getline(cin, ten);
        cout << "SDT: ";
        getline(cin, sdt);
    }
    void xuat() {
        cout << "Ma: "     << ma
             << " - Ten: " << ten
             << " - SDT: " << sdt << endl;
    }
    string getMa(){
         return ma; }
};

class Muon {
private:
    string maDocGia, maSach, ngayMuon, ngayTra;
public:
    void nhap() {
        cin.ignore();
        cout << "Ma doc gia: ";
        getline(cin, maDocGia);
        cout << "Ma sach: "; 
        getline(cin, maSach);
        cout << "Ngay muon: "; 
        getline(cin, ngayMuon);
        cout << "Ngay tra: ";
        getline(cin, ngayTra);
    }
    void xuat() {
        cout << "Doc gia: " << maDocGia
             << " - Sach: " << maSach
             << " - Muon: " << ngayMuon
             << " - Tra: "  << ngayTra << endl;
    }
    string getMaSach() { return maSach; }
};

const int MAX = 100;
Sach*  dsSach[MAX];
DocGia dsDocGia[MAX];
Muon   dsMuon[MAX];
int soSach = 0, soDocGia = 0, soMuon = 0;

void themDocGia() {
    dsDocGia[soDocGia].nhap();
    soDocGia++;
}

void hienThiDocGia() {
    cout << "\nDANH SACH DOC GIA:\n";
    for (int i = 0; i < soDocGia; i++)
        dsDocGia[i].xuat();
}

void hienThiSach() {
    cout << "\nDANH SACH SACH:\n";
    for (int i = 0; i < soSach; i++)
        dsSach[i]->xuat();
}

// NGUYEN ANH VU
// Hàm xử lý sách + mượn trả
void xoaSach() {
    string ma;
    cin.ignore();
    cout << "Nhap ma sach can xoa: "; getline(cin, ma);
    for (int i = 0; i < soSach; i++) {
        if (dsSach[i]->getMa() == ma) {
            delete dsSach[i];
            for (int j = i; j < soSach - 1; j++)
                dsSach[j] = dsSach[j + 1];
            soSach--;
            cout << "Da xoa!\n";
            return;
        }
    }
    cout << "Khong tim thay!\n";
}

void timSach() {
    string ten;
    cin.ignore();
    cout << "Nhap ten sach: "; getline(cin, ten);
    bool timThay = false;
    for (int i = 0; i < soSach; i++) {
        if (dsSach[i]->getTen().find(ten) != string::npos) {
            dsSach[i]->xuat();
            timThay = true;
        }
    }
    if (!timThay)
        cout << "Khong tim thay sach!\n";
}

void themSach() {
    int loai;
    do {
        cout << "Chon loai sach:\n";
        cout << "1. Sach giao khoa\n";
        cout << "2. Sach van hoc\n";
        cout << "3. Sach khoa hoc\n";
        cout << "Chon: "; cin >> loai;
        if (loai < 1 || loai > 3)
            cout << "Lua chon khong hop le, nhap lai!\n";
    } while (loai < 1 || loai > 3);

    if (loai == 1)
        dsSach[soSach] = new SachGiaoKhoa();
    else if (loai == 2)
        dsSach[soSach] = new SachVanHoc();
    else
        dsSach[soSach] = new SachKhoaHoc();

    dsSach[soSach]->nhap();
    soSach++;
}

void muonSach() {
    Muon m;
    m.nhap();
    for (int i = 0; i < soSach; i++) {
        if (dsSach[i]->getMa() == m.getMaSach()) {
            if (dsSach[i]->getSoLuong() > 0) {
                dsSach[i]->setSoLuong(dsSach[i]->getSoLuong() - 1);
                dsMuon[soMuon++] = m;
                cout << "Muon thanh cong!\n";
            } else {
                cout << "Het sach!\n";
            }
            return;
        }
    }
    cout << "Khong tim thay sach!\n";
}

void traSach() {
    string maSach;
    cin.ignore();
    cout << "Nhap ma sach tra: "; getline(cin, maSach);
    for (int i = 0; i < soMuon; i++) {
        if (dsMuon[i].getMaSach() == maSach) {
            for (int j = 0; j < soSach; j++) {
                if (dsSach[j]->getMa() == maSach)
                    dsSach[j]->setSoLuong(dsSach[j]->getSoLuong() + 1);
            }
            for (int j = i; j < soMuon - 1; j++)
                dsMuon[j] = dsMuon[j + 1];
            soMuon--;
            cout << "Tra thanh cong!\n";
            return;
        }
    }
    cout << "Khong tim thay!\n";
}

void hienThiMuon() {
    cout << "\nDANH SACH MUON:\n";
    for (int i = 0; i < soMuon; i++)
        dsMuon[i].xuat();
}

// NGUYEN MANH CUONG
// main
int main() {
    int chon;
    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Them sach\n";
        cout << "2. Hien thi sach\n";
        cout << "3. Xoa sach\n";
        cout << "4. Tim sach\n";
        cout << "5. Them doc gia\n";
        cout << "6. Hien thi doc gia\n";
        cout << "7. Muon sach\n";
        cout << "8. Tra sach\n";
        cout << "9. DS muon\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        cin >> chon;

        switch (chon) {
            case 1: themSach();      break;
            case 2: hienThiSach();   break;
            case 3: xoaSach();       break;
            case 4: timSach();       break;
            case 5: themDocGia();    break;
            case 6: hienThiDocGia(); break;
            case 7: muonSach();      break;
            case 8: traSach();       break;
            case 9: hienThiMuon();   break;
            case 0: cout << "Thoat!\n"; break;
            default: cout << "Lua chon khong hop le!\n";
        }
    } while (chon != 0);

    for (int i = 0; i < soSach; i++)
        delete dsSach[i];

    return 0;
}