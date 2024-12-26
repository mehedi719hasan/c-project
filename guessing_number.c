#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main()
{
    int random, guessing;
    int guees_of_number = 0;
    srand(time(NULL));

    printf("\nWelcome to the world of Guessing numbers\n");
    
    random = (rand() % 100) + 1;//generating a random number.
    
    printf("\nPlease enter youe guessing number between (1 to 100) . ");

    do
    {

        scanf("%d", &guessing);
        guees_of_number++;
        if (guessing < random)
        {
            printf("Guess a large number .\n");
        }
        else if (guessing > random)
        {
            printf("Guess a smaller number . \n");
        }
        else
        {
            printf("\ncongratulatinons you have successfully guess the right number in %d attetm\n", guees_of_number);
        }

    } while (random != guessing);
    printf("\nBye Bye thank you for playing gaming");
    printf("\n Developed by : mehedi hasan");
    return 0;
}