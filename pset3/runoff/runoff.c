#include <cs50.h>
#include <stdio.h>

// DR: Added string library
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;

    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{

    // printf("voter: %i, rank: %i, name: %s\n", voter, rank, name);

    // What will be returned when done by default
    bool is_valid = false;

    // Will store integervalues returned by strcmp()
    int compare;

    // Iterate through the cadnidates array by the number of max candidates
    for (int i = 0; i < MAX_CANDIDATES; i++)
    {
        // If the value is null, break the loop meaning the array reached the limit of values.
        if (candidates[i].name == NULL)
        {
            // Stop the loop
            break;
        }

        // Compare the given name argument to the value of the property 'name' of each candidate struct in the candidates array
        compare = strcmp(candidates[i].name, name);

        // if strcmp returns 0 meaning a match then set prefrences array to the values it should have and set the return value to true.
        if (compare == 0)
        {
            // Debug preferences value assignments
            // printf("preferences[%i][%i] = %i\n", voter, rank, i);
            // Set prefrences
            preferences[voter][rank] = i;

            // Set return value to true
            is_valid = true;

            // Stop the loop.
            break;
        }

    }

    // TODO
    return is_valid;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Iterate the preferences array and use the int value from the rank index to find that candidate
    // in the candidate array and add to its values. r = rank index
    for (int i = 0, r = 0; i < voter_count; i++)
    {
        // If candidate has been eliminated
        if (candidates[preferences[i][r]].eliminated == true)
        {
            // Debug whos eliminated
            // printf("%s is eliminated...\n", candidates[preferences[i][r]].name);

            // Add one for rank index
            ++r;

            // Set back an iteration
            --i;
        }
        else
        {
            // Debug who gets the vote
            // printf("%s got the vote! \n", candidates[preferences[i][r]].name);

            // Add a vote to the proper candidate.
            candidates[preferences[i][r]].votes += 1;

            // Set back the voter's rank to the first preference
            r = 0;
        }


    }

    // End function execution.
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // Set the default return value to false
    bool winner = false;

    // Iterate the candidates array
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if i'th candidates number of votes is greater than half the amount of voters.
        bool greater_than_half = candidates[i].votes > voter_count / 2;

        // If the i'th candidates number of votes is greater than half
        if (greater_than_half)
        {
            // Election is over winner is allready found
            printf("%s\n", candidates[i].name);

            // Set the return value to true
            winner = true;
        }
    }

    // Returns true or false
    return winner;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = voter_count;

    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            if (candidates[i].votes < min)
            {
                min = candidates[i].votes;
            }
        }
    }

    // End function execution.
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // this variable gets returned no matter what & false by default
    bool if_tie = false;

    // i = index of candidate, mc = min counter, cl = candidates left
    for (int i = 0, mc = 0, cl = 0; i < candidate_count; i++)
    {
        // If candidate hasnt been eliminated then continue
        if (!candidates[i].eliminated)
        {
            // Candidates left plus one
            cl += 1;

            // If the number of the i'th candidate's votes equals the final minmimum provided
            if (candidates[i].votes == min)
            {
                // Minimum count plus one
                mc += 1;
            }
        }

        // When the loop is on its last iteration
        if (i == candidate_count - 1)
        {
            // If the minmimum counter equals the candidates left then there is a tie
            if (mc == cl)
            {
                // Set the return value to true
                if_tie = true;
            }
            // If the above block isnt executed then there is no tie
        }

    }

    // Returns true or false based on the above outcome.
    return if_tie;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    // Iterate candidates array
    for (int i = 0; i < candidate_count; i++)
    {
        // If the i'th candidate's votes equals the given mininum
        if (candidates[i].votes == min)
        {
            // Eliminate that candidate
            candidates[i].eliminated = true;
        }
    }

    // End function execution
    return;
}
