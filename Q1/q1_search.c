#include <stdio.h>
#include <stdlib.h>

int steps;    /* comparisons made by the last search */

/* a[] is sorted in ascending order. Returns the index of key, or -1. */
int binary_search(const int a[], int n, int key)
{
    steps = 0;
    /* TODO 1: Overflow-safe binary search counting every comparison */
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        steps++;
        if (a[mid] == key) {
            return mid;
        } else if (a[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int linear_search(const int a[], int n, int key)
{
    steps = 0;
    for (int i = 0; i < n; i++) {
        steps++;
        if (a[i] == key) return i;
    }
    return -1;
}

int main(void)
{
    printf("=== Q1 Complete-the-Code: Trial Catalogue (n = 10) ===\n");
    int accession[] = {1021, 1048, 1103, 1190, 1222, 1305, 1377, 1402, 1460, 1533};
    int n = sizeof accession / sizeof accession[0];
    int keys[] = {1021, 1305, 1533, 1400};
    for (int k = 0; k < 4; k++) {
        int pos = binary_search(accession, n, keys[k]);
        printf("Book %d -> index %d, comparisons = %d\n", keys[k], pos, steps);
    }

    printf("\n=== Q1 Student B Scale Experiment: n = 1,000 | 10,000 | 100,000 ===\n");
    int sizes[] = {1000, 10000, 100000};
    for (int s = 0; s < 3; s++) {
        int sz = sizes[s];
        int *arr = malloc((size_t)sz * sizeof(int));
        for (int i = 0; i < sz; i++) arr[i] = 10000 + i * 2; /* sorted even IDs */

        long lin_succ = 0, bin_succ = 0;
        for (int t = 0; t < 200; t++) {
            int target = arr[(t * (sz / 200)) % sz];
            linear_search(arr, sz, target); lin_succ += steps;
            binary_search(arr, sz, target); bin_succ += steps;
        }
        linear_search(arr, sz, 999999); int lin_miss = steps;
        binary_search(arr, sz, 999999); int bin_miss = steps;

        printf("n=%6d | Linear avg_hit=%7.1f, miss=%6d | Binary avg_hit=%5.2f, miss=%2d\n",
               sz, lin_succ / 200.0, lin_miss, bin_succ / 200.0, bin_miss);
        free(arr);
    }
    return 0;
}
