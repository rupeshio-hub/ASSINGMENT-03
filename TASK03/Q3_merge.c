#include <stdio.h>

/* Stable merge: when scores are equal, campus A is copied first. */
int merge(const int a[], int na, const int b[], int nb, int out[]) {
    int i = 0, j = 0, k = 0;

    while (i < na && j < nb) {
        if (a[i] >= b[j]) out[k++] = a[i++];
        else out[k++] = b[j++];
    }
    while (i < na) out[k++] = a[i++];
    while (j < nb) out[k++] = b[j++];
    return k;
}

void print_list(const int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    putchar('\n');
}

int main(void) {
    int campusA[] = {98, 91, 85, 72};
    int campusB[] = {95, 91, 80};
    int merged[7];

    int n = merge(campusA, 4, campusB, 3, merged);
    printf("Merged merit list: ");
    print_list(merged, n);

    /* Empty-list test */
    int empty_result[4];
    n = merge(NULL, 0, campusA, 4, empty_result);
    printf("One empty list: ");
    print_list(empty_result, n);

    /* Equal-score test */
    int equalA[] = {90, 90}, equalB[] = {90, 90}, equalOut[4];
    n = merge(equalA, 2, equalB, 2, equalOut);
    printf("All equal scores: ");
    print_list(equalOut, n);
    return 0;
}
