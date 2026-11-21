#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DISTRICTS 3
#define MONTHS 4

void district_totals(const double rain[][MONTHS], int d, double totals[]) {
    for (int i = 0; i < d; i++) {
        double sum = 0.0;
        for (int j = 0; j < MONTHS; j++) sum += rain[i][j];
        totals[i] = sum;
    }
}

void monthly_averages(const double rain[][MONTHS], int d, double avgs[]) {
    for (int j = 0; j < MONTHS; j++) {
        double sum = 0.0;
        for (int i = 0; i < d; i++) sum += rain[i][j];
        avgs[j] = sum / d;
    }
}

void wettest_cell(const double rain[][MONTHS], int d, int *best_d, int *best_m, double *max_val) {
    *best_d = 0; *best_m = 0; *max_val = rain[0][0];
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < MONTHS; j++) {
            if (rain[i][j] > *max_val) {
                *max_val = rain[i][j];
                *best_d = i;
                *best_m = j;
            }
        }
    }
}

int main(void) {
    printf("=== Q4 Hand-Verified 3x4 District Rainfall Analysis ===\n");
    double rain[DISTRICTS][MONTHS] = {
        {120.0, 180.0, 200.0, 100.0}, /* District 0: Total = 600.0 mm */
        { 40.0,  60.0,  50.0,  50.0}, /* District 1: Total = 200.0 mm (Deficient!) */
        {140.0, 210.0, 250.0, 150.0}  /* District 2: Total = 750.0 mm (Wettest D2,M2=250) */
    };
    double totals[DISTRICTS], avgs[MONTHS], max_val;
    int bd, bm;

    district_totals(rain, DISTRICTS, totals);
    monthly_averages(rain, DISTRICTS, avgs);
    wettest_cell(rain, DISTRICTS, &bd, &bm, &max_val);

    double state_avg_annual = 0.0;
    for (int i = 0; i < DISTRICTS; i++) {
        printf("District %d Annual Total = %.1f mm\n", i, totals[i]);
        state_avg_annual += totals[i];
    }
    state_avg_annual /= DISTRICTS;

    printf("Monthly State Averages  : ");
    for (int j = 0; j < MONTHS; j++) printf("M%d=%.1f ", j, avgs[j]);
    printf("\nWettest District-Month  : District %d, Month %d (%.1f mm)\n", bd, bm, max_val);
    printf("State Annual Mean = %.2f mm | 60%% Threshold = %.2f mm\n",
           state_avg_annual, 0.60 * state_avg_annual);
    for (int i = 0; i < DISTRICTS; i++) {
        if (totals[i] < 0.60 * state_avg_annual) {
            printf("Deficient District      : District %d (%.1f mm < %.2f mm)\n",
                   i, totals[i], 0.60 * state_avg_annual);
        }
    }

    printf("\n=== Q4 Cache Locality Benchmark: 2000 x 2000 Matrix (20 passes) ===\n");
    const int N = 2000;
    double (*mat)[2000] = malloc(sizeof(double[2000][2000]));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            mat[i][j] = 1.0;

    volatile double sink = 0.0;
    clock_t t0 = clock();
    for (int rep = 0; rep < 20; rep++)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                sink += mat[i][j];
    clock_t t1 = clock();

    for (int rep = 0; rep < 20; rep++)
        for (int j = 0; j < N; j++)
            for (int i = 0; i < N; i++)
                sink += mat[i][j];
    clock_t t2 = clock();

    double row_ms = 1000.0 * (double)(t1 - t0) / CLOCKS_PER_SEC;
    double col_ms = 1000.0 * (double)(t2 - t1) / CLOCKS_PER_SEC;
    printf("Row-wise traversal    : %.2f ms\n", row_ms);
    printf("Column-wise traversal : %.2f ms (%.2fx slower due to L1/L2 cache misses)\n",
           col_ms, col_ms / (row_ms > 0.01 ? row_ms : 0.01));
    free(mat);
    return 0;
}
