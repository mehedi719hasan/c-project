#include <stdio.h>
#include <math.h>

void Addition(int, int);
void Subtraction(int, int);
void Multiplication(int, int);
void Division(int, int);
void Modulus(int, int);
void po_w(int, int);
void squareroot(double  value);

int main()
{
    int first_value, Second_value;
    double value;

    int choice;
    do
    {
        printf("-------------------------------------------\n");
        printf("Welcome to my new calculator project\n\n");
        printf("choose one of the following Option : \n");
        printf("1.  Addition\n");
        printf("2.  Subtraction\n");
        printf("3.  Multiplication\n");
        printf("4.  Division\n");
        printf("5.  Modulus\n");
        printf("6.  pow\n");
        printf("7.  squareroot\n");
        printf("8.  Exit\n");

        printf("Now, enter your coices: ");

        scanf("%d", &choice);
        if (choice >= 1 && choice <= 6)
        {
            printf("Enter your first value: ");
            scanf("%d", &first_value);
            printf("Enter your Second value: ");
            scanf("%d", &Second_value);
        }
        if(choice==7){
            printf("Enter your value for squreroot :");
            scanf("%lf",&value);
        }

        switch (choice)
        {
        case 1:
        {

            Addition(first_value, Second_value);
            break;
        }
        case 2:
        {
            Subtraction(first_value, Second_value);
            break;
        }
        case 3:
        {

            Multiplication(first_value, Second_value);
            break;
        }
        case 4:
        {

            Division(first_value, Second_value);
            break;
        }
        case 5:
        {

            Modulus(first_value, Second_value);
            break;
        }
        case 6:
        {

            po_w(first_value, Second_value);
            break;
        }
        case 7:

        {
            squareroot(value);
            break;
        }
        case 8:
        {
            printf("Logging out.\n");
            break;
        }
        default:
        {
            printf("Invalid choice.\n");
        }
        }

    } while (choice != 8);

    printf("Successfully you terminate the code:\n");

    return 0;
}

void Addition(int first_value, int Second_value)
{

    int sum = first_value + Second_value;
    printf("sum is : %d\n", sum);
}
void Subtraction(int first_value, int Second_value)
{

    int sub = first_value - Second_value;
    printf("subtraction is : %d\n", sub);
}
void Multiplication(int first_value, int Second_value)
{
    long long int mul = first_value * Second_value;
    printf("Multliplication is : %lld\n", mul);
}

void Division(int first_value, int Second_value)
{
    if (Second_value == 0)
    {
        printf("Error ! Division by 0 is not Allow.\n");
    }
    else
    {
        double Div = (double)first_value / Second_value;
        printf("Division is : %.2lf\n", Div);
    }
}
void Modulus(int first_value, int Second_value)
{
    if (Second_value == 0)
    {
        printf("Error ! Division by 0 is not Allow.\n");
    }
    else
    {
        int modu_lus = first_value % Second_value;
        printf("Modulus is : %d\n", modu_lus);
    }
}
void po_w(int first_value, int Second_value)
{
    long long int power = (long long)pow(first_value, Second_value);
    printf("Pow is : %lld\n", power);
}
void squareroot(double  value){
    if(value<0){
        printf("Error! Negative number does not have a real square root.\n");
    }else{
          printf("Square Root is : %.2f\n", sqrt(value));
    }
}
