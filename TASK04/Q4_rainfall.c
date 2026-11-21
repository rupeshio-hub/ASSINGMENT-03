#include <stdio.h>

#define DISTRICTS 38
#define MONTHS 12

void read_rainfall(double rain[DISTRICTS][MONTHS]) {
    printf("Enter rainfall (mm) for %d districts x %d months:\n", DISTRICTS, MONTHS);
    for (int i = 0; i < DISTRICTS; i++) {
        printf("District %d: ", i + 1);
        for (int j = 0; j < MONTHS; j++) {
            if (scanf("%lf", &rain[i][j]) != 1 || rain[i][j] < 0) {
                printf("Invalid rainfall value.\n");
                return;
            }
        }
    }
}

void annual_totals(const double rain[DISTRICTS][MONTHS],
                   double totals[DISTRICTS]) {
    for (int i = 0; i < DISTRICTS; i++) {
        totals[i] = 0;
        for (int j = 0; j < MONTHS; j++) totals[i] += rain[i][j];
    }
}

double state_monthly_average(const double rain[DISTRICTS][MONTHS]) {
    double sum = 0;
    for (int i = 0; i < DISTRICTS; i++)
        for (int j = 0; j < MONTHS; j++) sum += rain[i][j];
    return sum / (DISTRICTS * MONTHS);
}

void wettest_month(const double rain[DISTRICTS][MONTHS],
                   int *district, int *month, double *maximum) {
    *maximum = rain[0][0];
    *district = 0;
    *month = 0;
    for (int i = 0; i < DISTRICTS; i++) {
        for (int j = 0; j < MONTHS; j++) {
            if (rain[i][j] > *maximum) {
                *maximum = rain[i][j];
                *district = i;
                *month = j;
            }
        }
    }
}

void print_deficient(const double totals[DISTRICTS], double state_average) {
    /* Compare each district's average monthly rainfall with 60% of the
       state's average monthly rainfall. */
    double threshold = 0.60 * state_average;
    printf("Districts below 60%% of state monthly average (%.2f mm):\n", threshold);
    for (int i = 0; i < DISTRICTS; i++) {
        if (totals[i] / MONTHS < threshold)
            printf("District %d (district monthly average %.2f mm)\n",
                   i + 1, totals[i] / MONTHS);
    }
}

int main(void) {
    double rain[DISTRICTS][MONTHS], totals[DISTRICTS];
    double maximum, average;
    int wetDistrict, wetMonth;

    read_rainfall(rain);
    annual_totals(rain, totals);
    average = state_monthly_average(rain);
    wettest_month(rain, &wetDistrict, &wetMonth, &maximum);

    printf("\nAnnual totals:\n");
    for (int i = 0; i < DISTRICTS; i++)
        printf("District %d: %.2f mm\n", i + 1, totals[i]);

    printf("State average monthly rainfall: %.2f mm\n", average);
    printf("Wettest: District %d, Month %d = %.2f mm\n",
           wetDistrict + 1, wetMonth + 1, maximum);
    print_deficient(totals, average);
    return 0;
}
