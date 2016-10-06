#include<stdio.h>
#include<limits.h>
#define size 4
int page[100];
int n;
void fifo(){
    int curPos=0;//current position
    int fault=0;
    int i,j;
    int memory[size]={};//0 will be assigned
    for(i=0;i<n;i++){
        for(j=0;j<size;j++){
            if(page[i]==memory[j])
                break;
        }
        if(j>=size){
            memory[curPos]=page[i];
            curPos=(curPos+1)%size;
            fault++;
        }
    }
    printf("%d page faults",fault);
    
}
void lfu(){
    int flag[100]={};//flag[i]=0 denotes not in page table, 1 denotes in page table
    int memory[size]={};
    int frequency[100]={};
    int fault=0;
    int i,j,k;
    for(i=0;i<n;i++){
        for(j=0;j<size;j++){
            if(page[i]==memory[j])
                break;
        }
        if(j>=size){
            fault++;
            int minFre=INT_MAX;//minimum frequency
            for(k=0;k<n;k++){
                if(frequency[k]<minFre)
                    minFre=frequency[k];
            }
            for(k=0;k<n;k++){
                if(flag[k]==1&&frequency[k]==minFre){
                    break;
                }
            }
            f
        }
    }
    
}
int main(){
    printf("enter number of pages  ");
    scanf("%d",&n);
    int i;
    for(i=0;i<n;i++)
        scanf("%d",&page[i]);
    fifo();
    lfu();
    return 0;
}