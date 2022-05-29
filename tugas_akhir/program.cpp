#include <iostream>
#include <iomanip>
#include <limits>
#include <fstream>
#include <string>
using namespace std;

// --- deklarasi struct ---

int pilih, lc, kt, stok[100], pin, pl, pk, pj, pukul, np[100];
string jam1[20], jam2[20], lab1, lab2, kolab[100], kode;
int lk = -1;
int st = 0;
int lp = -1;
int lb = 0;
char yn, ex, kp[100];

struct lab
{
    int stock;
    char kode_lab[100];
    char nama_lab[100];
    string sd;
} lab[100];

struct pakai
{
    int lp, jam1, jam2, dipakai;
    char nama[100];
    string npm;
    char prodi[100];
    char kl[100];
    char pelajaran[100];
    char dosen[100];
    char status, kelas[100];
} pakaiLab[100];

void tabelLab();
void pilihanJam();
void jam();
void pilihanjam2();

// --- MAIN APPLICATION ---

int main()
{
    ofstream outData;

menu:
    cout << "\n	  PROGRAM PEMAKAIAN\n 	LABORATORIUM & KELAS \n"
         << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << "1. PENGECEKAN LAB/KELAS " << setw(15) << " " << setw(4) << "2. MENGGUNAKAN LAB/KELAS " << setw(9) << endl;
    cout << endl
         << "3. MENGEMBALIKAN LAB/KELAS" << setw(15) << " " << setw(4) << "4. INPUT LAB/KELAS" << setw(9) << endl
         << endl;

    cout << "Masukan pilihan: ";
    cin >> pilih;
    switch (pilih)
    {
    case 1:

        system("cls");
        cout << "\n"
             << endl;
        tabelLab();
        cout << "Apakah ingin Melihat Data File ? (y/n) :";
        cin >> ex;
        if (ex == 'y' || ex == 'Y')
        {
            ofstream file_keluaran;
            file_keluaran.open("data.txt");

            file_keluaran << "--------------------------------------------------------------------\n";
            file_keluaran << " No  Kode Lab/kelas            Nama Lab/kelas                  Stock\n";
            file_keluaran << "--------------------------------------------------------------------\n";
            for (lc = 0; lc <= lk; lc++)
            {

                if (lab[lc].stock == 0)
                {
                    lab[lc].sd = "sedang digunakan";
                }
                else
                {
                    lab[lc].sd = "Tidak Digunakan";
                }

                file_keluaran << setw(2) << lc + 1 << setw(8) << lab[lc].kode_lab << setw(22) << lab[lc].nama_lab << setw(22) << lab[lc].sd << setw(22) << pakaiLab[lc].nama << setw(22) << pakaiLab[lc].npm << setw(22) << pakaiLab[lc].kelas;
                file_keluaran << endl;
            }
            file_keluaran.close();
            string line;
            ifstream file_input;
            file_input.open("data.txt");
            system("pause");
            system("cls");
            goto menu;
        }
        else
        {

            cout << "\n\n Baiklah \n"
                 << endl;
            system("pause");
            system("cls");
            goto menu;
        }
        break;

    case 2:
    pakai:

        system("cls");

        cout << endl;
        cout << endl;
        if (lb == 0)
        {
            cout << "\n\n Data Lab/Kelas Belum Tersedia \n"
                 << endl;
            system("pause");
            system("cls");
            goto menu;
        }
        else
        {
            tabelLab();
            cout << "\n"
                 << endl;
            cout << "\t\t\t Transaksi Peminjaman : \n";
            cout << "\t\t\t____________________\n\n";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            lp = 1;
        kode:
            cout << " Kode lab/Kelas \t\t:";
            gets(kp);

            for (kt = 0; kt < lp; kt++)
            {

                cout << " Masukan NPM \t\t:";
                getline(cin, pakaiLab[kt].npm);
                cout << "\n Masukan Nama  \t\t: ";
                gets(pakaiLab[kt].nama);
                cout << " Masukan Prodi  \t\t: ";
                gets(pakaiLab[kt].prodi);
                cout << " Masukan Pelajaran  \t\t: ";
                gets(pakaiLab[kt].pelajaran);
                cout << " Masukan Kelas  \t\t: ";
                gets(pakaiLab[kt].kelas);
                cout << " Masukan Nama Dosen  \t\t: ";
                gets(pakaiLab[kt].dosen);
                cout << "\tMulai Jam Pemakaian :" << endl;
                pilihanJam();
                cout << "\nSilahkan Pilih Jam Sesuai NO :";
                cin >> pakaiLab[kt].jam1;

                jam();
                cout << "\tJam Selesai Pemakaian :" << endl;
                pilihanJam();
                cout << "\nSilahkan Pilih Jam Sesuai NO :";
                cin >> pakaiLab[kt].jam2;
                pilihanjam2();
                cout << endl;
                cout << "Dari Pukul " << jam1[kt] << " - " << jam2[kt] << " WIB" << endl;
                pukul = pakaiLab[kt].jam2 - pakaiLab[kt].jam1;
                cout << "Lama Pemakaian : " << pukul << " Jam" << endl;
            }
            int l = 1;
            l++;
            cout << " Status dipinjam (y) ? \t\t:";
            cin >> pakaiLab[lp].status;
            lab[lp].stock = 0;
            cout << endl;

            cout << "Apakah Anda Ingin Menambahkan Data Lagi ? (y/n) :";
            cin >> yn;

            if (yn == 'y' || yn == 'Y')
            {
                goto pakai;
            }
            else
            {
                st = 1;
                cout << "\n\n Data Berhasil Disimpan \n"
                     << endl;

                system("pause");
                system("cls");
                goto menu;
            }
        }

        break;

    case 3:
        system("cls");
    pengembalian:
        if (st == 0)
        {
            cout << "\n\n Belum Ada Yang meminjam \n"
                 << endl;
            system("pause");
            system("cls");
            goto menu;
        }
        else
        {
            cout << "\t\t\tDaftar Nama Yang Meminjam" << endl;
            cout << "\t\t\t________________\n"
                 << endl;
            cout << "-----------------------------------------------\n";
            cout << " No  Nama            Kelas                  NPM\n";
            cout << "-----------------------------------------------\n";

            for (lc = 0; lc <= lk; lc++)
            {
                cout << setw(2) << lc + 1 << setw(8) << pakaiLab[lc].nama << setw(22) << pakaiLab[lc].kelas << setw(22) << pakaiLab[lc].npm;
                cout << endl;
            }
            cout << endl;
            cout << "\n"
                 << endl;
            cout << "\t\t\tMasukan NPM Peminjaman :";
            cin >> kode;
            cout << "\t\t\t____________________\n"
                 << endl;
            cout << endl;
            for (pl = 0; pl <= lp; pl++)
            {
                if (pakaiLab[pl].npm == kode)
                {
                    cout << " Nama Lab/Kelas \t\t:" << pakaiLab[pl].nama;
                    cout << endl;
                    cout << " Prodi \t\t:" << pakaiLab[pl].prodi;
                    cout << endl;
                    if (lab[pl].kode_lab == pakaiLab[pl].kl)
                    {
                        cout << " Kode lab/kelas plt\t\t:" << lab[pl].kode_lab << endl;
                        cout << " Judul lab/kelas plt\t\t:" << lab[pl].nama_lab << endl;
                    }
                    cout << " Dosen \t\t:" << pakaiLab[pl].dosen << endl;
                    cout << " Status : " << pakaiLab[pl].status;
                    lab[pl].stock = 1;
                    if ((pakaiLab[pl].status == 'y') || (pakaiLab[pl].status == 'Y'))
                    {
                        cout << " (di Pinjam) " << endl;
                    }
                    else
                    {
                        cout << " (di kembalikan) " << endl;
                    }
                    cout << endl;
                    cout << " Sudah di kembalikan ? (y/n) : ";
                    cin >> yn;
                    if ((yn == 'Y') || (yn == 'y'))
                    {
                        cout << " ganti status ( input n ) :";
                        cin >> pakaiLab[pl].status;
                        cout << "\n\n Data Berhasil Disimpan \n"
                             << endl;

                        system("pause");
                        system("cls");
                        goto menu;
                    }
                    else
                    {
                        cout << "\n\n Data Berhasil Disimpan \n"
                             << endl;
                        system("pause");
                        system("cls");
                        goto menu;
                    }
                }
                else
                {
                    cout << "\n\n Data Tidak Di temukan \n"
                         << endl;
                    cout << " Apakah ingin mengulang kembali ? (y/n) : ";
                    cin >> yn;
                    if (yn == 'Y' || yn == 'y')
                    {
                        system("cls");
                        goto pengembalian;
                    }
                    else
                    {
                        system("cls");
                        goto menu;
                    }
                }
            }
        }

        break;

    case 4:
    atas:
        system("cls");
        cout << "\n"
             << endl;
        cout << "\t\t\tInput Lab : \n"; //input Lab berdasarkan jumlah  Lab yang mau di input
        cout << "\t\t\t____________________\n"
             << endl;
        cout << endl;

        lk++;
        cout << " Masukan data Lab/Kelas Ke \t: " << lk + 1 << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << " Kode lab/kelas \t\t:";
        gets(lab[lk].kode_lab);
        cout << " judul Lab/kelas \t\t:";
        gets(lab[lk].nama_lab);
        lab[lk].stock = 1;

        cout << endl;
        cout << "Apakah Anda Ingin Menambahkan Data Lagi ? (y/n) :";
        cin >> yn;
        if (yn == 'y' || yn == 'Y')
        {
            goto atas;
        }
        else
        {
            cout << "\n\n Data Berhasil Disimpan \n"
                 << endl;
            lb = 1;
            system("pause");
            system("cls");
            goto menu;
        }
        {
            cout << "\n\n Data Berhasil Disimpan \n"
                 << endl;
            system("pause");
            system("cls");
            goto menu;
        }

        break;

    default:
        break;
    }
}

void jam()
{
    if (pakaiLab[kt].jam1 == 1)
    {
        jam1[kt] = "08:00";
        pakaiLab[kt].jam1 = 8;
    }
    else if (pakaiLab[kt].jam1 == 2)
    {
        jam1[kt] = "09:00";
        pakaiLab[kt].jam1 = 9;
    }
    else if (pakaiLab[kt].jam1 == 3)
    {
        jam1[kt] = "10:00";
        pakaiLab[kt].jam1 = 10;
    }
    else if (pakaiLab[kt].jam1 == 4)
    {
        jam1[kt] = "11:00";
        pakaiLab[kt].jam1 = 11;
    }
    else if (pakaiLab[kt].jam1 == 5)
    {
        jam1[kt] = "12:00";
        pakaiLab[kt].jam1 = 12;
    }
    else if (pakaiLab[kt].jam1 == 6)
    {
        jam1[kt] = "13:00";
        pakaiLab[kt].jam1 = 13;
    }
    else if (pakaiLab[kt].jam1 == 7)
    {
        jam1[kt] = "14:00";
        pakaiLab[kt].jam1 = 14;
    }
    else if (pakaiLab[kt].jam1 == 8)
    {
        jam1[kt] = "15:00";
        pakaiLab[kt].jam1 = 15;
    }
    else if (pakaiLab[kt].jam1 == 9)
    {
        jam1[kt] = "16:00";
        pakaiLab[kt].jam1 = 16;
    }
    else if (pakaiLab[kt].jam1 == 10)
    {
        jam1[kt] = "17:00";
        pakaiLab[kt].jam1 = 17;
    }
}

void pilihanjam2()
{
    if (pakaiLab[kt].jam2 == 1)
    {
        jam2[kt] = "08:00";
        pakaiLab[kt].jam2 = 8;
    }
    else if (pakaiLab[kt].jam2 == 2)
    {
        jam2[kt] = "09:00";
        pakaiLab[kt].jam2 = 9;
    }
    else if (pakaiLab[kt].jam2 == 3)
    {
        jam2[kt] = "10:00";
        pakaiLab[kt].jam2 = 10;
    }
    else if (pakaiLab[kt].jam2 == 4)
    {
        jam2[kt] = "11:00";
        pakaiLab[kt].jam2 = 11;
    }
    else if (pakaiLab[kt].jam2 == 5)
    {
        jam2[kt] = "12:00";
        pakaiLab[kt].jam2 = 12;
    }
    else if (pakaiLab[kt].jam2 == 6)
    {
        jam2[kt] = "13:00";
        pakaiLab[kt].jam2 = 13;
    }
    else if (pakaiLab[kt].jam2 == 7)
    {
        jam2[kt] = "14:00";
        pakaiLab[kt].jam2 = 14;
    }
    else if (pakaiLab[kt].jam2 == 8)
    {
        jam2[kt] = "15:00";
        pakaiLab[kt].jam2 = 15;
    }
    else if (pakaiLab[kt].jam2 == 9)
    {
        jam2[kt] = "16:00";
        pakaiLab[kt].jam2 = 16;
    }
    else if (pakaiLab[kt].jam2 == 10)
    {
        jam2[kt] = "17:00";
        pakaiLab[kt].jam2 = 17;
    }
}

void pilihanJam()
{
    cout << setw(2) << "1. 08:00" << setw(15) << " " << setw(4) << "2. 09:00" << setw(9) << endl;
    cout << setw(2) << "3. 10:00" << setw(15) << " " << setw(4) << "4. 11:00" << setw(9) << endl;
    cout << setw(2) << "5. 14:00" << setw(15) << " " << setw(4) << "6. 13:00" << setw(9) << endl;
    cout << setw(2) << "7. 14:00" << setw(15) << " " << setw(4) << "8. 15:00" << setw(9) << endl;
    cout << setw(2) << "9. 16:00" << setw(15) << " " << setw(4) << "10. 17:00" << setw(9) << endl;
}

void tabelLab()
{
    cout << "\t\t\tDaftar Lab/kelas" << endl;
    cout << "\t\t\t___________\n"
         << endl;
    cout << "----------------------------------------------------------------------------------\n";
    cout << " No  Kode Lab/kelas            Nama Lab/kelas                  Ketrangan Lab/Kelas\n";
    cout << "----------------------------------------------------------------------------------\n";

    for (lc = 0; lc <= lk; lc++)
    {
        if (lab[lc].stock == 0)
        {
            lab[lc].sd = "Sedang Digunakan";
        }
        else
        {
            lab[lc].sd = "Tidak Digunakan";
        }

        cout << setw(2) << lc + 1 << setw(8) << lab[lc].kode_lab << setw(22) << lab[lc].nama_lab << setw(22) << lab[lc].sd;
        cout << endl;
    }
    cout << endl;
}
