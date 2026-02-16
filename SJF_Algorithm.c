/*
 * Shortest Job First (SJF) Scheduling Algorithm :-
    
   1. Start the program.

   2. Read the number of processes '4n'.

   3. Read the burst time of each process.

   4. Assign process numbers to each process.

   5. Sort all processes in ascending order of burst time.

   6. Set waiting time of the first process as 0.

   7. Calculate waiting time of each process as the sum of burst times of all 
      previous processes.

   8. Calculate turnaround time using:
         Turnaround Time = Waiting Time + Burst Time

   9. Calculate average waiting time and average turnaround time.

   10. Display process number, burst time, waiting time, turnaround time, and 
       averages.

   11. Stop the program.

*/

#include <stdio.h>

int main() {
    int n;
    int bt[20], wt[20], tat[20], p[20];
    int i, j;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter burst time of processes:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &bt[i]);
        p[i] = i + 1;   // process number
    }

    // Sorting processes according to burst time (SJF)
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (bt[i] > bt[j]) {
                int temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    wt[0] = 0; // waiting time of first process
    
    printf("\nExecution Order (Gantt Chart):\n");
    for (i = 0; i < n; i++) {
         printf("P%d", p[i]);
    if (i != n - 1)
        printf(" -> ");
    }
    printf("\n");

    for (i = 1; i < n; i++) {
        wt[i] = 0;
        for (j = 0; j < i; j++) {
            wt[i] += bt[j];
        }
    }

    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    avg_wt /= n;
    avg_tat /= n;

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\n ", p[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);

    return 0;
}
