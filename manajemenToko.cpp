#include <iostream>
#include <cctype>
#include <fstream>
#include <iomanip>

using namespace std;

const string fileLoginInfo = "loginInfo.csv";
const string fileAdmin = "adminInfo.csv";
const string fileListBuku = "ListBuku.csv";
const int kapasitasBuku = 100;

string spaceToUnderscore(string str);
string UnderscoreToSpace(string str);

void mainMenu();
void firstMenu(string &user, int &mode);
void adminMenu(string user);
void buyerMenu(string user);

bool registerUsers(string &user, string pasw);
bool loginUsers(string &user, string pasw, int &mode);

void addBook(int newBook, int tambahBuku);
void listBook();

struct buku{
    string idBuku;
    string namaBuku;
    string penerbitBuku;
    string authorBuku;
    string genre;
    int tahunTerbit;
    int harga;
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
    firstMenu(user, mode);

    switch(mode){
        case 1:
            system("cls");
            adminMenu(user);
        break;
        case 2:
            system("cls");
            buyerMenu(user);
        break;
    }
}

void firstMenu(string &user, int &mode){
    int pil;
    string pasw;

    while(true){
        system("cls");
        cout << "|| Selamat Datang di GaraMedia ||\n";
        cout << "[1]. Register\n";
        cout << "[2]. Login\n";
        cout << "[3]. EXIT\n";
        cout << "Input: ";
        cin >> pil;

        switch(pil){
            case 1:
                cout << "Username \t: ";
                cin >> user;
                cout << "Password \t: ";
                cin >> pasw;
                if(registerUsers(user, pasw)){
                    cout << "Registrasi Berhasil! Silakan Login!\n";
                    system("pause");
                }
                break;
                
            case 2:
                cout << "Username: ";
                cin >> user;
                cout << "Password: ";
                cin >> pasw;
                if(loginUsers(user, pasw, mode)){
                    cout << "Login Berhasil!\n";
                    system("pause");
                    return;
                }
            break;
            case 3:
                cout << "Terimakasih Telah Berkunjung!\n";
                system("pause");
                exit(0);
            break;
            default:
                cout << "Input Salah!\n";
                system("pause");
        }
    }
}

bool registerUsers(string &user, string pasw){

    // Check apakah username available or tidak

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
        cout << "Username Telah Digunakan!\n";
        system("pause");
        return false;
    }

    fileCheck.close();

    // Jika, available lanjut 

    ofstream fileInput(fileLoginInfo, ios::app);
    fileInput << user << ' ' << pasw << '\n';
    fileInput.close();

    return true;
}


void adminMenu(string user){
    int pil, newBook, tambahBuku;
    while(pil !=4){
        system("cls");
        cout << "Hai Admin "<< user << "! \n";
        cout << "Selamat Datang di Dashboard GaraMedia Online\n";
        cout << "[1]. Tambah Buku\n";
        cout << "[2]. List Buku\n"; // showing judul dari buku aja, nanti contohnya misal 
                                    //1. Buku A
                                    //2. Buku B
                                    //3. dst
                                    // 4. back
        cout << "[3]. Cari Buku\n"; // fungsi cari yg di file gw blm tau kek apa si, buat apa aja yang penting bisa dicari, nanti pas dah ketemu dibuat list kek gini aja atau buat sendiri lah bebas
                                    // =================================================
                                    // Judul Buku   : Buku A
                                    // Genre        : Seegs
                                    // Penulis      : Wahyu
                                    // Penerbit     : blabal
                                    // Tahun Terbit : 2424
                                    // =================================================
                                    // menu back
        cout << "[4]. EXIT\n";
        cout << "Input: ";
        cin >> pil;
        switch(pil){
            case 1:
                cout << "Jumlah Buku Yang Ingin Ditambahkan: ";
                cin >> tambahBuku;
                addBook(newBook, tambahBuku);
            break;
            case 2:
                listBook();
            break;
        }
    }
}

void listBook(){
    ifstream fileCheck(fileListBuku);
    string lineCheck, judulTemp, idTemp, authorTemp, penerbitTemp, tahunTemp, hargaTemp;
    if(!fileCheck.is_open()){
        cout << "File Error!\n";
        system("pause");
        return;
    }
    while(fileCheck >> idTemp >> judulTemp >> authorTemp >> penerbitTemp >> tahunTemp >> hargaTemp){
        judulTemp = UnderscoreToSpace(judulTemp);
        cout << judulTemp << ' ' << idTemp << '\n';
    }
    system("pause");

}

void addBook(int newBook, int tambahBuku){
    ofstream fileInput(fileListBuku, ios::app);
    string judulTemp, penerbitTemp, authorTemp, genreTemp, lineCheck;

    int count = 0;

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
        cout << "Di Gudang Sekarang Berisi " << count + 1 << " Judul Buku!\n";
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
    getline(cin, daftarBuku[tambahBuku].namaBuku);
    judulTemp = spaceToUnderscore(daftarBuku[tambahBuku].namaBuku);

    cout << "Masukkan Genre Buku: ";
    getline(cin, daftarBuku[tambahBuku].genre);
    
    cout << "Masukkan Author Buku: ";
    getline(cin, daftarBuku[tambahBuku].authorBuku);
    authorTemp = spaceToUnderscore(daftarBuku[tambahBuku].authorBuku);

    cout << "Masukkan Penerbit Buku: ";
    getline(cin, daftarBuku[tambahBuku].penerbitBuku);
    penerbitTemp = spaceToUnderscore(daftarBuku[tambahBuku].penerbitBuku);

    cout << "Masukkan Tahun Terbit: ";
    cin >> daftarBuku[tambahBuku].tahunTerbit;
    cout << "Masukkan Harga Buku: ";
    cin >> daftarBuku[tambahBuku].harga;
    fileInput << daftarBuku[tambahBuku].idBuku << ' ' << judulTemp << ' ' << authorTemp << ' ' << penerbitTemp << ' ' << daftarBuku[tambahBuku].tahunTerbit << ' ' << daftarBuku[tambahBuku].harga << '\n';
    system("cls");

    return addBook(newBook + 1, tambahBuku - 1);
}

void buyerMenu(string user){
    cout << "Hai "<< user << "! \n";
    cout << "Selamat Datang di GaraMedia Online\n";
    cout << "[1]. Beli Buku\n"; // beli buku dibuat ada struknya si yak, jadi pas user udh cekout brp buku, insert duitnya, nanti muncul struknya
    cout << "[2]. List Buku\n"; // jadiin 1 fungsi aja ama yang versi adminnya, sama soalnya tinggal panggil doang
    cout << "[3]. Cari Buku\n"; // jadiin 1 fungsi aja ama yang versi adminnya, sama soalnya tinggal panggil doang, kasih kondisi tambahan deh, abis dicari, ada menu beli, kek gini
                                // =================================================
                                // Judul Buku   : Buku A
                                // Genre        : Seegs
                                // Penulis      : Wahyu
                                // Penerbit     : blabal
                                // Tahun Terbit : 2424
                                // =================================================
                                // menu beli // ini ngarah ke fungsi menu Beli Buku
                                // menu back
    cout << "[4]. EXIT\n";
    cout << "Input: ";
}

bool loginUsers(string &user, string pasw, int &mode){
    ifstream fileCheckAdmin(fileAdmin);
    ifstream fileCheckUsers(fileLoginInfo);
    string tempUsn, tempPasw;
    bool adminCoy = false;
    bool userCoy = false;

    if(!fileCheckAdmin.is_open()){
        cout << "File Error!\n";
        system("pause");
        return false;
    }

    if(!fileCheckUsers.is_open()){
        cout << "File Error!\n";
        system("pause");
        return false;
    }

    while(fileCheckAdmin >> tempUsn >> tempPasw){
        if(tempUsn == user){
            adminCoy = true;
            fileCheckAdmin.close();
            break;
        }
    }

    if(adminCoy){
        if(tempPasw != pasw){
            cout << "Username atau Password Admin Salah!\n";
            system("pause");
            fileCheckAdmin.close();
            return false;
        }else{
            fileCheckAdmin.close();
            mode = 1;
            return true;
        }
    }else{
        while(fileCheckUsers >> tempUsn >> tempPasw){
            if(tempUsn == user){
                userCoy = true;
                fileCheckUsers.close();
                break;
            }
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
            mode = 2;
            return true;
        }
    }else{
        cout << "Username Tidak Ada! Silakan Register Terlebih Dahulu!\n";
        fileCheckUsers.close();
        system("pause");
        return false;
    }

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