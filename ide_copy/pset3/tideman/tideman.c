#include <cs50.h>
#include <string.h>
#include <stdio.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

// User - defined helper functions
bool valid(int start);
bool has_cycle(int start, bool visitor[]);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");


    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    int i;
    for (i = 0; i < candidate_count; i++)
    {
        if (!strcmp(candidates[i], name))
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    int i, j;
    for (i = 0; i < candidate_count; i++)
    {
        for (j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    int i, j;
    pair_count = 0;
    for (i = 0; i < candidate_count; i++)
    {
        for (j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    int i, j;
    pair temp;
    for (i = 0; i < pair_count - 1; i++)
    {
        for (j = 0; j < pair_count - i - 1; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[j + 1].winner][pairs[j + 1].loser])
            {
                temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }

        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        //assume there are no cycles and set locked to true
        locked[pairs[i].winner][pairs[i].loser] = true;

        //check if the assumption is true or false
        //i.e. if valid continue with next iteration

        //else revert lock that was set!
        if (!valid(pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
    return;
}

//initiates call to has_cycle
//true if no cycles found
//false if cycles found
bool valid(int start)
{
    bool visitor[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        visitor[i] = false;
    }
    if (has_cycle(start, visitor))
    {
        return false;
    }
    return true;
}

//function which traverse each and every path until it finds cycle
//if a candidate is already visited then visitor[candidate] = true
bool has_cycle(int start, bool visitor[])
{
    if (visitor[start] == true)
    {
        //returns true only if visitor[candidate] is already met
        return true;
    }
    visitor[start] = true;
    for (int i = 0; i < candidate_count; i++)
    {
        //if we have lock [start -> i :: true]
        //then we recursively traverse through i -> all locks
        if (locked[start][i] && (has_cycle(i, visitor)))
        {
            return true;
        }
    }
    //if no closed cycles were found return false
    return false;

}

// Print the winner of the election
void print_winner(void)
{
    int i, j, flag;
    for (j = 0; j < candidate_count; j++)
    {
        flag = 1;
        for (i = 0; i < candidate_count; i++)
        {
            if (locked[i][j] != false)
            {
                flag = 0;
                break;
            }
        }
        if (flag == 1)
        {
            printf("%s\n", candidates[j]);
            break;
        }
    }
    // TODO
    return;
}