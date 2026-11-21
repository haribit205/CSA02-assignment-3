#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 30

int strcasecmp_custom(const char *a, const char *b) {
    while (*a && *b) {
        int ca = tolower((unsigned char)*a);
        int cb = tolower((unsigned char)*b);
        if (ca != cb) return ca - cb;
        a++; b++;
    }
    return tolower((unsigned char)*a) - tolower((unsigned char)*b);
}

int main(void) {
    printf("=== Q6 String Directory: Direct strcpy Sort vs. Index Array Sort ===\n");
    int sizes[] = {100, 500, 5000};
    for (int s = 0; s < 3; s++) {
        int n = sizes[s];
        char (*names1)[MAX_LEN] = malloc((size_t)n * MAX_LEN);
        char (*names2)[MAX_LEN] = malloc((size_t)n * MAX_LEN);
        int *idx = malloc((size_t)n * sizeof(int));

        unsigned int seed = 12345u;
        for (int i = 0; i < n; i++) {
            seed = seed * 1664525u + 1013904223u;
            snprintf(names1[i], MAX_LEN, "Student_%04u_HostelBlock_%c",
                     seed % 9999u, 'A' + (i % 4));
            strcpy(names2[i], names1[i]);
            idx[i] = i;
        }

        /* 1. Insertion sort moving 30-byte char rows via strcpy */
        long long comps1 = 0, char_bytes1 = 0;
        for (int i = 1; i < n; i++) {
            char key[MAX_LEN];
            strcpy(key, names1[i]);
            char_bytes1 += MAX_LEN;
            int j = i - 1;
            while (j >= 0) {
                comps1++;
                if (strcmp(names1[j], key) > 0) {
                    strcpy(names1[j + 1], names1[j]);
                    char_bytes1 += MAX_LEN;
                    j--;
                } else break;
            }
            strcpy(names1[j + 1], key);
            char_bytes1 += MAX_LEN;
        }

        /* 2. Insertion sort moving 4-byte integer indices only */
        long long comps2 = 0, idx_bytes2 = 0;
        for (int i = 1; i < n; i++) {
            int key_idx = idx[i];
            idx_bytes2 += sizeof(int);
            int j = i - 1;
            while (j >= 0) {
                comps2++;
                if (strcmp(names2[idx[j]], names2[key_idx]) > 0) {
                    idx[j + 1] = idx[j];
                    idx_bytes2 += sizeof(int);
                    j--;
                } else break;
            }
            idx[j + 1] = key_idx;
            idx_bytes2 += sizeof(int);
        }

        printf("n=%4d | Direct strcpy: comps=%8lld, bytes=%9lld | Index sort: comps=%8lld, bytes=%8lld (%.1fx less data moved)\n",
               n, comps1, char_bytes1, comps2, idx_bytes2, (double)char_bytes1 / idx_bytes2);
        free(names1); free(names2); free(idx);
    }

    printf("\n=== Q6 Duplicate Detection, Case Ordering & 29/30-Char Boundary Test ===\n");
    char dir[6][MAX_LEN] = {
        "Apple", "Arjun Kumar", "Arjun Kumar", "Hariharasudhan", "apple",
        "12345678901234567890123456789" /* 29 chars + '\0' = 30 bytes */
    };
    /* Sort dir */
    for (int i = 1; i < 6; i++) {
        char tmp[MAX_LEN]; strcpy(tmp, dir[i]);
        int j = i - 1;
        while (j >= 0 && strcmp(dir[j], tmp) > 0) {
            strcpy(dir[j + 1], dir[j]); j--;
        }
        strcpy(dir[j + 1], tmp);
    }
    printf("ASCII Order ('Apple' < 'apple' because 'A'=65 < 'a'=97): ");
    for (int i = 0; i < 6; i++) printf("[%s] ", dir[i]);
    printf("\nDuplicates found: ");
    for (int i = 1; i < 6; i++) {
        if (strcmp(dir[i], dir[i - 1]) == 0) printf("\"%s\" ", dir[i]);
    }
    /* Binary search for present and missing name */
    int low = 0, high = 5, bsteps = 0, found = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        bsteps++;
        int cmp = strcmp(dir[mid], "Hariharasudhan");
        if (cmp == 0) { found = mid; break; }
        else if (cmp < 0) low = mid + 1;
        else high = mid - 1;
    }
    printf("\nBinary search \"Hariharasudhan\" -> idx=%d (%d comps) | 29-char len=%zu (30th char truncated by fgets(30))\n",
           found, bsteps, strlen("12345678901234567890123456789"));
    return 0;
}
