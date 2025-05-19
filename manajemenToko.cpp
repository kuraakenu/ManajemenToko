#include <iostream>
#include <cctype>
#include <fstream>
#include <iomanip>

using namespace std;

const string fileAdmin = "adminInfo.csv";
const string fileLoginInfo = "loginInfo.csv";
const string fileListBuku = "ListBuku.csv";
const int kapasitasBuku = 100;

string spaceToUnderscore(string str);
string UnderscoreToSpace(string str);
string EditUpLowCase(string str);

void mainMenu();
void firstMenu(string &user);
void adminMenu(string user);

bool registerUsers(string &user, string pasw);
bool loginUsers(string &user, string pasw);

void addBook(int tambahBuku);
void updateBook();
void listBook();
void searchBook();

// bntr jakl
//okee


struct buku{
    string idBuku;
    string judulBuku;
    string penerbitBuku;
    string authorBuku;
    string genre;
    string tahunTerbit;
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
    firstMenu(user);
    
    int pil, newBook, tambahBuku;
    while(pil !=4){
        system("cls");
        cout << "Hai Admin "<< user << "! \n";
        cout << "Selamat Datang di Dashboard GaraMedia Online\n";
        cout << "[1]. Update Data Buku\n";
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
        cout << "[4]. Tambah Buku \n";
        cout << "[5]. EXIT \n";
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
                cout << "Jumlah Buku Yang Ingin Ditambahkan: ";
                cin >> tambahBuku;
                addBook(tambahBuku);

            break;

            case 5:
            exit(0);
            break;

            default: 
            cout << "Input salah!! \n";
            break;
        }
    }
}

void firstMenu(string &user){
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
                if(loginUsers(user, pasw)){
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

void listBook(){
    ifstream fileCheck(fileListBuku);
    string judulTemp, idTemp, authorTemp, penerbitTemp, tahunTemp, hargaTemp, genreTemp;
    if(!fileCheck.is_open()){
        cout << "File Error!\n";
        system("pause");
        return;
    }
    while(fileCheck >> idTemp >> judulTemp >> genreTemp >> authorTemp >> penerbitTemp >> tahunTemp >> hargaTemp){
        judulTemp = UnderscoreToSpace(judulTemp);
        cout << judulTemp << ' ' << idTemp << '\n';
    }
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
    string judulTemp, idTemp, authorTemp, penerbitTemp, tahunTemp, hargaTemp, genreTemp;
    int i = 0;
    int hargaInt = 0;
    while(fileCheck >> idTemp >> judulTemp >> genreTemp >> authorTemp >> penerbitTemp >> tahunTemp >> hargaTemp){
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
        hargaInt = stoi(hargaTemp);
        daftarBuku[i].harga = hargaInt;
        i++;
    }
    fileCheck.close();
    int pil;
    while(pil != 3){
        system("cls");
        cout << "[1]. Cari Berdasarkan Judul\n";
        cout << "[2]. Cari Berdasarkan Genre\n";
        cout << "[3]. BACK\n";
        cout << "Input \t:";
        cin >> pil;
        string stringCari;
        bool found;
        int i, x;
        x = count + 1;
        int hitung = 0;
        
        bool ditemukan = false;
        
        switch(pil){
            case 1:
                daftarBuku[count].judulBuku;
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
                    cout << "Judul Buku Ditemukan!\n";
                    system("pause");
                }else{
                    cout << "Judul Buku Tidak Ditemukan\n";
                    system("pause");
                }
                
            break;

            case 2: 
                daftarBuku[count].genre;
                cout << "Masukkan Genre: ";
                cin.ignore();
                getline(cin, stringCari);
                stringCari = EditUpLowCase(stringCari);

                for(int i = 0; i < count; i++){
                    if(daftarBuku[i].genre == stringCari){
                        cout << i+1 << ". " << daftarBuku[i].judulBuku << '\n';
                    }
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


void updateBook(){
    ifstream fileIn(fileListBuku);
    ofstream fileTemp("tempListBuku.csv");
    string idCari;
    bool found = false;

    if (!fileIn.is_open() || !fileTemp.is_open()) {
        cout << "File Error!\n";
        system("pause");
        return;
    }

    cout << "Masukkan ID Buku yang ingin diupdate: ";
    cin >> idCari;

    string idTemp, judulTemp, authorTemp, penerbitTemp, genreTemp;
    int tahunTemp, hargaTemp;

    while (fileIn >> idTemp >> judulTemp >> genreTemp >> authorTemp >> penerbitTemp >> tahunTemp >> hargaTemp) {
        if (idTemp == idCari) {
            found = true;
            cin.ignore();
            cout << "Masukkan Judul Baru      : ";
            getline(cin, judulTemp);
            judulTemp = spaceToUnderscore(judulTemp);

            cout << "Masukkan Genre Baru      : ";
            getline(cin, genreTemp);

            cout << "Masukkan Author Baru     : ";
            getline(cin, authorTemp);
            authorTemp = spaceToUnderscore(authorTemp);

            cout << "Masukkan Penerbit Baru   : ";
            getline(cin, penerbitTemp);
            penerbitTemp = spaceToUnderscore(penerbitTemp);

            cout << "Masukkan Tahun Terbit Baru: ";
            cin >> tahunTemp;

            cout << "Masukkan Harga Baru      : ";
            cin >> hargaTemp;

            fileTemp << idTemp << ' ' << judulTemp << ' ' << authorTemp << ' ' << penerbitTemp << ' ' << tahunTemp << ' ' << hargaTemp << '\n';

        } else {
            fileTemp << idTemp << ' ' << judulTemp << ' ' << authorTemp << ' ' << penerbitTemp << ' ' << tahunTemp << ' ' << hargaTemp << '\n';
        }
    }

    fileIn.close();
    fileTemp.close();

    remove(fileListBuku.c_str());
    rename("tempListBuku.csv", fileListBuku.c_str());

    if(found){
        cout << "Data Buku Berhasil Diperbarui!\n";
    }else{
        cout << "ID Buku Tidak Ditemukan!\n";
    }

    system("pause");
}


void addBook(int tambahBuku){
    ofstream fileInput(fileListBuku, ios::app);
    string judulTemp, penerbitTemp, authorTemp, genreTemp, lineCheck;

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
    fileInput << daftarBuku[tambahBuku].idBuku << ' ' << judulTemp << ' ' << genreTemp << ' ' << authorTemp << ' ' << penerbitTemp << ' ' << daftarBuku[tambahBuku].tahunTerbit << ' ' << daftarBuku[tambahBuku].harga << '\n';
    system("cls");

    return addBook(tambahBuku - 1);
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