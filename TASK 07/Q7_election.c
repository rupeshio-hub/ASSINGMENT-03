#include <stdio.h>

#define MAX_CANDIDATES 12
#define MAX_VOTES 500000

typedef struct {
    int candidate;
    int votes;
} Result;

void sort_results(Result results[], int n) {
    /* Insertion sort in descending vote order. */
    for (int i = 1; i < n; i++) {
        Result key = results[i];
        int j = i - 1;
        while (j >= 0 && results[j].votes < key.votes) {
            results[j + 1] = results[j];
            j--;
        }
        results[j + 1] = key;
    }
}

int main(void) {
    int candidates, vote_count;
    int counts[MAX_CANDIDATES + 1] = {0};
    int valid = 0, invalid = 0;
    int votes[MAX_VOTES];
    Result results[MAX_CANDIDATES];

    printf("Number of candidates (1-%d): ", MAX_CANDIDATES);
    if (scanf("%d", &candidates) != 1 ||
        candidates < 1 || candidates > MAX_CANDIDATES) {
        printf("Invalid candidate count.\n");
        return 1;
    }

    printf("Number of votes (0-%d): ", MAX_VOTES);
    if (scanf("%d", &vote_count) != 1 ||
        vote_count < 0 || vote_count > MAX_VOTES) {
        printf("Invalid vote count.\n");
        return 1;
    }

    printf("Enter candidate number for each vote:\n");
    for (int i = 0; i < vote_count; i++) {
        if (scanf("%d", &votes[i]) != 1) {
            printf("Invalid input.\n");
            return 1;
        }
        if (votes[i] >= 1 && votes[i] <= candidates) {
            counts[votes[i]]++;
            valid++;
        } else {
            invalid++;
        }
    }

    for (int i = 0; i < candidates; i++) {
        results[i].candidate = i + 1;
        results[i].votes = counts[i + 1];
    }
    sort_results(results, candidates);

    printf("\nValid votes: %d\nInvalid votes: %d\n", valid, invalid);
    printf("Candidate totals (descending):\n");
    for (int i = 0; i < candidates; i++)
        printf("Candidate %d: %d\n", results[i].candidate, results[i].votes);

    if (results[0].votes == 0) {
        printf("No winner: no valid votes were recorded.\n");
    } else if (candidates > 1 && results[0].votes == results[1].votes) {
        printf("Tie for first place.\n");
    } else {
        printf("Winner: Candidate %d with %d votes.\n",
               results[0].candidate, results[0].votes);
    }
    return 0;
}
