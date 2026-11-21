[README.md](https://github.com/user-attachments/files/35210352/README.md)
# CSA02 – C Programming (Assignment 3 – CO3)

- **Student Name:** U. Hariharasudhan
- **Register Number:** 1912260036
- **Course:** CSA02 – C Programming (CO3: Searching, Sorting, Merging, 2D Arrays & Strings)
- **Compiler & Version:** `gcc (Debian 12.2.0-14+deb12u1) 12.2.0`
- **Compilation Command:** `gcc -Wall -Wextra -std=c11 <source.c> -o <executable>`

## Repository Structure & Execution Results

### Task01: Q1 – Searching a Library Catalogue (Linear vs. Overflow-Safe Binary Search)
- **Compile & Run:** `cd Task01 && gcc -Wall -Wextra -std=c11 q1_search.c -o q1_search && ./q1_search`
- **Files:** `q1_search.c`, `q1_search_output.png`, `q1_search_output.txt`
- **Result Summary:** Trial n=10 matches expected output; 100k scale test confirms ~16 avg / 17 max comparisons.

### Task02: Q2 – Sorting Examination Hall Seating Register (Bubble, Selection, Insertion)
- **Compile & Run:** `cd Task02 && gcc -Wall -Wextra -std=c11 q2_sort.c -o q2_sort && ./q2_sort`
- **Files:** `q2_sort.c`, `q2_sort_output.png`, `q2_sort_output.txt`
- **Result Summary:** Insertion sort wins nearly-sorted data (12,191 vs 1.2M bubble comps at n=10,000).

### Task03: Q3 – Merging Two Descending Merit Lists
- **Compile & Run:** `cd Task03 && gcc -Wall -Wextra -std=c11 q3_merge.c -o q3_merge && ./q3_merge`
- **Files:** `q3_merge.c`, `q3_merge_output.png`, `q3_merge_output.txt`
- **Result Summary:** Matches expected descending output; handles empty lists in 0 comps and preserves tie order.

### Task04: Q4 – 2D District Rainfall Records & Row-Major Cache Benchmark
- **Compile & Run:** `cd Task04 && gcc -Wall -Wextra -std=c11 q4_rain.c -o q4_rain && ./q4_rain`
- **Files:** `q4_rain.c`, `q4_rain_output.png`, `q4_rain_output.txt`
- **Result Summary:** 3x4 hand-verified totals/averages match; 2000x2000 row-wise scan is 1.67x faster than column-wise.

### Task05: Q5 – SMS Feedback Analyser Without string.h
- **Compile & Run:** `cd Task05 && gcc -Wall -Wextra -std=c11 q5_sms.c -o q5_sms && ./q5_sms`
- **Files:** `q5_sms.c`, `q5_sms_output.png`, `q5_sms_output.txt`
- **Result Summary:** Matches expected word count (7) & palindrome (1, 0); tab test returns 4 words; snprintf prevents overflow.

### Task06: Q6 – Hostel Resident Directory String Sorting & Searching
- **Compile & Run:** `cd Task06 && gcc -Wall -Wextra -std=c11 q6_names.c -o q6_names && ./q6_names`
- **Files:** `q6_names.c`, `q6_names_output.png`, `q6_names_output.txt`
- **Result Summary:** Index-array sorting moves 7.5x fewer bytes than 30-byte strcpy swaps across n=100..5000.

### Task07: Q7 – Student Council Election Counter from First Principles
- **Compile & Run:** `cd Task07 && gcc -Wall -Wextra -std=c11 q7_elect.c -o q7_elect && ./q7_elect`
- **Files:** `q7_elect.c`, `q7_elect_output.png`, `q7_elect_output.txt`
- **Result Summary:** Detects invalid votes and ties on sample ballots; processes 500,000 votes in ~2.2 ms (O(v)).
