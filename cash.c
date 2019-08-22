#include <stdio.h>
#include <cs50.h>
#include <math.h>

int get_user_input();
int get_num_coins(int amt);

int main(int argc, char const *argv[])
{
    float amt = get_user_input();
    printf("Num Coins %i \n", get_num_coins(amt));
    return 0;
}

int get_num_coins(int amt)
{
    int num_coins = 0;
    int num25Coins = 0;
    int num10Coints = 0;
    int num5Coins = 0;
    if (amt >= 25)
    {
        num25Coins += (amt / 25);
        amt = amt % 25;
        printf(" 25 Cents X %i \n", num25Coins);
    }
    if (amt >= 10)
    {
        num10Coints += (amt / 10);
        amt = amt % 10;
        printf(" 10 Cents X %d \n", num10Coints);
    }
    if (amt >= 5)
    {
        num5Coins += (amt / 5);
        amt = amt % 5;
        printf(" 5 Cents X %i \n", num5Coins);
    }

    printf(" 1 Cents X %i \n", amt);

    num_coins = num25Coins + num10Coints + num5Coins + amt;

    return num_coins;
}

int get_user_input()
{
    float ret_val = 0;
    do
    {
        ret_val = get_float("Please enter an amount: ");
    } while (ret_val < 0.0);
    return ret_val * 100;
}