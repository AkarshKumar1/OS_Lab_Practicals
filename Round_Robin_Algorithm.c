/* Round Robin Scheduling Implementation 

Algorithm :-

1. Start the program.

2. Read the number of processes n.

3. Read burst time of each process.

4. Assign process IDs.

5. Read the Time Quantum (TQ).

6. Initialize remaining burst time = burst time.

7. Repeat until all processes are completed:

 -> For each process:

     -> If remaining burst time > 0:

           -> If remaining burst time > TQ:

               . Execute process for TQ.

               . Reduce remaining burst time by TQ.

           -> Else:

               . Execute process for remaining burst time.

               . Calculate waiting time.

               . Set remaining burst time = 0.

8. Calculate Turnaround Time:

  -> Turnaround Time = Burst Time + Waiting Time


9. Calculate average waiting time and average turnaround time.

10. Display results.

11. Stop the program.

*/

#include <stdio.h>

int main() {
    int n, tq;
    int at[20], bt[20], rem_bt[20];
    int wt[20], tat[20], ct[20];
    int i, time = 0, completed = 0;
    int visited[20] = {0};
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        rem_bt[i] = bt[i];
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);

    printf("\n--- Gantt Chart ---\n");

    while (completed < n) {
        int executed = 0;

        for (i = 0; i < n; i++) {

            if (at[i] <= time && rem_bt[i] > 0) {

                executed = 1;
                printf("| P%d (%d-%d) ", i + 1, time,
                       time + (rem_bt[i] > tq ? tq : rem_bt[i]));

                if (rem_bt[i] > tq) {
                    time += tq;
                    rem_bt[i] -= tq;
                } else {
                    time += rem_bt[i];
                    ct[i] = time;
                    rem_bt[i] = 0;
                    completed++;
                }
            }
        }

        if (!executed)
            time++;   // If no process is ready, increment time
    }

    // Calculate WT and TAT
    for (i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    avg_wt /= n;
    avg_tat /= n;

    printf("|\n");

    printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);

    return 0;
}
