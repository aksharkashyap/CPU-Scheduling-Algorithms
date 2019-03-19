#include<unistd.h>
#include<stdio.h>

//srtf - shortest remaining time first

int main(){

int arrivalTime[50],burstTime[50],completionTime,waitingTime,TurnAroundTime;
int smallestBT=0;

int n;
printf("Please enter number of processes: ");
scanf("%d",&n);

for (int i=0;i<n;i++){
printf("Arrival Time for Process: %d\n",i+1);
scanf("%d",&arrivalTime[i]);

printf("Burst Time for Process: %d\n",i+1);
scanf("%d",&burstTime[i]);
}

for(int i=0; i<n;i++){
    if(burstTime[i] < burstTime[i+1]){
        smallestBT = burstTime[i];
    }
    else if(burstTime[i+1] < burstTime[i]){
        smallestBT = burstTime[i+1];
    }

    }

printf(" smallest burstTime %d ",smallestBT);


}
