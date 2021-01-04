// Libraries
#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// Function Protoypes
const int ALPHA_LENGTH = 26;
const int ASCII_START = 65;
const int ASCII_END = 90;
int table[ALPHA_LENGTH][3];
int did_pass = 1;
// Sets the table to used.
void set_table(void);

// Evaluates the string from argv[1] and simutaniously adds the keys to the table.
int evaluate_key(string);

// Asks for plain text and returns the cipher text.
int plaintext_cipher(void);

//  Set main to take commandline arguments using argc and set a pointer to argv[]
int main(int argc, char *argv[])
{
//  Set table to be used.
    set_table();

//  If characters are set in argument #2 then true so continue.
    if (argc == 2)
    {
//      Evaulates the string for duplicate chars and special charachters.
        did_pass = evaluate_key(argv[1]);
    }



//  else command was not properly given an argument return 1.
    else
    {
        printf("Usage: ./subsitution key\n");
        return 1;
    }


// TABLE DEBUGGER
// To see as ASCII integers instead of alphanumerics then change the all %c to %i formatters.
//  printf("ASCII: [ \n");
//  for(int i = 0; i < ALPHA_LENGTH; i++)
//  {
//     printf("    [ %i, %i, %i],\n", table[i][0], table[i][1], table[i][2]);
//  }
//  printf("] \n");

//  printf("Normal Chars: [ \n");
//  for(int i = 0; i < ALPHA_LENGTH; i++)
//  {
//     printf("    [ %c, %c, %i],\n", table[i][0], table[i][1], table[i][2]);
//  }
//  printf("] \n");

//  Done
    return did_pass;
}



void set_table(void)
{
//  Looping through with ASCII numbers starting from 65 ending with 90.
    for (int a = ASCII_START * 1, i = 0; a <= ASCII_END; ++a)
    {
        if (i <= 26)
        {
//          table[0] = { 65, 0, 0 }
//          table[1] = { 66, 0, 0 }
            table[i][0] = a;
            table[i][1] = 0;
            table[i][2] = 0;

//          Go up a index when done.
            ++i;
        }
    }
}

int evaluate_key(string key)
{
    int key_length = strlen(key);
    if (key_length == 26)
    {

        for (int i = 0; i < 26; i++)
        {
//          if ASCII number is in range of lowercase ASCII numbers then make it uppercase.
            if (key[i] >= 97 && key[i] <= 122)
            {
//              Uppercase char is always -32 away from its lowecase char and vice versa +32.
                key[i] = key[i] - 32;
            }
//          if ASCII number is in range of uppercase ASCII numbers then continue.
            if (key[i] <= ASCII_END && key[i] >= ASCII_START)
            {
// Debug        printf("Table: %i \n", table[i][0]);
// Debug        printf("Key: %i \n", key[i]);
// Debug        printf("Char: %c\n", table[key[i] - ASCII_START][0]);

//              if that letter has not been used meaning 0, then make it 1 meaning used.
                if (table[key[i] - ASCII_START][2] == 0)
                {
//                  Set the marker to 1 for future iterations.
                    table[key[i] - ASCII_START][2] = 1;

//                  Add that .
                    table[i][1] = key[i];
                    if (i == 25)
                    {
                        return plaintext_cipher();
                    }
                }
//              else that means that the character has been used so stop and return 1.
                else
                {
                    return 1;
                }
            }
//          else that means there is a character that does not belong so stop and return 1.
            else
            {
                return 1;
            }
        }
//      Program is done
        return 0;
    }
//  else that means that the
    else
    {
        printf("Key must contain 26 characters \n");
        return 1;
    }
}


int plaintext_cipher(void)
{
    string plain_text = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plain_text); i++)
    {
        int x = plain_text[i];
        if (x >= 97 && x <= 122)
        {
            // int temp1 = toupper(plain_text[i]);
            printf("%c", (table[(x - 32) - ASCII_START][1] + 32));
        }
        else if (x >= ASCII_START && x <= ASCII_END)
        {
            // int temp2 = toupper(plain_text[i]);
            printf("%c", table[x - ASCII_START][1]);
        }
        else
        {
            printf("%c", plain_text[i]);
        }
    }

    printf("\n");
    did_pass = 0;
    return 0;

}



















