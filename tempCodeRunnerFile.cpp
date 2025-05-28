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