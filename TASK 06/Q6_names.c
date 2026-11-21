#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAMES 5000
#define NAME_LEN 30

long strcmp_calls = 0;
long character_copies = 0;

int compare_names(const char a[], const char b[]) {
    strcmp_calls++;
    return strcmp(a, b);
}

void remove_newline(char s[]) {
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') s[len - 1] = '\0';
}

void sort_names(char names[][NAME_LEN], int n) {
    char temp[NAME_LEN];
    for (int i = 1; i < n; i++) {
        int j = i;
        while (j > 0 && compare_names(names[j - 1], names[j]) > 0) {
            strcpy(temp, names[j - 1]); character_copies += strlen(temp) + 1;
            strcpy(names[j - 1], names[j]); character_copies += strlen(names[j]) + 1;
            strcpy(names[j], temp); character_copies += strlen(temp) + 1;
            j--;
        }
    }
}

int binary_search_name(char names[][NAME_LEN], int n, const char key[]) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int cmp = compare_names(names[mid], key);
        if (cmp == 0) return mid;
        if (cmp < 0) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int main(void) {
    static char names[MAX_NAMES][NAME_LEN];
    char key[NAME_LEN];
    int n;

    printf("Number of names (1-%d): ", MAX_NAMES);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_NAMES) {
        printf("Invalid number of names.\n");
        return 1;
    }
    getchar(); /* consume newline */

    for (int i = 0; i < n; i++) {
        printf("Name %d: ", i + 1);
        if (fgets(names[i], NAME_LEN, stdin) == NULL) return 1;
        remove_newline(names[i]);
    }

    sort_names(names, n);
    printf("\nSorted names:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", names[i]);
        if (i > 0 && strcmp(names[i], names[i - 1]) == 0)
            printf("  DUPLICATE: %s\n", names[i]);
    }

    printf("\nName to search: ");
    if (fgets(key, sizeof key, stdin) == NULL) return 1;
    remove_newline(key);

    int pos = binary_search_name(names, n, key);
    if (pos >= 0) printf("%s found at sorted index %d.\n", key, pos);
    else printf("%s not found.\n", key);

    printf("strcmp calls (sorting + search): %ld\n", strcmp_calls);
    printf("Characters copied during swaps: %ld\n", character_copies);
    return 0;
}
