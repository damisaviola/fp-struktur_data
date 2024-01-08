#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int UKURAN_MAKS = 10;

struct Siswa {
    string nama;
    int umur;
    string jenisKelamin;
    string tglLahir;
};

Siswa siswa[UKURAN_MAKS];
int depan = -1;
int belakang = -1;

void clearScreen() {
    system("cls");
}

bool penuh() {
    return (belakang == UKURAN_MAKS - 1);
}

bool kosong() {
    return (depan == -1 || depan > belakang);
}

void masukkanAntrian(string nama, int umur, string jenisKelamin, string tglLahir) {
    if (penuh()) {
        cout << "\n\t\t\t\Kuota penerimaan siswa sudah penuh";
    } else {
        if (depan == -1) {
            depan = 0;
        }
        belakang++;
        if (belakang >= UKURAN_MAKS) {
            belakang = UKURAN_MAKS - 1; 
        }
        siswa[belakang].nama = nama;
        siswa[belakang].umur = umur;
        siswa[belakang].jenisKelamin = jenisKelamin;
        siswa[belakang].tglLahir = tglLahir;

        cout << "\n\t\t\t\tSiswa " << nama << " berhasil ditambahkan";
    }
}



void bubbleSort() {
    for (int i = depan; i < belakang; i++) {
        for (int j = depan; j < belakang - i; j++) { // Ubah kondisi perulangan
            if (siswa[j].nama > siswa[j + 1].nama) {
                swap(siswa[j], siswa[j + 1]);
            }
        }
    }
}



void keluarkanAntrian() {
    if (kosong()) {
        cout << "\n\t\t\t\Tidak ada siswa yang mendaftar";
    } else {
        cout << "\n\t\t\t\ Calon Siswa " << siswa[depan].nama << " status:\n";
        cout << "\t\t\t1. LULUS\n";
        cout << "\t\t\t2. TIDAK LULUS\n";
        cout << "\t\t\tPilih status: ";
        
        int status;
        cin >> status;

        if (status == 1) {
            cout << "\t\t\tSiswa dinyatakan LULUS";
        } else if (status == 2) {
            cout << "\t\t\tSiswa dinyatakan TIDAK LULUS";
        } else {
            cout << "\t\t\tPilihan tidak valid";
        }

        depan++;
    }
}


void tampilkanSiswa() {
    if (kosong()) {
        cout << "\n\t\t\t\Tidak ada siswa yang mendaftar";
    } else {
    	
    	bubbleSort();
        cout << "\n\n\t\t\t\Daftar Siswa yang Mendaftar:\n";
        for (int i = depan; i <= belakang; i++) {
            cout << "\t\t\t\Nama: " << siswa[i].nama << ", Umur: " << siswa[i].umur << ",Jenis Kelamin: " << siswa[i].jenisKelamin << ", Tanggal Lahir: " << siswa[i].tglLahir << endl;
        }
    }
}

int binarySearchNama(string namaToFind) {
    int left = depan;
    int right = belakang;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (siswa[mid].nama == namaToFind) {
            return mid;
        } else if (siswa[mid].nama < namaToFind) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

void updateDataSiswa() {
    string namaToUpdate;
    cout << "\n\t\t\t\Masukkan nama siswa yang ingin diupdate: ";
    cin.ignore();
    getline(cin, namaToUpdate);

    int indexToUpdate = binarySearchNama(namaToUpdate);

    if (indexToUpdate != -1) {
        cout << "\n\t\t\t\Siswa " << siswa[indexToUpdate].nama << " ditemukan.\n";
        cout << "\t\t\t\Masukkan informasi baru:\n";

        int pilihanUpdate;
        cout << "\t\t\t\ 1. Update Umur\n";
        cout << "\t\t\t\ 2. Update Jenis Kelamin\n";
        cout << "\t\t\t\ 3. Update Tanggal Lahir\n";
        cout << "\t\t\t\ 4. Update Nama\n";
        cout << "\t\t\t\ Pilihan Anda: ";
        cin >> pilihanUpdate;

        switch (pilihanUpdate) {
            case 1:
                cout << "\t\t\t\Masukkan umur baru: ";
                cin >> siswa[indexToUpdate].umur;
                break;
            case 2:
                cout << "\t\t\t\Masukkan jenis kelamin baru: ";
                cin.ignore();
                getline(cin, siswa[indexToUpdate].jenisKelamin);
                break;
            case 3:
                cout << "\t\t\t\Masukkan tanggal lahir baru (DD/MM/YYYY): ";
                cin.ignore();
                getline(cin, siswa[indexToUpdate].tglLahir);
                break;
            case 4:
                cout << "\t\t\t\Masukkan Nama Baru : ";
                cin.ignore();
                getline(cin, siswa[indexToUpdate].nama);
                break;
            default:
            	clearScreen();
                cout << "\n\t\t\t\Pilihan tidak valid\n";
        }
        clearScreen();
        cout << "\n\t\t\t\Informasi siswa berhasil diupdate.\n";
    } else {
        cout << "\n\t\t\t\Siswa tidak ditemukan\n";
    }
}

void cariBerdasarkanNama() {
    string nama;
    cout << "\n\t\t\t\Masukkan nama siswa yang ingin dicari: ";
    cin.ignore();
    getline(cin, nama);

    int result = binarySearchNama(nama);
    if (result != -1) {
        cout << "\n\t\t\t\Siswa " << siswa[result].nama << " ditemukan" << endl;
        cout << "\t\t\t\Detail siswa - Umur: " << siswa[result].umur << ", Jenis Kelamin: " << siswa[result].jenisKelamin << ", Tanggal Lahir: " << siswa[result].tglLahir << endl;
    } else {
        cout << "\n\t\t\t\Siswa tidak ditemukan\n";
    }
}

int binarySearchByAge(int umur) {
    int left = depan;
    int right = belakang;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (siswa[mid].umur == umur) {
            return mid;
        } else if (siswa[mid].umur < umur) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

void cariBerdasarkanUmur() {
    int umur;
    cout << "\n\t\t\t\Masukkan umur siswa yang ingin dicari: ";
    cin >> umur;

    int hasilPencarian = binarySearchByAge(umur);

    if (hasilPencarian != -1) {
        int count = 0;
        cout << "\n\t\t\t\Siswa dengan umur " << umur << " ditemukan:\n";


        for (int i = hasilPencarian; i >= 0 && siswa[i].umur == umur; i--) {
            cout << "\t\t\t\Nama: " << siswa[i].nama << ",Jenis Kelamin: " << siswa[i].jenisKelamin << ",Tanggal Lahir: " << siswa[i].tglLahir << endl;
            count++;
        }

        for (int i = hasilPencarian + 1; i <= belakang && siswa[i].umur == umur; i++) {
            cout << "\t\t\t\Nama: " << siswa[i].nama << ",Jenis Kelamin: " << siswa[i].jenisKelamin << ",Tanggal Lahir: " << siswa[i].tglLahir << endl;
            count++;
        }

        if (count == 0) {
            cout << "\t\t\t\Tidak ada siswa dengan umur " << umur << endl;
        }
    } else {
        cout << "\t\t\t\Tidak ada siswa dengan umur " << umur << endl;
    }
}

int main() {
    int pilihan;
    string nama, jenisKelamin, tglLahir;
    int umur;

    do {
        clearScreen();
        cout << "\n\n\n\n\n\n";
        cout << "\t\t\t\tPROGRAM PENERIMAAN SISWA BARU\n\n";
        cout << "\t\t\t\t1. Daftar siswa\n";
        cout << "\t\t\t\t2. Proses penerimaan siswa\n";
        cout << "\t\t\t\t3. Tampilkan daftar siswa yang mendaftar\n";
        cout << "\t\t\t\t4. Cari siswa\n";
        cout << "\t\t\t\t5. Update data siswa\n";
        cout << "\t\t\t\t6. Sortir\n";
        cout << "\t\t\t\t7. Selesai\n\n";
        cout << "\t\t\t\tPilihan Anda: ";

        cin >> pilihan;

        switch (pilihan) {
            case 1:
    			clearScreen();
    			if (penuh()) {
       			cout << "\n\t\t\t\Kuota penerimaan siswa sudah penuh\n";
        		break;
    		}
    			cin.ignore(); 
    			cout << "\n\t\t\t\tMasukkan nama siswa: ";
    			getline(cin, nama);

    			cout << "\t\t\t\tMasukkan umur siswa: ";
    			cin >> umur;
    			cin.ignore(); 

    			cout << "\t\t\t\tMasukkan jenis kelamin siswa: ";
    			getline(cin, jenisKelamin);
	
    			cout << "\t\t\t\tMasukkan tanggal lahir siswa (DD/MM/YYYY): ";
    			getline(cin, tglLahir);

    			masukkanAntrian(nama, umur, jenisKelamin, tglLahir);
    			break;


            case 2:
                clearScreen();
                keluarkanAntrian();
                break;

            case 3:
                clearScreen();
                tampilkanSiswa();
                break;

            case 4:
                clearScreen();
                int pilihanCari;
                cout << "\n\t\t\t\t1. Cari berdasarkan nama\n";
                cout << "\t\t\t\t2. Cari berdasarkan umur\n";

                cout << "\t\t\t\tPilihan Anda: ";
                cin >> pilihanCari;
                clearScreen();
                if (pilihanCari == 1) {
                    cariBerdasarkanNama();
                } else if (pilihanCari == 2) {
                    cariBerdasarkanUmur();
                } else {
                    cout << "\n\t\t\t\tPilihan tidak valid\n";
                }
                break;

            case 5:
                clearScreen();
                updateDataSiswa();
                break;

          case 6:
    int pilihanTampil;
    do {
        clearScreen();
        cout << "\n\t\t\t\t1. Tampilkan data sebelum diurutkan\n";
        cout << "\t\t\t\t2. Tampilkan data setelah diurutkan\n";
        cout << "\t\t\t\tPilihan Anda: ";
        cin >> pilihanTampil;
        cin.ignore(); 

        clearScreen();

        switch (pilihanTampil) {
            case 1:
                if (kosong()) {
                    cout << "\n\t\t\t\tTidak ada data yang tersedia\n";
                } else {
                    cout << "\n\t\t\t\tData sebelum diurutkan:\n";
                    for (int i = depan; i <= belakang; i++) {
                        cout << "\t\t\t\tNama: " << siswa[i].nama << ", Umur: " << siswa[i].umur << ", Jenis Kelamin: " << siswa[i].jenisKelamin << ", Tanggal Lahir: " << siswa[i].tglLahir << endl;
                    }
                }
                break;

            case 2:
                if (kosong()) {
                    cout << "\n\t\t\t\tTidak ada data yang tersedia\n";
                } else {
                    tampilkanSiswa();
                }
                break;

            default:
                cout << "\n\t\t\t\tPilihan tidak valid\n";
                break;
        }

        if (pilihanTampil == 1 || pilihanTampil == 2) {
            cout << "\n\t\t\t\Tekan tombol apa saja untuk kembali ke menu...";
            cin.ignore();
            cin.get();
        }

    } while (pilihanTampil != 1 && pilihanTampil != 2);
    break;

		case 7:

    	break;



	default:
    cout << "\n\t\t\t\Pilihan tidak valid\n";
    break;
	}

	cout << "\n\t\t\t\Tekan tombol apa saja untuk melanjutkan...";
	cin.ignore();
	cin.get();

} while (pilihan != 7); 


    return 0;
}

