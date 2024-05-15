#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include <ctime>
#include <iomanip>
// file yang di include
#include "DBanggota.h"
#include "DBbuku.h"
using namespace std;
// daftar deklarasi porsedur
void clearScreen()
{
#ifdef _WIN32 // For windows
    system("cls");
#else
    system("clear"); // for linux
#endif
}
// prosedur dari anggota
void DBanggota();
// prosedur dari buku
void DBbuku();
// prosedur dari sirkulasi
void DBsirkulasi();
void cetak_keterangan(const string &file_anggota, const string &file_buku, const string &file_sirkulasi);
void k_peminjam(const string &file_anggota);
void pinjam(const string &file_buku);
void simpan_ke_database(const string &file_sirkulasi);
// end
// struktur database
// menu interface
int main()
{
    int pilihan;
    // Admin dapat mengakses Database Anggota dan Database Buku
    // Penggunjung hanya mengakses sistem sirkulasi
    cout << "Pilihan program: " << endl;
    cout << "1. Database Anggota\n"
         << "2. Database Buku\n"
         << "3. Sistem Sirkulasi\n";
    cout << "Pilih: ";
    cin >> pilihan;
    switch (pilihan)
    {
    case 1:
        // anggota
        DBanggota();
        break;
    case 2:
        // buku
        DBbuku();
        break;
    case 3:
        // status
        DBsirkulasi();
        break;
    case 4:
        //
    default:
        break;
    }
    // database pusat yang untuk cek seluruh data

    // endl
}
// menu interface end

// sistem sirkulasi
// data peminjaman
struct SIRKULASI
{
    string ID_pinjam;
    string ID_peminjam;
    string NAMA_peminjam;
    string NOtelp_peminjam;
    int ISBN_dipinjam;
    string Namabuku_dipinjam;
    string penulis;
    int tahun_terbit;
    int jumlah_eksemplar;
    string status_pinjam;
};
// Struct Peminjaman
struct PEMINJAMAN
{
    int ISBN_dipinjam;
    string Namabuku_dipinjam;
    string penulis;
    int tahun_terbit;
    int jumlah_eksemplar;
};
// Struct peminjam
struct PEMINJAM
{
    string ID_peminjam;
    string NAMA_peminjam;
    string NOtelp_peminjam;
    string status_pinjam;
};

// vector silkulasi global
vector<SIRKULASI> data_sirkulasi;
vector<PEMINJAMAN> daftar_buku_dipinjam;
vector<PEMINJAM> daftar_peminjam;

// Peminjaman
// cetak
string buat_random(int n)
{
    srand(time(nullptr));
    string angka_random;
    for (int i = 0; i < n; ++i)
    {
        angka_random += to_string(rand() % 10); // Menghasilkan angka acak antara 0 dan 9
    }
    return angka_random;
}
void cetak_keterangan(const string &file_anggota, const string &file_buku, const string &file_sirkulasi)
{
    cout << "Daftar Peminjaman:" << endl;
    cout << "==========================================" << endl;
    for (size_t i = 0; i < daftar_peminjam.size(); ++i)
    {
        SIRKULASI sirkulasi;
        sirkulasi.ID_pinjam = buat_random(3);
        sirkulasi.ID_peminjam = daftar_peminjam[i].ID_peminjam;
        sirkulasi.NAMA_peminjam = daftar_peminjam[i].NAMA_peminjam;
        sirkulasi.NOtelp_peminjam = daftar_peminjam[i].NOtelp_peminjam;
        sirkulasi.ISBN_dipinjam = daftar_buku_dipinjam[i].ISBN_dipinjam;
        sirkulasi.Namabuku_dipinjam = daftar_buku_dipinjam[i].Namabuku_dipinjam;
        sirkulasi.penulis = daftar_buku_dipinjam[i].penulis;
        sirkulasi.tahun_terbit = daftar_buku_dipinjam[i].tahun_terbit;
        sirkulasi.jumlah_eksemplar = daftar_buku_dipinjam[i].jumlah_eksemplar;
        sirkulasi.status_pinjam = daftar_peminjam[i].status_pinjam;
        // tampilkan data
        cout << "No Peminjaman      : " << sirkulasi.ID_pinjam << endl;
        cout << "ID Peminjam        : " << sirkulasi.ID_peminjam << endl;
        cout << "Nama Peminjam      : " << sirkulasi.NAMA_peminjam << endl;
        cout << "Nomor Telepon      : " << sirkulasi.NOtelp_peminjam << endl;
        cout << "ISBN Dipinjam      : " << sirkulasi.ISBN_dipinjam << endl;
        cout << "Nama Buku Dipinjam : " << sirkulasi.Namabuku_dipinjam << endl;
        cout << "Penulis            : " << sirkulasi.penulis << endl;
        cout << "Tahun Terbit       : " << sirkulasi.tahun_terbit << endl;
        cout << "Jumlah Eksemplar   : " << sirkulasi.jumlah_eksemplar << endl;
        cout << "Status             : " << sirkulasi.status_pinjam << endl;
        cout << "==========================================" << endl;

        data_sirkulasi.push_back(sirkulasi);
    }
    ofstream file(file_sirkulasi, ios::app);
    if (file.is_open())
    {
        for (const auto &s : data_sirkulasi)
        {
            file << s.ID_pinjam << "," << s.ID_peminjam << ","
                 << s.NAMA_peminjam << "," << s.NOtelp_peminjam << ","
                 << s.ISBN_dipinjam << "," << s.Namabuku_dipinjam << ","
                 << s.penulis << "," << s.tahun_terbit << ","
                 << s.jumlah_eksemplar << "," << s.status_pinjam << "\n";
        }
        file.close();
        cout << "Data berhasil diinput ke " << file_sirkulasi << endl;
    }
    else
    {
        cout << "Gagal membuka " << file_sirkulasi << " untuk penulisan." << endl;
    }
}

// keterangan peminjam
void k_peminjam(const string &file_anggota)
{
    ifstream file(file_anggota);
    string nama_peminjam;
    // mengambil keterangan peminjaman
    cout << "Silahkan isi identitas peminjaman!" << endl;
    cout << "Nama: ";
    getline(cin, nama_peminjam);

    if (file.is_open())
    {
        vector<anggota> identitas_peminjam;
        anggota peminjam_b;
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            getline(ss, peminjam_b.id_anggota, ',');
            getline(ss, peminjam_b.nama, ',');
            getline(ss, peminjam_b.no_telp, ',');
            daftar_anggota.push_back(peminjam_b);
        }
        file.close();

        // konfirmasi identitas
        bool ditemukan = false;
        for (const auto &a : daftar_anggota)
        {
            if (a.nama == nama_peminjam)
            {
                cout << "Konfirmasi Anggota dengan identitas " << endl;
                cout << "Id                 : " << a.id_anggota << endl;
                cout << "Nama               : " << a.nama << endl;
                cout << "Nomor Telepon      : " << a.no_telp << endl;
                // konfirmasi meninjam
                char konfirmasi;

                cout << "Lanjut Ingin mencetak keterangan peminjaman?(y/n): ";
                cin >> konfirmasi;
                cin.ignore();
                if (konfirmasi == 'y' || konfirmasi == 'Y')
                {
                    string s_pinjam = "meninjam";
                    PEMINJAM konfirmasi_peminjam;
                    konfirmasi_peminjam.ID_peminjam = a.id_anggota;
                    konfirmasi_peminjam.NAMA_peminjam = a.nama;
                    konfirmasi_peminjam.NOtelp_peminjam = a.no_telp;
                    konfirmasi_peminjam.status_pinjam = s_pinjam;
                    daftar_peminjam.push_back(konfirmasi_peminjam);
                    ditemukan = true;
                    cetak_keterangan("database_anggota.txt", "database_buku.txt", "database_sirkulasi.txt");
                }
                ditemukan = true;
                break;
            }
        }
        if (!ditemukan)
        {
            cout << "Anggota tidak ditemukan." << endl;
        }
    }
    else
    {
        cout << "Gagal membuka file " << file_anggota << endl;
        return;
    }
}
static int nextID = 1;
void pinjam(const string &file_buku)
{
    ifstream file(file_buku);
    if (!file.is_open())
    {
        cout << "Gagal membuka file" << file_buku << endl;
        return;
    }
    vector<buku> daftar_buku_pinjam;
    buku pinjam_b;
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        ss >> pinjam_b.ISBN;
        ss.ignore();
        getline(ss, pinjam_b.judul, ',');
        getline(ss, pinjam_b.penulis, ',');
        ss >> pinjam_b.tahun_terbit;
        ss.ignore();
        ss >> pinjam_b.jumlah_eksemplar;
        // if (ss.fail())
        // {
        //     cout << "Gagal membaca jumlah eksemplar." << endl;
        //     return;
        // }
        daftar_buku_pinjam.push_back(pinjam_b);
    }
    file.close();
    cout << "Silahkan tulis judul buku yang anda ingin cari." << endl;
    cout << "Judul : ";
    string cari_buku;
    getline(cin, cari_buku);
    bool ditemukan = false;
    for (buku &b : daftar_buku_pinjam)
    {
        if (to_string(b.ISBN) == cari_buku || b.judul == cari_buku)
        {
            cout << "Buku yang ditemukan." << endl;
            cout << "ISBN             : " << b.ISBN << endl;
            cout << "Judul            : " << b.judul << endl;
            cout << "Penulis          : " << b.penulis << endl;
            cout << "Tahun terbit     : " << b.tahun_terbit << endl;
            cout << "Jumlah eksemplar : " << b.jumlah_eksemplar << endl;
            // konfirmasi meninjam
            char konfirmasi;

            cout << "Ingin meninjam buku ini?(y/n): ";
            cin >> konfirmasi;
            cin.ignore();
            if (konfirmasi == 'y' || konfirmasi == 'Y')
            {
                PEMINJAMAN peminjaman;

                peminjaman.ISBN_dipinjam = b.ISBN;
                peminjaman.Namabuku_dipinjam = b.judul;
                peminjaman.penulis = b.penulis;
                peminjaman.tahun_terbit = (b.tahun_terbit);
                peminjaman.jumlah_eksemplar = b.jumlah_eksemplar;
                daftar_buku_dipinjam.push_back(peminjaman);
                
                // simpan ke file database_sirkulasi.txt
                // simpan_ke_database("database_sirkulasi.txt");
                k_peminjam("database_anggota.txt");
            }

            break;
        }
    }
    if (!ditemukan)
    {
        cout << "Buku tidak ditemukan." << endl;
    }
}

// Peminjamann end
void pengembalian(const string &file_sirkulasi, const string &temp_sirkulasi)
{
    // buat file temp_sirkulas.txt
    ofstream file_temp(temp_sirkulasi);
    //
    ifstream file_sumber(file_sirkulasi);

    if (!file_temp.is_open() || !file_sumber.is_open())
    {
        cout << "gagal membuka file." << endl;
        return;
    }
    cout << "Silahkan masukkan nomor peminjama anda!" << endl;
    string cari_no_pinjam;
    cout << "Nomor Peminjaman: ";
    getline(cin, cari_no_pinjam);

    string line;
    bool nomor_ditemukan = false;
    while (getline(file_sumber, line))
    {
        stringstream ss(line);
        SIRKULASI temp;
        getline(ss, temp.ID_pinjam, ',');
        getline(ss, temp.ID_peminjam, ',');
        getline(ss, temp.NAMA_peminjam, ',');
        getline(ss, temp.NOtelp_peminjam, ',');
        ss >> temp.ISBN_dipinjam;
        ss.ignore();
        getline(ss, temp.Namabuku_dipinjam, ',');
        getline(ss, temp.penulis, ',');
        ss >> temp.tahun_terbit;
        ss.ignore();
        ss >> temp.jumlah_eksemplar;
        ss.ignore();
        getline(ss, temp.status_pinjam, ',');

        if (temp.ID_pinjam == cari_no_pinjam)
        {
            cout << "INFORMASI PEMINJAMAN ANDA SEBAGAI BERIKUT." << endl;
            cout << "==========================================" << endl;
            cout << "No Peminjaman      : " << temp.ID_pinjam << endl;
            cout << "ID Peminjam        : " << temp.ID_peminjam << endl;
            cout << "Nama Peminjam      : " << temp.NAMA_peminjam << endl;
            cout << "Nomor Telepon      : " << temp.NOtelp_peminjam << endl;
            cout << "ISBN Dipinjam      : " << temp.ISBN_dipinjam << endl;
            cout << "Nama Buku Dipinjam : " << temp.Namabuku_dipinjam << endl;
            cout << "Penulis            : " << temp.penulis << endl;
            cout << "Tahun Terbit       : " << temp.tahun_terbit << endl;
            cout << "Jumlah Eksemplar   : " << temp.jumlah_eksemplar << endl;
            cout << "Status             : " << temp.status_pinjam << endl;
            cout << "==========================================" << endl;

            char konfirmasi;
            cout << "Apakah anda yakin ingin mengembalikan buku ini? (y/n): ";
            cin >> konfirmasi;

            if (konfirmasi == 'y' || konfirmasi == 'Y')
            {
                nomor_ditemukan = true;
            }
        }
        else
        {
            file_temp << line << endl;
        }
    }
    file_temp.close();
    file_sumber.close();

    if (nomor_ditemukan)
    {
        if (remove(file_sirkulasi.c_str()) != 0)
        {
            cout << "gagal memperbarui data dari database." << endl;
            return;
        }

        if (rename(temp_sirkulasi.c_str(), file_sirkulasi.c_str()) != 0)
        {
            cout << "gagal ubah nama file temp" << endl;
            return;
        }

        cout << "Buku berhasi dihapus dari database." << endl;
    }
    else
    {
        cout << "No Peminjaman" << cari_no_pinjam << "' tidak ditemukan dalam database atau tidak terhapus." << endl;
    }
}
// pengembalian end
void DBsirkulasi()
{
    bool kembali = true;
    char kembali_menu;
    do
    {
        cout << "Selamat datang di Perpustakaan ...." << endl;
        cout << "Menu : \n"
             << "1. Pinjam\n"
             << "2. kembalikan\n"
             << "3. Keluar" << endl;
        cout << "Pilih: ";
        cin.ignore();
        int pilih;
        cin >> pilih;
        cin.ignore();
        switch (pilih)
        {
        case 1:
            pinjam("database_buku.txt");
            break;
        case 2:
            pengembalian("database_sirkulasi.txt", "temp_sirkulai.txt");
            break;
        default:
            break;
        }
        cout << "Apakah Anda ingin kembali ke menu?" << endl;
        cout << "Pilih (y/n): ";
        cin >> kembali_menu;

        if (kembali_menu == 'n' || kembali_menu == 'N')
        {
            kembali = false;
        }
    } while (kembali);
}
// sistem sirkulasi end
