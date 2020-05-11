#include <stdio.h>
#include <stdlib.h>    //uzywam do system cls
#include <conio.h>     //uzywam do getch


const int int_max = 2147408579;   // najwiekszy mozliwy int - numer albumu     2,147,483,647 - 75068   

void menu();                  
void hex_oct();
void oct_hex();

int main() {

    printf("It's hexadecimal <--> octal converter\n");   
    menu();

    return 0;
}
void menu() {
    char option;
    do {
        printf("\nChoose option: \n1. Exit \n2.Hex to Oct (16)->(8) \n3.Oct to Hex (8)->(16) \n4.Screen cleaning\n");
        option = _getch();      //odczyt wyboru opcji przez uzytkownika z autamtycznym przejsciem do opcji
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
            system("cls || clear");       //czyszczenie ekranu
            break;
        default:
            puts("Wrong number!");
        }
    } while (option != '1');
}
void hex_oct() {
    printf("\nYou choose hex to oct convert\n(16): "); 
    char hex[12] = { 0 };                               
    int i;
    scanf_s("%s", hex, 12);                                 //wprowadzenie liczby szesnastkowej bufor ustawiony na 12 znaków , max_int w 16 ma 8 znaków

    for (i = 0; *(hex+i) != '\0'; i++)
      if (*(hex + i) < 48 || (*(hex + i) > 57 && *(hex + i) < 65) || (*(hex + i) > 70 && *(hex + i) < 97) || *(hex + i) > 102){
            printf("\nIt is not natural / hex number\n");                            //sprawdzenie poprawnosci wczytywanych cyfr/liter
            menu();                                                                 //cofniecie do menu gdy znajdziemy nieprawidlowa wartosc
        }

    int base = 1, dec_val = -1;

    for (i--; i >= 0; i--)                                // konwersja z 16 na 10   
    {
        
        if (*(hex + i) >= '0' && *(hex + i) <= '9')             // dla cyfr
            dec_val += (*(hex + i) - 48) * base;
        else if (*(hex + i) >= 'A' && *(hex + i) <= 'F')        // dla dużych liter
            dec_val += (*(hex + i) - 55) * base;
        else if (*(hex + i) >= 'a' && *(hex + i) <= 'f')        // dla małych liter
            dec_val += (*(hex + i) - 87) * base;

            base = base * 16;
    }
    if (dec_val<0 || dec_val > int_max) {                                     // sprawdzenie czy podana liczba nie jest większa od int_max
        printf("Your number is too big!\n");
        menu();
    }
              
    char oct[20] = { 0 };                                           // konwersja z 10 na 8
    i = 0;                                                  
    while (dec_val != 0) {
        int x = dec_val % 8;
  
            x += 48;                             // do cyfry dziesiętnej dodaje 48 uzyskując wartość jej znaku w ASCII
      
            *(oct + i++) = x;                     // dokonuje konwersji przypisaniem wartosc ASCII do tablicy char oct
        dec_val = dec_val / 8;
    }
    
    printf("(8): ");                             // wyswietlam tablice oct
    for (i; i >= 0; i--)
        printf("%c", *(oct + i));
}
void oct_hex() {                                                                   
    printf("\nYou choose oct to hex convert\n");
    char oct[15] = { 0 };
    scanf_s("%s", oct, 15);                                 //wprowadzenie liczby ósemkowej bufor ustawiony na 15 znaków , max_int w 8 ma 11 znaków
    int i = 0;
    for (i; *(oct + i) != '\0'; i++)
        if (*(oct + i) < 48 || *(oct + i) > 55) {                      //sprawdzenie czy liczba została wprowadzona poprawnie, jedynie cyfry 0-7
            printf("\nIt is not natural / oct number\n");
            menu();
        }

    int base = 1, dec_val = -1;                     //konwersja z 8 na 10
    for (i; i >= 0; i--) 
        if (*(oct + i) > 0)
        {
            dec_val += (*(oct + i) - 48) * base;
            base = base * 8;
        }
    if (dec_val < 0 || dec_val > int_max) {                                     // sprawdzenie czy podana liczba nie jest większa od int_max lub mniejsza od 0
        printf("Your number is too big!\n");
        menu();
    }

    char hex[15] = { 0 };                                                  //konwersja z 10 na 16
    i = 0;                                          
    while (dec_val != 0) {
        int x = dec_val % 16;

        if(x < 10)  x += 48;
        else x += 55;                            //dla x<10 dodajemy 48 lub 55 zeby uzyskac liczbe reprezentujaca znaki 0-9 lub znaki A-F w ASCII

        *(hex + i++) = x;                    //dokonuje konwersji przypisaniem wartosc ASCII do tablicy char hexx

        dec_val = dec_val / 16;         
    }
    
    printf("(16): ");                    //wyswietlam tablice hex
    for (i; i >= 0; i--)
        printf("%c", *(hex + i));
}
