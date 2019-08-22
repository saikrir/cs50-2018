#include <stdio.h>
#include <cs50.h>

int get_user_input();
void printPyramid(int layers);

int main(void)
{
    int userInput = get_user_input();
    printPyramid(userInput);
    return 0;
}

void printPyramid(int layers)
{
    for (int i = 1; i <= layers; i++)
    {
        for (int j = layers; j >= i; j--)
        {
            printf(" ");
        }
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}

int get_user_input()
{
    int userInput = 0;
    do
    {
        userInput = get_int("Please enter a positive number less than 23: ");
    } while (userInput < 0 || userInput > 23);
    return userInput;
}
