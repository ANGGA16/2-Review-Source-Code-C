#include <stdio.h>
#include <string.h>

#define SIZE_NAME 16
#define SIZE_CHARECTERS 21

/******************
* Function Name: sort
* Input: Susunan kata yang dipisahkan, jumlah kata
* Output: Void
* Function Operation: Menyortir Array
******************/
void sort(char sortedArr[][SIZE_CHARECTERS], int wordNum){

    char temp[SIZE_CHARECTERS];
    const int ONE = 1;

    // mengurutkan nama berdasarkan urutan abjad, membandingkan nama depan
    for(int k = 0; k < wordNum - ONE; k++){

        // membandingkan nama kedua
        for(int j = k + ONE; j < wordNum; j++){

            // ganti nama hanya jika nama kiri lebih besar dari nama kanan
            if(strcmp(sortedArr[k], sortedArr[j]) > 0){

                // mengganti pesanan
                strcpy(temp, sortedArr[k]);
                strcpy(sortedArr[k], sortedArr[j]);
                strcpy(sortedArr[j], temp);
            }
        }
    }
}

/******************
* Function Name:strList
* Input: Susunan kata kosong, susunan kata, susunan petunjuk, susunan token
* Output: Jumlah elemen dalam array
* Function Operation: memisahkan array dengan kata-kata
******************/
int strList(char sortedArr[][SIZE_CHARECTERS], char mainStr[], char hint[], char sep[]){

    // membuat variabel untuk mengetahui di mana kata-kata dimulai
    const char start = ':';

    // menyimpan petunjuknya
    for(int i = 0; mainStr[i] != start; i++){
        hint[i] = mainStr[i];
    }

    // membuat penunjuk untuk memulai dari kata pertama
    char *token;
    token = strchr(mainStr, start);

    // memisahkan kata-kata
    token += sizeof(char);
    token = strtok(token, sep);

    // jumlah kata dalam permainan
    int wordNum = 0;

    // mengatasi setiap kata ke array baru
    while (token != NULL){
        strcpy(sortedArr[wordNum], token);
        token = strtok(NULL, sep);
        wordNum++;
    }

    // mengembalikan jumlah kata dalam permainan
    return wordNum;
}

/******************
* Function Name:shape
* Input: jumlah stage
* Output:Void
* Function Operation: mencetak bentuknya
******************/
void shape(int stage){

    // bilangan bulat konstan untuk garis tahapan bentuk
    const int ZERO = 0, ONE = 1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5, SIX = 6;

    // pencetakan tahap 1
    if(stage == ONE){
        printf(" _________________\n");
        for(int t = 0; t < FIVE; t++){
            printf("|                |\n");
        }
        printf("|________________|\n");
    }

    // pencetakan tahap 2
    else if(stage == TWO){
        printf(" _________________\n");
        for(int t = 0; t < FIVE; t++){
            if(t == ONE || t == TWO){
                printf("|  **            |\n");
            }
            else{
                printf("|                |\n");
            }
        }
        printf("|________________|\n");
    }

    // pencetakan tahap 3
    else if(stage == THREE){
        printf(" _________________\n");
        for(int t = 0; t < FIVE; t++){
            if(t == ONE || t == TWO){
                printf("|  **        **  |\n");
            }
            else{
                printf("|                |\n");
            }
        }
        printf("|________________|\n");
    }

    // pencetakan tahap 4
    else if(stage == FOUR){
        printf(" _________________\n");
        for(int t = 0; t < FIVE; t++){
            if(t == ZERO){
                printf("|  --            |\n");
            }
            else if(t == ONE || t == TWO){
                printf("|  **        **  |\n");
            }
            else{
                printf("|                |\n");
            }
        }
        printf("|________________|\n");
    }

    // pencetakan tahap 5
    else if(stage == FIVE){
        printf(" _________________\n");
        for(int t = 0; t < FIVE; t++){
            if(t == ZERO){
                printf("|  --        --  |\n");
            }
            else if(t == ONE || t == TWO){
                printf("|  **        **  |\n");
            }
            else{
                printf("|                |\n");
            }
        }
        printf("|________________|\n");
    }

    // pencetakan tahap 6
    else if(stage == SIX){
        printf(" _________________\n");
        for(int t = 0; t < FIVE; t++){
            if(t == ZERO){
                printf("|  --        --  |\n");
            }
            else if(t == ONE || t == TWO){
                printf("|  **        **  |\n");
            }
            else if(t == FOUR){
                printf("| \\/\\/\\/\\/\\/\\/\\  |\n");
            }
            else{
                printf("|                |\n");
            }
        }
        printf("|________________|\n");
    }

}

/******************
* Function Name:game
* Input: array yang diurutkan, opsi yang dipilih untuk dimainkan, panjang opsi, array petunjuk
* Output:Void
* Function Operation: bermain "Hang Man"
******************/
void game(char sortedArr[][SIZE_CHARECTERS], int option, int lenOfOption, char hint[]){

    // variabel untuk mengetahui pada tahap apa Anda berada
    int stage = 1;

    // bendera untuk petunjuk dan pernyataan surat yang sama
    int hintFlag = 1;
    int outFlag = 1;
    int correctFlag = 1;


    // susunan jawabannya
    char answers[SIZE_CHARECTERS];

    // indeks huruf dalam array
    int letIndex = 0;

    // pilihan pengguna
    char choice = 0;
    char enter;

    // char konstan untuk array jawaban dan baris
    const char UNDERLINE = '_', SPACE = ' ', ASTERISK = '*' ;

    // susunan baris jawaban
    char line[lenOfOption];

    // membuat baris jawaban
    for(int i = 0; i < lenOfOption; i++){

        // jika tempat itu adalah sebuah surat
        if(sortedArr[option][i] != SPACE){
            line[i] = UNDERLINE;
        }

        // jika tempat itu adalah sebuah spasi
        else{
            line[i] = SPACE;
        }
    }

    // bilangan bulat konstan untuk pohon logika dalam game
    const int ZERO = 0, ONE = 1, SIX = 6;

    // permainan itu sendiri!
    while(ONE){

        // mencetak bentuknya
        shape(stage);

        // memeriksa apakah pengguna menang, jika dia menang - hancurkan
        if (strcmp(line, sortedArr[option]) == ZERO){
            printf("The word is %s, good job!", sortedArr[option]);
            break;
        }

        // mencetak baris jawaban
        for(int i = 0; i < lenOfOption; i++){
            printf("%c", line[i]);
        }

        // memeriksa kebutuhan mencetak pernyataan "petunjuk".
        if(hintFlag == ONE){
            printf("\ndo you want a clue? press -> *");
        }

        // huruf yang dicoba pengguna
        printf("\nThe letters that you already tried:");

        // mencetak susunan huruf yang digunakan
        for(int k = 0; k < letIndex;k++){
            if(k == letIndex - ONE){
                printf(" %c", answers[k]);
            }
            else{
                printf(" %c,", answers[k]);
            }
        }

        // meminta surat
        printf("\nplease choose a letter:\n");

        scanf("%*[^\n]");
        scanf("%*[^\n]%*c");
        scanf("%c %c", &enter, &choice);

        // jika pengguna menginginkan petunjuk
        if(choice == ASTERISK && hintFlag == ONE){
            printf("the clue is: ");
            for(int i = 0; i < strlen(hint); i++){
                printf("%c", hint[i]);
            }
            printf(".\n");
            hintFlag = 0;
        }

        // jika pengguna tidak menginginkan petunjuk
        else if(choice != ASTERISK){

            // memeriksa apakah surat itu digunakan
            for(int i = 0; i < letIndex; i++){

                // jika surat itu digunakan
                if(choice == answers[i]){
                    outFlag = 0;
                }
            }

            // jika belum digunakan
            if(outFlag == ONE){

                // letakkan di array huruf yang digunakan
                answers[letIndex] = choice;
                letIndex++;


                // jika suratnya benar
                for(int i = 0; i < lenOfOption; i++){
                    if(sortedArr[option][i] == choice){
                        line[i] = choice;
                        correctFlag = 0;
                    }
                }

                // jika suratnya salah
                if(correctFlag == ONE){

                    // naikkan stage
                    stage++;

                    // jika ini tahap akhir
                    if(stage == SIX){
                        shape(stage);
                        printf("The word is %s, GAME OVER!", sortedArr[option]);
                        break;
                    }
                }
            }

            // jika surat itu digunakan
            else{
                printf("You've already tried that letter.\n");
            }

        }

        // mendefinisikan ulang semua bendera
        outFlag = 1;
        correctFlag = 1;
    }
}

int main() {

    // susunan kata utama yang harus ditebak dalam permainan
    char mainStr[SIZE_NAME*SIZE_CHARECTERS];
    char sortedArr[SIZE_NAME][SIZE_CHARECTERS];
    char hint[SIZE_CHARECTERS] = {0};

    // menanyakan kata-kata kepada pengguna
    printf("Enter your words:\n");
    scanf("%[^\n]", mainStr);

    // mengirimkan susunan kata dipisahkan dan mendapatkan jumlah kata
    int wordNum = strList(sortedArr, mainStr,hint, ",");

    // mengirimkan array terpisah untuk diurutkan
    sort(sortedArr, wordNum);

    // mencetak array yang diurutkan sebagai daftar
    const int ONE = 1;
    printf("choose an option:\n");
    for(int i = 0; i < wordNum; i++){
        printf("%d: %s\n", (i + ONE), sortedArr[i]);
    }

    // variabel untuk menyimpan opsi
    int option;
    scanf("%d", &option);
    option -= ONE;

    // memeriksa panjang kata. karena arraynya dimulai dari 0, tetapi daftarnya dari 1, jadi (opsi- 1).
    int lenOfOption = strlen(sortedArr[option]);

    // akan memulai permainan!
    game(sortedArr, option, lenOfOption, hint);

    return 0;
}
