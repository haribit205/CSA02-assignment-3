#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CANDIDATES 12

typedef struct {
    int id;
    long votes;
} CandidateResult;

void run_election(const int ballots[], long num_ballots, int num_cands, int verbose) {
    long counts[MAX_CANDIDATES + 1] = {0}; /* 1-indexed: 1..num_cands */
    long valid = 0, invalid = 0;

    /* Stage 2: Single O(v) pass with frequency count array */
    for (long i = 0; i < num_ballots; i++) {
        int v = ballots[i];
        if (v >= 1 && v <= num_cands) {
            counts[v]++;
            valid++;
        } else {
            invalid++;
        }
    }

    CandidateResult res[MAX_CANDIDATES];
    for (int c = 0; c < num_cands; c++) {
        res[c].id = c + 1;
        res[c].votes = counts[c + 1];
    }

    /* Sort candidates in descending order of votes (stable insertion sort) */
    for (int i = 1; i < num_cands; i++) {
        CandidateResult key = res[i];
        int j = i - 1;
        while (j >= 0 && res[j].votes < key.votes) {
            res[j + 1] = res[j];
            j--;
        }
        res[j + 1] = key;
    }

    if (verbose) {
        printf("Total Ballots = %ld | Valid = %ld | Invalid = %ld\n", num_ballots, valid, invalid);
        for (int c = 0; c < num_cands; c++) {
            double pct = (valid > 0) ? (100.0 * res[c].votes / valid) : 0.0;
            printf("  Rank %d: Candidate #%d -> %ld votes (%.1f%%)\n",
                   c + 1, res[c].id, res[c].votes, pct);
        }
        if (valid == 0) {
            printf("Result: NO VALID VOTES CAST\n");
        } else if (num_cands > 1 && res[0].votes == res[1].votes) {
            int tied = 1;
            while (tied < num_cands && res[tied].votes == res[0].votes) tied++;
            printf("Result: TIE between %d candidates with %ld votes each!\n", tied, res[0].votes);
        } else {
            printf("Result: WINNER is Candidate #%d with %ld votes\n", res[0].id, res[0].votes);
        }
    }
}

int main(void) {
    printf("=== Q7 Hand-Verified Small Election with Invalid Ballots & Tie ===\n");
    int sample_ballots[] = {2, 1, 2, 0, 3, 1, -1, 5, 2, 1}; /* 4 candidates: C1=3, C2=3, C3=1, C4=0, Invalid=3 */
    run_election(sample_ballots, 10, 4, 1);

    printf("\n=== Q7 Performance Benchmark: v = 5,000 vs. v = 500,000 Votes ===\n");
    long scales[] = {5000L, 500000L};
    for (int s = 0; s < 2; s++) {
        long v = scales[s];
        int *ballots = malloc((size_t)v * sizeof(int));
        for (long i = 0; i < v; i++) ballots[i] = (int)((i % 14)); /* includes 0 and 13 as invalid */
        clock_t t0 = clock();
        for (int rep = 0; rep < 50; rep++) run_election(ballots, v, 12, 0);
        clock_t t1 = clock();
        double avg_ms = (1000.0 * (double)(t1 - t0) / CLOCKS_PER_SEC) / 50.0;
        printf("v = %6ld votes, c = 12 candidates -> Avg O(v) Counting Time = %.4f ms\n", v, avg_ms);
        free(ballots);
    }
    return 0;
}
