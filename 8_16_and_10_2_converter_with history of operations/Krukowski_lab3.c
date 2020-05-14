#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <windows.h>
#include <string.h>

int licznik_operacji = 0;

int oct_hex();
int hex_oct();
int dec_bin();
int bin_dec();
int print();
void deleteNode();
void nowy_element();


typedef struct History_of_operations {
    char* data;
    struct History_of_operations* prev;
    struct History_of_operations* next;
} History_of_operations;

int main() {
    History_of_operations* head;
    head = (History_of_operations*)malloc(sizeof(History_of_operations));
    head = NULL;

    char* input=malloc(256*sizeof(input));
    char option;
    do {
        system("cls");
        printf("It's decimal <--> binary converter and hexadecimal <--> octal converter with history of operations\n");
        printf("\nChoose option: \n0. Exit \n1.Dec to Bin (10)->(2)\n2.Bin to Dec (2)->(10)\n3.Hex to Oct (16)->(8) \n4.Oct to Hex (8)->(16)\n5.Screen cleaning\n6.History");
        option = _getch();
        switch (option) {
        case '0':
            puts("Exit");
            break;
        case '1':
            dec_bin();
            Sleep(3000);
            break;
        case '2':
            bin_dec();
            Sleep(3000);
            break;
        case '3':
            printf("\nYou choose hex to oct convert\n(16): "); //wprowadzenie liczby szesnastkowej bufor ustawiony na 15 znaków , max_int w 16 ma 8 znaków
            scanf_s("%s", input, 15);
            hex_oct(input);
            nowy_element(&head, input);
            Sleep(3000);
            break;
        case '4':
            printf("\nYou choose oct to hex convert\n");     //wprowadzenie liczby ósemkowej bufor ustawiony na 15 znaków , max_int w 8 ma 11 znaków
            scanf_s("%s", input, 15);
            oct_hex(input);
            nowy_element(&head, input);
            Sleep(3000);
            break;
        case '5':
            system("cls || clear");       //czyszczenie ekranu
            break;
        case '6':
            print(head);
            puts("History of operations:");
            break;
        default:
            puts("Wrong number!");
        }
    } while (option != '0');

    return 0;
}

int dec_bin(){
    int* tab = malloc(sizeof(tab));
    int dec, i;
    printf("Enter decimal number:\n(10) ");
    scanf_s("%d", &dec);
    if (dec >= 0) {
        for (i = 0; dec > 0; ++i) {
            *(tab + i) = dec % 2;
            dec /= 2;
        }
        printf("Binary of given number is:\n(2) ");
        for (i--; i >= 0; i--)
            printf("%d", *(tab + i));
    }
    else
        puts("Your number is too low!");

    return *tab;
}

int bin_dec() {
    int a, x = 0, i=0;
    long long bin;
    printf("Enter any binary number:\n(2): ");
    scanf_s("%lld", &bin);

    while(bin){
        a = bin % 10;
        if (a != 1 && a != 0) {
            puts("It is not binary number!");
            return 0;
        }
        x += a * (pow(2, i++));
        bin /= 10;
    }
    printf("Decimal of given number is:\n(10) %ld", x);
    return x;
}

int hex_oct(char* hex) {  
    int i;
    for (i = 0; *(hex + i) != '\0'; i++)
        if (*(hex + i) < 48 || (*(hex + i) > 57 && *(hex + i) < 65) || (*(hex + i) > 70 && *(hex + i) < 97) || *(hex + i) > 102) {
            printf("\nIt is not natural / hex number\n");                            //sprawdzenie poprawnosci wczytywanych cyfr/liter
            return 0;                                                                //cofniecie do menu gdy znajdziemy nieprawidlowa wartosc
        }

    int base = 1, dec_val = 0;

    for (i--; i >= 0; i--, base *= 16)                                // konwersja z 16 na 10   
        if (*(hex + i) >= '0' && *(hex + i) <= '9')             // dla cyfr
            dec_val += (*(hex + i) - 48) * base;
        else if (*(hex + i) >= 'A' && *(hex + i) <= 'F')        // dla dużych liter
            dec_val += (*(hex + i) - 55) * base;
        else if (*(hex + i) >= 'a' && *(hex + i) <= 'f')        // dla małych liter
            dec_val += (*(hex + i) - 87) * base;

    char* oct = malloc(sizeof(oct));                                          // konwersja z 10 na 8
    while (dec_val){
        int x = dec_val % 8;

        x += 48;                             // do cyfry dziesiętnej dodaje 48 uzyskując wartość jej znaku w ASCII

        *(oct + ++i) = x;                     // dokonuje konwersji przypisaniem wartosc ASCII do tablicy char oct
        dec_val /= 8;
    }

    printf("(8): ");                             // wyswietlam tablice oct
    for (i; i >= 0; i--)
        printf("%c", *(oct + i));
}

int oct_hex(char* oct) {
    int i = 0;
    for (i; *(oct + i) != '\0'; i++)
        if (*(oct + i) < 48 || *(oct + i) > 55) {                      //sprawdzenie czy liczba została wprowadzona poprawnie, jedynie cyfry 0-7
            printf("\nIt is not natural / oct number\n");
            return;
        }

    int base = 1, dec_val = 0;                     //konwersja z 8 na 10
    for (i; i >= 0; --i)
        if (*(oct + i) > 0)
        {
            dec_val += (*(oct + i) - 48) * base;
            base = base * 8;
        }
    if (dec_val < 0) {                                     // sprawdzenie czy podana liczba nie jest większa od int_max lub mniejsza od 0
        printf("Your number is too big!\n");
        return;
    }

    char* hex = malloc(sizeof(hex));     //konwersja z 10 na 16
    
    while (dec_val != 0) {
        int x = dec_val % 16;

        if (x < 10)  x += 48;
        else x += 55;                            //dla x<10 dodajemy 48 lub 55 zeby uzyskac liczbe reprezentujaca znaki 0-9 lub znaki A-F w ASCII

        *(hex + ++i) = x;                    //dokonuje konwersji przypisaniem wartosc ASCII do tablicy char hexx

        dec_val = dec_val / 16;
    }

    printf("(16): ");                    //wyswietlam tablice hex
    for (i; i >= 0; i--)
        printf("%c", *(hex + i));
       
    return *hex;
}

int print(History_of_operations* head)
{

    int licznik_o = licznik_operacji;
    printf("\nIlosc zajetych miejsc w pamieci: %i/10\n", licznik_o);
    char option;
    printf("\n");
    if (head == NULL) printf("Nothing is here yet :(");
    else
    {
        History_of_operations* current = head;
        printf("Ostatnio wykonana operacja [%i]:", licznik_o);
        printf("%s\n", current);
        printf("\n[n]-next [p]-previous [d]-delete [esc]-wyjscie\n"); 
        do {
            option = _getch();
            switch (option)
            {
            case 'n':
            case 'N':
                if (current->prev == NULL)
                {
                    printf("Brak nastepnego elementu");
                }
                else
                {
                    current = current->prev;
                    licznik_o++;
                    printf("(%i/10): %s\n", licznik_o, current);
                }
                break;
            case 'p':
            case 'P':
                if (current->next == NULL)
                    printf("Brak poprzedniego elementu");
                else{
                    current = current->next;
                    licznik_o--;
                    printf("\n(%i/10): %s\n", licznik_o, current);
                }
                break;
            case 'd':
            case 'D':
                deleteNode(&current, current);
              
                break;
            case 27:  //(escape key ASCII)
                system("cls || clear");
                return 0;
                break;
            default:
                printf("Zly wybor");
                printf("\n");
                break;
            }
        } while (option != 27);
    }
    Sleep(1000);
}

void nowy_element(History_of_operations** head, char* input[256])
{
    if (*head == NULL) {
        *head = (History_of_operations*)malloc(sizeof(History_of_operations));
        (*head)->data = *input;
        (*head)->prev = NULL;
        (*head)->next = NULL;

    }
    else {
        History_of_operations* current;
        current = (History_of_operations*)malloc(sizeof(History_of_operations));
        current->data = *input;
        current->prev = NULL;
        current->next = *head;
        (*head)->prev = current;
        *head = current;
    }
    licznik_operacji++;
}
void deleteNode(struct History_of_operations* head_ref, struct History_of_operations* current)
{
    /* base case */
    if (head_ref == NULL || current == NULL)
        return;
    
    /* If node to be deleted is head node */
    if (current->next != NULL)
        head_ref = current->next;
    else if (current->prev != NULL)
        head_ref = current->prev;

  
    current = NULL;


    /* Finally, free the memory occupied by del*/
    free(current);
    licznik_operacji--;
    return;
}


   



