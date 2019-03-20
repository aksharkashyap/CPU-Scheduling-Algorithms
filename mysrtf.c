#include<unistd.h>
#include<stdio.h>

//srtf - shortest remaining time first

int main(){

int arrivalTime[50],burstTime[50],completionTime[50],waitingTime[50],TurnAroundTime[50];
int smallestBT=0, totalBT=0,pos;

int n;
printf("Please enter number of processes: ");
scanf("%d",&n);

for (int i=0;i<n;i++){
printf("Arrival Time for Process: %d\n",i+1);
scanf("%d",&arrivalTime[i]);

printf("Burst Time for Process: %d\n",i+1);
scanf("%d",&burstTime[i]);

totalBT += burstTime[i];
}

while(totalBT !=0){

for (int time=0;;time++){

    for(int i=0;i<n;i++){

        if(arrivalTime[i]<=time){

            for (int j=i;j<n;j++){
                if(burstTime[j] < burstTime[j+1]){
                    smallestBT = burstTime[j];
                    pos = j;
                }
                else{
                    smallestBT = burstTime[j+1];
                    pos = j+1;
                }
            }
            burstTime[pos]--;
            completionTime[pos]++;

        }
    }
}
}

for (int i=0; i<n; i++){
    TurnAroundTime[i] = completionTime[i] - arrivalTime[i];
    waitingTime[i] = TurnAroundTime[i] - burstTime[i];
}

for (int i=0; i<n; i++){
    printf("%d\n",TurnAroundTime[i] );
    printf("%d\n",waitingTime[i] );
}


}
