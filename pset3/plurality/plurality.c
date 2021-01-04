#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
            i -= 1;
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    bool canidate_found = false;
    //  DR: Looped through all canidates.
    for (int i = 0; i < candidate_count; i++)
    {
        // DR: If 'strcmp()' returns 0 meaning match is true.
        if (strcmp(name, candidates[i].name) == 0)
        {
            // DR: Add one vote if name was found.
            candidates[i].votes += 1;

            // DR: Return the expected bool value of true.
            canidate_found = true;
        }
    }
    return canidate_found;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // DR: Initilaized a value that dosent change representing the max number of times.
    const int LOOP_MAX = candidate_count - 1;

    // DR: Set pointers to reference directly to a hexadecimal memory location
    int votes;
    string name;

    // DR: Loop through all canidates.
    for (int i = 0, king_number = 0, stage = 1; i < candidate_count; i++)
    {
        // DR: Easier variables to work with through out iterations.
        votes = candidates[i].votes;
        name = candidates[i].name;

        // DR: Stage 1: If the loop is hasnt found the king number yet
        if (stage == 1)
        {
            // If the number of votes is greater than the current king number
            if (king_number < votes)
            {
                // DR: Change the king number to the current votes value.
                king_number = votes;
// Debug
//                printf("%s is now king with votes at %i", *name, *votes);
            }

            // If the loop has iterated every possible canidate's number of votes then set loop to
            // then execute stage 2 @if (done == 0) { ... }
            if (i == LOOP_MAX)
            {
// Debug
//              printf("Stage 1 ran %i times \n king number is: %i \n", i, king_number);
                i = -1;
                stage += 1;
            }
        }

        // Stage 2: If the search for the king number is over or stage is now 2;
        if (stage == 2 && i != -1)
        {
// Debug
//          printf("Running stage 0 \n comparing votes: %i to %i\n", *votes, king_number);

            // Now that the loop has been reset
            // If the canidates number of votes equal the king number then printf their name & \n
            if (votes == king_number)
            {
                // Print out the string data type of winner !
                printf("%s\n", name);
            }
        }
    }
    // TODO
    return;
}
