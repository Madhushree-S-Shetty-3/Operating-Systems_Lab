#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void FCFS(int AT[], int BT[], int CT[], int TAT[], int WT[], int n, int *current_time) {
    for (int i = 0; i < n; i++) {
        if (*current_time < AT[i])
            *current_time = AT[i];

        CT[i] = *current_time + BT[i];
        TAT[i] = CT[i] - AT[i];
        WT[i] = TAT[i] - BT[i];

        *current_time = CT[i];
    }
}

void sort_by_arrival(int AT[], int BT[], int isSystem[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (AT[j] > AT[j + 1]) {
                int temp = AT[j];
                AT[j] = AT[j + 1];
                AT[j + 1] = temp;

                temp = BT[j];
                BT[j] = BT[j + 1];
                BT[j + 1] = temp;

                temp = isSystem[j];
                isSystem[j] = isSystem[j + 1];
                isSystem[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, sys_count = 0, user_count = 0;
    int AT[MAX], BT[MAX], CT[MAX], TAT[MAX], WT[MAX], isSystem[MAX];
    int sys_AT[MAX], sys_BT[MAX], user_AT[MAX], user_BT[MAX];
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the arrival time, burst time and type (1 for system process, 0 for user process) for all the processes:\n");

    for (int i = 0; i < n; i++) {
        printf("\nProcess %d:\n", i + 1);
        printf("Arrival time: ");
        scanf("%d", &AT[i]);
        printf("Burst Time: ");
        scanf("%d", &BT[i]);
        printf("Type (1 for system, 0 for user): ");
        scanf("%d", &isSystem[i]);

        if (isSystem[i]) {
            sys_AT[sys_count] = AT[i];
            sys_BT[sys_count] = BT[i];
            sys_count++;
        } else {
            user_AT[user_count] = AT[i];
            user_BT[user_count] = BT[i];
            user_count++;
        }
    }

    sort_by_arrival(sys_AT, sys_BT, isSystem, sys_count);
    sort_by_arrival(user_AT, user_BT, isSystem, user_count);

    int current_time = 0;
    int total_wt = 0, total_tat = 0;

    printf("\n\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\tType\n");

    int i = 0, j = 0;
    while (i < sys_count || j < user_count) {
        if (i < sys_count && (j >= user_count || sys_AT[i] <= current_time)) {
            if (current_time < sys_AT[i])
                current_time = sys_AT[i];

            CT[i] = current_time + sys_BT[i];
            TAT[i] = CT[i] - sys_AT[i];
            WT[i] = TAT[i] - sys_BT[i];

            current_time = CT[i];

            printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\tSystem\n", i + 1, sys_AT[i], sys_BT[i], CT[i], TAT[i], WT[i]);
            total_wt += WT[i];
            total_tat += TAT[i];

            i++;
        } else if (j < user_count) {
            if (current_time < user_AT[j])
                current_time = user_AT[j];

            CT[i + j] = current_time + user_BT[j];
            TAT[i + j] = CT[i + j] - user_AT[j];
            WT[i + j] = TAT[i + j] - user_BT[j];

            current_time = CT[i + j];

            printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\tUser\n", i + 1 + j, user_AT[j], user_BT[j], CT[i + j], TAT[i + j], WT[i + j]);
            total_wt += WT[i + j];
            total_tat += TAT[i + j];

            j++;
        }
    }

    float avg_wt = (float)total_wt / n;
    float avg_tat = (float)total_tat / n;

    printf("\nAverage waiting time = %0.3f", avg_wt);
    printf("\nAverage turn around time = %0.3f\n", avg_tat);

    return 0;
}
