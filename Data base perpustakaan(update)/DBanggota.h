// DATABASE ANGGOTA
using namespace std;
void clearScreen();
struct anggota
{
    string id_anggota;
    string nama;
    string alamat;
    string no_telp;
    string tanggal_lahir;
    string status_keanggotaan;
};
// error handling file duplikat
// Deklarasikan vektor di luar fungsi agar dapat diakses secara global
vector<anggota> daftar_anggota;
set<string> id_anggota_set;
bool cekDuplikatFile(const string &id)
{
    ifstream file("database_anggota.txt");
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string id_anggota;
            getline(ss, id_anggota, ',');
            if (id_anggota == id)
            {
                file.close();
                return true; // Jika ID anggota ditemukan dalam file, kembalikan true
            }
        }
        file.close();
    }
    return false; // Jika ID anggota tidak ditemukan dalam file, kembalikan false
}
// Fungsi untuk memeriksa duplikat saat input
bool cekDuplikatInput(const string &id)
{
    for (const auto &a : daftar_anggota)
    {
        if (a.id_anggota == id)
        {
            return true;
        }
    }
    return false;
}
bool cekDuplikat(const string &id)
{
    // Pertama, cek dalam file teks
    if (cekDuplikatFile(id))
    {
        return true;
    }
    // Jika tidak ditemukan dalam file, lanjutkan ke pemeriksaan input
    if (cekDuplikatInput(id))
    {
        return true;
    }
    return false;
}
// cek file end

// input data
void inputdata_baruA(const string &file_anggota)
{
    int jumlah_anggota;
    cout << "Silahkan masukkan jumlah anggota!" << endl;
    cout << "Jumlah anggota: ";
    cin >> jumlah_anggota;
    cin.ignore();

    for (int i = 0; i < jumlah_anggota; ++i)
    {
        anggota temp; // vektor anggota
        cout << "Masukkan data anggota ke-" << i + 1 << ": " << endl;
        do
        {
            cout << "id                 : ";
            getline(cin, temp.id_anggota);
            // Memeriksa duplikat di file
            if (cekDuplikatFile(temp.id_anggota))
            {
                cout << "ID yang Anda masukkan telah ada dalam database. Silakan masukkan ID lain." << endl;
                continue;
            }
            // Memeriksa duplikat pada proses input
            if (id_anggota_set.find(temp.id_anggota) != id_anggota_set.end())
            {
                cout << "ID yang Anda masukkan telah ada dalam proses input. Silakan masukkan ID lain." << endl;
                continue;
            }
            break;
        } while (cekDuplikat(temp.id_anggota));

        id_anggota_set.insert(temp.id_anggota); // Menambahkan ID anggota baru ke dalam set

        cout << "Nama               : ";
        getline(cin, temp.nama);
        cout << "Alamat             : ";
        getline(cin, temp.alamat);
        cout << "No telp            : ";
        getline(cin, temp.no_telp);
        cout << "Tanggal lahir      : ";
        getline(cin, temp.tanggal_lahir);
        cout << "Status keanggotaan : ";
        getline(cin, temp.status_keanggotaan);
        cout << endl;

        daftar_anggota.push_back(temp);
    }

    ofstream file(file_anggota, ios::app);
    if (file.is_open())
    {
        for (const auto &a : daftar_anggota)
        {
            file << a.id_anggota << "," << a.nama << ","
                 << a.alamat << "," << a.no_telp << ","
                 << a.tanggal_lahir << "," << a.status_keanggotaan << "\n";
        }
        file.close();
        cout << "Data berhasil diinput ke " << file_anggota << endl;
    }
    else
    {
        cout << "Gagal membuka " << file_anggota << " untuk penulisan." << endl;
    }
}
// input data end

// tampilkan data anggota

// Validasi data untuk memastikan setiap ID hanya muncul sekali
void validasiData(vector<anggota> &data_anggota)
{
    set<string> id_set;         // Set untuk menyimpan ID yang sudah ditampilkan
    vector<anggota> data_valid; // Vektor untuk menyimpan data yang sudah divalidasi
    for (const auto &a : data_anggota)
    {
        // Periksa apakah ID sudah ditampilkan sebelumnya
        if (id_set.find(a.id_anggota) != id_set.end())
        {
            // Jika ID sudah ditampilkan, lewati data ini
            continue;
        }
        // Tambahkan ID ke set
        id_set.insert(a.id_anggota);
        // Tambahkan data ke vektor data yang sudah divalidasi
        data_valid.push_back(a);
    }
    // Perbarui vektor data anggota dengan data yang sudah divalidasi
    data_anggota = data_valid;
}

// Tampilkan data anggota
void tampilkanData(const vector<anggota> &data_anggota)
{
    int indeks = 1;
    cout << "Isi Database Anggota:\n";
    for (const auto &a : data_anggota)
    {
        cout << "Anggota ke-" << indeks << ":" << endl;
        cout << "Id                 : " << a.id_anggota << endl;
        cout << "Nama               : " << a.nama << endl;
        cout << "Alamat             : " << a.alamat << endl;
        cout << "No telp            : " << a.no_telp << endl;
        cout << "Tanggal lahir      : " << a.tanggal_lahir << endl;
        cout << "Status keanggotaan : " << a.status_keanggotaan << endl;
        cout << endl;
        indeks++;
    }
}

// perbarui file dengan data yang telah di validasi
void perbaruiFile(const string &file_anggota, const vector<anggota> &data_anggota)
{
    ofstream file(file_anggota);
    if (file.is_open())
    {
        for (const auto &a : data_anggota)
        {
            file << a.id_anggota << "," << a.nama << ","
                 << a.alamat << "," << a.no_telp << ","
                 << a.tanggal_lahir << "," << a.status_keanggotaan << "\n";
        }
        file.close();
        cout << "File " << file_anggota << " berhasil diperbarui dengan data yang sudah divalidasi." << endl;
    }
    else
    {
        cout << "Gagal membuka " << file_anggota << " untuk penulisan." << endl;
    }
}

// Qouick short

void swapAnggota(anggota &a, anggota &b)
{
    anggota temp = a;
    a = b;
    b = temp;
}

void quick_sort_anggota(vector<anggota> &array, int first, int last)
{
    if (first < last)
    {
        int low = first;
        int high = last;

        // Pilih pivot
        string pivot = array[(low + high) / 2].id_anggota;

        // Partition array
        while (low <= high)
        {
            // Temukan elemen yang lebih besar dari pivot
            while (array[low].id_anggota < pivot)
                low++;
            // Temukan elemen yang lebih kecil dari pivot
            while (array[high].id_anggota > pivot)
                high--;
            // Jika low <= high, tukar elemen dan naikkan loow, turunkan high
            if (low <= high)
            {
                swapAnggota(array[low], array[high]);
                low++;
                high--;
            }
        }

        // Panggil rekursif quick_sort_anggota untuk bagian sebelum dan setelah pivot
        quick_sort_anggota(array, first, high);
        quick_sort_anggota(array, low, last);
    }
}

// Tampilkan data anggota setelah divalidasi
void outputA(const string &file_anggota)
{
    ifstream file(file_anggota);
    if (file.is_open())
    {
        anggota temp_a;
        vector<anggota> data_anggota; // Vektor untuk menyimpan data anggota dari file
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            getline(ss, temp_a.id_anggota, ',');
            getline(ss, temp_a.nama, ',');
            getline(ss, temp_a.alamat, ',');
            getline(ss, temp_a.no_telp, ',');
            getline(ss, temp_a.tanggal_lahir, ',');
            getline(ss, temp_a.status_keanggotaan, ',');
            data_anggota.push_back(temp_a); // Tambahkan data anggota ke vektor
        }
        file.close();

        // Validasi data untuk memastikan setiap ID hanya muncul sekali
        validasiData(data_anggota);

        // Urutkan data anggota berdasarkan ID anggota menggunakan quick sort
        quick_sort_anggota(data_anggota, 0, data_anggota.size() - 1);

        // Tampilkan data anggota setelah divalidasi
        tampilkanData(data_anggota);

        // update data yang sudah divalidasi untuk menghindari penumpukan
        perbaruiFile(file_anggota, data_anggota);
    }
    else
    {
        cout << "Gagal membuka " << file_anggota << " untuk pembacaan." << endl;
    }
}

// tampilkan data anggota end

// hapus data
void hapusA(const string &file_anggota, const string &temp_anggota)
{
    ofstream file_temp(temp_anggota);
    ifstream file_sumber(file_anggota);
    if (!file_temp.is_open() || !file_sumber.is_open())
    {
        cout << "Gagal membuka file." << endl;
        return;
    }

    cin.ignore();
    string cari;
    cout << "Masukkan id atau nama yang ingin dihapus: ";
    getline(cin, cari);
    string line;
    bool anggota_ditemukan = false;
    while (getline(file_sumber, line))
    {
        stringstream ss(line);
        anggota temp;
        getline(ss, temp.id_anggota, ',');
        getline(ss, temp.nama, ',');
        getline(ss, temp.alamat, ',');
        getline(ss, temp.no_telp, ',');
        getline(ss, temp.tanggal_lahir, ',');
        getline(ss, temp.status_keanggotaan, ',');

        string cari_lower = temp.nama;
        transform(cari_lower.begin(), cari_lower.end(), cari_lower.begin(), ::tolower);
        string dicari_lower = cari;
        transform(dicari_lower.begin(), dicari_lower.end(), dicari_lower.begin(), ::tolower);

        if (dicari_lower == cari_lower || temp.id_anggota == cari)
        {
            cout << "Buku yang akan dihapus: " << endl;
            cout << "Id : " << temp.id_anggota << endl;
            cout << "Nama: " << temp.nama << endl;
            cout << "Alamat: " << temp.alamat << endl;
            cout << "No telp: " << temp.no_telp << endl;
            cout << "Tanggal lahir: " << temp.tanggal_lahir << endl;
            cout << "Status anggota: " << temp.status_keanggotaan << endl;
            cout << endl;

            char konfirmasi;
            cout << "Apakah anda yakon ingin menghapus data anggota ini? (y/n): ";
            cin >> konfirmasi;

            if (konfirmasi == 'y' || konfirmasi == 'Y')
            {
                anggota_ditemukan = true;
            }
        }
        else
        {
            file_temp << line << endl;
        }
    }
    file_temp.close();
    file_sumber.close();

    if (anggota_ditemukan)
    {
        if (remove(file_anggota.c_str()) != 0)
        {
            cout << "Gagal menghapus buku dari database." << endl;
            return;
        }

        if (rename(temp_anggota.c_str(), file_anggota.c_str()) != 0)
        {
            cout << "Gagal mengubah nama file sementara." << endl;
            return;
        }
        cout << "anggota berhasil dihapus dari database" << endl;
    }
    else
    {
        cout << "Anggota dengan id atau nama " << cari << " Tidak ditemukan dalam database atau tidak dihapus." << endl;
    }
}
// hapus data end

// update data
void updateA(const string &file_anggota)
{
   ifstream file(file_anggota);
    if (file.is_open())
    {
        daftar_anggota.clear(); // Kosongkan vektor sebelum mengisi kembali
        anggota temp_a;
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            getline(ss, temp_a.id_anggota, ',');
            getline(ss, temp_a.nama, ',');
            getline(ss, temp_a.alamat, ',');
            getline(ss, temp_a.no_telp, ',');
            getline(ss, temp_a.tanggal_lahir, ',');
            getline(ss, temp_a.status_keanggotaan, ',');
            daftar_anggota.push_back(temp_a); // Tambahkan data anggota ke vektor
        }
        file.close();
    }
    else
    {
        cout << "Gagal membuka file " << file_anggota << endl;
        return;
    }

    string input;
    cout << "Masukkan id atau nama anggota yang ingin diupdate: " << endl;
    cout << "Nama atau id: ";
    cin.ignore();
    getline(cin, input);
    bool anggota_ditemukan = false;
    anggota anggota_terpilih;
    vector<anggota> anggota_yang_dirubah;
    vector<anggota> gabungan;

    // Cari data anggota
    for (size_t i = 0; i < daftar_anggota.size(); ++i)
    {
        if (daftar_anggota[i].id_anggota == input || daftar_anggota[i].nama == input)
        {
            anggota_terpilih = daftar_anggota[i];
            anggota_ditemukan = true;
            break;
        }
    }

    if (anggota_ditemukan)
    {
        // Tampilkan data anggota
        cout << "Id : " << anggota_terpilih.id_anggota << endl;
        cout << "Nama: " << anggota_terpilih.nama << endl;
        cout << "Alamat: " << anggota_terpilih.alamat << endl;
        cout << "No telp: " << anggota_terpilih.no_telp << endl;
        cout << "Tanggal lahir: " << anggota_terpilih.tanggal_lahir << endl;
        cout << "Status anggota: " << anggota_terpilih.status_keanggotaan << endl;

        char konfirmasi;
        cout << "Ingin melakukan update data anggota ini?(y/n): ";
        cin >> konfirmasi;
        cin.ignore();
        if (konfirmasi == 'y' || konfirmasi == 'Y')
        {
            anggota temp;
            cout << "Masukkan data baru!" << endl;
            cout << "Id: ";
            getline(cin, temp.id_anggota);
            if (cekDuplikatFile(temp.id_anggota) || cekDuplikatInput(temp.id_anggota))
            {
                cout << "ID yang Anda masukkan sudah ada dalam database. Masukkan ID lain." << endl;
                return;
            }
            cout << "Nama: ";
            getline(cin, temp.nama);
            cout << "Alamat: ";
            getline(cin, temp.alamat);
            cout << "No telp: ";
            getline(cin, temp.no_telp);
            cout << "Tanggal lahir: ";
            getline(cin, temp.tanggal_lahir);
            cout << "Status keanggotaan: ";
            getline(cin, temp.status_keanggotaan);

            anggota_yang_dirubah.push_back(temp);
        }

         else
        {
            // tidak ada update maka tidak ada data yang berubah 
            gabungan.push_back(anggota_terpilih);
        }
    }
    else
    {
        cout << "Anggota tidak ditemukan. Apakah anda ingin menambahkannya sebagai anggota baru?(y/Y)" << endl;
        char tambahA;
        cin >> tambahA;
        if (tambahA == 'y' || tambahA == 'Y')
        {
            inputdata_baruA(file_anggota);
            return;
        }
    }

    for (size_t i = 0; i < daftar_anggota.size(); ++i)
    {
        if (daftar_anggota[i].id_anggota != anggota_terpilih.id_anggota)
        {
            gabungan.push_back(daftar_anggota[i]);
        }
        else
        {
            for (size_t j = 0; j < anggota_yang_dirubah.size(); ++j)
            {
                gabungan.push_back(anggota_yang_dirubah[j]);
            }
        }
    }

    // Simpan perubahan ke file
    ofstream outfile(file_anggota);
    if (outfile.is_open())
    {
        for (const auto &a : gabungan)
        {
            outfile << a.id_anggota << "," << a.nama << ","
                    << a.alamat << "," << a.no_telp << ","
                    << a.tanggal_lahir << "," << a.status_keanggotaan << "\n";
        }
        outfile.close();
        cout << "Data anggota berhasil diupdate." << endl;
    }
    else
    {
        cout << "Gagal membuka file untuk menulis ulang" << endl;
    }
}

// GUI anggota
void DBanggota()
{
    bool kembali = true;
    char kembali_menu;
    do
    {
        int pilih;
        cout << "MENU PILIHAN \n"
             << "1. Kelola Data \n"
             << "2. Tampilkan \n"
             << "3. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;
        // input data anggota
        if (pilih == 1)
        {
            int pilih_menu;
            cout << "Apa yang ingin anda lakukan: \n"
                 << "1. Buat\n"
                 << "2. Ubah data\n"
                 << "3. Hapus\n";
            cout << "Pilih: ";
            cin >> pilih_menu;
            switch (pilih_menu)
            {
            case 1:
                inputdata_baruA("database_anggota.txt");
                break;
            case 2:
                updateA("database_anggota.txt");
                break;
            case 3:
                hapusA("database_anggota.txt", "anggota_temp.txt");
                break;
            default:
                break;
            }
        }
        // tampilkan data
        if (pilih == 2)
        {
            outputA("database_anggota.txt");
        }

        if (kembali_menu == 'y')
        {
            kembali = true;
        }
        if (kembali_menu == 'n')
        {
            kembali = false;
        }
        cout << "Apakah anda ingin kembali ke menu?" << endl;
        cout << "Pilih(y/n):";
        cin >> kembali_menu;
        clearScreen();
    } while (kembali);
}
// GUI anggota