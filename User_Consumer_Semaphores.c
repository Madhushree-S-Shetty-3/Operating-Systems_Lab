#include<stdio.h>
#include<stdlib.h>
int mutex=1,full=0,empty=5,x=0;
void wait(int *s) {
    while(*s <= 0);
    (*s)--;
}

void signal(int *s) {
    (*s)++;
}
void producer()
{
    wait(&empty);
    wait(&mutex);
    x++;
    printf("Producer has produced: Item %d\n",x);
    signal(&mutex);
    signal(&full);
}
void consumer()
{
    wait(&full);
    wait(&mutex);
    printf("Consumer has consumed: Item %d\n",x);
    x--;
    signal(&mutex);
    signal(&empty);
}
void main()
{
    int ch;
    printf("Enter 1.Producer 2.Consumer 3.Exit\n");
    while(1)
    {
        printf("Enter your choice:\n");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                if(mutex==1 && empty!=0)
                producer();
                else
                    printf("Buffer is full!\n");
                break;
            case 2:
                if(mutex==1 && full!=0)
                consumer();
                else
                    printf("Buffer is empty!\n");
                break;
            case 3:exit(0);
            default:printf("Invalid choice!\n");
        }
    }
}
