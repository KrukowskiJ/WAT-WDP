#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>


void hex_oct();
void oct_hex();
void menu() {
    char option;
    do {
        printf("\nChoose option: \n1. Exit \n2.Hex to Oct (16)->(8) \n3.Oct to Hex (8)->(16) \n4.Screen cleaning\n");
        option = _getch();
        switch (option) {
        case '1':
            puts("Exit");
            break;
        case '2':
            hex_oct();
            break;
        case '3':
            oct_hex();
            break;
        case '4':
            system("cls");
            break;
        default:
            puts("Wrong number!");
        }
    } while (option != '1');
}
int * hex_bin(char hex[],int bin[]) { //To convert hex to binary first
    int j = 0,i=0;
    int* wsk = bin;
    for (i; hex[i] != '\0'; i++) {
        switch (hex[i]) {
        case '0':
            bin[j] = 0;
            bin[j + 1] = 0;
            bin[j + 2] = 0;
            bin[j + 3] = 0;
            j += 4;
            break;
        case '1':
            bin[j] = 0;
            bin[j + 1] = 0;
            bin[j + 2] = 0;
            bin[j + 3] = 1;
            j += 4;
            break;
        case '2':
            bin[j] = 0;
            bin[j + 1] = 0;
            bin[j + 2] = 1;
            bin[j + 3] = 0;
            j += 4;
            break;
        case '3':
            bin[j] = 0;
            bin[j + 1] = 0;
            bin[j + 2] = 1;
            bin[j + 3] = 1;
            j += 4;
            break;
        case '4':
            bin[j] = 0;
            bin[j + 1] = 1;
            bin[j + 2] = 0;
            bin[j + 3] = 0;
            j += 4;
            break;
        case '5':
            bin[j] = 0;
            bin[j + 1] = 1;
            bin[j + 2] = 0;
            bin[j + 3] = 1;
            j += 4;
            break;
        case '6':
            bin[j] = 0;
            bin[j + 1] = 1;
            bin[j + 2] = 1;
            bin[j + 3] = 0;
            j += 4;
            break;
        case '7':
            bin[j] = 0;
            bin[j + 1] = 1;
            bin[j + 2] = 1;
            bin[j + 3] = 1;
            j += 4;
            break;
        case '8':
            bin[j] = 1;
            bin[j + 1] = 0;
            bin[j + 2] = 0;
            bin[j + 3] = 0;
            j += 4;
            break;
        case '9':
            bin[j] = 1;
            bin[j + 1] = 0;
            bin[j + 2] = 0;
            bin[j + 3] = 1;
            j += 4;
            break;
        case 'a':
        case 'A':
            bin[j] = 1;
            bin[j + 1] = 0;
            bin[j + 2] = 1;
            bin[j + 3] = 0;
            j += 4;
            break;
        case 'b':
        case 'B':
            bin[j] = 1;
            bin[j + 1] = 0;
            bin[j + 2] = 1;
            bin[j + 3] = 1;
            j += 4;
            break;
        case 'c':
        case 'C':
            bin[j] = 1;
            bin[j + 1] = 1;
            bin[j + 2] = 0;
            bin[j + 3] = 0;
            j += 4;
            break;
        case 'd':
        case 'D':
            bin[j] = 1;
            bin[j + 1] = 1;
            bin[j + 2] = 0;
            bin[j + 3] = 1;
            j += 4;
            break;
        case 'e':
        case 'E':
            bin[j] = 1;
            bin[j + 1] = 1;
            bin[j + 2] = 1;
            bin[j + 3] = 0;
            j += 4;
            break;
        case 'f':
        case 'F':
            bin[j] = 1;
            bin[j + 1] = 1;
            bin[j + 2] = 1;
            bin[j + 3] = 1;
            j += 4;
            break;
        default:
            printf("\nInvalid input.\n");
        }
    }
    return wsk;
}
int * oct_bin(char oct[], int bin[]) {
    int j=0,i=0;

    int* wsk = bin;
    for (i; oct[i] != '\0'; i++) {
        switch (oct[i]) {
        case '0':
            bin[j] = 0;
            bin[j + 1] = 0;
            bin[j + 2] = 0;
            j += 3;
            break;
        case '1':
            bin[j] = 0;
            bin[j + 1] = 0;
            bin[j + 2] = 1;
            j += 3;
            break;
        case '2':
            bin[j] = 0;
            bin[j + 1] = 1;
            bin[j + 2] = 0;
            j += 3;
            break;
        case '3':
            bin[j] = 0;
            bin[j + 1] = 1;
            bin[j + 2] = 1;
            j += 3;
            break;
        case '4':
            bin[j] = 1;
            bin[j + 1] = 0;
            bin[j + 2] = 0;
            j += 3;
            break;
        case '5':
            bin[j] = 1;
            bin[j + 1] = 0;
            bin[j + 2] = 1;
            j += 3;
            break;
        case '6':
            bin[j] = 1;
            bin[j + 1] = 1;
            bin[j + 2] = 0;
            j += 3;
            break;
        case '7':
            bin[j] = 1;
            bin[j + 1] = 1;
            bin[j + 2] = 1;
            j += 3;
            break;
        default:
            printf("\nInvalid input.\n");
        }
    }
    return wsk;
}
void bin_oct(int bin[], char* wsk) {        //To convert binary to octal




    int i = 0, j=0,  val = 0, b;
    for (i = 0; bin[i] != 2; i++);

    i -= 1;


    while (i>= 0) {

        if(i>=2)
        b = 100 * bin[i - 2] + 10 * bin[i - 1] + bin[i];
        else if(i==1)
        b = 10 * bin[i - 1] + bin[i];
        else if(i==0)
        b = bin[i];

        switch (b) {
        case 0:
            val = 48;
            break;
        case 1:
            val = 49;
            break;
        case 10:
            val = 50;
            break;
        case 11:
            val = 51;
            break;
        case 100:
            val = 52;
            break;
        case 101:
            val = 53;
            break;
        case 110:
            val = 54;
            break;
        case 111:
            val = 55;
            break;
        }
        *(wsk + j) = val;
        j++;
        i-=3;


    }
    printf("(8) : ");
    for (j-=2; j >= 0; j--)
        printf("%c", *(wsk + j));
}
void bin_hex(int bin[], char* wsk) { //To convert binary to octal
    int i = 0, j = 0, val = 0, b=0;
    for (i = 0; bin[i] != 2; i++);

    i -= 1;

    while (i>=0) {
        if (i >= 3)
            b = 1000 * bin[i-3] + 100 * bin[i - 2] + 10 * bin[i - 1] + bin[i];
        else if (i == 2)
            b=100 * bin[i - 2] + 10 * bin[i - 1] + bin[i];
        else if (i == 1)
            b = 10 * bin[i - 1] + bin[i];
        else if (i == 0)
            b = bin[i];

        switch (b) {
        case 0:
            val = 48;
            break;
        case 1:
            val = 49;
            break;
        case 10:
            val = 50;
            break;
        case 11:
            val = 51;
            break;
        case 100:
            val = 52;
            break;
        case 101:
            val = 53;
            break;
        case 110:
            val = 54;
            break;
        case 111:
            val = 55;
            break;
        case 1000:
            val = 56;
            break;
        case 1001:
            val = 57;
            break;
        case 1010:
            val = 65;
            break;
        case 1011:
            val = 66;
            break;
        case 1100:
            val = 67;
            break;
        case 1101:
            val = 68;
            break;
        case 1110:
            val = 69;
            break;
        case 1111:
            val = 70;
            break;


        }
        *(wsk + j) = val;
        j++;
        i -= 4;


    }
    printf("(16) : ");
    for (j-=1; j >= 0; j--)
        printf("%c", *(wsk + j));
}
void hex_oct() {                                                                        // to convert hexadecimal number to octal
    char oct[20];
    char* wsk = oct;

    printf("\nYou choose hex to oct convert\n");
    char hex[20] = { 0 };
    scanf_s("%s", hex, 20);
    for (int i = 0; hex[i] != '\0'; i++)
        if (int(hex[i]) < 48 || (int(hex[i]) > 57 && int(hex[i]) < 65) || int(hex[i]) > 70) {
            printf("\nIt is not natural / hex number\n");
            menu();}

    int bin[40];
    for (int i = 0; i < 40; i++) bin[i] = 2;



    int* a;
    a = hex_bin(hex,bin);
    bin_oct(bin, wsk);                                                               // convert Binary to Octal
}
void oct_hex() {                                                                    // to convert octal to hexadecimal
    char hex[20];
    char* wsk = hex;

    printf("\nYou choose oct to hex convert\n");
    char oct[20] = { 0 };
    scanf_s("%s", oct, 20);
    for (int i = 0; oct[i] != '\0'; i++)
        if (int(oct[i]) < 48 || int(oct[i]) > 55){
            printf("\nIt is not  / oct number\n");
            menu();
             }


    int bin[40];
    for (int i = 0; i < 40; i++) bin[i] = 2;




    int* a;
    a = oct_bin(oct, bin);
    bin_hex(bin, wsk);
}

int main() {

    printf("It's hexadecimal <--> octal converter\n");
    menu();

    return 0;
}
