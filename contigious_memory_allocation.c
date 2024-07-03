#include <stdio.h>
#include <stdlib.h>

#define MAX 25

void firstFit(int nb, int nf, int b[], int f[]) {
    int ff[MAX] = {0};
    int allocated[MAX] = {0}; 
    for (int i = 0; i < nf; i++) {
        ff[i] = -1; 
        for (int j = 0; j < nb; j++) {
            if (allocated[j] == 0 && b[j] >= f[i]) {
                ff[i] = j;
                allocated[j] = 1;
                break;
            }
        }
    }

    printf("\nFile_no:\tFile_size :\tBlock_no:\tBlock_size:");
    for (int i = 0; i < nf; i++) {
        if (ff[i] != -1)
            printf("\n%d\t\t%d\t\t%d\t\t%d", i + 1, f[i], ff[i] + 1, b[ff[i]]);
        else
            printf("\n%d\t\t%d\t\t-\t\t-", i + 1, f[i]);
    }
}

void bestFit(int nb, int nf, int b[], int f[]) {
    int ff[MAX] = {0};
    int allocated[MAX] = {0}; 
    for (int i = 0; i < nf; i++) {
        int best = -1;
        ff[i] = -1; 
        for (int j = 0; j < nb; j++) {
            if (allocated[j] == 0 && b[j] >= f[i]) {
                if (best == -1 || b[j] < b[best])
                    best = j;
            }
        }
        if (best != -1) {
            ff[i] = best;
            allocated[best] = 1;
        }
    }

    printf("\nFile_no:\tFile_size :\tBlock_no:\tBlock_size:");
    for (int i = 0; i < nf; i++) {
        if (ff[i] != -1)
            printf("\n%d\t\t%d\t\t%d\t\t%d", i + 1, f[i], ff[i] + 1, b[ff[i]]);
        else
            printf("\n%d\t\t%d\t\t-\t\t-", i + 1, f[i]);
    }
}

void worstFit(int nb, int nf, int b[], int f[]) {
    int ff[MAX] = {0};
    int allocated[MAX] = {0}; 

    for (int i = 0; i < nf; i++) {
        int worst = -1;
        ff[i] = -1; 
        for (int j = 0; j < nb; j++) {
            if (allocated[j] == 0 && b[j] >= f[i]) {
                if (worst == -1 || b[j] > b[worst])
                    worst = j;
            }
        }
        if (worst != -1) {
            ff[i] = worst;
            allocated[worst] = 1;
        }
    }

    printf("\nFile_no:\tFile_size :\tBlock_no:\tBlock_size:");
    for (int i = 0; i < nf; i++) {
        if (ff[i] != -1)
            printf("\n%d\t\t%d\t\t%d\t\t%d", i + 1, f[i], ff[i] + 1, b[ff[i]]);
        else
            printf("\n%d\t\t%d\t\t-\t\t-", i + 1, f[i]);
    }
}

int main() {
    int nb, nf, choice;

    printf("Memory Management Scheme");
    printf("\nEnter the number of blocks: ");
    scanf("%d", &nb);
    printf("Enter the number of files: ");
    scanf("%d", &nf);
    int b[nb], f[nf];
    printf("\nEnter the size of the blocks:\n");
    for (int i = 0; i < nb; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &b[i]);
    }
    printf("Enter the size of the files:\n");
    for (int i = 0; i < nf; i++) {
        printf("File %d: ", i + 1);
        scanf("%d", &f[i]);
    }

    while (1) {
        printf("\n1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("\n\tMemory Management Scheme - First Fit\n");
                firstFit(nb, nf, b, f);
                break;
            case 2:
                printf("\n\tMemory Management Scheme - Best Fit\n");
                bestFit(nb, nf, b, f);
                break;
            case 3:
                printf("\n\tMemory Management Scheme - Worst Fit\n");
                worstFit(nb, nf, b, f);
                break;
            case 4:
                printf("\nExiting...\n");
                exit(0);
                break;
            default:
                printf("\nInvalid choice.\n");
                break;
        }
    }

    return 0;
}
