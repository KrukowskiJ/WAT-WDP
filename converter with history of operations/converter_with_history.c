#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>

#define Clean_Tab(i,tab) for (int i = 0; i < 100; i++) *(tab + i) = 00   // makro czyszczenie tablicy

int count = 0;  //licznik operacji zmienna globalna

typedef struct History_of_operations {          //TWORZENIE STRUKTURY
    char* data;                                   //wejscie
    char* type;                                  //typ
    char* output;                                  //wyjscie

    struct History_of_operations* prev;          //wskaznik na nowszy element
    struct History_of_operations* next;             //wskaznik na starszy element
} History_of_operations;


//prototypy funkcji
int oct_hex();             
int hex_oct();
int dec_bin();
int bin_dec();
int print();            //wyswietlanie historii
int pop_front();            //usuwanie od najnowszego
int pop_current();          //usuwanie aktualnie wyświetlanego w historii elementu
int pop_back();             //usuwanie od najstarszego
void push(History_of_operations** head, char* input);           // dodawanie do listy
int show();                                      //wyswietlanie na gorze ilosci dostepnych miejsc w pamieci oraz 3 ostatnich wyników

int main(void)
{
    clock_t begin = clock();   //poczatek pomiaru czasu
    History_of_operations* head;                                     
    head = (History_of_operations*)malloc(sizeof(History_of_operations));
    head = NULL;
    char input[100] = "INPUT";                 //inicjalizacja wejsca i wyjscia , typu
    char output[100] = "OUTPUT";
    char* type;

    char option = '-1';
    do {
        if (count >= 10) {       //warunek dla przepełnienia pamieci
            system("cls");
            printf("Full memory space! Please delete some records");
            print(head);           // odsyła do historii by usunac element jezeli pamiec przepelniona
        }
        else
        {   
            system("cls");
                   show(head);              //wyswietlanie informacji na gorze programu 
            printf("\n\nIt's decimal <--> binary converter and hexadecimal <--> octal converter with history of operations\n");
            printf("\nChoose option: \n0. Exit \n1.Dec to Bin (10)->(2)\n2.Bin to Dec (2)->(10)\n3.Hex to Oct (16)->(8) \n4.Oct to Hex (8)->(16)\n5.Screen cleaning\n6.History\n");
            option = _getch();
            switch (option) {
            case '0':                   //koniec programu
                system("cls");
                clock_t end = clock();               //koniec pomiaru czasu
                double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;             //przeliczenie czasu na sekundy

                time_t curtime; 
                wchar_t buff[26];
                errno_t error;
                time(&curtime);
                error = _wctime_s(buff, 26, &curtime);
                wprintf_s(L"Finished computation at %s", buff);             //data i godzina zakonczenia programu


                printf("Elapsed time: %g s\n", time_spent);                  //Czas działania programu
                puts("...Exit");
                Sleep(2000);
                break;

            case '1':                                                    //konwersja 10 -> 2
                printf("\nYou choose dec to bin convert\n");
                dec_bin(input,output);
                type = "(10) -> (2): ";
                push(&head, input, output, type);                     //dodanie elementu do listy
                Sleep(3000);
                break;
            case '2':
                printf("\nYou choose bin to dec convert\n");                 //konwersja 2 -> 10
                bin_dec(input,output);
                type = "(2) -> (10): ";                                         
                push(&head, input, output, type);                               //dodanie elementu do listy
                Sleep(2000);
                break;
            case '3':
                printf("\nYou choose hex to oct convert\n(16): ");                  //konwersja 16 -> 8
                scanf_s("%s", input, 35);
                strncpy_s(output, 35, input, 35);               
                hex_oct(output);
                type = "(16) -> (8): ";
                push(&head, input, output, type);                                   
                Sleep(2000);
                break;
            case '4':
                printf("\nYou choose oct to hex convert\n(8): ");     //konwersja 8 -> 16
                scanf_s("%s", input, 35);
                strncpy_s(output, 35, input, 35);
                oct_hex(output);
                type = "(8) -> (16): ";
                push(&head, input, output, type);          //dodanie elementu do listy
                Sleep(2000);
                break;
            case '5':
                system("cls || clear");       //czyszczenie ekranu
                break;
            case '6':
                puts("\nHistory of operations:\n");                 //Historia operacji
                head = print(head);
                break;
            default:
                puts("Wrong number!");
                Sleep(2000);
            }
        }
    } while (option != '0');

}

void push(History_of_operations** head, char* input[100], char* output[100], char* type[20])
{
    if (*input == NULL)          //jezeli wprowadzamy np enter
        return 0;

    History_of_operations* current;


    current = (History_of_operations*)malloc(sizeof(History_of_operations));
    current->data = (History_of_operations*)malloc(100 * sizeof(History_of_operations));           //zarezerwowanie pamieci dla wejscia wyjscia i typu
    strncpy_s(current->data, 100, input, 100);                                                         //zapis wejscia
    current->type = (History_of_operations*)malloc(20 * sizeof(History_of_operations));
    strncpy_s(current->type, 20, type, 20);                                                            //zapis typu
    current->output = (History_of_operations*)malloc(100*sizeof(History_of_operations));
    strncpy_s(current->output, 100, output, 100);                                                         //zapis wyjscia

   

    if (*head == NULL)          //dodanie pierwszego elementu
    {
        current->prev = NULL;       //łączenia z innymi elementami na zero, ponieważ dodajemy pierwszy element
        current->next = NULL;
    }
    else                           //dodanie kolejnego elementu
    {
        current->prev = NULL;          //wskaznik na nastepny zero
        current->next = (*head);          //wskaznik na poprzedni dla current = obecny najnowszy
        (*head)->prev = current;          // wskaznik na nastepny obecnie najnowszego na current
    }
    *head = current;                //przypisujemy do listy 
    count++;                        //zmniejszamy ilosc mniejsc w pamieci (10 - count)
}

int show(History_of_operations* head)            //WYSWIETLA NIEKTÓRE INFORMACJE NA GÓRZE PODCZAS DZIAŁANIA PROGRAMU
{
    int i = -1;

    if (count >= 10)                                           //komunikat gdy pamiec przepelniona
    {
        printf("------FULL MEMORY------\n");
        printf("Delete some records to continue...\n");
        Sleep(2000);
        return;
    }
    else if (head == NULL) printf("List is empty");        //komunikat gdy lista pusta
    else
    {
        if (head)
            while (head->prev != NULL)             //przesuniecie do najnowszego elementu
                

        printf("Free slots in history: %d/10\n", 10 - count);           //ilosc wolnych miejsc
        printf("Last 3 results: ");                 //wyswietlenie ostatnich 3 wyników
        while (head != NULL && ++i < 3) {

            if (head)
                printf("\n%s :%s %s ", head->data, head->type, head->output);

            head = head->next;
        }
    }
}

int print(History_of_operations* head)
{  
    char option = '-1';
    printf("\n[N] - next [P] - previous [D]- remove front [E] - remove back [U] - remove current [ESC] - wyjscie\n");         //wyswietlenie menu historii
    int count2 = count;
    if(head)
    while (head->prev != NULL)     //przesuniecie na najnowszy element
        head = head->prev;

    if (head) printf("Last convertion: [%i/10]:  %s %s  %s\n", count, head->data, head->type, head->output);      //wyswietlenie ostatniej operacji

    if (!head) printf("Nothing is here yet :(");         // komunikat gdy pusta lista
    else
        do {

            option = _getch();
            switch (option)
            {
            case 'n':                                    //przesuniecie na element nowszy
            case 'N':
                if (head->prev == NULL)          //sprawdzenie czy nastepny element istnieje
                {
                    printf(" It is last element on list ");
                }
                else
                {
                    head = head->prev;
                    count2++;
                    printf("\n(%i/10): %s %s %s \n", count2, head->data, head->type, head->output);
                }
                break;
            case 'p':                                                   
            case 'P':                                                   //przesuniecie na element starszy
                if (head->next == NULL)                                 //sprawdzenie czy poprzedni element istnieje
                    printf(" It is first element on list ");
                else {
                    head = head->next;
                    count2--;
                    printf("\n(%i/10): %s %s %s\n", count2, head->data, head->type, head->output);
                }
                break;
            case 'd':             //usuniecie od najnowszego elementu
            case 'D':
                head = pop_front(&head);
                printf("Free slots in history: %d/10\n", 10 - count);
                break;
            case 'e':
            case 'E':
                head = pop_back(&head);        //usuniecie od najstarszego elementu
                printf("Free slots in history: %d/10\n", 10 - count);
                break;
            case 'u':
            case 'U':
                head = pop_current(&head);    //usuniecie bieżącego elementu
                printf("Free slots in history: %d/10\n", 10 - count);
                break;
            case 27:                                     //(escape key ASCII) wyjście z Historii
                printf("\n... closing History");
                return head;
                break;
            default:
                printf("Wrong choice!");          //zły wybor dla znaku spoza podanych
                printf("\n");
                break;
            }
        } while (option != 27);
        Sleep(2000);

}

int pop_front(History_of_operations** head)
{
    if (count == 0) {
        printf("NOTHING TO DELETE!");               //gdy licznik operacji jest 0 konczymy dzialanie funkcji
        return 0;
    }

    while ((*head)->prev != NULL)      //przesuwamy na najnowszy element
        (*head) = (*head)->prev;


    if ((*head)->next != NULL) {        //gdy jest wiele elementów
        (*head) = (*head)->next;        //przesuwamy glowe na starszy element
        count--;                        //zwiekszamy ilosc
        (*head)->prev = NULL;           //usuwamy wskaznik na element ktory chcemy usunac (najnowszy)
        free((*head)->prev);            //usuwamy najnowszy element
        return *head;
    }
    else               //gdy jest 1 element
    {
        head = NULL;       //czyscimy i zwalniamy pamiec z  listy
        free(head);
        count = 0;        //licznik operacji na zero
        return 0;
    }
}

int pop_back(History_of_operations** head)        //usuwanie od najstarszego
{
    if (count == 0) {
        printf("NOTHING TO DELETE!");     // gdy licznik operacji jest 0 konczymy dzialanie funkcji
        return 0;
    }

    if ((*head)->next == NULL)         //gdy jest jeden element
    {
        head = NULL;
        free(head);
        count = 0;
        printf("Free slots in history: %d/10", 10 - count);
        return 0;
    }
    else                                                      //gdy jest wiele elementów    tutaj troche inaczej niz poprzednie usuwanie :)
    {
        while ((*head)->next->next != NULL)        //przesuwamy na drugi najstarszy elemeent
            *head = (*head)->next;

        (*head)->next = NULL;
        free((*head)->next);          //usuwamy najstarszy element
        
        count--;                        //licznik +1;
        printf("Free slots in history: %d/10", 10 - count);
        return *head;
    }
}

int pop_current(History_of_operations** head)
{
    if (count == 0) {
        printf("NOTHING TO DELETE!");              //gdy lista pusta
        return 0;
    }

    History_of_operations* current = *head;

    
    if ((*head)->next == NULL)
    {
        if ((*head)->prev == NULL) {       //dla 1 elementu na liscie
            head = NULL;
            free(head);
            count--;
            return 0;
        }
        else                 //dla najstarszego elementu
        current->prev->next = NULL;           //usuwam wsk na najstarszy el
        *head = current->prev;                //zmieniam heada na drugi najstarszy element
        current = NULL;
        free(current);
        
    }
    else if (current->prev == NULL)       //dla najnowszego elementu
    {
        current->next->prev = NULL;          // usuwam wskaznik na najnowszy el
        *head = current->next;                  //zmieniam heada na drugi najnowszy el
        current = NULL;
        free(current);                        
    }
    else                                        //dla elementu z środka
    {
        current->prev->next = current->next;        //wskaźniki sąsiadów przerzucam na siebie nawzajem
        current->next->prev = current->prev;
        *head = current->prev;                      //wskaznik przesuwam na element nowszy
        free(current);                       //usuwam aktualnie wyswietlany element
    }
    count--;
    return *head;

}


int dec_bin(char* input, char* output) {


    int dec = 0, dec2=0, i = 0;
    char a[256] = { 0 };
    Clean_Tab(i, output);  //czyszczenie wyjścia
    Clean_Tab(i, input);  //czyszczenie wyjścia

    printf("(10): ");
    scanf_s("%s", input,30);       //wczytanie wejścia

    for (i = 0; input[i]!='\0'; i++)
        dec2 += (input[i] - 48) * pow(10,i);            //zamiana wejscia na int

    for (--i; dec2 > 0; i--) {
        dec += (dec2 % 10)* pow(10,i);           //odwrocenie tablicy int
        dec2 /= 10;

    }

    if (dec > 0) {
        for (i = 0; dec > 0; ++i) {
            a[i] = dec % 2 + 48;                 //zamiana wprowadzonej liczby na liczbę binarną,  jednocześnie zmiana typu (int) -> (char)  by wykluczyć ew. błędy gdy użytkownik wprowadzi niepoprawne danew
            dec /= 2;
        }
        



        printf("\n(2): ");
        int k = 0;
        for (k = i - 1, i = 0; k >= 0; i++, k--)             //odwrocenie tablicy
            *(output + k) = a[i];
        
    }
    else if (dec == 0) {
        printf("\n(2): 0"); *output = '0'; return 0;           //warunek dla zera
    }
    else {
        puts("Your number is too big!");   
        i = 0;                                                          //liczba za duża, ujemna lub podano znaki / litery zamiast cyfr
        Clean_Tab(i, output);
        return 0;
    }
    printf("%s\n ", output);       //wyswietlenie wyniku
    return *output;
}

int bin_dec(char* input, char* output)
{
    int a, i = 0, j = 0;
    int  x = 0;

    printf("Enter any binary number:\n(2): ");
    scanf_s("%s", input, 40);                                                 //wczytuje liczbe binarna jako tablice
    while (input[i] !='\0') i++;                                             //sprawdzam rozmiar podanej liczby

    if (input[0] == '0' && i == 1) {
        printf("\nDecimal of given number is:\n(10) %s", input); return 0;                            // warunek w przypadku podania zera 
    }
    if (--i >= 31) {
        puts("Your number is bigger than Max Int Size!"); Clean_Tab(i, input); return 0;             //warunek dla liczby wiekszej od inta
    }
    while (i + 1) {
        a = input[i] - 48;
        i--;
        if (a != 1 && a != 0) {                                //sprawdzam czy podana liczba jest liczbą binarną
            puts("It is not binary number!");
            Clean_Tab(i, input);
            return 0;
        }
        x += a * (pow(2, j++));                          // konwersja na decymalna liczbe x
    }

    Clean_Tab(i, output);                                          //czyszczenie tablicy tab

    int xx = x;                                          //zapamietuje x do drugiej zmiennej

    for (i = 0; x > 0; i++)                              //licze ilosc cyfr liczby dziesietnej x
        x = x / 10;

    while (xx > 0) {
        *(output + --i) = xx % 10 + 48;                    //przypisuje do tablicy tab cyfry z liczby dziesietnej jako znaki
        xx /= 10;
    }

    printf("\n(10): %s\n", output);
    return *output;
}

int hex_oct(char* hex) {
    int i;
    for (i = 0; *(hex + i) != '\0'; i++)
        if (*(hex + i) < 48 || (*(hex + i) > 57 && *(hex + i) < 65) || (*(hex + i) > 70 && *(hex + i) < 97) || *(hex + i) > 102) {
            printf("\nIt is not natural / hex number\n");                            //sprawdzenie poprawnosci wczytywanych cyfr/liter
            Clean_Tab(i, hex);
            return 0;                                                                //cofniecie do menu gdy znajdziemy nieprawidlowa wartosc
        }

    int base = 1, dec_val = 0;

    for (i--; i >= 0; i--, base *= 16)                                // konwersja z 16 na 10   
        if (*(hex + i) >= '0' && *(hex + i) <= '9')             // dla cyfr
            dec_val += (*(hex + i) - 48) * base;
        else if (*(hex + i) >= 'A' && *(hex + i) <= 'F')            // dla dużych liter
            dec_val += (*(hex + i) - 55) * base;
        else if (*(hex + i) >= 'a' && *(hex + i) <= 'f')            // dla małych liter
            dec_val += (*(hex + i) - 87) * base;

    int* oct = malloc(sizeof(oct));                                                 // konwersja z 10 na 8
    i = 0;
    while (dec_val) {
        int x = dec_val % 8;
        x += 48;                                                                    // do cyfry dziesiętnej dodaje 48 uzyskując wartość jej znaku w ASCII
        *(oct + i) = x;                                                                 // dokonuje konwersji przypisaniem wartosc ASCII do tablicy char oct   
        i++;
        dec_val /= 8;
    }

    Clean_Tab(i, hex);

    for (int b = 0; i > 0; b++)
        *(hex + b) = *(oct + --i);

    printf("\n(8): %s\n", hex);                                                         //wyswietlam tablice hex
    return *hex;
}

int oct_hex(char* oct) {
    int i = 0;
    for (i; *(oct + i) != '\0'; i++)
        if (*(oct + i) < 48 || *(oct + i) > 55) {                      //sprawdzenie czy liczba została wprowadzona poprawnie, jedynie cyfry 0-7
            printf("\nIt is not natural / oct number\n");
            for (int i = 0; i < 256; i++)
                *(oct + i) = 00;
            return 0;
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
        return 0;
    }
    Clean_Tab(i, oct);
    int* hex = malloc(sizeof(int));     //konwersja z 10 na 16
    i = 0;
    while (dec_val != 0) {
        int x = dec_val % 16;

        if (x < 10)  x += 48;
        else x += 55;                            //dla x<10 dodajemy 48 lub 55 zeby uzyskac liczbe reprezentujaca znaki 0-9 lub znaki A-F w ASCII

        *(hex + i) = x;                    //dokonuje konwersji przypisaniem wartosc ASCII do tablicy char hexx
        i++;
        dec_val = dec_val / 16;
    }

    for (int b = 0; i > 0; b++) {         //odwrocenie tablicy
        *(oct + b) = *(hex + --i);
    }
    printf("\n(16): ");                    //wyswietlam tablice hex
    printf("%s", oct);
    return *oct;
}