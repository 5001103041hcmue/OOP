#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <fstream> 
#include <sstream> 
#include <windows.h> 
using namespace std;

// --- HAM TO MAU ---
void Mau(int k) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
}

template <class T>
T nhapkhongam(const string &msg) 
{
    T x;
    cout << msg;
    cin >> x;
    while (x < 0) 
    {
        Mau(12); cout << "Gia tri khong duoc am. Nhap lai: "; Mau(15);
        cin >> x;
    }
    cin.ignore();
    return x;
}

bool KiemTraChua(string chuoiMe, string chuoiCon) {
    if (chuoiMe.find(chuoiCon) != string::npos) return true;
    return false;
}

// ========================================================================
//                              CLASS GIANG VIEN
// ========================================================================
class GiangVien 
{
protected: 
    string maDD;
    string hoTen;
    string gioiTinh; 
    string monHoc;   
    float heSoLuong;
    int soTietDay;   
    int soTietVang;  
public:
    GiangVien(string ma="", string ten="", string gt="", string mon="", float hsl=0, int tiet=0, int vang=0);
    virtual ~GiangVien(){} 
    
    void setMaDD(string ma); void setHoTen(string ten); void setGioiTinh(string gt);
    void setMonHoc(string mon); void setHeSoLuong(float hsl); void setSoTietDay(int s); void setSoTietVang(int v);

    string getMaDD(); string getHoTen(); string getGioiTinh(); string getMonHoc();
    float getHeSoLuong(); int getSoTietDay(); int getSoTietVang();

    int getSoTietThucTe(); 
    void HienThiXuatPhat(); 

    virtual long ThanhToanLuong() = 0;
    virtual void HienThiThongTin() = 0 ;
    virtual int getLoaiGV() = 0;
    virtual string LayPhieuLuong() = 0; 

    virtual void GhiFile(ofstream &f);
    virtual void DocFile(ifstream &f);

    friend istream& operator>>(istream &is, GiangVien &g);
    friend ostream& operator<<(ostream &os, GiangVien &g);
};

// ========================================================================
//                              CLASS CO HUU
// ========================================================================
class CoHuu: public GiangVien 
{
private:
    int thamNien;
    long luongCung;
    long TienTrongDM200t;
    long TienNgoaiDM200t;
public:
    CoHuu(string ma="", string ten="", string gt="", string mon="", float hsl=0, int tiet=0, int vang=0, int tn=0, long lcs=2340000, long tien1Tiet=0);
    CoHuu(const CoHuu &c);
    ~CoHuu();

    void setThamNien(int tn); void setTienTrongDM200t(long t); void setTienNgoaiDM200t(long t);
    int getThamNien(); long getTienTrongDM200t(); long getTienNgoaiDM200t();

    long TinhLuongCoBan();
    long TinhPhuCap();
    long TinhTienTrongDM();
    long TinhTienNgoaiDM();

    long ThanhToanLuong();
    void HienThiThongTin();
    int getLoaiGV() { return 1; } 
    string LayPhieuLuong(); 

    void GhiFile(ofstream &f);
    void DocFile(ifstream &f);

    friend istream& operator>>(istream &is, CoHuu &c);
    friend ostream& operator<<(ostream &os, CoHuu &c);
};

// ========================================================================
//                            CLASS THINH GIANG
// ========================================================================
class ThinhGiang: public GiangVien {
private:
    string maGV;
    long tienTheoTiet;
public:
    ThinhGiang(string maDD="", string maGV_="", string ten="", string gt="", string mon="", float hsl=0, int tiet=0, int vang=0, long tien=0);
    ThinhGiang(const ThinhGiang &t);
    ~ThinhGiang();

    void setMaGV(string m); void setTienTheoTiet(long t);
    string getMaGV(); long getTienTheoTiet();
    
    long ThanhToanLuong();
    void HienThiThongTin();
    int getLoaiGV() { return 2; } 
    string LayPhieuLuong(); 

    void GhiFile(ofstream &f);
    void DocFile(ifstream &f);

    friend istream& operator>>(istream &is, ThinhGiang &t);
    friend ostream& operator<<(ostream &os, ThinhGiang &t);
};

// ========================================================================
//                     DINH NGHIA HAM CHI TIET
// ========================================================================

// --- GIANG VIEN ---
GiangVien::GiangVien(string ma, string ten, string gt, string mon, float hsl, int tiet, int vang) { 
    maDD=ma; hoTen=ten; gioiTinh=gt; monHoc=mon; heSoLuong=hsl; soTietDay=tiet; soTietVang=vang;
}
void GiangVien::setMaDD(string ma){ maDD=ma; } void GiangVien::setHoTen(string ten){ hoTen=ten; }
void GiangVien::setGioiTinh(string gt){ gioiTinh=gt; } void GiangVien::setMonHoc(string mon){ monHoc=mon; }
void GiangVien::setHeSoLuong(float hsl){ heSoLuong=hsl; } void GiangVien::setSoTietDay(int s){ soTietDay=s; }
void GiangVien::setSoTietVang(int v){ soTietVang=v; }
string GiangVien::getMaDD(){ return maDD; } string GiangVien::getHoTen(){ return hoTen; }
string GiangVien::getGioiTinh(){ return gioiTinh; } string GiangVien::getMonHoc(){ return monHoc; }
float GiangVien::getHeSoLuong(){ return heSoLuong; } int GiangVien::getSoTietDay(){ return soTietDay; }
int GiangVien::getSoTietVang(){ return soTietVang; }

int GiangVien::getSoTietThucTe() {
    int thuc = soTietDay - soTietVang;
    return (thuc < 0) ? 0 : thuc;
}

void GiangVien::HienThiXuatPhat() {
    cout << left << setw(10) << maDD 
         << left << setw(32) << hoTen    
         << left << setw(6)  << gioiTinh 
         << left << setw(45) << monHoc;  
}

void GiangVien::GhiFile(ofstream &f) {
    f << getLoaiGV() << endl << maDD << endl << hoTen << endl << gioiTinh << endl << monHoc << endl << heSoLuong << endl << soTietDay << endl << soTietVang << endl;
}
void GiangVien::DocFile(ifstream &f) {
    getline(f, maDD); getline(f, hoTen); getline(f, gioiTinh); getline(f, monHoc);
    f >> heSoLuong; f >> soTietDay; f >> soTietVang;
}
istream& operator>>(istream &is, GiangVien &g) {
    cout<<"Nhap ma dinh danh: "; is>>ws; getline(is,g.maDD);
    cout<<"Nhap ho ten: "; getline(is,g.hoTen);
    cout<<"Nhap gioi tinh: "; getline(is, g.gioiTinh);
    cout<<"Nhap mon hoc: ";   getline(is, g.monHoc);
    g.setHeSoLuong(nhapkhongam<float>("Nhap he so luong: "));
    g.setSoTietDay(nhapkhongam<int>("Nhap so tiet day: "));
    g.setSoTietVang(nhapkhongam<int>("Nhap so tiet vang: ")); 
    return is;
}

// --- CO HUU ---
CoHuu::CoHuu(string ma,string ten,string gt,string mon,float hsl,int tiet,int vang,int tn,long lcs,long tien1Tiet)
: GiangVien(ma,ten,gt,mon,hsl,tiet,vang) { 
    thamNien=tn; luongCung=lcs; TienTrongDM200t=tien1Tiet; TienNgoaiDM200t=(long)(tien1Tiet*1.5); 
}
CoHuu::CoHuu(const CoHuu &c): GiangVien(c) {
    thamNien=c.thamNien; luongCung=c.luongCung; TienTrongDM200t=c.TienTrongDM200t; TienNgoaiDM200t=c.TienNgoaiDM200t;
}
CoHuu::~CoHuu(){}
void CoHuu::setThamNien(int tn){ thamNien=tn; } void CoHuu::setTienTrongDM200t(long t){ TienTrongDM200t=t; }
void CoHuu::setTienNgoaiDM200t(long t){ TienNgoaiDM200t=t; }
int CoHuu::getThamNien(){ return thamNien; } long CoHuu::getTienTrongDM200t(){ return TienTrongDM200t; }
long CoHuu::getTienNgoaiDM200t(){ return TienNgoaiDM200t; }

long CoHuu::TinhLuongCoBan() { return (long)(getHeSoLuong() * luongCung); }
long CoHuu::TinhPhuCap() { return (long)(TinhLuongCoBan() * 0.3 + TinhLuongCoBan() * thamNien * 0.01); }
long CoHuu::TinhTienTrongDM() { return min(getSoTietThucTe(), 200) * TienTrongDM200t; }
long CoHuu::TinhTienNgoaiDM() { return max(getSoTietThucTe() - 200, 0) * TienNgoaiDM200t; }

long CoHuu::ThanhToanLuong() {
    return TinhLuongCoBan() + TinhPhuCap() + TinhTienTrongDM() + TinhTienNgoaiDM();
}

void CoHuu::HienThiThongTin() {
    HienThiXuatPhat(); 
    // Tang cot Loai len 12
    cout << left << setw(12) << "Co Huu" 
         << right << setw(8) << getSoTietThucTe() 
         << right << setw(15) << ThanhToanLuong() << endl;
}

// GIU NGUYEN CODE CUA BAN
string CoHuu::LayPhieuLuong() {
    stringstream ss;
    string line = "==============================================================\n";
    string strHSL = "(HSL " + to_string(getHeSoLuong()).substr(0, 4) + ")"; 

    ss << line << "||                PHIEU LUONG GIANG VIEN CO HUU             ||\n" << line;
    ss << "|| " << left << setw(30) << ("Ho ten: " + getHoTen()) << left << setw(26) << ("Ma: " + getMaDD()) << " ||\n";
    ss << "|| " << left << setw(30) << ("Mon: " + getMonHoc()) << left << setw(26) << ("TN: " + to_string(thamNien) + " nam") << " ||\n";
    ss << line << "||                      CHI TIET THU NHAP                   ||\n||                                                          ||\n";

    ss << "|| " << left << setw(35) << ("1. Luong co ban " + strHSL + ":") << right << setw(21) << (to_string(TinhLuongCoBan()) + " VND") << " ||\n";
    ss << "|| " << left << setw(35) << "2. Phu cap tham nien:" << right << setw(21) << (to_string(TinhPhuCap()) + " VND") << " ||\n";
    ss << "|| " << left << setw(35) << "3. Thu lao (Trong DM):" << right << setw(21) << (to_string(TinhTienTrongDM()) + " VND") << " ||\n";
    ss << "|| " << left << setw(35) << "4. Thu lao (Ngoai DM):" << right << setw(21) << (to_string(TinhTienNgoaiDM()) + " VND") << " ||\n";
    
    ss << "||                                                          ||\n";
    string chiTiet = "DKy: " + to_string(getSoTietDay()) + ", Vang: " + to_string(getSoTietVang()) + ", Thuc: " + to_string(getSoTietThucTe());
    ss << "|| * " << left << setw(54) << chiTiet << " ||\n";
    ss << line << "|| TONG THUC LANH: " << right << setw(39) << (to_string(ThanhToanLuong()) + " VND") << "  ||\n" << line;
    return ss.str();
}

void CoHuu::GhiFile(ofstream &f) { GiangVien::GhiFile(f); f << thamNien << endl << TienTrongDM200t << endl; }
void CoHuu::DocFile(ifstream &f) { GiangVien::DocFile(f); f >> thamNien; f >> TienTrongDM200t; TienNgoaiDM200t = (long)(TienTrongDM200t * 1.5); }
istream& operator>>(istream &is, CoHuu &c) {
    string temp; cout << "Nhap ma dinh danh: "; is.ignore(); getline(is, temp); c.setMaDD(temp);
    cout << "Nhap ho ten: "; getline(is, temp); c.setHoTen(temp);
    cout << "Nhap gioi tinh: "; getline(is, temp); c.setGioiTinh(temp);
    cout << "Nhap mon hoc: "; getline(is, temp); c.setMonHoc(temp);
    c.setHeSoLuong(nhapkhongam<float>("Nhap he so luong: "));
    c.setSoTietDay(nhapkhongam<int>("Nhap so tiet day: "));
    c.setSoTietVang(nhapkhongam<int>("Nhap so tiet vang: "));
    c.setThamNien(nhapkhongam<int>("Nhap tham nien: "));
    c.setTienTrongDM200t(nhapkhongam<long>("Tien 1 tiet: "));
    c.setTienNgoaiDM200t((long)(c.getTienTrongDM200t()*1.5));
    return is;
}

// --- THINH GIANG ---
ThinhGiang::ThinhGiang(string maDD_,string maGV_,string ten,string gt,string mon,float hsl,int tiet,int vang,long tien)
: GiangVien(maDD_,ten,gt,mon,hsl,tiet,vang) { maGV=maGV_; tienTheoTiet=tien; }
ThinhGiang::ThinhGiang(const ThinhGiang &t): GiangVien(t) { maGV=t.maGV; tienTheoTiet=t.tienTheoTiet; }
ThinhGiang::~ThinhGiang(){}
void ThinhGiang::setMaGV(string m){ maGV=m; } void ThinhGiang::setTienTheoTiet(long t){ tienTheoTiet=t; }
string ThinhGiang::getMaGV(){ return maGV; } long ThinhGiang::getTienTheoTiet(){ return tienTheoTiet; }

long ThinhGiang::ThanhToanLuong() { return getSoTietThucTe() * tienTheoTiet; }

void ThinhGiang::HienThiThongTin() {
    HienThiXuatPhat(); 
    // Tang cot Loai len 12 de vua chu Thinh Giang
    cout << left << setw(12) << "Thinh Giang" 
         << right << setw(8) << getSoTietThucTe() 
         << right << setw(15) << ThanhToanLuong() << endl;
}

// GIU NGUYEN CODE CUA BAN
string ThinhGiang::LayPhieuLuong() {
    stringstream ss;
    string line = "==============================================================\n";
    ss << line << "||              PHIEU LUONG GIANG VIEN THINH GIANG          ||\n" << line;
    ss << "|| " << left << setw(30) << ("Ho ten: " + getHoTen()) << left << setw(26) << ("Ma: " + getMaDD()) << " ||\n";
    ss << "|| " << left << setw(30) << ("Don vi: " + maGV) << left << setw(26) << ("Mon: " + getMonHoc()) << " ||\n";
    ss << line << "||                      CHI TIET THU NHAP                   ||\n";
    ss << "|| " << left << setw(35) << "1. Tong tiet dang ky:" << right << setw(21) << (to_string(getSoTietDay()) + " tiet") << " ||\n";
    ss << "|| " << left << setw(35) << "2. So tiet vang:" << right << setw(21) << (to_string(getSoTietVang()) + " tiet") << " ||\n";
    ss << "|| " << left << setw(35) << "3. So tiet thuc day:" << right << setw(21) << (to_string(getSoTietThucTe()) + " tiet") << " ||\n";
    ss << "|| " << left << setw(35) << "4. Don gia:" << right << setw(21) << (to_string(tienTheoTiet) + " VND") << " ||\n";
    ss << "||                                                          ||\n";
    ss << line << "|| TONG THUC LANH: " << right << setw(39) << (to_string(ThanhToanLuong()) + " VND") << "  ||\n" << line;
    return ss.str();
}

void ThinhGiang::GhiFile(ofstream &f) { GiangVien::GhiFile(f); f << maGV << endl << tienTheoTiet << endl; }
void ThinhGiang::DocFile(ifstream &f) { GiangVien::DocFile(f); f.ignore(); getline(f, maGV); f >> tienTheoTiet; }
istream& operator>>(istream &is, ThinhGiang &t) {
    string temp; cout << "Nhap ma dinh danh: "; is.ignore(); getline(is, temp); t.setMaDD(temp);
    cout << "Nhap ho ten: "; getline(is, temp); t.setHoTen(temp);
    cout << "Nhap gioi tinh: "; getline(is, temp); t.setGioiTinh(temp);
    cout << "Nhap mon hoc: ";   getline(is, temp); t.setMonHoc(temp);
    t.setHeSoLuong(nhapkhongam<float>("Nhap he so luong: "));
    t.setSoTietDay(nhapkhongam<int>("Nhap so tiet day: "));
    t.setSoTietVang(nhapkhongam<int>("Nhap so tiet vang: "));
    cout<<"Nhap ma GV: "; is>>ws; getline(is,t.maGV);
    t.setTienTheoTiet(nhapkhongam<long>("Tien theo tiet: "));
    return is;
}

// ========================================================================
//                          HAM PHU TRO (HELPER)
// ========================================================================
int TimViTriTheoMa(GiangVien* ds[], int n, string maCanTim) {
    for (int i = 0; i < n; i++) { if (ds[i]->getMaDD() == maCanTim) return i; } return -1; 
}

void HienThiHeaderBang() {
    Mau(14); // Vang
    cout << left << setw(10) << "Ma DD" 
         << left << setw(32) << "Ho Ten"   
         << left << setw(6)  << "GT" 
         << left << setw(45) << "Mon Hoc"  
         << left << setw(12) << "Loai"     // Tang len 12
         << right << setw(8) << "Tiet" 
         << right << setw(15) << "Thuc Linh" << endl;
    cout << setfill('-'); cout << setw(128) << "-" << endl; cout << setfill(' ');
    Mau(15); // Trang
}

void GhiDanhSachFile(GiangVien* ds[], int n) {
    ofstream f("ds_giangvien.txt"); if(!f) { Mau(12); cout << "Loi tao file!\n"; Mau(15); return; }
    f << n << endl; for(int i=0; i<n; i++) ds[i]->GhiFile(f); 
    f.close(); 
    Mau(10); cout << "\n>> DA TU DONG LUU FILE (ds_giangvien.txt) <<\n"; Mau(15);
}

void DocDanhSachFile(GiangVien* ds[], int &n) {
    ifstream f("ds_giangvien.txt"); if(!f) return; 
    for(int i=0; i<n; i++) delete ds[i]; n = 0;
    int soLuong; f >> soLuong;
    for(int i=0; i<soLuong; i++) {
        int loai; f >> loai; f.ignore(); 
        GiangVien* gv = NULL;
        if (loai == 1) gv = new CoHuu(); else if (loai == 2) gv = new ThinhGiang();
        if (gv != NULL) { gv->DocFile(f); ds[n++] = gv; }
    }
    f.close(); 
    Mau(10); cout << "\n>> DA TU DONG DOC FILE (ds_giangvien.txt) <<\n"; Mau(15);
}

void XoaGiangVien(GiangVien* ds[], int &n) {
    if (n == 0) return; string maCanXoa;
    cout << "Nhap ma dinh danh can xoa: "; cin.ignore(); getline(cin, maCanXoa);
    int viTri = TimViTriTheoMa(ds, n, maCanXoa);
    if (viTri == -1) { Mau(12); cout << "Khong tim thay!\n"; Mau(15); }
    else { delete ds[viTri]; for (int i = viTri; i < n - 1; i++) ds[i] = ds[i + 1]; n--; Mau(10); cout << "Da xoa!\n"; Mau(15); }
}

void TimKiemGiangVien(GiangVien* ds[], int n) {
    if (n == 0) { cout << "Danh sach trong!\n"; return; }
    string tuKhoa; cout << "Nhap tu khoa (Ma hoac Ten) de tim: "; cin.ignore(); getline(cin, tuKhoa);
    bool timThay = false;
    for (int i = 0; i < n; i++) {
        if (KiemTraChua(ds[i]->getMaDD(), tuKhoa) || KiemTraChua(ds[i]->getHoTen(), tuKhoa)) {
            if (!timThay) { cout << "\nKET QUA TIM KIEM:\n"; HienThiHeaderBang(); timThay = true; }
            ds[i]->HienThiThongTin(); 
        }
    }
    if (!timThay) { Mau(12); cout << "Khong tim thay ket qua nao!\n"; Mau(15); }
    else cout << "==============================================================================================================================\n";
}
void SapXepTheoLuong(GiangVien* ds[], int n, bool tangDan) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            long luongI = ds[i]->ThanhToanLuong();
            long luongJ = ds[j]->ThanhToanLuong();

            bool canDoiCho = false;
            
            if (tangDan) {
                if (luongI > luongJ) canDoiCho = true; // Thấp đứng trước, nếu I lớn hơn J thì đổi
            } else {
                if (luongI < luongJ) canDoiCho = true; // Cao đứng trước, nếu I bé hơn J thì đổi
            }

            if (canDoiCho) {
                // Hoán vị con trỏ (Swap)
                GiangVien* temp = ds[i];
                ds[i] = ds[j];
                ds[j] = temp;
            }
        }
    }
}
void BoLocGiangVien(GiangVien* ds[], int n) {
    if (n == 0) { cout << "Danh sach trong!\n"; return; }
    Mau(11); 
    cout << "\n=================== BO LOC & SAP XEP =================\n";
    cout << "1. Loc theo Gioi tinh (Nam/Nu)\n";
    cout << "2. Loc theo Mon hoc \n";
    cout << "3. Loc theo Loai (1.Co Huu / 2.Thinh Giang)\n"; 
    cout << "------------------------------------------------------\n";
    cout << "4. Sap xep Luong: Giam dan\n"; 
    cout << "5. Sap xep Luong: Tang dan\n";  
    cout << "0. Quay lai\n>> Nhap lua chon: ";
    Mau(15);
    
    int chon; cin >> chon;
    if (chon == 0) return;

    // --- XỬ LÝ SẮP XẾP ---
    if (chon == 4 || chon == 5) {
        bool tangDan = (chon == 5); 
        SapXepTheoLuong(ds, n, tangDan);
        
        Mau(10); cout << "\n>> DA SAP XEP DANH SACH THANH CONG!\n"; Mau(15);
        
        cout << "\nKET QUA SAU KHI SAP XEP:\n";
        HienThiHeaderBang();
        for(int i=0; i<n; i++) ds[i]->HienThiThongTin();
        cout << "==================================================================================================================================================\n";
        return; 
    }

    bool coKetQua = false; 
    if (chon == 3) {
        int loaiCanTim; cout << "Nhap loai muon xem (1.Co Huu, 2.Thinh Giang): "; cin >> loaiCanTim;
        cout << "\nKET QUA LOC:\n"; HienThiHeaderBang();
        for (int i = 0; i < n; i++) {
            if (ds[i]->getLoaiGV() == loaiCanTim) { ds[i]->HienThiThongTin(); coKetQua = true; }
        }
    }
    else if (chon == 1 || chon == 2) {
        string tuKhoa; cout << "Nhap tu khoa can loc: "; cin.ignore(); getline(cin, tuKhoa);
        cout << "\nKET QUA LOC:\n"; HienThiHeaderBang();
        for (int i = 0; i < n; i++) {
            bool thoaMan = false;
            if (chon == 1) thoaMan = KiemTraChua(ds[i]->getGioiTinh(), tuKhoa);
            else thoaMan = KiemTraChua(ds[i]->getMonHoc(), tuKhoa);
            if (thoaMan) { ds[i]->HienThiThongTin(); coKetQua = true; }
        }
    }
    else { Mau(12); cout << "Lua chon khong hop le!\n"; Mau(15); }
    
    if (!coKetQua && (chon >=1 && chon <=3)) { Mau(12); cout << "Khong tim thay giang vien nao phu hop!\n"; Mau(15); }
    if (chon >=1 && chon <=3) cout << "==================================================================================================================================================\n";
}

void SuaGiangVien(GiangVien* ds[], int n) {
    if (n == 0) { cout << "Danh sach trong!\n"; return; }
    string maCanSua; cout << "Nhap Ma DD can sua: "; cin.ignore(); getline(cin, maCanSua);
    int viTri = TimViTriTheoMa(ds, n, maCanSua);
    if (viTri == -1) { Mau(12); cout << "Khong tim thay!\n"; Mau(15); return; }

    cout << "\n--- Thong tin hien tai ---\n"; HienThiHeaderBang(); ds[viTri]->HienThiThongTin();
    cout << setfill('-'); cout << setw(128) << "-" << endl; cout << setfill(' ');
    cout << "CHON THONG TIN CAN SUA:\n";
    cout << "1. Ho ten\n2. Gioi tinh\n3. Mon hoc\n4. He so luong\n5. So tiet day\n6. So tiet VANG\n7. Thong tin rieng\n0. Huy bo\n>> Nhap lua chon: ";
    int chon; cin >> chon;
    if (chon == 1) { string ten; cout << "Nhap Ho ten moi: "; cin.ignore(); getline(cin, ten); ds[viTri]->setHoTen(ten); }
    else if (chon == 2) { string gt; cout << "Nhap Gioi tinh moi: "; cin.ignore(); getline(cin, gt); ds[viTri]->setGioiTinh(gt); }
    else if (chon == 3) { string mon; cout << "Nhap Mon hoc moi: "; cin.ignore(); getline(cin, mon); ds[viTri]->setMonHoc(mon); }
    else if (chon == 4) ds[viTri]->setHeSoLuong(nhapkhongam<float>("Nhap He so luong moi: "));
    else if (chon == 5) ds[viTri]->setSoTietDay(nhapkhongam<int>("Nhap So tiet day moi: "));
    else if (chon == 6) ds[viTri]->setSoTietVang(nhapkhongam<int>("Nhap So tiet vang moi: "));
    else if (chon == 7) {
        int loai = ds[viTri]->getLoaiGV(); 
        if (loai == 1) {
            CoHuu* ch = (CoHuu*)ds[viTri]; 
            ch->setThamNien(nhapkhongam<int>("Nhap tham nien moi: "));
            long tien = nhapkhongam<long>("Nhap tien trong DM moi: ");
            ch->setTienTrongDM200t(tien); ch->setTienNgoaiDM200t((long)(tien * 1.5));
        }
        else if (loai == 2) {
            ThinhGiang* tg = (ThinhGiang*)ds[viTri]; 
            string maTruong; cout << "Nhap Ma GV tai truong moi: "; cin.ignore(); getline(cin, maTruong);
            tg->setMaGV(maTruong); tg->setTienTheoTiet(nhapkhongam<long>("Nhap tien theo tiet moi: "));
        }
    }
    if (chon >= 1 && chon <= 7) { Mau(10); cout << "Da cap nhat thanh cong!\n"; Mau(15); }
}

void XuatPhieuLuong(GiangVien* ds[], int n) {
    if (n == 0) { cout << "Danh sach trong!\n"; return; }
    string ma; cout << "Nhap Ma DD can in phieu luong: "; cin.ignore(); getline(cin, ma);
    int viTri = TimViTriTheoMa(ds, n, ma);
    if (viTri == -1) { Mau(12); cout << "Khong tim thay!\n"; Mau(15); return; }
    
    string noiDung = ds[viTri]->LayPhieuLuong();
    Mau(11); cout << "\n" << noiDung << endl; Mau(15);

    char hoi; cout << "Ban co muon xuat ra file " << ma << ".txt khong? (c/k): "; cin >> hoi;
    if (hoi == 'c' || hoi == 'C') {
        ofstream f((ma + ".txt").c_str()); 
        if (f) { f << noiDung; f.close(); Mau(10); cout << ">> Da xuat file thanh cong!\n"; Mau(15); }
        else { Mau(12); cout << "Loi tao file!\n"; Mau(15); }
    }
}
void InGiua(string text, int width = 155) {
    int len = text.length();
    int padding = (width - len) / 2;
    
    if (padding > 0) {
        // In khoảng trắng
        for(int i=0; i<padding; i++) cout << " "; 
    }
    cout << text << endl;
}
// Hàm in Logo ASCII Art "HCMUE"
void InLogoTruong() {
    Mau(11); // Xanh Lơ
    cout << "\n";
    // Copy từng dòng logo vào hàm InGiua, nó sẽ tự căn
    InGiua("  _    _    _____   __  __   _   _   ______ ");
    InGiua(" | |  | |  / ____| |  \\/  | | | | | |  ____|");
    InGiua(" | |__| | | |      | \\  / | | | | | | |__   ");
    InGiua(" |  __  | | |      | |\\/| | | | | | |  __|  ");
    InGiua(" | |  | | | |____  | |  | | | |_| | | |____ ");
    InGiua(" |_|  |_|  \\_____| |_|  |_|  \\___/  |______|");
    cout << "\n";
    InGiua("TRUONG DAI HOC SU PHAM TP. HO CHI MINH");
    Mau(15); // Trả lại màu trắng
}
void menu() {
    Mau(11); // Xanh Lo
    cout << "\n============================================================\n";
    cout << "||                   QUAN LY GIANG VIEN                   ||\n";
    cout << "============================================================\n";
    cout << "||  1. Them giang vien co huu                             ||\n";
    cout << "||  2. Them giang vien thinh giang                        ||\n";
    cout << "||  3. Xuat danh sach giang vien                          ||\n";
    cout << "||  4. Xoa giang vien theo ma                             ||\n";
    cout << "||  5. Tim kiem giang vien                                ||\n"; 
    cout << "||  6. Sua thong tin giang vien                           ||\n"; 
    cout << "||  7. In phieu luong chi tiet                            ||\n"; 
    cout << "||  8. Bo loc danh sach                                   ||\n";
    cout << "||  0. Thoat                                              ||\n";
    cout << "============================================================\n";
    cout << ">> Nhap lua chon: ";
    Mau(15); // Trang
}
void GoChu(string text, int delay) {
    for (int i = 0; i < text.length(); i++) {
        cout << text[i];
        Sleep(delay); // Tạm dừng một chút rồi in chữ tiếp theo
    }
    cout << endl;
}
int main() {
    GiangVien* ds[100]; int n = 0; string chon;
    DocDanhSachFile(ds, n);
    Mau(14); // Vàng
    GoChu("Dang khoi dong he thong quan ly...", 30); // Chữ chạy vèo vèo
    Sleep(500);
    GoChu("Ket noi du lieu...", 30);
    Sleep(500);
    Mau(10);
    cout << ">> OK! San sang lam viec." << endl;
    Sleep(1000);
    InLogoTruong();
    while (true) {
        menu(); cin >> chon; 
        if(chon == "0") { GhiDanhSachFile(ds, n); break; }
        if(chon == "1") { CoHuu *c = new CoHuu(); cin >> *c; ds[n++] = c; Mau(10); cout << "Them thanh cong!\n"; Mau(15); }
        else if(chon == "2") { ThinhGiang *t = new ThinhGiang(); cin >> *t; ds[n++] = t; Mau(10); cout << "Them thanh cong!\n"; Mau(15); }
        else if(chon == "3") {
            if(n == 0) cout << "Danh sach trong!\n";
            else {
                #ifdef _WIN32 
                system("cls"); 
                #endif
                cout << "\n============================================================== DANH SACH GIANG VIEN ==============================================================\n";
                HienThiHeaderBang(); for(int i = 0; i < n; i++) ds[i]->HienThiThongTin();
                cout << "==================================================================================================================================================\n";
            }
        }
        else if(chon == "4") XoaGiangVien(ds, n);
        else if(chon == "5") TimKiemGiangVien(ds, n);
        else if(chon == "6") SuaGiangVien(ds, n);
        else if(chon == "7") XuatPhieuLuong(ds, n);
        else if(chon == "8") BoLocGiangVien(ds, n);
        else { Mau(12); cout << "Lua chon khong hop le!\n"; Mau(15); }
    }
    for(int i=0;i<n;i++) delete ds[i]; return 0;
}
