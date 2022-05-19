#include <iostream>
using namespace std;

static float STATICsoTienGop = 0.0;
static bool STATICisBeHui = false;
class ConHui {
public:
	string ten;
	float soTienHienCo;
	float soTienDauGia;
	bool isDie;
	ConHui() {
		isDie = false;
	}

	void SetSoTienDauGia(float _soTienDauGia) {
		soTienDauGia = _soTienDauGia;
	}

	void Nhap() {
		cout << "Nhap lan luot ten va so tien hien co: ";
		cin >> ten >> soTienHienCo;
	}

	void Xuat(float tongsoTienPhaiTra) {
		cout << ten << ", so tien hien co: " << soTienHienCo<< ", so tien phai tra: " << tongsoTienPhaiTra << ", kha nang chay no: ";
		if (KhaNangChayNo(tongsoTienPhaiTra) > 0.0) {
			cout << KhaNangChayNo(tongsoTienPhaiTra) << "%" << endl;
		}
		else {
			cout << "0%" << endl;
		}
	}

	float KhaNangChayNo(float tongsoTienPhaiTra) {
		return (tongsoTienPhaiTra - soTienHienCo) / tongsoTienPhaiTra * 100;
	}
	void HotHui(int numConHui) {
		soTienHienCo += (numConHui - 1) * (STATICsoTienGop - soTienDauGia);
		isDie = true;
	}
	float GopHui(float soTienDauGia) {
		float soTien =  isDie ? STATICsoTienGop : (STATICsoTienGop - soTienDauGia);
		soTienHienCo -= soTien;
		if (soTienHienCo < 0) {
			STATICisBeHui = true;
		}
		return soTien;
	}

};

class ChuHui {
public:
	ConHui conhuis[100];
	int numConHui;
	int numLuot;
	int DemConHuiSong() {
		int numConHuiSong = 0;
		for (int i = 0; i < numConHui; i++) {
			if (!conhuis[i].isDie) numConHuiSong++;
		}
		return numConHuiSong;
	}

	void Nhap() {
		cout << "--Nhap so luong con hui: ";
		cin >> numConHui;
		for (int i = 0; i < numConHui; i++) {
			conhuis[i].Nhap();
		}
	}

	void ChoiMotLuot(int soLuotHienTai) {
		
		float maxTienDauGia = 0;
		int iNguoiHotHui = 0;
		if (DemConHuiSong() > 1) {
			cout << "--Nhap lan luot so tien dau gia: " << endl;
			for (int i = 0; i < numConHui; i++) {
				float tmpTienDauGia;
				if (!conhuis[i].isDie) {
					cout << "Nhap so tien dau gia cua " << conhuis[i].ten << ": ";
					cin >> tmpTienDauGia;
					conhuis[i].SetSoTienDauGia(tmpTienDauGia);
					if (maxTienDauGia < tmpTienDauGia) {
						maxTienDauGia = tmpTienDauGia;
						iNguoiHotHui = i;
					}
				}


			}
		}

		if (DemConHuiSong() > 1) {
			for (int i = 0; i < numConHui; i++) {

				if (i == iNguoiHotHui) {
					conhuis[i].HotHui(numConHui);
				}
				else {
					conhuis[i].GopHui(maxTienDauGia);
				}
			}

		} else {
			for (int i = 0; i < numConHui; i++) {
				if (conhuis[i].isDie == false) {
					conhuis[i].HotHui(numConHui);
				}
				else {
					conhuis[i].GopHui(maxTienDauGia);
				}
			}
		
		
		}

		cout << "--Thong ke luot " << soLuotHienTai + 1 << ": " << endl;
		if (STATICisBeHui) {
			cout << "Be hui :v" << endl;
			return;
		}
		else {
			for (int i = 0; i < numConHui; i++) {
				conhuis[i].Xuat((numLuot - 1 - soLuotHienTai) * STATICsoTienGop);
			}
		}
	}
	void Choi() {
		numLuot = numConHui;
		// cout << "Nhap vao so luot: "; cin >> numLuot;
		cout << "--Nhap vao so tien gop: "; cin >> STATICsoTienGop;

		for (int i = 0; i < numLuot; i++) {
			ChoiMotLuot(i);
		}
	}
};

int main() {
	ChuHui chuHui;
	chuHui.Nhap();
	chuHui.Choi();

	return 0;
}