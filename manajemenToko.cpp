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

void updateBook();
void listBook();
void searchBook();
void addBook(int tambahBuku);
void sortingBuku();
void OutputForSort();
void updateStock(int *a, int *b);

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

void mainMenu(){

    string user;
    int mode = 0;
    firstMenu(user);
    
    int pil, newBook, tambahBuku;
    pil = 0;
    while(pil != 6){
        system("cls");
        cout << "Hai Admin "<< user << "! \n";
        cout << "Selamat Datang di Dashboard Toko Buku Online\n";
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
                updateBook();
            break;
            case 2:
                listBook();
            break;
            case 3:
                searchBook();
            break;
            case 4:
            system("cls");
                cout << "Jumlah Buku Yang Ingin Ditambahkan: ";
                cin >> tambahBuku;
                addBook(tambahBuku);
            break;

            case 5:
                sortingBuku();
            break;

            case 6:
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

void updateBook(){
    ifstream fileCheck(fileListBuku);

    if(!fileCheck.is_open()){
        cout << "File Error!\n";
        system("pause");
        return;
    }

    string idTemp, judulTemp, authorTemp, penerbitTemp, genreTemp, tahunTemp, updated;
    int hargaTemp, stokTemp, stokTambah, pil, count;
    bool done = false;
    count = 0;

    while(fileCheck >> idTemp >> judulTemp >> genreTemp >> authorTemp >> penerbitTemp >> tahunTemp >> hargaTemp >> stokTemp){
        judulTemp = UnderscoreToSpace(judulTemp);
        genreTemp = UnderscoreToSpace(genreTemp);
        authorTemp = UnderscoreToSpace(authorTemp);
        penerbitTemp = UnderscoreToSpace(penerbitTemp);
        daftarBuku[count].idBuku = idTemp;
        daftarBuku[count].judulBuku = judulTemp;
        daftarBuku[count].genre = genreTemp;
        daftarBuku[count].authorBuku = authorTemp;
        daftarBuku[count].penerbitBuku = penerbitTemp;
        daftarBuku[count].tahunTerbit = tahunTemp;
        daftarBuku[count].harga = hargaTemp;
        daftarBuku[count].stok = stokTemp;
        count++;
    }
    fileCheck.close();
    pil = 0;
    while(pil != 3){
        ofstream fileTemp("tempList.txt");
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
                for(int i = 0; i < count; i++){
                    if(idTemp == daftarBuku[i].idBuku){
                        cin.ignore();
                        cout << "--------------------------------\n";
                        cout << "Masukkan Judul Baru        : ";
                        getline(cin, judulTemp);
                        judulTemp = EditUpLowCase(judulTemp);
                        judulTemp = spaceToUnderscore(judulTemp);

                        cout << "Masukkan Genre Baru        : ";
                        getline(cin, genreTemp);
                        genreTemp = EditUpLowCase(genreTemp);
                        genreTemp = spaceToUnderscore(genreTemp);

                        cout << "Masukkan Author Baru       : ";
                        getline(cin, authorTemp);
                        authorTemp = EditUpLowCase(authorTemp);
                        authorTemp = spaceToUnderscore(authorTemp);

                        cout << "Masukkan Penerbit Baru     : ";
                        getline(cin, penerbitTemp);
                        penerbitTemp = EditUpLowCase(penerbitTemp);
                        penerbitTemp = spaceToUnderscore(penerbitTemp);

                        cout << "Masukkan Tahun Terbit Baru : ";
                        cin >> tahunTemp;

                        cout << "Masukkan Harga Baru        : ";
                        cin >> hargaTemp;

                        cout << "Masukkan Stok Baru         : ";
                        cin >> stokTemp;

                        fileTemp << idTemp << ' ' << judulTemp << ' ' << genreTemp << ' ' << authorTemp << ' ' << penerbitTemp << ' ' << tahunTemp << ' ' << hargaTemp << ' ' << stokTemp << '\n';
                    }else{
                        fileTemp << daftarBuku[i].idBuku << ' ' << spaceToUnderscore(daftarBuku[i].judulBuku) << ' ' << spaceToUnderscore(daftarBuku[i].genre) << ' ' << spaceToUnderscore(daftarBuku[i].authorBuku) << ' ' << spaceToUnderscore(daftarBuku[i].penerbitBuku) << ' ' << daftarBuku[i].tahunTerbit << ' ' <<daftarBuku[i].harga << ' ' << daftarBuku[i].stok << '\n';
                    }
                }
                done = true;
            break;
            case 2:
                system("cls");
                cout << "Masukkan ID Buku: ";
                cin >> idTemp;
                updated = idTemp;
                for(int i = 0; i < count; i++){
                    if(idTemp == daftarBuku[i].idBuku){
                        system("cls");
                        cout << "=================================================\n";
                        cout << "ID Buku        : " << daftarBuku[i].idBuku << '\n';
                        cout << "Judul Buku     : " << daftarBuku[i].judulBuku << '\n';
                        cout << "Genre          : " << daftarBuku[i].genre << '\n';
                        cout << "Author         : " << daftarBuku[i].authorBuku << '\n';
                        cout << "Penerbit       : " << daftarBuku[i].penerbitBuku << '\n';
                        cout << "Tahun Terbit   : " << daftarBuku[i].tahunTerbit << '\n';
                        cout << "Harga          : " << daftarBuku[i].harga << '\n';
                        cout << "Stok           : " << daftarBuku[i].stok << '\n';
                        cout << "=================================================\n";
                        cout << "-\n";
                        cout << "Input Stok Baru: ";
                        cin >> stokTambah;

                        updateStock(&stokTambah, &daftarBuku[i].stok);

                        fileTemp << daftarBuku[i].idBuku << ' ' << spaceToUnderscore(daftarBuku[i].judulBuku) << ' ' << spaceToUnderscore(daftarBuku[i].genre) << ' ' << spaceToUnderscore(daftarBuku[i].authorBuku) << ' ' << spaceToUnderscore(daftarBuku[i].penerbitBuku) << ' ' << daftarBuku[i].tahunTerbit << ' ' <<daftarBuku[i].harga << ' ' << daftarBuku[i].stok << '\n';
                    }else{
                        fileTemp << daftarBuku[i].idBuku << ' ' << spaceToUnderscore(daftarBuku[i].judulBuku) << ' ' << spaceToUnderscore(daftarBuku[i].genre) << ' ' << spaceToUnderscore(daftarBuku[i].authorBuku) << ' ' << spaceToUnderscore(daftarBuku[i].penerbitBuku) << ' ' << daftarBuku[i].tahunTerbit << ' ' <<daftarBuku[i].harga << ' ' << daftarBuku[i].stok << '\n';
                    }
                }
                done = true;
            break;
            case 3:
                fileTemp.close();
                remove("tempList.txt");
                return;
            break;
            default:
                cout << "Input Salah!\n";
                system("pause");
            break;
        }


        if(done){
            fileTemp.close();
            remove(fileListBuku.c_str());
            rename("tempList.txt", fileListBuku.c_str());

            ifstream fileCheck(fileListBuku);
            system("cls");
            cout << "Buku Berhasil Di Update!\n";
            cout << "-\n";
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

void updateStock(int *a, int *b){
    *b = *a;
}

void listBook(){
    ifstream fileCheck(fileListBuku);
    string judulTemp, idTemp, authorTemp, penerbitTemp, tahunTemp, hargaTemp, genreTemp, stokTemp;
    if(!fileCheck.is_open()){
        cout << "-\n";
        cout << "File Error!\n";
        system("pause");
        return;
    }
    int i = 1;
    system("cls");
    cout << "List Judul Buku Di Gudang\n";
    cout << "--------------------------------\n";
    while(fileCheck >> idTemp >> judulTemp >> genreTemp >> authorTemp >> penerbitTemp >> tahunTemp >> hargaTemp >> stokTemp){
        judulTemp = UnderscoreToSpace(judulTemp);
        cout << i << ". "<< judulTemp << '\n';
        i++;
    }
    cout << "--------------------------------\n";
    fileCheck.close();
    system("pause");
}

void searchBook(){
    ifstream fileCheck(fileListBuku);
    string lineCheck;
    int count = 0;
    if(!fileCheck.is_open()){
        cout << "File Error!\n";
        system("pause");
        return;
    }

    while(getline(fileCheck, lineCheck)){
            count += 1;
    }
    fileCheck.close();

    fileCheck.open(fileListBuku);
    string judulTemp, idTemp, authorTemp, penerbitTemp, tahunTemp, hargaTemp, genreTemp, stokTemp;
    int i = 0;
    int hargaInt = 0;
    int stokInt = 0;
    while(fileCheck >> idTemp >> judulTemp >> genreTemp >> authorTemp >> penerbitTemp >> tahunTemp >> hargaTemp >> stokTemp){
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
    fileCheck.close();
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
        int i, x, j;
        x = count + 1;
        int hitung = 0;
        
        switch(pil){
            case 1:
                daftarBuku[count].judulBuku;
                cout << "-\n";
                cout << "Masukkan Judul: ";
                cin.ignore();
                getline(cin, stringCari);
                stringCari = EditUpLowCase(stringCari);
                daftarBuku[x];
                found = false;
                i = 0;

                while(!found && i <= count){
                    if(daftarBuku[i].judulBuku == stringCari){
                        found = true;
                    }else{
                        i++;
                    }
                }

                if(i < x){
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
                daftarBuku[count].genre;
                cout << "-\n";
                cout << "Masukkan Genre: ";
                cin.ignore();
                getline(cin, stringCari);
                stringCari = EditUpLowCase(stringCari);
        
                j = 1;
                system("cls");
                cout << "Buku Dengan Genre " << stringCari << '\n';
                cout << "-\n";

                for(i = 0; i < count; i++){
                    if(daftarBuku[i].genre == stringCari){
                        found = true;
                        cout << j << ". " << daftarBuku[i].judulBuku << '\n';
                        j++;
                    }
                }

                cout << "-\n";

                if(found == false){
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

void addBook(int tambahBuku){
    ofstream fileInput(fileListBuku, ios::app);
    string judulTemp, penerbitTemp, authorTemp, genreTemp, lineCheck;
    
    int num = 1;
    int count = 1;

    if(!fileInput.is_open()){
        cout << "File Error!\n";
        system("pause");
        return;
    }
    
    if(tambahBuku == 0){
        ifstream fileCheck(fileListBuku);
        while(getline(fileCheck, lineCheck)){
            count += 1;
        }
        system("cls");
        cout << "Selesai! Anda Baru Saja Menambahkan Buku Kedalam Gudang!\n";
        cout << "Di Gudang Sekarang Berisi " << count << " Judul Buku!\n";
        cout << "-\n";
        system("pause");
        fileInput.close();
        fileCheck.close();
        return;
    }

    system("cls");
    cout << "Masukkan ID Buku: ";
    cin >> daftarBuku[tambahBuku].idBuku;

    cout << "Masukkan Judul Buku: ";
    cin.ignore();
    getline(cin, daftarBuku[tambahBuku].judulBuku);
    judulTemp = (daftarBuku[tambahBuku].judulBuku); 
    judulTemp = spaceToUnderscore(judulTemp);

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
    cout << "Masukkan Stok Buku: ";
    cin >> daftarBuku[tambahBuku].stok;
    fileInput << daftarBuku[tambahBuku].idBuku << ' ' << judulTemp << ' ' << genreTemp << ' ' << authorTemp << ' ' << penerbitTemp << ' ' << daftarBuku[tambahBuku].tahunTerbit << ' ' << daftarBuku[tambahBuku].harga << ' ' << daftarBuku[tambahBuku].stok << '\n';
    system("cls");
    return addBook(tambahBuku - 1);
}

void sortingBuku() {
    buku daftarBuku[kapasitasBuku];
    int x = 0;
    
    ifstream Database(fileListBuku);
    if (!Database.is_open()) {
        cout << "File Error!\n";
        system("pause");
        return;
    }
    
    string idTemp, judulTemp, genreTemp, authorTemp, penerbitTemp, tahunTemp, hargaTemp, stokTemp;
    int hargaInt, stokInt;
    
    while(Database >> idTemp >> judulTemp >> genreTemp >> authorTemp >> penerbitTemp >> tahunTemp >> hargaTemp >> stokTemp){
        judulTemp = UnderscoreToSpace(judulTemp);
        genreTemp = UnderscoreToSpace(genreTemp);
        authorTemp = UnderscoreToSpace(authorTemp);
        penerbitTemp = UnderscoreToSpace(penerbitTemp);
        daftarBuku[x].idBuku = idTemp;
        daftarBuku[x].judulBuku = judulTemp;
        daftarBuku[x].genre = genreTemp;
        daftarBuku[x].authorBuku = authorTemp;
        daftarBuku[x].penerbitBuku = penerbitTemp;
        daftarBuku[x].tahunTerbit = tahunTemp;
        hargaInt = stoi(hargaTemp);
        daftarBuku[x].harga = hargaInt;
        stokInt = stoi(stokTemp);
        daftarBuku[x].stok = stokInt;
        x++;
    }
    Database.close();

    if(x == 0){
        cout << "Tidak Ada Data Untuk Diurutkan!\n";
        system("pause");
        return;
    }
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
                for(int i = 0; i < x - 1;i++){
                    for(int j = 0 ; j < x - i - 1; j++){
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
                for(int i = 0; i < x - 1;i++){
                    for(int j = 0 ; j < x - i - 1; j++){
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
            for(int i = 0; i < x; i++){
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
    bool adminCoy = false;
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
    bool newWord = true;
    for(char &lw : str){
        lw = tolower(lw);
    }

    for (char &up : str){
        if(isspace(up)){
            newWord = true;
        }else if (newWord) {
            up = toupper(up);
            newWord = false;
        }
    }
    return str;
}