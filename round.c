#include<stdio.h>
#include<limits.h>
#include<string.h>

struct process
{
    int arrivalTime;
    int brustTime;
    char name[10];
    int status;//initially assigned to 0, it becomes 1 when process gets over
    int waitingTime;
    int turnAroundTime;
};

int queue[100],front=0,rear=-1;//ready queue
int nop;
struct process p[10];
int currentTime;//HOLDS THE current time
int timeslice;
int completedProcess;//keeps count of completed process

/*enqueue all the process whose arrival time is less than or equal to current time*/
void enqueue()
{
    int minArrival;
    int minIndex,i;
    while(1)//breaks when all process with arrival time less than or equal to current time is enqueued
    {
        minArrival=currentTime;
        minIndex=-1;
        for(i=0;i<nop;i++)//this loop chooses process with less arrival time compared to other process (srrival time <=currenttime)
        {
            if(p[i].status!=1&&p[i].arrivalTime<=currentTime)//not completed process and arrival time <= current time
            {
                if(minArrival>p[i].arrivalTime)
                {
                    minArrival=p[i].arrivalTime;
                    minIndex=i;
                }
                else if(currentTime==p[i].arrivalTime&&minIndex==-1)
                {
                    minIndex=i;
                }
            }
        }

        /*if above loop returns no process, minindex is -1 implies all process having (AT<=CT) are enqueued*/
        if(minIndex!=-1)
        {
            queue[++rear]=minIndex;
            p[minIndex].status=1;
        }
        else
            break;
    }
}

/*returns process from queue*/
int dequeue()
{
    return queue[front++];
}
void roundrobin()
{
    int processAT[10];
    int minArival=INT_MAX;
    int minIndex;
    int i;
    int index;

    /*copy of initial arrival time to calculate TAT*/
    for(i=0;i<nop;i++)
    {
        processAT[i]=p[i].arrivalTime;
    }

    /*initially process wit minimum arrival time*/
    for(i=0;i<nop;i++)
    {
        if(p[i].arrivalTime<minArival)
        {
            minArival=p[i].arrivalTime;
            minIndex=i;
        }
    }
    currentTime=minArival;

    printf("|");
    while(completedProcess<nop)
    {
        enqueue();
        index=dequeue();//dequeueing a process from ready queue
        if(p[index].brustTime>timeslice&&completedProcess!=nop-1)
        {
            printf("p%d",index+1);
            for(i=1;i<timeslice;i++)
                printf("  ");
            printf("|");
            p[index].brustTime=p[index].brustTime-timeslice;//updates the brusttime
            p[index].waitingTime=p[index].waitingTime+currentTime-p[index].arrivalTime;//updates arrival time
            p[index].status=0;
            currentTime+=timeslice;//increments current time
            p[index].arrivalTime=currentTime;//set the arrival time of the process to current time so that it gets enqueued
        }
        else//if brust time is less that timeslice
        {
            printf("p%d",index+1);
            for(i=1;i<p[index].brustTime;i++)
                printf("  ");
            printf("|");
            p[index].waitingTime=p[index].waitingTime+(currentTime-p[index].arrivalTime);
            currentTime=currentTime+p[index].brustTime;
            p[index].brustTime=0;
            p[index].status=1;//sets process is completed
            p[index].arrivalTime=INT_MAX;
            p[index].turnAroundTime=currentTime-processAT[index];
            completedProcess++;//increments Completed process
        }
    }
    printf("\n");

}
void waitingTimeDisplay()
{
    int sum=0;
    int i;
    printf("\nwaiting time");
    for(i=0;i<nop;i++)
    {
        printf("\n%s - %d minutes",p[i].name,p[i].waitingTime);
        sum=sum+p[i].waitingTime;
    }
    printf("\nAverage WaitingTime: %f minutes\n",(float)sum/nop);

}
void turnAroundTimeDisplay()
{
    int sum=0;
    int i;
    printf("\nTurnAroundTime time");
    for(i=0;i<nop;i++)
    {
        printf("\n%s - %d minutes",p[i].name,p[i].turnAroundTime);
        sum=sum+p[i].turnAroundTime;
    }
    printf("\nAverage  TurnAroundTime: %f minutes\n",(float)sum/nop);

}
int main()
{
    int i;
    float tempAT;

    /*get the input*/
    printf("enter the number of process:");
    scanf("%d",&nop);
    printf("\nenter the name,arrival time and brust time of processes\n");
    for(i=0;i<nop;i++){
        printf("process %d\n",i+1);
        scanf("%s%f%d",p[i].name,&tempAT,&p[i].brustTime);
        p[i].status=0;
        p[i].waitingTime=0;
    }
    printf("enter the time slice:\n");
    scanf("%d",&timeslice);


    roundrobin();//calling round robin function
    turnAroundTimeDisplay();//display TAT
    waitingTimeDisplay();//display WT

    return 0;
}
