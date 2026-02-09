#include <stdio.h>

int main() {
    int n = 3;
    int bt[3] = {5, 3, 2};        // Burst Time
    int pr[3] = {3, 1, 2};        // Priority
    int wt[3], tat[3];
    int p[3] = {1, 2, 3};         // Process IDs (P1, P2, P3)
    int i, j;

    float avg_wt = 0, avg_tat = 0;

    // Sorting based on priority (lower value = higher priority)
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (pr[i] > pr[j]) {
                int temp;

                temp = pr[i];
                pr[i] = pr[j];
                pr[j] = temp;

                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    wt[0] = 0;

    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    for (i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    avg_wt /= n;
    avg_tat /= n;

    printf("Process\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               p[i], bt[i], pr[i], wt[i], tat[i]);
    }

     // Display execution sequence
    printf("\nPriority Execution Sequence:\n");
    for (i = 0; i < n; i++) {
        printf("P%d", p[i]);
        if (i != n - 1)
            printf(" -> ");
    }


    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);

    return 0;
}
