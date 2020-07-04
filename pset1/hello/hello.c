#include <stdio.h>
#include <cs50.h>

// Write the usual int main void.
int main(void)
{
    // Ask user for their name with cs50's get_string() function.
    string name = get_string("What is your name ?\n");

    // With the the %s identifier representing 'string' the same data type
    // is expected to be passed as a argument to stdio.h's printf() function
    printf("Hello, %s\n", name);

    // Done
    return 0;
}
