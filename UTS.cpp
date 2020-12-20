#include <iostream>
// #include <string>

using namespace std;

	// deklarasivarible global



void rincian(int bulan,int pinjaman,double bunga,double totalCicilan, string nama,string pkrjn);
void pembayaran(int bulan, double totalCicilan);

int main()
{
	int pinjaman, a,bulan,cicilan = 0;
	double bunga;
	string nama,pkrjn;

	cout << "Program Pinjaman Uang dengan Metode Pembayran Cicilan" << endl;

	cout << "Nama : "; getline(cin, nama);
	cout << "Pekerjaan : "; getline(cin, pkrjn);

	cout << "Masukan Total Pinjaman : "; cin >> pinjaman;
	// cout << "masukan lama cicilan : "; cin >> bulan;
	cout << "=======================================\n";
	cout << "pilihan lama cicilan (perbulan)\n";
	cout << "1. 6 bulan dengan bunga 0.7%\n";
	cout << "2. 12 bulan dengan bunga 0.8%\n";
	cout << "3. 18 bulan dengan bunga 0.9%\n";
	cout << "4. 24 bulan dengan bunga 1.0 %\n";
	cout << "=======================================\n";
	cout << "Pilih lama cicilan : "; cin >> a;

	while(a < 1 || a > 4){
		cout << "Tidak ada dalam pilihan, masukan ulangan : "; cin >> a; 
	}

	switch (a){
		case 1 :bulan = 6;bunga=0.7;break; 
		case 2 :bulan = 12;bunga=0.8;break; 
		case 3 :bulan = 18;bunga=0.9;break; 
		case 4 :bulan = 24;bunga=1;break;
		// default : cout << "Terjadi Kesalahan" <<endl;exit(0);break;
	}
	// cout << bunga << endl;
	double totalCicilan = pinjaman + (pinjaman * bunga/100);

	rincian(bulan,pinjaman,bunga,totalCicilan, nama, pkrjn);
	pembayaran(bulan, totalCicilan);

	cin.get();
	return 0;
}

void rincian(
	int bulan, 
	int pinjaman, 
	double bunga, 
	double totalCicilan, 
	string nama, 
	string pkrjn
) {
	system("clear");
	cout <<  endl;
	cout << "================[Rincian]===============\n";
	cout << "Nama peminjam : " << nama << endl; 
	cout << "Nama pekerjaan : " << pkrjn << endl; 
	cout << "lama cicilan : " << bulan << " bulan" << endl;
	cout << "Peminjaman : " << pinjaman << endl;
	cout << "Bunga (%) : " << bunga << "%" << endl;
	cout << "Bunga (Rupiah) : " << (pinjaman * bunga/100) << endl;
	cout << "cicilan perbulan sebesar : " << totalCicilan/bulan << endl;
}

void pembayaran(int bulan, double totalCicilan){
	int jumlah=0, x=1;
	double pembayaran;
	do
	{
		double cicilanPerBulan = totalCicilan/bulan;
		cout << endl;
		cout << endl;
		cout << "=======================================\n";

		cout << "Pembayaran Cicilan ke-" << x << " : "; cin >> pembayaran;
		while(pembayaran < cicilanPerBulan){
			cout << "Uang kurang, masukan kembali : "; cin >> pembayaran; 
		}

		if (pembayaran > cicilanPerBulan){
			cout << "Kembalian : " << pembayaran - cicilanPerBulan << endl;
		}

		x++;

		jumlah += cicilanPerBulan;
		cout << "sisa pembayaran : " << totalCicilan - jumlah << endl;
		cout << "sisa waktu cicilan : " << (bulan - x) + 1 << endl;
	// } while (jumlah < totalCicilan && x <= bulan);
	} while (x <= bulan);

	cout << endl;

	if ((totalCicilan - jumlah) < 0){
		cout << "Cicilan tidak lunas" << endl;
	}else{
		cout << "Cicilan lunas" << endl;
	}
}