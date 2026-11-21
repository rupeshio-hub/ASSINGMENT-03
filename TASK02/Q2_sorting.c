#include <stdio.h>

#define N 6

typedef struct {
    long comparisons;
    long moves;
} Stats;

void print_array(const int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    putchar('\n');
}

Stats bubble_sort(int a[], int n) {
    Stats s = {0, 0};
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            s.comparisons++;
            if (a[j] > a[j + 1]) {
                int t = a[j]; a[j] = a[j + 1]; a[j + 1] = t;
                s.moves += 3;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
    return s;
}

Stats selection_sort(int a[], int n) {
    Stats s = {0, 0};
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            s.comparisons++;
            if (a[j] < a[min]) min = j;
        }
        if (min != i) {
            int t = a[i]; a[i] = a[min]; a[min] = t;
            s.moves += 3;
        }
    }
    return s;
}

Stats insertion_sort(int a[], int n) {
    Stats s = {0, 0};
    for (int i = 1; i < n; i++) {
        int key = a[i], j = i - 1;
        while (j >= 0) {
            s.comparisons++;
            if (a[j] > key) {
                a[j + 1] = a[j];
                s.moves++;
                j--;
            } else break;
        }
        a[j + 1] = key;
        s.moves++;
    }
    return s;
}

void run_case(const char *label, const int source[], int n) {
    int a[N];
    Stats s;
    printf("\n%s input: ", label);
    print_array(source, n);

    for (int i = 0; i < n; i++) a[i] = source[i];
    s = bubble_sort(a, n);
    printf("Bubble:    "); print_array(a, n);
    printf("  comparisons=%ld, moves=%ld\n", s.comparisons, s.moves);

    for (int i = 0; i < n; i++) a[i] = source[i];
    s = selection_sort(a, n);
    printf("Selection: "); print_array(a, n);
    printf("  comparisons=%ld, moves=%ld\n", s.comparisons, s.moves);

    for (int i = 0; i < n; i++) a[i] = source[i];
    s = insertion_sort(a, n);
    printf("Insertion: "); print_array(a, n);
    printf("  comparisons=%ld, shifts/writes=%ld\n", s.comparisons, s.moves);
}

int main(void) {
    const int sorted[N]   = {12, 18, 25, 31, 44, 50};
    const int nearly[N]   = {12, 18, 31, 25, 44, 50};
    const int reverse[N]  = {50, 44, 31, 25, 18, 12};
    const int random[N]   = {31, 12, 50, 18, 44, 25};

    run_case("Already sorted", sorted, N);
    run_case("Nearly sorted", nearly, N);
    run_case("Reverse sorted", reverse, N);
    run_case("Random", random, N);
    return 0;
}
