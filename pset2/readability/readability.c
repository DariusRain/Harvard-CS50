#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// These variables will determine the output of the entire program
float number_of_letters = 0, number_of_words = 0, number_of_sentences = 0;

// This function will contribute to adding values to the variables above
void analyze_text(string);

// This function will perform the algorithm and return a grade
void liau_alg(void);

int main(void)
{
//  Ask for text
    string input_sentences = get_string("Text:");

//  After the input is done this function will start the process of counting and assigning to global variables.
    analyze_text(input_sentences);

    // Debug
    // printf("l:%i\nw:%i\ns:%i\n", number_of_letters, number_of_words, number_of_sentences);


//  After the number_of_x variables have gotten their assigned values then this is ready.
    liau_alg();

//  Done
    return 0;
}

// Handles the logic of sorting the string
void analyze_text(string text)
{
// These variables will never change and represent the chars that end a sentence.
    const char QUESTION_MARK = '?', EXCL_POINT = '!', PERIOD = '.';

//  Loop through the entires string variable text
    for (int i = 0, string_length = strlen(text); i < string_length; i++)
    {
//      If it has a space and the the next char isnt a space then add
        if (isspace(text[i]) && !isspace(text[i + 1]))
        {
            ++number_of_words;
        }
//      Else if it is a a letter and not a number
        else if (isalpha(text[i]) && !isdigit(text[i]))
        {
//          if this is the first round of the loop then that means add a word becuase there was no space
            if (i == 0)
            {
                ++number_of_words;
            }
            ++number_of_letters;
        }
//      else if the char equals to any of the sentence enders above.
        else if (text[i] == QUESTION_MARK || text[i] == EXCL_POINT || text[i] == PERIOD)
        {

            ++number_of_sentences;
        }

    }
}

// Handles the algorithm and return of grade
void liau_alg(void)
{
//  Perform the formula provided by Harvard Cs50 and make sure that everything being calculated is a float due to errors happening becuase of presiscion.
    float liau = 0.0588 * (100 * number_of_letters / number_of_words) - 0.296 * (100 * number_of_sentences / number_of_words) - 15.8;

//  After the operation is finished above this variable will take in the rounded float
    float grade_to_round = round(liau);

//  Unsure if this was necessary was having trouble with values and format specifiers but this will make sure it is a whole number when outputted
    int grade = grade_to_round;
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}







