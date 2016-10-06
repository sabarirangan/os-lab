#include<stdio.h>
#include<float.h>
#include<limits.h>
#include<string.h>
#include<malloc.h>
struct person
{
    char *name;
    int arrivalTime;
    int processingTime;

    int status;
    int priority;
};
struct idle
{
    int sTime;
    int duration;
};
void ganttChart(struct person p[],int index[],int n,struct idle id[],int idlecount)
{
    int i,j=0,k;
    float temp;
    int currTime=0;
    printf("+");
    for(i=0;i<n;i++){
        for(k=0;k<p[index[i]].processingTime;k++){
            printf("----");
        }
        currTime+=p[index[i]].processingTime;
        if(j<idlecount&&currTime==id[j].sTime){
                printf("+");
            for(k=0;k<id[j].duration;k++){
            printf("----");
        }
        currTime+=id[j].duration;
        j++;

        }
        printf("+");
    }
    currTime=0;
    j=0;
    printf("\n|");
    for(i=0;i<n;i++){
        printf("%s",p[index[i]].name);
        for(k=strlen(p[index[i]].name);k<4*p[index[i]].processingTime;k++){
            printf(" ");
        }

        currTime+=p[index[i]].processingTime;
        if(idlecount>j&&currTime==id[j].sTime){
                printf("|");
                printf("idle");

            for(k=0;k<4*id[j].duration-4;k++){
            printf(" ");
        }
        currTime+=id[j].duration;
        j++;

        }
    printf("|");
    }
    currTime=0;
    j=0;
    printf("\n+");
    for(i=0;i<n;i++){
        for(k=0;k<p[index[i]].processingTime;k++){
            printf("----");
        }
        currTime+=p[index[i]].processingTime;
        if(j<idlecount&&currTime==id[j].sTime){
                printf("+");
            for(k=0;k<id[j].duration;k++){
            printf("----");
        }
        currTime+=id[j].duration;
        j++;

        }
        printf("+");

    }
    printf("\n");
    currTime=0;
    j=0;
    temp=(currTime+202)/100.0;
    printf("%0.2f",temp);
    for(i=0;i<n;i++)
    {
        for(k=3;k<4*p[index[i]].processingTime;k++)
            printf(" ");
        currTime+=p[index[i]].processingTime;
        temp=(currTime+202)/100.0;
    printf("%0.2f",temp);

        if(j<idlecount&&currTime==id[j].sTime)
        {

           for(k=3;k<4*id[j].duration;k++)
               printf(" ");
            currTime+=id[j].duration;
            temp=(currTime+202)/100.0;
    printf("%0.2f",temp);
            j++;

        }

    }
}
void turnAroundTime(struct person p[],int index[],int n,struct idle id[],int idlecount)
{
    printf("\n");
    int *cTime=malloc(n*sizeof(int));
    int i,j=0;
    float temp;
    int currTime=0;
    for(i=0;i<n;i++)
    {
        if(j<idlecount&&currTime==id[j].sTime)
        {
            currTime=currTime+id[j].duration;
            j++;
        }
        currTime+=p[index[i]].processingTime;
        cTime[index[i]]=currTime-p[index[i]].arrivalTime;

    }
    for(i=0;i<n;i++)
    {
        printf("%s-%d minutes",p[i].name,cTime[i]);
        printf("\n");
    }
    int sum=0;
    for(i=0;i<n;i++)
    {
        sum+=cTime[i];
    }
    printf("\naverage turnaroundtime is %0.2f minutes\n",sum/6.0);
}
void waitingTime(struct person p[],int index[],int n,struct idle id[],int idlecount)
{
    int *cTime=malloc(n*sizeof(int));
    int i,j=0;
    int currTime=0;
    for(i=0;i<n;i++)
    {
        if(j<idlecount&&currTime==id[j].sTime)
        {
            currTime=currTime+id[j].duration;
            j++;
        }
        cTime[index[i]]=currTime-p[index[i]].arrivalTime;
        currTime+=p[index[i]].processingTime;
    }
    for(i=0;i<n;i++)
    {
        printf("%s-%d minutes",p[i].name,cTime[i]);
        printf("\n");
    }
    int sum=0;
    for(i=0;i<n;i++)
    {
        sum+=cTime[i];
    }
    printf("\naverage waitingtime is %0.2f minutes\n",sum/6.0);
}
void prioritysch(struct person p[],int n)
{
    struct idle *id=malloc(n*sizeof(struct idle));
    int *index=malloc(n*sizeof(int));
    int i,j,k=0,flag=0,f=0;
    int minArrival=INT_MAX;
    int minIndex;
    int currTime=0;
    for(i=0;i<n;)
    {
        for(j=0;j<n;j++)
        {
            if(p[j].status==0&&currTime>=p[j].arrivalTime&&p[j].priority==0&&p[j].arrivalTime<minArrival)
            {
                minArrival=p[j].arrivalTime;
                minIndex=j;
                f=1;
            }

        }
        if(f!=1)
        {
            for(j=0;j<n;j++)
            {
                if(p[j].status==0&&currTime>=p[j].arrivalTime&&p[j].arrivalTime<minArrival)
                {
                minArrival=p[j].arrivalTime;
                minIndex=j;
                }
            }

        }
    f=0;
    if(minArrival!=INT_MAX)
    {
        p[minIndex].status=1;
        currTime+=p[minIndex].processingTime;
        minArrival=INT_MAX;
        index[i++]=minIndex;
        if(flag==1)
        {
            k++;
            flag=0;
        }
    }
    else
    {
        if(flag!=1)
        {
            id[k].sTime=currTime;
            currTime+=1;
            id[k].duration=1;
            flag=1;
        }
        else
        {
            currTime+=1;
            id[k].duration+=1;
        }

    }
}
    ganttChart(p,index,n,id,k);
printf("\n\n\nTURNARAUNDTIME:\n\n");
    turnAroundTime(p,index,n,id,k);
printf("\n\n\nWAITINGTIME:\n\n");
    waitingTime(p,index,n,id,k);
}
void sjf(struct person p[],int n)
{
    int *index=malloc(n*sizeof(int));
    int currTime=0;
    int minProcess=INT_MAX;
    int i,j,k=0,minIndex,flag=0;
    struct idle *id=malloc(n*sizeof(struct idle));
    for(j=0;j<n;)
    {for(i=0;i<n;i++){
        if(p[i].status==0&&p[i].arrivalTime<=currTime){
            if(minProcess>p[i].processingTime)
            {
                minProcess=p[i].processingTime;
                minIndex=i;

            }
        }
    }
    if(minProcess!=INT_MAX)
    {index[j]=minIndex;
    p[minIndex].status=1;
    currTime+=p[minIndex].processingTime;
    minProcess=INT_MAX;
    j++;
    if(flag==1){
                k++;
                flag=0;
            }
        }
        else
        {
            
            if(flag!=1)
            {
                id[k].sTime=currTime;
                currTime+=1;
                id[k].duration=1;
                flag=1;

            }
            else
            {
                currTime+=1;
                id[k].duration+=1;

            }
        }

    }
    ganttChart(p,index,n,id,k);
    printf("\n\n\nTURNARAUNDTIME:\n\n");
    turnAroundTime(p,index,n,id,k);
    printf("\n\n\nWAITINGTIME:\n\n");
    waitingTime(p,index,n,id,k);
}
void fifo(struct person p[],int n)
{
    int *index=malloc(n*sizeof(int));
    struct idle *id=malloc(n*sizeof(struct idle));
    int i,j,k=0,flag=0;
    float minArrival=FLT_MAX;
    int pindex;
    int currTime=0,idlecount=0;
    for(i=0;i<n;)
    {
        for(j=0;j<n;j++)
        {
            if(p[j].status==0&&(int)p[j].arrivalTime<=currTime&&minArrival>p[j].arrivalTime)
            {
                minArrival=p[j].arrivalTime;
                pindex=j;
            }
        }

        if(minArrival!=FLT_MAX)
        {
            p[pindex].status=1;
            index[i++]=pindex;
            minArrival=FLT_MAX;
            currTime=currTime+p[pindex].processingTime;
            if(flag==1){
                k++;
                flag=0;
            }
        }
        else
        {
            if(flag!=1)
            {
                id[k].sTime=currTime;
                currTime+=1;
                id[k].duration=1;
                flag=1;

            }
            else
            {
                currTime+=1;
                id[k].duration+=1;

            }
        }

    }

    ganttChart(p,index,n,id,j);
    turnAroundTime(p,index,n,id,j);
    waitingTime(p,index,n,id,j);
}
int main()
{
    int i;
    struct person p[6];
    //assignment
    //person 1
    p[5].name="Anand";
    p[5].arrivalTime=0;
    p[5].processingTime=2;
    p[5].priority=1;
    p[5].status=0;
    //person 2
    p[4].name="Rajkumar";
    p[4].arrivalTime=2;
    p[4].processingTime=3;
    p[4].priority=1;
    p[4].status=0;
    //person 3
    p[3].name="Daniel";
    p[3].arrivalTime=3;
    p[3].processingTime=4;
    p[3].priority=1;
    p[3].status=0;
    //person4
    p[2].name="Shanmugam";
    p[2].arrivalTime=0;
    p[2].processingTime=3;
    p[2].priority=0;
    p[2].status=0;
    //person 5
    p[1].name="Nickil";
    p[1].arrivalTime=1;
    p[1].processingTime=2;
    p[1].priority=0;
    p[1].status=0;
    //person6
    p[0].name="Nikitha";
    p[0].arrivalTime=18;
    p[0].processingTime=4;
    p[0].priority=0;
    p[0].status=0;

    fifo(p,6);

    for(i=0;i<6;i++){
        p[i].status=0;
    }
        printf("\n\n");
    sjf(p,6);
    for(i=0;i<6;i++){
        p[i].status=0;
    }
        printf("\n\n");
    prioritysch(p,6);
        return 0;
}
