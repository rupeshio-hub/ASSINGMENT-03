#include <stdio.h>
#include <ctype.h>

/* Counts words separated by one or more whitespace characters. */
int word_count(const char s[]) {
    int count = 0, inside = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (isspace((unsigned char)s[i])) {
            inside = 0;
        } else if (!inside) {
            count++;
            inside = 1;
        }
    }
    return count;
}

/* Returns 1 for a palindrome, ignoring case and non-letters. */
int is_palindrome(const char s[]) {
    int left = 0, right = 0;
    while (s[right] != '\0') right++;
    right--;

    while (left < right) {
        while (left < right && !isalpha((unsigned char)s[left])) left++;
        while (left < right && !isalpha((unsigned char)s[right])) right--;

        if (tolower((unsigned char)s[left]) !=
            tolower((unsigned char)s[right])) return 0;
        left++;
        right--;
    }
    return 1;
}

void to_upper_manual(char s[]) {
    for (int i = 0; s[i] != '\0'; i++)
        s[i] = (char)toupper((unsigned char)s[i]);
}

void reverse_manual(char s[]) {
    int left = 0, right = 0;
    char temp;
    while (s[right] != '\0') right++;
    right--;
    while (left < right) {
        temp = s[left]; s[left] = s[right]; s[right] = temp;
        left++; right--;
    }
}

int main(void) {
    char message[] = "Meet at the library at 5 PM";
    char upper[] = "Meet at the library!";
    char reversed[] = "Student Feedback";

    printf("Words: %d\n", word_count(" Meet at the library at 5 PM "));
    printf("Palindrome results: %d %d\n",
           is_palindrome("Madam, I'm Adam"), is_palindrome("Hello"));
    printf("Tab-separated words: %d\n", word_count("one\ttwo   three"));

    to_upper_manual(upper);
    printf("Uppercase: %s\n", upper);
    reverse_manual(reversed);
    printf("Reversed: %s\n", reversed);
    (void)message;
    return 0;
}
