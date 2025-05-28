#include <iostream>
#include <cctype>
#include <fstream>
#include <iomanip>

using namespace std;

const string fileLoginInfo = "loginInfo.txt";
const string fileListBuku = "listBuku.txt";
const int kapasitasBuku = 100;

string spaceToUnderscore(string str);
string UnderscoreToSpace(string str);
string EditUpLowCase(string str);

void mainMenu();
void firstMenu(string &user);

bool registerUsers(string &user, string pasw);
bool loginUsers(string &user, string pasw);

void updateBook(int jumlahBuku);
void listBook(int jumlahBuku);
void searchBook(int jumlahBuku);
void addBook(int tambahBuku, int jumlahBuku);
void sortingBuku(int jumlahBuku);
void OutputForSort();
void updateStock(int *a, int *b);
void fileLoader(int *a);

struct buku{
    string idBuku;
    string judulBuku;
    string penerbitBuku;
    string authorBuku;
    string genre;
    string tahunTerbit;
    int harga;
    int stok;
};
buku daftarBuku[kapasitasBuku];

int main(){
    system("cls");
    mainMenu();
    return 0;
}

void fileLoader(int *a){
    // klo gada file, membuat file
    ifstream fileCheck(fileListBuku);
    if(!fileCheck.is_open()){
        ofstream fileCreate(fileListBuku);
        fileCreate.close();
    }
    fileCheck.close();

    ifstream fileLoad(fileListBuku);
    string judulTemp, idTemp, authorTemp, penerbitTemp, tahunTemp, genreTemp;
    int i = 0;
    int hargaInt, stokInt;
    while(fileLoad >> idTemp >> judulTemp >> genreTemp >> authorTemp >> penerbitTemp >> tahunTemp >> hargaInt >> stokInt){
        judulTemp = UnderscoreToSpace(judulTemp);
        genreTemp = UnderscoreToSpace(genreTemp);
        authorTemp = UnderscoreToSpace(authorTemp);
        penerbitTemp = UnderscoreToSpace(penerbitTemp);

        daftarBuku[i].idBuku = idTemp;
        daftarBuku[i].judulBuku = judulTemp;
        daftarBuku[i].genre = genreTemp;
        daftarBuku[i].authorBuku = authorTemp;
        daftarBuku[i].penerbitBuku = penerbitTemp;
        daftarBuku[i].tahunTerbit = tahunTemp;
        daftarBuku[i].harga = hargaInt;
        daftarBuku[i].stok = stokInt;
        i++;
    }

    fileLoad.close();
    *a = i;
}

void mainMenu(){

    string user;
    int mode = 0;
    firstMenu(user);
    
    int pil, tambahBuku;
    pil = 0;
    int jumlahBuku = 0;
    while(pil != 6){
        fileLoader(&jumlahBuku);
        system("cls");
        cout << "Hai Admin "<< user << "! \n";
        cout << "Selamat Datang di Dashboard Toko Buku\n";
        cout << "[1]. Update Data Buku\n";
        cout << "[2]. List Buku\n";
        cout << "[3]. Cari Buku\n"; 
        cout << "[4]. Tambah Buku \n";
        cout << "[5]. Urutkan Buku \n";
        cout << "[6]. EXIT \n";
        cout << "Input: ";
        cin >> pil;
        switch(pil){
            case 1:
                if(jumlahBuku == 0){
                    cout << "Tidak Ada Buku! Tambahkan Dulu!\n";
                    system("pause");
                }else{
                    updateBook(jumlahBuku);
                }
            break;
            case 2:
                if(jumlahBuku == 0){
                    cout << "Tidak Ada Buku! Tambahkan Dulu!\n";
                    system("pause");
                }else{
                    listBook(jumlahBuku);
                }
            break;
            case 3:
                if(jumlahBuku == 0){
                    cout << "Tidak Ada Buku! Tambahkan Dulu!\n";
                    system("pause");
                }else{
                    searchBook(jumlahBuku);
                }
            break;
            case 4:
            system("cls");
                cout << "Jumlah Buku Yang Ingin Ditambahkan: ";
                cin >> tambahBuku;
                if(tambahBuku <= 0){
                    cout << "Jumlah Buku Harus >= 1!\n";
                    system("pause");
                }else{
                    addBook(tambahBuku, jumlahBuku);
                }
            break;

            case 5:
                if(jumlahBuku == 0){
                    cout << "Tidak Ada Buku! Tambahkan Dulu!\n";
                    system("pause");
                }else{
                    sortingBuku(jumlahBuku);
                }
            break;

            case 6:
                cout << "Bye!\n";
                exit(0);
            break;

            default:
                cout << "-\n";
                cout << "Input salah!! \n";
            break;
        }
    }
}

void firstMenu(string &user){
    int pil = 0;
    string pasw;

    while(true){
        system("cls");
        cout << "--------------------------------\n";
        cout << "   SISTEM MANAJEMEN TOKO BUKU\n";
        cout << "--------------------------------\n";
        cout << "[1]. Register\n";
        cout << "[2]. Login\n";
        cout << "[3]. EXIT\n";
        cout << "Input: ";
        cin >> pil;

        switch(pil){
            case 1:
                cout << "-\n";
                cout << "Username: ";
                cin >> user;
                cout << "Password: ";
                cin >> pasw;
                if(registerUsers(user, pasw)){
                    cout << "-\n";
                    cout << "Registrasi Berhasil!\n" << "Silakan Login!\n";
                    system("pause");
                }
                break;
                
            case 2:
                cout << "-\n";
                cout << "Username: ";
                cin >> user;
                cout << "Password: ";
                cin >> pasw;
                if(loginUsers(user, pasw)){
                    cout << "-\n";
                    cout << "Login Berhasil!\n";
                    system("pause");
                    return;
                }
            break;
            case 3:
                cout << "-\n";
                cout << "Terimakasih Telah Berkunjung!\n";
                system("pause");
                exit(0);
            break;
            default:
                cout << "-\n";
                cout << "Input Salah!\n";
                system("pause");
        }
    }
}

void updateBook(int jumlahBuku){

    bool done = false;
    bool found = false;
    string idTemp, updated, judulTemp;
    int stokUbah = 0;
    int pil = 0;
    int indx = 0;
    ofstream fileTemp(fileListBuku, ios::trunc);
    while(pil != 3 && !done){
        system("cls");
        cout << "[1]. Update Keseluruhan\n";
        cout << "[2]. Update Stok\n";
        cout << "[3]. BACK\n";
        cout << "Input: ";
        cin >> pil;

        switch(pil){
            case 1:
                system("cls");
                cout << "Masukkan ID Buku: ";
                cin >> idTemp;
                updated = idTemp;
                for(int i = 0; i < jumlahBuku; i++){
                    if(idTemp == daftarBuku[i].idBuku){
                        found = true;
                        indx = i;
                        break;
                    }
                }
                if(found){
                        cin.ignore();
                        cout << "--------------------------------\n";
                        cout << "Masukkan Judul Baru        : ";
                        getline(cin, daftarBuku[indx].judulBuku);
                        daftarBuku[indx].judulBuku = EditUpLowCase(daftarBuku[indx].judulBuku);
                        cout << "Masukkan Genre Baru        : ";
                        getline(cin, daftarBuku[indx].genre);
                        daftarBuku[indx].genre = EditUpLowCase(daftarBuku[indx].genre);

                        cout << "Masukkan Author Baru       : ";
                        getline(cin, daftarBuku[indx].authorBuku);
                        daftarBuku[indx].authorBuku = EditUpLowCase(daftarBuku[indx].authorBuku);

                        cout << "Masukkan Penerbit Baru     : ";
                        getline(cin, daftarBuku[indx].penerbitBuku);
                        daftarBuku[indx].penerbitBuku = EditUpLowCase(daftarBuku[indx].penerbitBuku);

                        cout << "Masukkan Tahun Terbit Baru : ";
                        cin >> daftarBuku[indx].tahunTerbit;

                        cout << "Masukkan Harga Baru        : ";
                        cin >> daftarBuku[indx].harga;

                        cout << "Masukkan Stok Baru         : ";
                        cin >> daftarBuku[indx].stok;
                        done = true;

                        for(int i = 0; i < jumlahBuku; i++){
                            fileTemp << daftarBuku[i].idBuku << ' ' << spaceToUnderscore(daftarBuku[i].judulBuku) << ' ' << spaceToUnderscore(daftarBuku[i].genre) << ' ' << spaceToUnderscore(daftarBuku[i].authorBuku) << ' ' << spaceToUnderscore(daftarBuku[i].penerbitBuku) << ' ' << daftarBuku[i].tahunTerbit << ' ' <<daftarBuku[i].harga << ' ' << daftarBuku[i].stok << '\n';
                        }
                        fileTemp.close();
                }else{
                    cout << idTemp << " Tidak Ada Bukunya!\n";
                    system("pause");
                    for(int i = 0; i < jumlahBuku; i++){
                            fileTemp << daftarBuku[i].idBuku << ' ' << spaceToUnderscore(daftarBuku[i].judulBuku) << ' ' << spaceToUnderscore(daftarBuku[i].genre) << ' ' << spaceToUnderscore(daftarBuku[i].authorBuku) << ' ' << spaceToUnderscore(daftarBuku[i].penerbitBuku) << ' ' << daftarBuku[i].tahunTerbit << ' ' <<daftarBuku[i].harga << ' ' << daftarBuku[i].stok << '\n';
                        }
                        fileTemp.close();
                }

            break;
            case 2:
                system("cls");
                cout << "Masukkan ID Buku: ";
                cin >> idTemp;
                updated = idTemp;
                for(int i = 0; i < jumlahBuku; i++){
                    if(idTemp == daftarBuku[i].idBuku){
                        found = true;
                        indx = i;
                        break;
                    }
                }
                
                if(found){
                        system("cls");
                        cout << "=================================================\n";
                        cout << "ID Buku        : " << daftarBuku[indx].idBuku << '\n';
                        cout << "Judul Buku     : " << daftarBuku[indx].judulBuku << '\n';
                        cout << "Genre          : " << daftarBuku[indx].genre << '\n';
                        cout << "Author         : " << daftarBuku[indx].authorBuku << '\n';
                        cout << "Penerbit       : " << daftarBuku[indx].penerbitBuku << '\n';
                        cout << "Tahun Terbit   : " << daftarBuku[indx].tahunTerbit << '\n';
                        cout << "Harga          : " << daftarBuku[indx].harga << '\n';
                        cout << "Stok           : " << daftarBuku[indx].stok << '\n';
                        cout << "=================================================\n";
                        cout << "-\n";
                        cout << "Input Stok Baru: ";
                        cin >> daftarBuku[indx].stok;

                        for(int i = 0; i < jumlahBuku; i++){
                            fileTemp << daftarBuku[i].idBuku << ' ' << spaceToUnderscore(daftarBuku[i].judulBuku) << ' ' << spaceToUnderscore(daftarBuku[i].genre) << ' ' << spaceToUnderscore(daftarBuku[i].authorBuku) << ' ' << spaceToUnderscore(daftarBuku[i].penerbitBuku) << ' ' << daftarBuku[i].tahunTerbit << ' ' <<daftarBuku[i].harga << ' ' << daftarBuku[i].stok << '\n';
                        }
                        fileTemp.close();
                        done = true;
                }else{
                    cout << idTemp << " Tidak Ada Bukunya!\n";
                    system("pause");
                    for(int i = 0; i < jumlahBuku; i++){
                            fileTemp << daftarBuku[i].idBuku << ' ' << spaceToUnderscore(daftarBuku[i].judulBuku) << ' ' << spaceToUnderscore(daftarBuku[i].genre) << ' ' << spaceToUnderscore(daftarBuku[i].authorBuku) << ' ' << spaceToUnderscore(daftarBuku[i].penerbitBuku) << ' ' << daftarBuku[i].tahunTerbit << ' ' <<daftarBuku[i].harga << ' ' << daftarBuku[i].stok << '\n';
                        }
                        fileTemp.close();
                }

            break;
            case 3:
                for(int i = 0; i < jumlahBuku; i++){
                    fileTemp << daftarBuku[i].idBuku << ' ' << spaceToUnderscore(daftarBuku[i].judulBuku) << ' ' << spaceToUnderscore(daftarBuku[i].genre) << ' ' << spaceToUnderscore(daftarBuku[i].authorBuku) << ' ' << spaceToUnderscore(daftarBuku[i].penerbitBuku) << ' ' << daftarBuku[i].tahunTerbit << ' ' << daftarBuku[i].harga << ' ' << daftarBuku[i].stok << '\n';
                }
                fileTemp.close();
                return;
            break;
            default:
                cout << "Input Salah!\n";
                system("pause");
            break;
        }


        if(done){
            ifstream fileCheck(fileListBuku);
            string genreTemp, authorTemp, penerbitTemp, tahunTemp, hargaTemp, stokTemp;
            
            system("cls");
            cout << "Buku Berhasil Di Update!\n";
            cout << "-\n";
            fileTemp.close();
            while(fileCheck >> idTemp >> judulTemp >> genreTemp >> authorTemp >> penerbitTemp >> tahunTemp >> hargaTemp >> stokTemp){
                if(updated == idTemp){
                    cout << "=================================================\n";
                    cout << "ID Buku        : " << UnderscoreToSpace(idTemp) << '\n';
                    cout << "Judul Buku     : " << UnderscoreToSpace(judulTemp) << '\n';
                    cout << "Genre          : " << UnderscoreToSpace(genreTemp) << '\n';
                    cout << "Author         : " << UnderscoreToSpace(authorTemp) << '\n';
                    cout << "Penerbit       : " << UnderscoreToSpace(penerbitTemp) << '\n';
                    cout << "Tahun Terbit   : " << tahunTemp << '\n';
                    cout << "Harga          : " << hargaTemp << '\n';
                    cout << "Stok           : " << stokTemp << '\n';
                    cout << "=================================================\n";
                    cout << "-\n";
                    system("pause");
                    break;
                }
            }
            fileCheck.close();
        }
    }
}

void listBook(int jumlahBuku){
    system("cls");
    cout << string(65, '=') << '\n';
    cout << left << setw(15) << "ID" << setw(25) << "Judul" << setw(15) << "Stok" << setw(15) << "Harga" << '\n';
    cout << string(65, '=') << '\n';
    for(int f = 0; f < jumlahBuku; f++){
        cout << left << setw(15) << daftarBuku[f].idBuku << setw(25) << daftarBuku[f].judulBuku << setw(15) << daftarBuku[f].stok << setw(15) << daftarBuku[f].harga << '\n';
    }
    cout << string(65, '=') << '\n';
    system("pause");
}

void searchBook(int jumlahBuku){

    int pil = 0;
    while(pil != 3){
        system("cls");
        cout << "Cari Buku di Gudang\n";
        cout << "--------------------------------\n";
        cout << "[1]. Cari Berdasarkan Judul\n";
        cout << "[2]. Cari Berdasarkan Genre\n";
        cout << "[3]. BACK\n";
        cout << "Input: ";
        cin >> pil;
        string stringCari;
        bool found;
        int i, j;
        int hitung = 0;
        
        switch(pil){
            case 1:
                cout << "-\n";
                cout << "Masukkan Judul: ";
                cin.ignore();
                getline(cin, stringCari);
                stringCari = EditUpLowCase(stringCari);

                found = false;
                i = 0;

                while(i <= jumlahBuku){
                    if(daftarBuku[i].judulBuku == stringCari){
                        found = true;
                        break;
                    }else{
                        i++;
                    }
                }

                if(found){
                    system("cls");
                    cout << "Buku Ditemukan!\n";
                    cout << "-\n";
                    cout << "=================================================\n";
                    cout << "Judul Buku     : " << daftarBuku[i].judulBuku << '\n';
                    cout << "Genre          : " << daftarBuku[i].genre << '\n';
                    cout << "Author         : " << daftarBuku[i].authorBuku << '\n';
                    cout << "Penerbit       : " << daftarBuku[i].penerbitBuku<< '\n';
                    cout << "Tahun Terbit   : " << daftarBuku[i].tahunTerbit << '\n';
                    cout << "Harga          : " << daftarBuku[i].harga << '\n';
                    cout << "Stok           : " << daftarBuku[i].stok << '\n';
                    cout << "=================================================\n";
                                    
                    system("pause");
                }else{
                    cout << "-\n";
                    cout << "Kita Belum Memiliki Buku Dengan Judul " << stringCari << '\n';
                    cout << "-\n";
                    system("pause");
                }
                
            break;

            case 2: 
                cout << "-\n";
                cout << "Masukkan Genre: ";
                cin.ignore();
                getline(cin, stringCari);
                stringCari = EditUpLowCase(stringCari);
        
                j = 1;
                system("cls");
                cout << "Buku Dengan Genre " << stringCari << '\n';
                cout << "-\n";

                for(i = 0; i < jumlahBuku; i++){
                    if(daftarBuku[i].genre == stringCari){
                        found = true;
                        cout << j << ". " << daftarBuku[i].judulBuku << '\n';
                        j++;
                    }
                }

                cout << "-\n";

                if(!found){
                    system("cls");
                    cout << "Kita Belum Memiliki Buku Dengan Genre " << stringCari << '\n';
                    cout << "-\n";
                }

                system("pause");
               
            break;

            case 3:
                return;
            break;
            
            default:
            cout << "Input salah !!! \n ";
            system("pause");
            break;
        }
    }
}

void addBook(int tambahBuku, int jumlahBuku){
    ofstream fileInput(fileListBuku, ios::app);
    string judulTemp, penerbitTemp, authorTemp, genreTemp, lineCheck, idTemp;
    int stokTemp;

    // Cek Apakah file ada atau tidak / terbuka atau tidak
    if(!fileInput.is_open()){
        cout << "File Error!\n";
        system("pause");
        return;
    }

    // karna rekursi, tambahBuku akan terus berkurang sampai 0
    if(tambahBuku == 0){
        fileInput.close();
        int count = 1;
        ifstream fileCount(fileListBuku);
        while(getline(fileCount, lineCheck)){ // cara kerjanya, getline akan baca kata dari fileCount sampai ke baris akhir, kalau ketemu newline di linecheck=0 maka linecheck +1, baca baris selanjutnya di linecheck = 1 dan seterusnya
            count++;
        }
        fileCount.close();

        system("cls");
        cout << "Selesai! Anda Baru Saja Menambahkan Buku Kedalam Gudang!\n";
        cout << "Di Gudang Sekarang Berisi " << count << " Judul Buku!\n"; // + 1 karena count masih menghitung file yang sblm masuk ke rekursi, setelah masuk karna blm return atau masuk rekursi lagi, datanya blm ke update 
        system("pause");
        return;
    }

    bool sudahAda = false;

    while(!sudahAda){
        system("cls");
        cout << "Masukkan ID Buku: ";
        cin >> idTemp;
    
        for(int i = 0; i < jumlahBuku; i++){
            if(daftarBuku[i].idBuku == idTemp){
                sudahAda = true;
            }
        }
        if(sudahAda){
            cout << "ID Buku Sudah Ada!\n";
            cout << "Gunakan Setelah " << idTemp << "!\n";
            system("pause");
            sudahAda = false;
        }else{
            break;
        }
    }

    cout << "Masukkan Judul Buku: ";
    cin.ignore();

    //anjay bisa, kalo judul ada, tinggal nambah stok
    getline(cin, judulTemp);
    judulTemp = EditUpLowCase(judulTemp);

    for(int i = 0; i < jumlahBuku; i++){
        if(judulTemp == daftarBuku[i].judulBuku){
            ofstream fileTrunc(fileListBuku, ios::trunc);
            cout << "Tambah Stok Buku: ";
            cin >> stokTemp;
            daftarBuku[i].stok += stokTemp;
                for(int j = 0; j < jumlahBuku; j++){
                    fileTrunc << daftarBuku[j].idBuku << ' ' << spaceToUnderscore(daftarBuku[j].judulBuku) << ' ' << spaceToUnderscore(daftarBuku[j].genre) << ' ' << spaceToUnderscore(daftarBuku[j].authorBuku) << ' ' << spaceToUnderscore(daftarBuku[j].penerbitBuku) << ' ' << daftarBuku[j].tahunTerbit << ' ' << daftarBuku[j].harga << ' ' << daftarBuku[j].stok << '\n';
                }
                cout << "Anda Berhasil Menambahkan Stok ke Buku " << daftarBuku[i].judulBuku << " Menjadi " << daftarBuku[i].stok << "!\n";
                system("pause");
                fileTrunc.close();
                fileInput.close();
                return;
        }
    }

    cout << "Masukkan Genre Buku: ";
    getline(cin, daftarBuku[tambahBuku].genre);
    genreTemp = EditUpLowCase(daftarBuku[tambahBuku].genre);
    genreTemp = spaceToUnderscore(genreTemp);
    
    cout << "Masukkan Author Buku: ";
    getline(cin, daftarBuku[tambahBuku].authorBuku);
    authorTemp = EditUpLowCase(daftarBuku[tambahBuku].authorBuku);
    authorTemp = spaceToUnderscore(authorTemp);

    cout << "Masukkan Penerbit Buku: ";
    getline(cin, daftarBuku[tambahBuku].penerbitBuku);
    penerbitTemp = EditUpLowCase(daftarBuku[tambahBuku].penerbitBuku);
    penerbitTemp = spaceToUnderscore(penerbitTemp);

    cout << "Masukkan Tahun Terbit: ";
    cin >> daftarBuku[tambahBuku].tahunTerbit;
    cout << "Masukkan Harga Buku: ";
    cin >> daftarBuku[tambahBuku].harga;

    cout << "Masukkan Jumlah Stok: ";
    cin >> daftarBuku[tambahBuku].stok;

    fileInput << idTemp << ' ' << spaceToUnderscore(judulTemp) << ' ' << genreTemp << ' ' << authorTemp << ' ' << penerbitTemp << ' ' << daftarBuku[tambahBuku].tahunTerbit << ' ' << daftarBuku[tambahBuku].harga << ' ' << daftarBuku[tambahBuku].stok << '\n';
    system("cls");

    // masukkin ke struct array, biar kebaca data barunya. karna ini rekursi dan fileLoader ada di Menu, jadi tidak terbaca kalau tidak ditambahkan ke struct array dulu
    daftarBuku[jumlahBuku].idBuku = idTemp;
    daftarBuku[jumlahBuku].judulBuku = judulTemp;
    daftarBuku[jumlahBuku].genre = genreTemp;
    daftarBuku[jumlahBuku].authorBuku = authorTemp;
    daftarBuku[jumlahBuku].penerbitBuku = penerbitTemp;
    daftarBuku[jumlahBuku].tahunTerbit = daftarBuku[tambahBuku].tahunTerbit;
    daftarBuku[jumlahBuku].harga = daftarBuku[tambahBuku].harga;
    daftarBuku[jumlahBuku].stok = daftarBuku[tambahBuku].stok;

    return addBook(tambahBuku - 1, jumlahBuku + 1);
}

void sortingBuku(int jumlahBuku){

    int pil = 0;
    while(pil != 3){
        bool swap = false;
        system("cls"); 
        cout << "Urutkan Berdasarkan:\n";
        cout << "[1]. Judul Buku \n";
        cout << "[2]. Harga Buku \n";
        cout << "[3]. BACK\n";
        cout << "Input: ";
        cin >> pil;
    
        switch(pil){
            case 1:
                for(int i = 0; i < jumlahBuku - 1;i++){
                    for(int j = 0 ; j < jumlahBuku - i - 1; j++){
                        bool tukar = false;
                        if(daftarBuku[j].judulBuku > daftarBuku[j+1].judulBuku){
                            tukar = true;
                        }
                        if(tukar){
                            buku temp = daftarBuku[j];
                            daftarBuku[j] = daftarBuku[j+1];
                            daftarBuku[j+1] = temp;
                        }
                    }
                }
                swap = true;
            break;
            case 2:
                for(int i = 0; i < jumlahBuku - 1;i++){
                    for(int j = 0 ; j < jumlahBuku - i - 1; j++){
                        bool tukar = false;
                        if(daftarBuku[j].harga > daftarBuku[j+1].harga){
                            tukar = true;
                        }
                        if(tukar){
                            buku temp = daftarBuku[j];
                            daftarBuku[j] = daftarBuku[j+1];
                            daftarBuku[j+1] = temp;
                        }
                    }
                }
                swap = true;
            break;
            case 3:
                return;
            break;
            default:
                cout << "Input Salah!\n";
                system("pause");
            break;
        }
        if(swap){
            ofstream SaveFile(fileListBuku, ios::trunc);
            for(int i = 0; i < jumlahBuku; i++){
                SaveFile << daftarBuku[i].idBuku << " " << spaceToUnderscore(daftarBuku[i].judulBuku) << " " << spaceToUnderscore(daftarBuku[i].genre) << " " 
                << spaceToUnderscore(daftarBuku[i].authorBuku) << " " << spaceToUnderscore(daftarBuku[i].penerbitBuku)<< " " <<
                daftarBuku[i].tahunTerbit << " " << daftarBuku[i].harga << " " << daftarBuku[i].stok << '\n';
            }
            SaveFile.close();
            OutputForSort();
            cout << "Data Telah Berhasil Diurutkan dan Disimpan Kedalam File\n";
            system("pause");
        }else{
            cout << "Gagal Mensort Data!\n";
            system("pause");
            return;
        }
    }
}

void OutputForSort(){
    ifstream Database(fileListBuku);
    if(!Database.is_open()){
        cout << "File Error!\n";
        return;
    }
    int i = 1;
    string id, judul, genre1, penulis, penerbit1, tahun;
    int harga1, stok;
    
    while(Database >> id >> judul >> genre1 >> penulis >> penerbit1 >> tahun >> harga1 >> stok){
        judul = UnderscoreToSpace(judul);
        penulis = UnderscoreToSpace(penulis);
        penerbit1 = UnderscoreToSpace(penerbit1);
        cout << "Buku ke-" << i << endl;
        cout << "ID         : " << id << endl;
        cout << "Judul      : " << judul << endl;
        cout << "Penulis    : " << penulis << endl;
        cout << "Harga      : " << harga1 << endl;
        cout << "Stok       : " << stok << '\n';
        cout << '\n';
        i++;
    }

    Database.close();
}

bool loginUsers(string &user, string pasw){
    ifstream fileCheckUsers(fileLoginInfo);
    string tempUsn, tempPasw;
    bool userCoy = false;

    if(!fileCheckUsers.is_open()){
        cout << "File Error!\n";
        system("pause");
        return false;
    }

    while(fileCheckUsers >> tempUsn >> tempPasw){
        if(tempUsn == user){
            userCoy = true;
            break;
        }
    }

    if(userCoy){
        if(tempPasw != pasw){
            cout << "Username atau Password Salah!\n";
            system("pause");
            fileCheckUsers.close();
            return false;
        }else{
            fileCheckUsers.close();
            return true;
        }
    }else{
        cout << "Username Tidak Ada! Silakan Register Terlebih Dahulu!\n";
        fileCheckUsers.close();
        system("pause");
        return false;
    }

}

bool registerUsers(string &user, string pasw){
    ifstream fileCheck(fileLoginInfo);
    string tempUsn;
    bool sudahAda = false;

    if(!fileCheck.is_open()){
        cout << "File Error!\n";
        system("pause");
        return false;
    }

    while(fileCheck >> tempUsn){
        if(tempUsn == user){
            sudahAda = true;
        }
    }

    if(sudahAda){
        cout << "-\n";
        cout << "Username Telah Digunakan!\n";
        system("pause");
        return false;
    }

    fileCheck.close();

    ofstream fileInput(fileLoginInfo, ios::app);
    fileInput << user << ' ' << pasw << '\n';
    fileInput.close();

    return true;
}

string spaceToUnderscore(string str){
    string temp = str;

    for(int i = 0; i < str.length(); i++){
        if(temp[i] == ' '){
            temp.replace(i,1,1,'_');
        }
    }

    return temp;
}

string UnderscoreToSpace(string str){
    string temp = str;

    for(int i = 0; i < str.length(); i++){
        if(temp[i] == '_'){
            temp.replace(i,1,1,' ');
        }
    }
 
    return temp;
}

string EditUpLowCase(string str){
    bool newWord = true; // apakah awal kata baru

    for(char &lw : str){ // loop mengubah semua char di str menjadi kecil , // : adalah range-based loop, melakukan penguilangan untuk setiap elemen str
        lw = tolower(lw); // mengubah char yang ada di variabel lw menjadi kecil
    }

    for(char &up : str){
        if(isspace(up)){ // cek apakah char tersebut merupakan spasi, jika iya, next char bakal kapital
            newWord = true; // setelah spasi adalah awal kata baru
        }else if(newWord){ // dan jika new word, char selanjutnya setelah spasi
            up = toupper(up); // mengubah char yang ada di variabel up menjadi kapital
            newWord = false; // setelah diubah artinya, next char bukan kapital
        }
    }
    return str;
}