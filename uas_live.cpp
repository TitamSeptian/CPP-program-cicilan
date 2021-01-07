#include <iostream>
#include <string>

using namespace std;

void opreasi(int a, int b, string opr);

int main(){
	int bil1, bil2, pilih;
	string opr;
	cout << "Kalkulator" << endl;
	cout << "Masukan bil 1 :"; cin >> bil1;
	cout << "Masukan bil 2 :"; cin >> bil2;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "1. Petambahan" << endl;
	cout << "2. Pengurangan" << endl;
	cout << "3. Perkalian" << endl;
	cout << "4. Pembagian" << endl;
	cout << "4. Pangkat 2" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "Pilih : "; cin >> pilih;
	switch (pilih){
		case 1 : opreasi(bil1, bil2, "+");break;
		case 2 : opreasi(bil1, bil2, "-");break;
		case 3 : opreasi(bil1, bil2, "*");break;
		case 4 : opreasi(bil1, bil2, "/");break;
		case 5 : opreasi(bil1, bil2, "p2");break;
		default : cout << "Terjadi Kesalaha saat memilih" << endl;
	}


	cin.get();
	return 0;
}
void opreasi(int a, int b, string opr){
	cout << "Hasil ";
	if (opr == "+"){
		cout << "Tambah : " << a+b << endl;
	}else if(opr == "-"){
		cout << "kurang : " << a-b << endl;
	}else if(opr == "*"){
		cout << "kali : " << a*b << endl;
	}else if(opr == "/"){
		cout << "Bagi : " << a/b << endl;
	}else if(opr == "p2"){
		cout << "Pangkat :"<< endl;
		cout << "\tpangkat bil1 : " << a*a << endl;
		cout << "\tpangkat bil2 : " << b*b << endl;
	}

}