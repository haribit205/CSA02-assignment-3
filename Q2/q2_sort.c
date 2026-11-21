#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    long long comps;
    long long moves; /* swaps or shifts */
} Metrics;

Metrics bubble_sort(int a[], int n) {
    Metrics m = {0, 0};
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            m.comps++;
            if (a[j] > a[j + 1]) {
                int tmp = a[j]; a[j] = a[j + 1]; a[j + 1] = tmp;
                m.moves += 3; /* 3 element assignments per swap */
                swapped = 1;
            }
        }
        if (!swapped) break; /* early-exit optimization */
    }
    return m;
}

Metrics selection_sort(int a[], int n) {
    Metrics m = {0, 0};
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            m.comps++;
            if (a[j] < a[min_idx]) min_idx = j;
        }
        if (min_idx != i) {
            int tmp = a[i]; a[i] = a[min_idx]; a[min_idx] = tmp;
            m.moves += 3;
        }
    }
    return m;
}

Metrics insertion_sort(int a[], int n) {
    Metrics m = {0, 0};
    for (int i = 1; i < n; i++) {
        int key = a[i];
        m.moves++;
        int j = i - 1;
        while (j >= 0) {
            m.comps++;
            if (a[j] > key) {
                a[j + 1] = a[j];
                m.moves++;
                j--;
            } else {
                break;
            }
        }
        a[j + 1] = key;
        m.moves++;
    }
    return m;
}

void fill_order(int base[], int n, int mode) {
    for (int i = 0; i < n; i++) base[i] = 260001 + i;
    if (mode == 0) return; /* Sorted */
    if (mode == 1) {       /* Nearly sorted: 5% late entries swapped near end */
        int k = (n >= 400) ? 20 : (n / 20 + 1);
        for (int i = n - k; i < n; i++) {
            int pos = (i * 7) % n;
            int t = base[i]; base[i] = base[pos]; base[pos] = t;
        }
    } else if (mode == 2) { /* Reverse sorted */
        for (int i = 0; i < n; i++) base[i] = 260000 + n - i;
    } else {                /* Random (deterministic LCG) */
        unsigned int seed = 42u;
        for (int i = n - 1; i > 0; i--) {
            seed = seed * 1664525u + 1013904223u;
            int j = (int)(seed % (unsigned int)(i + 1));
            int t = base[i]; base[i] = base[j]; base[j] = t;
        }
    }
}

int main(void) {
    printf("=== Q2 Sorting Comparison: Comparisons & Moves across n = 100, 1000, 10000 ===\n");
    int sizes[] = {100, 1000, 10000};
    const char *modes[] = {"Sorted", "NearlySorted", "Reverse", "Random"};
    for (int s = 0; s < 3; s++) {
        int n = sizes[s];
        int *base = malloc((size_t)n * sizeof(int));
        int *work = malloc((size_t)n * sizeof(int));
        for (int mode = 0; mode < 4; mode++) {
            fill_order(base, n, mode);
            memcpy(work, base, (size_t)n * sizeof(int));
            Metrics mb = bubble_sort(work, n);
            memcpy(work, base, (size_t)n * sizeof(int));
            Metrics ms = selection_sort(work, n);
            memcpy(work, base, (size_t)n * sizeof(int));
            Metrics mi = insertion_sort(work, n);
            printf("n=%5d | %-12s | Bub(C=%8lld,M=%8lld) | Sel(C=%8lld,M=%6lld) | Ins(C=%8lld,M=%8lld)\n",
                   n, modes[mode], mb.comps, mb.moves, ms.comps, ms.moves, mi.comps, mi.moves);
        }
        free(base); free(work);
    }
    return 0;
}
