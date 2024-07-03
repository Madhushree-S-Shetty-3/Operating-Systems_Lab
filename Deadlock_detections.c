#include <stdio.h>

int main() {
    int n, m, i, j, k;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], request[n][m], avail[m];

    for (int i = 0; i < n; i++) {
        printf("Enter details for P%d\n", i);
        printf("Enter allocation -- ");
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
        printf("Enter Request -- ");
        for (int j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    printf("Enter Available Resources -- ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    int finish[n], safeSeq[n], work[m], flag,f=0;
    for (i = 0; i < n; i++) {
        finish[i] = 0;
    }

    for (j = 0; j < m; j++) {
        work[j] = avail[j];
    }

    int count = 0;
    while (count < n) {
        flag = 0;f=0;
        for (i = 0; i < n; i++) {
            if (finish[i] == 0)
            {
                for(int j=0;j<m;j++)
                    if(alloc[i][j]!=0)
                        f=1;
                if(f)
                {
                    int canProceed = 1;
                    for (j = 0; j < m; j++) {
                        if (request[i][j] > work[j]) {
                            canProceed = 0;
                            break;
                        }
                    }
                    if (canProceed) {
                        for (k = 0; k < m; k++) {
                            work[k] += alloc[i][k];
                        }
                        safeSeq[count++] = i;
                        finish[i] = 1;
                        flag = 1;
                    }
                }
                else
                {
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    flag = 1;
                }
            }
        }
        if (flag == 0) {
            break;
        }
    }

    int deadlock = 0;
    for (i = 0; i < n; i++) {
        if (finish[i] == 0) {
            deadlock = 1;
            printf("\nSystem is in a deadlock state.\n");
            printf("The deadlocked processes are: ");
            for (j = 0; j < n; j++) {
                if (finish[j] == 0) {
                    printf("P%d ", j);
                }
            }
            printf("\n");
            break;
        }
    }

    if (deadlock == 0) {
        printf("\nSystem is not in a deadlock state.\n");
        printf("Safe Sequence is: ");
        for (i = 0; i < n; i++) {
            printf("P%d ", safeSeq[i]);
        }
        printf("\n");
    }

    return 0;
}
