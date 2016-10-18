#include<stdio.h>
int n;
int x,a[100];
int initialHead;
int previousHead;
int time;

void fcfs()
{
    int i,moves=0;
    int current=initialHead;
    for(i=0;i<x;i++){
        moves+=abs(current-a[i]);
        current=a[i];
    }
    printf("\nFCFS \n");
    printf("time taken is %d ms \n",moves*time);

}

void srtf()
{
    int i,moves=0;
    int flag[1000]={};
    int minSeek=100000;
    int current=initialHead;
    int index;
    int count=0;
    while(count<x){
        for(i=0;i<x;i++){
            if(flag[i]!=0)
            continue;
            if(abs(current-a[i])<minSeek){
                minSeek=abs(current-a[i]);
                index=i;
            }
        }
        flag[index]=1;
        count++;
        moves+=abs(current-a[index]);
        current=a[index];
        minSeek=100000;
    }
    printf("\nSRTF \ntime taken is %d ms",moves*time);


}
void SCAN()
{
    int diff=previousHead-initialHead;
    int moves=0;
    int i;

    if(diff>0){
        int max=-1;
        for(i=0;i<x;i++){
        if(a[i]>max)
            max=a[i];
        }
        moves+=(initialHead);
        moves+=max;
    }
    else{
        int min=n+1;
        for(i=0;i<x;i++){
        if(a[i]<min)
            min=a[i];
        }
        moves+=n-initialHead-1;
        moves+=(n-min-1);

    }
    printf("\nSCAN \ntime taken is %d ms",moves*time);
}

void LOOK()
{
    int diff=previousHead-initialHead;
    int moves=0;
    int i;
    int min=n+1;
    for(i=0;i<x;i++){
        if(a[i]<min)
            min=a[i];
    }
    int max=-1;
    for(i=0;i<x;i++){
        if(a[i]>max)
            max=a[i];
    }
    if(diff>0){

        moves+=(initialHead-min);
        moves+=max-min;
    }
    else{

        moves+=max-initialHead;
        moves+=(max-min);

    }
    printf("\nLOOK \ntime taken is %d ms",moves*time);

}

int main()
{
    int i;
    printf("enter number of cylinders ");
    scanf("%d",&n);
    printf("enter number of requests  ");
    scanf("%d",&x);
    printf("enter the requests\n");
    for(i=0;i<x;i++){
        scanf("%d",&a[i]);
    }
    printf("\nenter the current position of head ");
    scanf("%d",&initialHead);
    printf("\nenter the previous position of head ");
    scanf("%d",&previousHead);
    printf("\nenter the time taken to move from one cylinder to another (ms) ");
    scanf("%d",&time);
    fcfs();
    srtf();
    SCAN();
    LOOK();
    return 0;
}
