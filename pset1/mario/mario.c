// 0. Included the libraries
#include <stdio.h>
#include <cs50.h>

// Create a function that will execute inside the for loop based on the height and the value of iteration
void spacesAndHashes(int, int);

// Create a recursive function that asks for height.
int askForHeight(void);

//  1. Write the usual int main void
int main(void)
{
    int height = askForHeight();
    for (int i = 0; i < height; ++i)
    {
        spacesAndHashes(height - i,  i + 1);
    }
    return 0;
}


//  2. Below main:
int askForHeight(void)
{
    // Ask for height
    int height = get_int("Height:");

//  4. Inside function, create an if statement that checks if height is less than eight and greater than -1
    if (height <= 8 && height > 0)
    {

        return height;

    }
    else
    {

        //  5. Else return height recursively, if the above 'if' statement renders false.
        return askForHeight();

    }
}


// 3. Below main:
void spacesAndHashes(int numberOfSpaces, int numberOfHashes)
{
    //  Print the number of spaces starting from one to make it one less so when there is one space at the end of which
    // shouldnt be outputted scince it is always all hashes.
    for (int i = 1; i < numberOfSpaces; i++)
    {
        printf(" ");
    }

    //  Print the number of hashes in a similar way but start from zero becuase all hashes are going to be
    // outputted regardless of what happens.
    for (int i = 0; i < numberOfHashes; i++)
    {
        printf("#");
    }
    // Print new line for row
    printf("\n");
}
