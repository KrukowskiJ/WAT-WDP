#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int dec_to_bin(int ID){
    int tab[20],i;
    int b;
    printf("Enter decimal number:\n(10) ");
    scanf("%d",&b);
        if(b <= 75068){
            for(i = 0; b > 0; i++){
                tab[i] = b % 2;
                b = b / 2;
            }
            printf("Binary of given number is:\n(2) ");
            for(i;i > 0;i--)
                printf("%d",tab[i-1]);
        }else
            puts("Your number is too high!");
}
int bin_to_dec(long long BIN_ID){
    long int x=0;
    int i,a,n;
	printf("Enter any binary number:\n(2) ");
	scanf("%ld", &n);

    if(n <= BIN_ID){
        for(i = 0; n != 0; ++i){
            a = n % 10;
            if(a != 1 && a != 0){
                puts("It is not binary number!");
                return;
            }
            x = a * (pow(2,i)) + x;
            n = n / 10;
        }
        printf("Decimal of given number is:\n(10) %ld",x);
    }
    else
        puts("Your number is too high!");
}
int main(){
    const int ID = 75068;
    const long long BIN_ID = 10010010100111100;
    int option;

    do{
        printf("\n\nChoose option:\n1.Decimal to binary (10)->(2)\n2.Binary to decimal (2)->(10)\n3.Exit\n\n");
        scanf("%d",&option);
            if(option == 1)
                dec_to_bin(ID);
            else if (option == 2)
                bin_to_dec(BIN_ID);
            else if (option == 3){
                puts("Exit");
                exit(0);
            }
            else
             puts("Wrong number!");

    }while(option != 3);

    return 0;
}
