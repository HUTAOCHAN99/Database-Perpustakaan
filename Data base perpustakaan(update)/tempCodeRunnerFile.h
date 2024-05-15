void updateA(const string &file_anggota)
{
    ifstream file(file_anggota);
    if (!file.is_open())
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

    // Gabungkan data yang tidak diubah dengan data yang sudah diubah
    vector<anggota> gabungan;
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