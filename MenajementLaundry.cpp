// Nama   : Wira Fikri Ramadanu
// Nim    : 23343023
// Matkul : Praktikum Algoritma

#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>  
#include <cstdlib>  
#include <cstring>  

using namespace std;

char savedusername[24], savedpassword[24], username[24], password[24];
int i = 0;

struct Pesanan {
    string jenis;
    double beratAtauJumlah;
    double totalHarga;
    int id_pelanggan;
    int status;
};

struct Pelanggan {
    string nama;
    string alamat;
    string nomor;
    int id;
};

// Fungsi untuk menyimpan data pelanggan ke dalam file teks
void saveDataToFile(Pelanggan pelanggan[], int jumlahPelanggan, Pesanan pesanan[], int jumlahPesanan) {
    ofstream file("DataPelanggan.txt");

    if (file.is_open()) {
        // Menyimpan data pelanggan
        for (int i = 0; i < jumlahPelanggan; i++) {
            file << "Pelanggan\n";
            file << pelanggan[i].id << "\n";
            file << pelanggan[i].nama << "\n";
            file << pelanggan[i].alamat << "\n";
            file << pelanggan[i].nomor << "\n";
        }

        // Menyimpan data pesanan
        for (int i = 0; i < jumlahPesanan; i++) {
            file << "Pesanan\n";
            file << pesanan[i].id_pelanggan << "\n";
            file << pesanan[i].jenis << "\n";
            file << pesanan[i].beratAtauJumlah << "\n";
            file << pesanan[i].totalHarga << "\n";
            file << pesanan[i].status << "\n";
        }

        file.close();
        cout << "Data berhasil disimpan ke dalam file." << endl;
    } else {
        cout << "Gagal membuka file untuk penyimpanan data." << endl;
    }
}

// Fungsi untuk membaca data dari file teks
void loadDataFromFile(Pelanggan pelanggan[], int &jumlahPelanggan, Pesanan pesanan[], int &jumlahPesanan) {
    ifstream file("data.txt");

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line == "Pelanggan") {
                int id;
                string nama, alamat, nomor;

                file >> id;
                file.ignore();  // untuk mengabaikan newline setelah membaca id
                getline(file, nama);
                getline(file, alamat);
                getline(file, nomor);

                pelanggan[jumlahPelanggan].id = id;
                pelanggan[jumlahPelanggan].nama = nama;
                pelanggan[jumlahPelanggan].alamat = alamat;
                pelanggan[jumlahPelanggan].nomor = nomor;
                jumlahPelanggan++;
            } else if (line == "Pesanan") {
                int id_pelanggan, status;
                string jenis;
                double beratAtauJumlah, totalHarga;

                file >> id_pelanggan;
                file >> jenis;
                file >> beratAtauJumlah;
                file >> totalHarga;
                file >> status;

                pesanan[jumlahPesanan].id_pelanggan = id_pelanggan;
                pesanan[jumlahPesanan].jenis = jenis;
                pesanan[jumlahPesanan].beratAtauJumlah = beratAtauJumlah;
                pesanan[jumlahPesanan].totalHarga = totalHarga;
                pesanan[jumlahPesanan].status = status;
                jumlahPesanan++;
            }
        }

        file.close();
        cout << "Data berhasil dimuat dari file." << endl;
    } else {
        cout << "Gagal membuka file untuk membaca data." << endl;
    }
}

Pesanan prosesPesanan() {
    Pesanan pesanan;

    cout << "Jenis pemesanan (kiloan atau satuan): ";
    cin >> pesanan.jenis;

    if (pesanan.jenis == "kiloan") {
        cout << "Masukkan berat pakaian dalam kg     : ";
        cin >> pesanan.beratAtauJumlah;
        pesanan.totalHarga = 7000 * pesanan.beratAtauJumlah;
    } else if (pesanan.jenis == "satuan") {
        string jenisPakaian;
        cout << "Jenis pakaian (selimut, bedcover, atau sepatu): ";
        cin >> jenisPakaian;

        if (jenisPakaian == "selimut" || jenisPakaian == "bedcover" || jenisPakaian == "sepatu") {
            cout << "Masukkan jumlah satuan          : ";
            cin >> pesanan.beratAtauJumlah;

            if (jenisPakaian == "selimut") {
                pesanan.totalHarga = 10000 * pesanan.beratAtauJumlah;
            } else if (jenisPakaian == "bedcover") {
                pesanan.totalHarga = 15000 * pesanan.beratAtauJumlah;
            } else if (jenisPakaian == "sepatu") {
                pesanan.totalHarga = 20000 * pesanan.beratAtauJumlah;
            }
        } else {
            cout << "Pilihan tidak valid!" << endl;
            pesanan.totalHarga = 0;
        }
    } else {
        cout << "Pilihan tidak valid!" << endl;
        pesanan.totalHarga = 0;
    }

    return pesanan;
}

// Menu Utama
void displayMenu() {
    cout << "_________________________________________________________________________" << endl;
    cout << "                             Selamat datang                              " << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    cout << "Silakan pilih opsi berikut:                                              " << endl;
    cout << "   1. Input data pelanggan                                               " << endl;
    cout << "   2. Pemesanan layanan laundry                                          " << endl;
    cout << "   3. Menampilkan daftar pesanan yang belum selesai                      " << endl;
    cout << "   4. Menandai pesanan sebagai selesai                                   " << endl;
    cout << "   5. Menampilkan riwayat pesanan yang sudah selesai                     " << endl;
    cout << "   6. Cari data pelanggan berdasarkan ID                                 " << endl;
    cout << "   7. Keluar                                                             " << endl;
    cout << "_________________________________________________________________________" << endl;
    cout << "                                                                         " << endl;
    cout << "Masukkan pilihan Anda: ";
}

// Fungsi Untuk Input Data Pelanggan
void inputDataPelanggan(Pelanggan pelanggan[], int &jumlahPelanggan) {
    cout << "_________________________________________________________________________" << endl;
    cout << "                          Input data pelanggan                           " << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    cout << "Masukkan nama pelanggan             : ";
    getline(cin >> ws, pelanggan[jumlahPelanggan].nama);
    cout << "Masukkan alamat pelanggan           : ";
    getline(cin >> ws, pelanggan[jumlahPelanggan].alamat);
    cout << "Masukkan nomor telepon pelanggan    : ";
    getline(cin >> ws, pelanggan[jumlahPelanggan].nomor);
    pelanggan[jumlahPelanggan].id = jumlahPelanggan + 1;
    cout << "                                                                         " << endl;
    cout << "ID Data Pelanggan anda adalah " << pelanggan[jumlahPelanggan].id << endl;
    jumlahPelanggan++;
    cout << endl;
}

// Fungsi Untuk Pemesanan
void orderLaundryService(Pelanggan pelanggan[], Pesanan pesanan[], int jumlahPelanggan, int &jumlahPesanan) {
    cout << "_________________________________________________________________________" << endl;
    cout << "                       Pemesanan Layanan Laundry                         " << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    int idPelanggan;
    cout << "Masukkan ID pelanggan               : ";
    cin >> idPelanggan;

    int index = -1;
    for (int i = 0; i < jumlahPelanggan; i++) {
        if (pelanggan[i].id == idPelanggan) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "ID pelanggan tidak valid" << endl;
        return;
    }

    cout << "Data pelanggan ditemukan            :" << endl;
    cout << "Nama                                : " << pelanggan[index].nama << endl;
    cout << "Alamat                              : " << pelanggan[index].alamat << endl;
    cout << "Nomor telepon                       : " << pelanggan[index].nomor << endl;

    Pesanan newPesanan = prosesPesanan();
    newPesanan.id_pelanggan = idPelanggan;
    newPesanan.status = 0;

    cout << "Total harga yang harus dibayar      : Rp " << newPesanan.totalHarga << endl;

    pesanan[jumlahPesanan] = newPesanan;
    jumlahPesanan++;
}

// Fungsi Untuk Menampilkan daftar pesanan yang belum selesai
void displayUnfinishedOrders(Pesanan pesanan[], int jumlahPesanan) {
    cout << "_________________________________________________________________________" << endl;
    cout << "                    Daftar pesanan yang belum selesai                    " << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    int found = 0;

    for (int i = 0; i < jumlahPesanan; i++) {
        if (pesanan[i].status == 0) {
            found = 1;
            cout << "ID pelanggan                        : " << pesanan[i].id_pelanggan << endl;
            cout << "Jenis cucian                        : " << pesanan[i].jenis << endl;
            cout << "Jumlah cucian                       : " << pesanan[i].beratAtauJumlah << endl;
            cout << "Total biaya                         : " << pesanan[i].totalHarga << endl;
            cout << endl;
        }
    }

    if (found == 0) {
        cout << "Tidak ada pesanan yang belum selesai" << endl;
    }
}

// Fungsi Untuk Menandai pesanan sebagai selesai
void markOrderCompleted(Pesanan pesanan[], int jumlahPesanan) {
    cout << "_________________________________________________________________________" << endl;
    cout << "                    Menandai pesanan sebagai selesai                     " << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    int idPelanggan;
    cout << "Masukkan ID pelanggan               : ";
    cin >> idPelanggan;

    int index = -1;
    for (int i = 0; i < jumlahPesanan; i++) {
        if (pesanan[i].id_pelanggan == idPelanggan && pesanan[i].status == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "ID pelanggan tidak valid atau tidak memiliki pesanan yang belum selesai" << endl;
        return;
    }

    cout << "Data pesanan ditemukan:" << endl;
    cout << "Jenis cucian                        : " << pesanan[index].jenis << endl;
    cout << "Jumlah cucian                       : " << pesanan[index].beratAtauJumlah << endl;
    cout << "Total biaya                         : " << pesanan[index].totalHarga << endl;

    pesanan[index].status = 1;

    cout << "Pesanan berhasil ditandai sebagai selesai" << endl;
    cout << endl;
}

// Fungsi Untuk Menghitung Total Pembayaran
int calculateTotalLaundryCost(Pesanan pesanan[], int jumlahPesanan) {
    int totalCost = 0;
    for (int i = 0; i < jumlahPesanan; i++) {
        if (pesanan[i].status == 1) {
            totalCost += pesanan[i].totalHarga;
        }
    }
    return totalCost;
}

// Fungsi Untuk Menampilkan riwayat pesanan yang sudah selesai
void displayCompletedOrderHistory(Pesanan pesanan[], int jumlahPesanan) {
    for (int i = 0; i < jumlahPesanan - 1; i++) {
        for (int j = 0; j < jumlahPesanan - i - 1; j++) {
            if (pesanan[j].id_pelanggan > pesanan[j + 1].id_pelanggan) {
                Pesanan temp = pesanan[j];
                pesanan[j] = pesanan[j + 1];
                pesanan[j + 1] = temp;
            }
        }
    }

    cout << "_________________________________________________________________________" << endl;
    cout << "                   Riwayat pesanan yang sudah selesai                    " << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    int found = 0;

    for (int i = 0; i < jumlahPesanan; i++) {
        if (pesanan[i].status == 1) {
            found = 1;
            cout << "ID pelanggan                        : " << pesanan[i].id_pelanggan << endl;
            cout << "Jenis cucian                        : " << pesanan[i].jenis << endl;
            cout << "Jumlah cucian                       : " << pesanan[i].beratAtauJumlah << endl;
            cout << "Total biaya                         : " << pesanan[i].totalHarga << endl;
            cout << endl;
        }
    }

    if (found == 0) {
        cout << "Tidak ada riwayat pesanan yang sudah selesai" << endl;
    }
}

// Fungsi Untuk Cari data pelanggan berdasarkan ID
int searchCustomerById(Pelanggan pelanggan[], int jumlahPelanggan, int idToSearch) {
    for (int i = 0; i < jumlahPelanggan; i++) {
        if (pelanggan[i].id == idToSearch) {
            return i;
        }
    }

    return -1;
}

// Funsi Utama
int main() {
    Pelanggan pelanggan[100];
    Pesanan pesanan[100];
    int jumlahPelanggan = 0;
    int jumlahPesanan = 0;
    int choice;

    strcpy(savedusername, "Danuu");
    strcpy(savedpassword, "dan123");

    do {
        cout << "Username : ";
        cin.getline(username, sizeof(username));
        cout << "Password : ";
        cin.getline(password, sizeof(password));

        if ((strcmp(username, savedusername) == 0) && (strcmp(password, savedpassword) == 0)) {
            i++;
            Sleep(2000);
            system("cls");
            break;
        } else {
            cout << "\n_________________________________________________________________________\n";
            cout << "                           PASSWORD SALAH\n";
            cout << "-------------------------------------------------------------------------\n";
            i++;
            Sleep(2000);
            system("cls");
        }
    } while (i < 3);

    if (i >= 3) {
        cout << "_________________________________________________________________________\n";
        cout << "                               AKSES DITOLAK\n";
        cout << "-------------------------------------------------------------------------\n";
        return 0;
    }

    // Memuat data dari file saat program dimulai
    loadDataFromFile(pelanggan, jumlahPelanggan, pesanan, jumlahPesanan);

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                inputDataPelanggan(pelanggan, jumlahPelanggan);
                break;
            case 2:
                orderLaundryService(pelanggan, pesanan, jumlahPelanggan, jumlahPesanan);
                break;
            case 3:
                displayUnfinishedOrders(pesanan, jumlahPesanan);
                break;
            case 4:
                markOrderCompleted(pesanan, jumlahPesanan);
                break;
            case 5:
                displayCompletedOrderHistory(pesanan, jumlahPesanan);
                break;
            case 6: {
                int customerIdToSearch;
                cout << "_________________________________________________________________________" << endl;
                cout << "                   Cari data pelanggan berdasarkan ID                    " << endl;
                cout << "-------------------------------------------------------------------------" << endl;
                cout << "Masukkan ID pelanggan               : ";
                cin >> customerIdToSearch;

                int customerIndex = searchCustomerById(pelanggan, jumlahPelanggan, customerIdToSearch);

                if (customerIndex != -1) {
                    cout << "Data pelanggan ditemukan" << endl;
                    cout << "                                    : ";
                    cout << "Nama                                : " << pelanggan[customerIndex].nama << endl;
                    cout << "Alamat                              : " << pelanggan[customerIndex].alamat << endl;
                    cout << "Nomor telepon                       : " << pelanggan[customerIndex].nomor << endl;
                } else {
                    cout << "Data pelanggan tidak ditemukan." << endl;
                }
                break;
            }
            case 7:
                cout << "Terima kasih! Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan pilih lagi." << endl;
        }
    } while (choice != 7);

    // Menyimpan data ke dalam file saat program berakhir
    saveDataToFile(pelanggan, jumlahPelanggan, pesanan, jumlahPesanan);

    return 0;
}

