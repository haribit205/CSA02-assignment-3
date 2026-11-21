#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* Counts words separated by one or more spaces/whitespace, without using string.h */
int word_count(const char s[])
{
    int count = 0, inside = 0;
    /* TODO 1: Scan string up to '\0'; count new word on whitespace -> non-whitespace */
    for (int i = 0; s[i] != '\0'; i++) {
        if (isspace((unsigned char)s[i])) {
            inside = 0;
        } else if (!inside) {
            inside = 1;
            count++;
        }
    }
    return count;
}

/* Returns 1 if s reads the same both ways, ignoring case and non-letters. */
int is_palindrome(const char s[])
{
    int left = 0, right = 0;
    while (s[right] != '\0') right++;
    right--;
    /* TODO 2: Move left forward and right backward, skipping non-letters */
    while (left < right) {
        while (left < right && !isalpha((unsigned char)s[left])) left++;
        while (left < right && !isalpha((unsigned char)s[right])) right--;
        if (tolower((unsigned char)s[left]) != tolower((unsigned char)s[right])) {
            return 0;
        }
        left++;
        right--;
    }
    return 1;
}

void to_upper_custom(char s[]) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') s[i] = (char)(s[i] - ('a' - 'A'));
    }
}

void reverse_custom(char s[]) {
    int n = 0;
    while (s[n] != '\0') n++;
    for (int i = 0, j = n - 1; i < j; i++, j--) {
        char tmp = s[i]; s[i] = s[j]; s[j] = tmp;
    }
}

int main(void)
{
    printf("=== Q5 Complete-the-Code: SMS Feedback Analyser ===\n");
    printf("Words: %d\n", word_count("  Meet at  the library at 5 PM "));
    printf("%d %d\n", is_palindrome("Madam, I'm Adam"), is_palindrome("Hello"));

    /* Additional Test: Tab character & empty string */
    printf("Tab test (\"Lab\\t3\\tis\\topen\"): Words = %d\n", word_count("Lab\t3\tis\topen"));
    printf("Empty string (\"\"): Words = %d, Palindrome = %d\n", word_count(""), is_palindrome(""));

    char msg[32] = "Hostel WiFi Good";
    to_upper_custom(msg);
    printf("Custom Upper  : %s\n", msg);
    reverse_custom(msg);
    printf("Custom Reverse: %s\n", msg);

    /* Safe bounded copy with snprintf replacing unsafe strcpy */
    char small_buf[10];
    const char *long_sms = "VeryLongFeedbackMessage";
    snprintf(small_buf, sizeof small_buf, "%s", long_sms);
    printf("Safe snprintf into 10-byte buffer: \"%s\" (Truncated safely, no overflow)\n", small_buf);
    return 0;
}
