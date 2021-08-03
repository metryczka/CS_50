#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

bool visited[MAX][MAX];

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
void swap(int* a, int* b);
void selectionSort(int arr[], int n);
bool checking (int j);
bool checking2 (int j);


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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank]= i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 1+i; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]=preferences[ranks[i]][ranks[j]]+1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++ )
    {
        for (int j = 0;  j < candidate_count; j++)
        {
            if (preferences[i][j]>preferences[j][i])
            {
                pairs[pair_count].winner= i;
                pairs[pair_count].loser= j;
                pair_count = pair_count + 1;
            }
        }
    }
    return;
}
//function for swaping
void swap(int* a, int* b)
{
    int remember = *a;
    *a = *b;
    *b = remember;
}
//function for selection sort of an array
void selectionSort(int arr[], int n)
{
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n - 1; i++)
    {

        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        // Swap the found minimum element
        // with the first element
        swap(&arr[min_idx], &arr[i]);
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int difference[pair_count];
    pair pairs_sorted[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        difference[i] = preferences[pairs[i].winner] - preferences[pairs[i].loser];
    }

    selectionSort(difference, pair_count);

    for (int j = 0; j < pair_count; j++)
    {
        for (int n = 0; n< pair_count; n++ )
        {
            if (difference[j] == preferences[pairs[n].winner] - preferences[pairs[n].loser])
            {
            pairs_sorted[j] = pairs[n];
            pairs[n] = pairs [j];
            pairs[j] = pairs_sorted[j];
            n = pair_count;
            }
        }


    }


    return;
}

bool checking (int j)

{
    for (int i = 0; i < candidate_count; i++)
    {
        if (visited[i][j] && locked[i][j]==0)
        {
            return false;
        }

    }

    return true;
}

bool checking2 (int j)

{
    for (int i = 0; i < candidate_count; i++)
    {
        if (visited[i][j])
        {
            return false;
        }

    }

    return true;
}



// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int n = 0; n < candidate_count; n++)
    {
        for(int j = 0; j < candidate_count; j++)
        {
            visited[n][j]=false;
        }

    }

    for (int i = 0; i < pair_count; i++)
    {
        if (checking(pairs[i].loser) || checking2(pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser]= true;
            visited[pairs[i].loser][pairs[i].winner]=true;
            visited[pairs[i].winner][pairs[i].loser]=true;
        }
    }

   // for (int k = 0; k < candidate_count; k++)
    //{
      //  for (int l = 0; l < candidate_count; l++ )
        //{
          //  printf("locked %i ", locked [k][l]);
        //}
        //printf("\n");
    //}

    //for (int k = 0; k < candidate_count; k++)
    //{
      //for (int l = 0; l < candidate_count; l++ )
        //{
          //  printf("check %i ", visited [k][l]);
        //}
        //printf("\n");
    //}

    return;
}


// Print the winner of the election
void print_winner(void)
{
    int suma [candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked [i][j]== true)
            suma [j] = suma[j]+1;
        }

    }
    for (int n = 0; n < candidate_count; n++)
    {
        if (suma [n] == 0)
        {
            printf("%s\n", candidates[n]);
        }
    }


    return;
}

