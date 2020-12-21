#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <ctime>
#include <math.h>       
#include <iomanip>       

using namespace std;

// deklarasivarible global
string satuan[] = {"", "satu", "dua", "tiga", "empat", "lima", "enam", "tujuh", "delapan", "sembilan"};

struct DataPeminjaman{
	int id_peminjaman;
	string nama;
	string pekerjaan;
	string tanggal_dibuat;//
	int lama_ciciclan;
	string status;//
	int pinjaman;
	double bunga;
	double total_cicilan;

	int cicilan_ke;
	string tanggal_bayar[24];
	int bayar[24];
	int kembalian[24]; 

};

int getPilihan();
void checkDatabase(fstream &data);
void writeData(fstream &data, int posisi, DataPeminjaman &inputPeminjaman);
int getDataSize(fstream &data);
DataPeminjaman readData(fstream &data, int posisi);
void addPeminjaman(fstream &data);
void rincian(fstream &data, int posisi, DataPeminjaman &inputPeminjaman);
void pembayaran(int bulan, double totalCicilan);
void tampilSemuaPeminjaman(fstream &data);
string convert(int x);
void tampiSpesifikPeminjaman(fstream &data){
	int no;
	DataPeminjaman Peminjaman;
	cout << "Pilih Nomor : "; cin >> no;
	Peminjaman = readData(data, no);
	cout << endl;
	cout << "|		Peminjaman 		|" <<endl;
	cout << "|Tanggal : " << Peminjaman.tanggal_dibuat << "|" << endl;
	cout << "|Nama : " << Peminjaman.nama << "|" << endl;
	cout << "|Pekerjaan : " << Peminjaman.pekerjaan << "|" << endl;
	cout << "|Pinjaman : " << Peminjaman.pinjaman << "|" << endl;
	cout << "|Bunga : " << Peminjaman.bunga << "%" << "|" << endl;
	cout << "|Total Cicilan : " << Peminjaman.total_cicilan << "|" << endl;
	cout << "|Lama Cicilan : " << Peminjaman.lama_ciciclan << "|" << endl;
	cout << "|Sisa waktu cicilan : " << Peminjaman.lama_ciciclan - Peminjaman.cicilan_ke << "|" << endl;
	if (Peminjaman.cicilan_ke > 0){
		cout << "|		riwayat Pembayaran 		|" << endl;
		for (int i = 0; i < Peminjaman.cicilan_ke; i++)
		{
			cout << "|		Pembayran cicilan ke-" << i+1 << "|"<< endl;
			cout << "|bayar :" << Peminjaman.bayar[i] << endl;
			cout << "|Tanggal Bayar :" << Peminjaman.tanggal_bayar[i] << endl;
			cout << "|Kembalian :" << Peminjaman.kembalian[i] << endl;
		}
	}else{
		cout << "Belum ada riwayat pembayaran" << endl;
	}
	
}
int main(){
	char is_continue;
	fstream data;
	int pilihan = getPilihan();
	while(pilihan != 5){
	checkDatabase(data); // check data.bin
		
		switch(pilihan){
			case 1:
				cout << "Lihat Peminjaman" << endl;
				tampilSemuaPeminjaman(data);
				// data.close();
				break;
			case 2:
				cout << "Lihat Spesifik Peminjaman" << endl;
				tampilSemuaPeminjaman(data);
				tampiSpesifikPeminjaman(data);
				break;
			case 3:
				cout << "Tambah Peminjaman" << endl;
				addPeminjaman(data);
				data.close();
				break;
			case 4:
				cout << "Bayar Peminjaman" << endl;
				tampilSemuaPeminjaman(data);
				break;
			default:
				cout << "Pilihan tidak ditemukan" << endl;
				break;
		}

		label_continue:

		cout << "Lanjutkan?(y/n) : ";
		cin >> is_continue;

		if ( (is_continue == 'y') | (is_continue == 'Y')){
			data.open("data.bin", ios::out | ios::in | ios::binary);
			pilihan = getPilihan();data.close();
		} else if ((is_continue == 'n') | (is_continue == 'N')){
			// data.close();
			break;
		} else {
			goto label_continue;
		}
	}
	// int size = getDataSize(data);
	// cout << size << endl;
	cout << "\nTerima Kasih Sudah Menggunakan Program ini " << endl;
	cout << endl;

	cin.get();
	return 0;
}

string convert(int x){
	if (x < 0)
	{
		return "negartive " + convert(-x);
	}
	else if (x < 10)
	{
		return satuan[x];
	}
	else if (x == 10)
	{
		return "sepuluh";
	}
	else if (x == 11)
	{
		return "sebelas";
	}
	else if (x < 20)
	{
		return satuan[x - 10] + " belas";
	}
	else if (x < 100)
	{
		return satuan[(x - (x % 10)) / 10] + " puluh " + convert(x % 10);
	}
	else if (x < 1000)
	{
		if (x < 200)
		{
			return "seratus " + convert(x % 100);
		}
		else
		{
			return satuan[(x - (x % 100)) / 100] + " ratus " + convert(x % 100);
		}
	}
	else if (x < 1000000)
	{
		if (x < 2000)
		{
			return "seribu " + convert(x % 1000);
		}
		else
		{
			return satuan[(x - (x % 1000)) / 1000] + " ribu " + convert(x % 100);
		}
	}
	return "angka harus kurang dari 1000000";
}

int getPilihan(){
	int pilihan;
	system("cls"); // for windows
	//system("clear") // for linux/macOS 
	cout << "Program Ciciclan " << endl;
	cout << "Pilih Menu" <<endl;
	cout << "1. Lihat Cicilan" << endl;
	cout << "2. Lihat Spesifik Cicilan" << endl;
	cout << "3. Tambah Cicilan" << endl;
	cout << "4. Bayar Cicilan" << endl;
	cout << "5. Selesai" << endl;
	cout << "Pilih (1-5) :"; cin >> pilihan; 
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
	return pilihan;
}

void checkDatabase(fstream &data){
	data.open("data.bin", ios::out | ios::in | ios::binary); 

	// check file ada atau tidak
	if (data.is_open()){ // kalo ada database
		cout << "\ndatabase ditemukan" << endl;
	} else { // kalo gak ada
		cout << "\ndatabase tidak ditemukan, buat database baru" << endl;
		data.close();
		data.open("data.bin", ios::trunc | ios::out | ios::in | ios::binary); // bikin baru database
	}
}

void writeData(fstream &data, int posisi, DataPeminjaman &inputPeminjaman){
	data.seekp((posisi - 1)*sizeof(DataPeminjaman), ios::beg); // mengarahkan posisi data
	data.write(reinterpret_cast<char*>(&inputPeminjaman),sizeof(DataPeminjaman)); // tulis file binary ke konsole
}

int getDataSize(fstream &data){
	int start, end;
	data.seekg(0,ios::beg); //
	start = data.tellg();
	data.seekg(0,ios::end);
	end = data.tellg();
	return (end-start)/sizeof(DataPeminjaman);
}

DataPeminjaman readData(fstream &data, int posisi){
	DataPeminjaman readPeminjaman;
	data.seekg((posisi - 1) * sizeof(DataPeminjaman),ios::beg);
	data.read(reinterpret_cast<char*>(&readPeminjaman),sizeof(DataPeminjaman));
	return readPeminjaman;
}

void addPeminjaman(fstream &data){
	
	DataPeminjaman inputPeminjaman, lastPeminjaman;

	int size = getDataSize(data);
	
	cout << "ukuran data : " << size << endl;

	if(size == 0){
		inputPeminjaman.id_peminjaman = 1;
	} else {
		lastPeminjaman = readData(data,size);
		cout << "id = " << lastPeminjaman.id_peminjaman << endl;
		inputPeminjaman.id_peminjaman = lastPeminjaman.id_peminjaman + 1;
	}

	cout << "Nama : "; getline(cin, inputPeminjaman.nama);
	cout << "Pekerjaan : "; getline(cin, inputPeminjaman.pekerjaan);
	cout << "Tanggal : "; getline(cin, inputPeminjaman.tanggal_dibuat);

	cout << "Masukan Total Pinjaman : "; cin >> inputPeminjaman.pinjaman;
	// cout << "masukan lama cicilan : "; cin >> bulan;
	cout << "=======================================\n";
	cout << "pilihan lama cicilan (perbulan)\n";
	cout << "1. 6 bulan dengan bunga 0.7%\n";
	cout << "2. 12 bulan dengan bunga 0.8%\n";
	cout << "3. 18 bulan dengan bunga 0.9%\n";
	cout << "4. 24 bulan dengan bunga 1.0 %\n";
	cout << "=======================================\n";
	cout << "Pilih lama cicilan : "; cin >> inputPeminjaman.lama_ciciclan;
	int a = inputPeminjaman.lama_ciciclan;
	while(a < 1 || a > 4){
		cout << "Tidak ada dalam pilihan, masukan ulangan : "; cin >> a; 
	}

	switch (a){
		case 1 :inputPeminjaman.lama_ciciclan = 6;inputPeminjaman.bunga=0.7;break; 
		case 2 :inputPeminjaman.lama_ciciclan = 12;inputPeminjaman.bunga=0.8;break; 
		case 3 :inputPeminjaman.lama_ciciclan = 18;inputPeminjaman.bunga=0.9;break; 
		case 4 :inputPeminjaman.lama_ciciclan = 24;inputPeminjaman.bunga=1;break;
		// default : cout << "Terjadi Kesalahan" <<endl;exit(0);break;
	}
	// time_t now = time(0);
	// char* date_time = ctime(&now);

	inputPeminjaman.status = "BLNS";
	inputPeminjaman.cicilan_ke = 0;
	// cout << inputPeminjaman.status << endl;
	// inputPeminjaman.tanggal_dibuat = date_time;
	// cout << inputPeminjaman.tanggal_dibuat << endl;

	// cout << bunga << endl;
	// string tanggal = timePtr->tm_mday << "/" << timePtr->tm_mon << "/" << (timePtr->tm_year+1900);
	// inputPeminjaman.tanggal = tanggal;
	inputPeminjaman.total_cicilan = round(inputPeminjaman.pinjaman + (inputPeminjaman.pinjaman * inputPeminjaman.bunga/100));
	writeData(data, size+1, inputPeminjaman);
	rincian(data, size+1, inputPeminjaman);

	// pembayaran(inputPeminjaman.bulan, totalCicilan);

	// writeData(data,size+1,inputPeminjaman);
}

void rincian(fstream &data, int posisi, DataPeminjaman &inputPeminjaman) {
	//system("cls"); //for windows
	//system("clear"); //for linux/ macOS
	// Mahasiswa RincianPeminjaman;
	data.read(reinterpret_cast<char*>(&inputPeminjaman),sizeof(DataPeminjaman));
	cout <<  endl;
	cout << "================[Rincian]===============\n";
	cout << "Tanggal : " << inputPeminjaman.tanggal_dibuat << endl; 
	cout << "Nama peminjam : " << inputPeminjaman.nama << endl; 
	cout << "Nama pekerjaan : " << inputPeminjaman.pekerjaan << endl; 
	cout << "lama cicilan : " << inputPeminjaman.lama_ciciclan << " bulan" << endl;
	cout << "Peminjaman : " << inputPeminjaman.pinjaman << endl;
	cout << "Bunga (%) : " << inputPeminjaman.bunga << "%" << endl;
	cout << "Bunga (Rupiah) : " << (inputPeminjaman.pinjaman * inputPeminjaman.bunga/100) << endl;
	cout << "cicilan perbulan sebesar : " << inputPeminjaman.total_cicilan/inputPeminjaman.lama_ciciclan << endl;
	cout << "STATUS : " << inputPeminjaman.status << endl;
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

void tampilSemuaPeminjaman(fstream &data){
	int size = getDataSize(data);
	DataPeminjaman Peminjaman;
	cout << left;
	if (size > 0)
	{
		/* code */
		cout<< setw(3) << "No" << setw(3) << "KD" << setw(20) << "Nama" << setw(10) << "Pinjaman" << setw(7) << "Status" << endl;
		
		// Peminjaman = readData(data, 1);
		// cout << 1 << "\t";
		// cout << Peminjaman.nama << "\t";
		// cout << Peminjaman.status << endl;
		for (int i = 1; i <= size; i++)
		{
			Peminjaman = readData(data, i);
			cout << left;
			cout << setw(3) << i;
			cout << setw(3) << Peminjaman.id_peminjaman;
			cout << setw(20) << Peminjaman.nama;
			cout << setw(10) << Peminjaman.pinjaman;
			cout << setw(7) << Peminjaman.status << endl;
		}
	}else{
		cout << "\nData Masih Kosong\n";
	}
			// cout << Peminjaman.pekerjaan << "\t";
			// cout << Peminjaman.lama_ciciclan << "\t";
			// cout << Peminjaman.pinjaman << "\t";
			// cout << Peminjaman.bunga << "\t";
			// cout << Peminjaman.cicilan_ke << "\t";
			// cout << Peminjaman.tanggal_dibuat << endl;
}
