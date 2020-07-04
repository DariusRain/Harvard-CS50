#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Create a function that takes a number a whole number paramater representing dollars that are converted cents after rmultiplying the input by 100 -> See ask_for_cash
void check_coins(int);

// Create a recursive function that only accepts positive inputs and returns a converted value of dollars to cents.
int ask_for_cash()
{

    // Prompt for input first every time this function is called.
    float dollars = get_float("Changed owed:");

    // Check if the number is even positive
    if (dollars > -1)
    {
        return round(dollars * 100);
    }

    // Calls itself again if the above is untrue and repeat this process until so.
    else
    {
        return ask_for_cash();
    }
}

int main()
{
    // This will call the recursive function above.
    float cash = ask_for_cash();

    // After the ask for cash function returns a value of dollars in cents
    // add that value to the check coins function where it will perform the greedy algorithm.
    check_coins(cash);

    // Done
    return 0;

}

void check_coins(int dollars)
{

    // Create an array and assign it the values of pennies, nickels, dimes and quartes as whole numbers becuase
    // one, I want a whole number as the returned value and 2, the dollars param is allready coverted to cents so the math wouldnt be correct
    int coins[] = {25, 10, 5, 1};

    // This variable will add the divided values
    int change_owed = 0;

    for (int i = 0; i <= 3; i++)
    {

        // This will value out to the number of coins that the dollars parameter is divisible by
        int value = dollars / coins[i];

        // This checks if the value can be divided by the value of the current coin in iteration.
        if (value > 0)
        {

            // Subtract the number of coins in cents from dollars by multiplying the number of coins by the value of coin.
            dollars -= value * coins[i];
            // And add the number of coins used in this iteration
            change_owed += value;

        }

    }
    // After the loop has iterated from coin increments of 25 to 1, the change_owed varabiable should have collected how many coins were used along the way.
    printf("%i\n", change_owed);
}