/*
Algorithm Steps:

1. Read the number of processes n.

2. Read Arrival Time (AT) and Burst Time (BT) for each process.

3. Sort all processes in ascending order of Arrival Time.

4. Set Completion Time of first process:
      ->    CT[0] = AT[0] + BT[0]

5. For each remaining process i = 1 to n-1:

      ->   If AT[i] ≤ CT[i-1]
           CT[i] = CT[i-1] + BT[i]

      ->   Else
           CT[i] = AT[i] + BT[i]

6. Calculate Turnaround Time (TAT) for each process:
      ->   TAT[i] = CT[i] - AT[i]

7. Calculate Waiting Time (WT) for each process:
      ->   WT[i] = TAT[i] - BT[i]

8. Display AT, BT, CT, TAT, WT.

*/


// FCFS Algorithm Implementation in C
#include <stdio.h>

int main() {
    int n, i, j;

    int pid[20], at[20], bt[20];
    int ct[20], tat[20], wt[20];
    int temp;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Read arrival time and burst time 
    for (i = 0; i < n; i++) {
        pid[i] = i + 1; // Process ID
        printf("Enter Arrival Time for process %d: ", pid[i]);
        scanf("%d", &at[i]);
        printf("Enter Burst Time for process %d: ", pid[i]);
        scanf("%d", &bt[i]);   
    }
    // Sort processes by Arrival Time (FCFS)
    for(i = 0; i < n - 1; i++){
        for(j = i + 1; j < n; j++){
            if(at[i] > at[j]){
                // Swap Arrival Time
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                // Swap Burst Time
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                // Swap Process ID
                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }
    // Calculate Completion Time
    ct[0] = at[0] + bt[0];
    for(i = 1; i < n; i++){
        if(at[i] <= ct[i - 1]){
            ct[i] = ct[i - 1] + bt[i];
        } else {
            ct[i] = at[i] + bt[i];
        }
    }
    // Calculate Turn Around Time and Waiting Time
    for(i = 0; i < n; i++){
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }
    // Display results
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
             pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    return 0;
}