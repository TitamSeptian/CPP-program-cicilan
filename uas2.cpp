#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <ctime>
#include <math.h>       

using namespace std;

// deklarasivarible global
time_t t = time(NULL);
tm* timePtr = localtime(&t);


struct DataPeminjaman{
	int id_peminjaman;
	string nama;
	string pekerjaan;
	string tanggal;
	int lama_ciciclan;
	string status;
	int pinjaman;
	double bunga;
	double total_cicilan;
};

struct DataCicilan{
	int id_cicilan;
	int id_peminjaman;
	int bayar;
	int kembalian; // => nullable
	int cicilan_ke;
};
void checkDatabase(fstream &data);
void writeData(fstream &data, int posisi, DataPeminjaman &inputPeminjaman);
int getDataSize(fstream &data);
DataPeminjaman readData(fstream &data, int posisi);
void addPeminjaman(fstream &data);
void rincian(fstream &data, int posisi, DataPeminjaman &inputPeminjaman);
void writeData(fstream &data, int posisi, DataPeminjaman &inputPeminjaman);
void pembayaran(int bulan, double totalCicilan);
int main()
{
	char is_continue;
	fstream data;
	checkDatabase(data); // check data.bin

	label_continue:
	cout << "SELAMAT DATANG DI PROGRAM"
	cout << "Pinjaman Baru?(y/n) : ";
	cin >> is_continue;
	if ( (is_continue == 'y') | (is_continue == 'Y')){
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		addPeminjaman(data);
	} else if ((is_continue == 'n') | (is_continue == 'N')){
		cout << "Lihat Pinjaman Lama";
		cout << "1. Lihat Peminjaman" << endl;
		cout << "2. Buka Peminjaman" << endl;
	} else {
		goto label_continue;
	}

	cin.get();
	return 0;
}

void checkDatabase(fstream &data){
	data.open("data.bin", ios::out | ios::in | ios::binary); 

	// check file ada atau tidak
	if (data.is_open()){ // kalo ada database
		cout << "database ditemukan" << endl;
	} else { // kalo gak ada
		cout << "database tidak ditemukan, buat database baru" << endl;
		data.close();
		data.open("data.bin", ios::trunc | ios::out | ios::in | ios::binary); // bikin baru database
	}
}

void writeData(fstream &data, int posisi, DataPeminjaman &inputPeminjaman){
	data.seekp((posisi - 1)*sizeof(DataPeminjaman), ios::beg); // mengarahkan posisi data
	data.write(reinterpret_cast<char*>(&inputPeminjaman),sizeof(DataPeminjaman)); // tulis file binary ke konsole

	

	cout <<  endl;
	cout << "================[Rincian]===============\n";
	cout << "Nama peminjam : " << inputPeminjaman.nama << endl; 
	cout << "Nama pekerjaan : " << inputPeminjaman.pekerjaan << endl; 
	cout << "lama cicilan : " << inputPeminjaman.lama_ciciclan << " bulan" << endl;
	cout << "Peminjaman : " << inputPeminjaman.pinjaman << endl;
	cout << "Bunga (%) : " << inputPeminjaman.bunga << "%" << endl;
	cout << "Bunga (Rupiah) : " << (inputPeminjaman.pinjaman * inputPeminjaman.bunga/100) << endl;
	cout << "cicilan perbulan sebesar : " << inputPeminjaman.total_cicilan/inputPeminjaman.lama_ciciclan << endl;
}

int getDataSize(fstream &data){
	int start, end;
	data.seekg(0,ios::beg);
	start = data.tellg();
	data.seekg(0,ios::end);
	end = data.tellg();
	return (end-start)/sizeof(DataPeminjaman);
}

DataPeminjaman readData(fstream &data, int posisi){
	DataPeminjaman readPeminjaman;
	data.seekg((posisi - 1)*sizeof(DataPeminjaman),ios::beg);
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
	system("cls"); //for windows
	//system("clear"); //for linux/ macOS
	cout <<  endl;
	cout << "================[Rincian]===============\n";
	cout << "Nama peminjam : " << inputPeminjaman.nama << endl; 
	cout << "Nama pekerjaan : " << inputPeminjaman.pekerjaan << endl; 
	cout << "lama cicilan : " << inputPeminjaman.lama_ciciclan << " bulan" << endl;
	cout << "Peminjaman : " << inputPeminjaman.pinjaman << endl;
	cout << "Bunga (%) : " << inputPeminjaman.bunga << "%" << endl;
	cout << "Bunga (Rupiah) : " << (inputPeminjaman.pinjaman * inputPeminjaman.bunga/100) << endl;
	cout << "cicilan perbulan sebesar : " << inputPeminjaman.total_cicilan/inputPeminjaman.lama_ciciclan << endl;
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

