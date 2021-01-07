#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <ctime>
#include <math.h>       
#include <iomanip>       

using namespace std;

// deklarasivarible global
// record
struct DataPeminjaman{ 
	int id_peminjaman;
	string nama;
	string pekerjaan;
	string tanggal_dibuat;
	int lama_ciciclan;
	string status;
	int pinjaman;
	double bunga;
	double total_cicilan;
	int cicilan_ke;
	string tanggal_bayar[24]; // array
	int bayar[24];
	int kembalian[24]; 

};

int getPilihan();
void checkDatabase(fstream &data);
void writeData(fstream &data, int posisi, DataPeminjaman &inputPeminjaman);
int getDataSize(fstream &data);
DataPeminjaman readData(fstream &data, int posisi); //file
void addPeminjaman(fstream &data);
void rincian(fstream &data, int posisi, DataPeminjaman &inputPeminjaman);
void tampilSemuaPeminjaman(fstream &data);

string satuan (int a){
	if (a==1) {return" Satu ";}
	else if (a==2) {return" Dua ";}
	else if (a==3) {return" Tiga ";}
	else if (a==4) {return" Empat ";}
	else if (a==5) {return" Lima ";}
	else if (a==6) {return" Enam ";}
	else if (a==7) {return" Tujuh ";}
	else if (a==8) {return" Delapan ";}
	else if (a==9) {return" Sembilan ";}
	else if (a==10) {return" Sepuluh ";}
	else if (a==11) {return" Sebelas ";}
	else{return "";}
	return "";
}
// rekursi
string terbilang (long long b){
	if (b<=11) {
		return satuan(b);
	} else if ((b>11) && (b<=19)){
		return terbilang(b%10) + "Belas ";
	}else if ((b>=20)&&(b<=99)){
		return terbilang(b/10) + "Puluh " + terbilang(b%10);
	}else if ((b>=100)&&(b<=199)){
		return "Seratus " + terbilang(b%100);
	}else if ((b>=200)&&(b<=999)){
		return terbilang(b/100) + "Ratus " +terbilang(b%100);
	}else if ((b>=1000)&&(b<=1999)){
		return"Seribu "+(b%1000);
	}else if ((b>=2000)&&(b<=9999)){
		return terbilang(b/1000) + "Ribu " +terbilang(b%1000);
	}else if ((b>=10000)&&(b<=99999)){
		return terbilang(b/1000) + "Ribu "+ terbilang(b%1000);
	}else if ((b>=100000)&&(b<=999999)){ 
		return terbilang(b/1000) + "Ribu " + terbilang(b%1000);
	}else if ((b>=1000000)&&(b<=999999999)){ 
		return terbilang (b/1000000) + "Juta " + terbilang (b%1000000);
	}else if ((b>=1000000000)&&(b<=999999999999)){ 
		return terbilang (b/1000000000) + "Milyar " + terbilang (b%1000000000);
	}else if ((b>=1000000000000)){
		return "Angka terlalu banyak.";
	}
	return "";
}

void tampiSpesifikPeminjaman(fstream &data);
void pembayaran(fstream &data);
int main(){
	char is_continue;
	fstream data; // deklarasi file i/o
	int size;
	int pilihan = getPilihan(); // mendapatkan pilihan dari menu
	while(pilihan != 5){
	checkDatabase(data); // check data.bin
		
		switch(pilihan){
			case 1:
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				cout << "|  Lihat Cicilan" << endl;
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				tampilSemuaPeminjaman(data); // fungsi nampilin
				// data.close();
				break;
			case 2:
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				cout << "| Lihat Spesifik Cicilan" << endl;
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				tampilSemuaPeminjaman(data); // fungsi nampilin
				size = getDataSize(data);
				if (size > 0){
					tampiSpesifikPeminjaman(data); // nampilin detail hanya 1 data
				}
				break;
			case 3:
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				cout << "|  Tambah Cicilan Baru" << endl;
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				addPeminjaman(data); // tambah  peminjman
				data.close();
				break;
			case 4:
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				cout << "|  Bayar Cicilan" << endl;
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				tampilSemuaPeminjaman(data);
				if (size > 0){
					pembayaran(data); // pembyarn
				}
				data.close();
				break;
			default:
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				cout << "|  -- Pilihan tidak ditemukan" << endl;
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				break;
		}

		label_continue:

		cout << "|  Lanjutkan?(y/n) : ";
		cin >> is_continue;

		if ( (is_continue == 'y') | (is_continue == 'Y')){
			data.open("data.bin", ios::out | ios::in | ios::binary);
			pilihan = getPilihan();data.close();
		} else if ((is_continue == 'n') | (is_continue == 'N')){
			// data.close();
			break;
		} else {
			goto label_continue; // ururan baca sitem bakal di arah kan ke label_continue: diatas cuy
		}
	}
	// int size = getDataSize(data);
	// cout << size << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "|  Terima Kasih Sudah Menggunakan Program ini " << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << endl;

	cin.get();
	return 0;
}



int getPilihan(){
	int pilihan;
	system("cls"); // for windows
	//system("clear") // for linux/macOS 
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "|  Program Cicilan Menggunakan c++" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "|  Pilih Menu" <<endl;
	cout << "|  1. Lihat Cicilan" << endl;
	cout << "|  2. Lihat Spesifik Cicilan" << endl;
	cout << "|  3. Tambah Cicilan" << endl;
	cout << "|  4. Bayar Cicilan" << endl;
	cout << "|  5. Selesai" << endl;
	cout << "| - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
	cout << "|  Pilih (1-5) :"; cin >> pilihan; 
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
	return pilihan;
}

void checkDatabase(fstream &data){
	data.open("data.bin", ios::out | ios::in | ios::binary); 

	// check file ada atau tidak
	if (data.is_open()){ // kalo ada database
		// cout << "\ndatabase ditemukan" << endl;
	} else { // kalo gak ada
		cout << "\n|  --- database tidak ditemukan, buat database baru..." << endl;
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
	data.seekg(0,ios::beg); // ambil posisi data di awal
	start = data.tellg(); // simpen di var start
	data.seekg(0,ios::end); // ambil posisi data di akhir
	end = data.tellg(); // simpen di var start
	return (end-start)/sizeof(DataPeminjaman); 
	/*
	Bakal return ukuran dari banyak data, misal ada 7 data
	*/
}
// seekg() dimulai dari 0
DataPeminjaman readData(fstream &data, int posisi){
	DataPeminjaman readPeminjaman; // deklarasi struct
	data.seekg((posisi - 1) * sizeof(DataPeminjaman),ios::beg); // mendapatkan dan memposisikan data
	data.read(reinterpret_cast<char*>(&readPeminjaman),sizeof(DataPeminjaman));
	return readPeminjaman; // retrun struct dari hasil .read()
}

void addPeminjaman(fstream &data){
	
	DataPeminjaman inputPeminjaman, lastPeminjaman;

	int size = getDataSize(data); // banyakdata/ ukuran data
	
	// cout << "ukuran data : " << size << endl;

	if(size == 0){
		inputPeminjaman.id_peminjaman = 1;
	} else {
		lastPeminjaman = readData(data,size);
		// cout << "id = " << lastPeminjaman.id_peminjaman << endl;
		inputPeminjaman.id_peminjaman = lastPeminjaman.id_peminjaman + 1;
	}
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "|  Nama 			: "; getline(cin, inputPeminjaman.nama);
	cout << "|  Pekerjaan 		: "; getline(cin, inputPeminjaman.pekerjaan);
	cout << "|  Tanggal 		: "; getline(cin, inputPeminjaman.tanggal_dibuat);

	cout << "|  Masukan Total Pinjaman : "; cin >> inputPeminjaman.pinjaman;
	// cout << "masukan lama cicilan : "; cin >> bulan;
	cout << "| - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
	cout << "|  pilihan lama cicilan (perbulan)\n";
	cout << "|  1. 6 bulan dengan bunga 0.7%\n";
	cout << "|  2. 12 bulan dengan bunga 0.8%\n";
	cout << "|  3. 18 bulan dengan bunga 0.9%\n";
	cout << "|  4. 24 bulan dengan bunga 1.0 %\n";
	cout << "| - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
	cout << "|  Pilih lama cicilan 	: "; cin >> inputPeminjaman.lama_ciciclan;
	int a = inputPeminjaman.lama_ciciclan;
	while(a < 1 || a > 4){
		cout << "|  Tidak ada dalam pilihan, masukan ulangan : "; cin >> a; 
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

	inputPeminjaman.status = "BLNS"; // ini set status
	inputPeminjaman.cicilan_ke = 0;
	// inputPeminjaman.tanggal = tanggal;
	inputPeminjaman.total_cicilan = round(inputPeminjaman.pinjaman + (inputPeminjaman.pinjaman * inputPeminjaman.bunga/100));
	writeData(data, size+1, inputPeminjaman); // menulis data menggunakan fungsi writeData()
	rincian(data, size+1, inputPeminjaman); // rincian print to console hasil yang tadi di inputkan
}

void rincian(fstream &data, int posisi, DataPeminjaman &inputPeminjaman) {
	//system("cls"); //for windows
	//system("clear"); //for linux/ macOS
	// Mahasiswa RincianPeminjaman;
	data.read(reinterpret_cast<char*>(&inputPeminjaman),sizeof(DataPeminjaman));
	cout <<  endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "|  ---Rincian\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "|  Tanggal 				: " << inputPeminjaman.tanggal_dibuat << endl; 
	cout << "|  Nama peminjam 			: " << inputPeminjaman.nama << endl; 
	cout << "|  Nama pekerjaan 			: " << inputPeminjaman.pekerjaan << endl; 
	cout << "|  lama cicilan 			: " << inputPeminjaman.lama_ciciclan << " bulan" << endl;
	cout << "|  Peminjaman 				: " << inputPeminjaman.pinjaman << endl;
	cout << "|  Bunga (%) 				: " << inputPeminjaman.bunga << "%" << endl;
	cout << "|  Bunga (Rupiah) 			: " << (inputPeminjaman.pinjaman * inputPeminjaman.bunga/100) << endl;
	cout << "|  cicilan perbulan sebesar: " << inputPeminjaman.total_cicilan/inputPeminjaman.lama_ciciclan << endl;
	cout << "|  STATUS 					: " << inputPeminjaman.status << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

void tampilSemuaPeminjaman(fstream &data){
	int size = getDataSize(data);
	DataPeminjaman Peminjaman;
	cout << left;
	if (size > 0)
	{
		/* 
		setw adalah ukuran/batas karakter yang akan ditulis

		 */
		cout << "|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "| "<< setw(3) << "No" << setw(3) << "KD" << setw(20) << "Nama" << setw(10) << "Pinjaman" << setw(7) << "Status" << endl;
		cout << "|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		for (int i = 1; i <= size; i++)
		{
			Peminjaman = readData(data, i);
			cout << left;
			cout << "| "<< setw(3) << i;
			cout << setw(3) << Peminjaman.id_peminjaman;
			cout << setw(20) << Peminjaman.nama;
			cout << setw(10) << Peminjaman.pinjaman;
			cout << setw(7) << Peminjaman.status << endl;
		}
	}else{
		cout << "| --- Data Masih Kosong " << endl;
	}
}

void tampiSpesifikPeminjaman(fstream &data){
	int no;
	DataPeminjaman Peminjaman;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "|  Pilih Nomor : "; cin >> no;
	Peminjaman = readData(data, no);
	cout << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "|  Tanggal 			: " << Peminjaman.tanggal_dibuat  << endl;
	cout << "|  Nama 				: " << Peminjaman.nama  << endl;
	cout << "|  Pekerjaan 			: " << Peminjaman.pekerjaan  << endl;
	cout << "|  Pinjaman 			: " << Peminjaman.pinjaman  << endl;
	cout << "|  Bunga 				: " << Peminjaman.bunga << "%"  << endl;
	cout << "|  Total Cicilan 		: " << Peminjaman.total_cicilan  << endl;
	cout << "|  Lama Cicilan 		: " << Peminjaman.lama_ciciclan  << endl;
	cout << "|  Sisa waktu cicilan 	: " << Peminjaman.lama_ciciclan - Peminjaman.cicilan_ke << endl;
	if (Peminjaman.cicilan_ke > 0){
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "|					riwayat pembayaran     				 		" << endl;
		for (int i = 0; i < Peminjaman.cicilan_ke; i++)
		{
			cout << "| - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
			cout << "|  Pembayran cicilan ke-" << i+1 << endl;
			cout << "|  bayar 			:" << Peminjaman.bayar[i] << endl;
			cout << "|  Tanggal Bayar 	:" << Peminjaman.tanggal_bayar[i] << endl;
			cout << "|  Kembalian 		:" << Peminjaman.kembalian[i] << endl;
			cout << "| - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
		}
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	}else{
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "|						belum riwayat pembayaran     			 		|" << endl;;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	}
	
}

void pembayaran(fstream &data){
	int no, total = 0;
	int bayar;
	string tgl;
	DataPeminjaman Peminjaman;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "Pilih Nomor : "; cin >> no;
	Peminjaman = readData(data, no);
	if ((Peminjaman.cicilan_ke) == Peminjaman.lama_ciciclan){
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "|  tidak ada tagihan pembayaran lagi" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	}else{
		total = Peminjaman.total_cicilan/Peminjaman.lama_ciciclan;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "|  Nama 				: " << Peminjaman.nama << endl;
		cout << "|  Pekerjaan 			: " << Peminjaman.pekerjaan << endl;
		cout << "|  Tanggal Bayar 		: "; getline(cin, tgl);
		cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignore ini untuk nambahin new line di inputan yang ngaco
		cout << "|  Cicilan bulan ke-" << Peminjaman.cicilan_ke+1 << endl;
		cout << "|  Bunga 				: " << (Peminjaman.pinjaman * Peminjaman.bunga/100) << endl;
		cout << "|  Total Tagihan 		: " << total << endl;
		cout << "|  Terbilang 			: " << terbilang(total) << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "|  bayar : "; cin >> bayar;
		while(bayar < total){
			cout << "|  Uang kurang, masukan kembali : "; cin >> bayar; 
		}

		if (bayar >total){
			cout << "|  Kembalian : " << bayar - total << endl;
		}
		cout << "|  Membuat Kwitansi...." << endl;
		ofstream kwitansi;
		kwitansi.open("kwitansi.txt", ios::trunc); // ini mau outpur file .txt
	    kwitansi << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	    kwitansi << "|  Tanggal   : " << tgl << "\n";
	    kwitansi << "|  Nama   	  : " << Peminjaman.nama << "\n";
	    kwitansi << "|  Cicilan ke: " << Peminjaman.cicilan_ke + 1 << "\n";
	    kwitansi << "|  Tagihan	  : " << total << "(" << terbilang(total) << ") \n";
	    kwitansi << "|  Bayar 	  : " << bayar << "\n";
	    kwitansi << "|  Kembalian : " << bayar - total << "\n\n";
	    kwitansi << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	    // kwitansi << "|  Terbilang : " << Peminjaman.total_cicilan << "\n";
	    kwitansi.close();
	    Peminjaman.kembalian[Peminjaman.cicilan_ke] = bayar - total;
	    Peminjaman.bayar[Peminjaman.cicilan_ke] = bayar;
	    Peminjaman.tanggal_bayar[Peminjaman.cicilan_ke] = tgl;
	    // cout << Peminjaman.cicilan_ke <<endl;
	    Peminjaman.cicilan_ke++;
	    // cout << Peminjaman.cicilan_ke <<endl;
	    if ((Peminjaman.cicilan_ke) == Peminjaman.lama_ciciclan)
	    {
	    	cout << "|  Pembayaran Lunas";
	    	Peminjaman.status = "LUNAS";
	    	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	    }

	    writeData(data, no, Peminjaman);
	}


}