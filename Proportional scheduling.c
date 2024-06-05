#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int n;
    printf("Enter number of processes:");
    scanf("%d",&n);
    int p[n],t[n],cum[n],m[n];int c=0;int total = 0,count=0;
    printf("Enter tickets of the processes:\n");
    for(int i=0;i<n;i++)
    {    
        scanf("%d",&t[i]);
        c+=t[i];
        cum[i]=c;
        p[i]=i+1;
        m[i]=0;
        total+= t[i];
    }
    while(count<n)
    {
        int wt=rand()%total;
        for (int i=0;i<n;i++) 
        {
            if (wt<cum[i] && m[i]==0) 
            {
                printf("The winning number is %d and winning participant is: %d\n",wt,p[i]); 
                m[i]=1;count++;
            }
        }
    }
    printf("\nProbabilities:\n");
    for (int i = 0; i < n; i++) 
    {
        printf("The probability of P%d winning: %.2f %\n",p[i],((double)t[i]/total*100));
    }
}
