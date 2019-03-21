#include<unistd.h>
#include<stdio.h>
#include<limits.h>

//srtf - shortest remaining time first

int main(){

bool flag = false;

int arrivalTime[50],burstTime[50],waitingTime[50],TurnAroundTime[50];
int smallestBT=0, totalBT=0,remainingBT[50],completionTime;
int posMinBT = 0, processDone = 0, time = 0, minimumBT = INT_MAX,TAT=0;

//enter the num of processes
int n;
printf("Please enter number of processes: ");
scanf("%d",&n);

// ask for arrival and burst time
for (int i=0;i<n;i++){
printf("Arrival Time for Process: %d\n",i+1);
scanf("%d",&arrivalTime[i]);

printf("Burst Time for Process: %d\n",i+1);
scanf("%d",&burstTime[i]);
printf("-------------------------------------------------\n");

// Copying burstime into remaining time
for (int i = 0; i < n; i++){
        remainingBT[i] = burstTime[i];
 }

}



do {

        for (int i = 0; i < n; i++) {

            if ((arrivalTime[i] <= time) && remainingBT[i] > 0 && (remainingBT[i] < minimumBT)){

                posMinBT = i;
                minimumBT = remainingBT[i];
                flag = true;
            }
        }

        if (flag == false) {
            time++;
            continue; // again iterate through the for loop
        }

        // Reduce remaining time by one
        remainingBT[posMinBT]--;

        // Update minimum
        minimumBT = remainingBT[posMinBT];
        if (minimumBT == 0)
            minimumBT = INT_MAX;

        // If a process gets completely executed
        if (remainingBT[posMinBT] == 0) {

            // Increment process
            processDone++;
            flag = false;

            // completion time calculation
            completionTime = time + 1;

            // WT calculation of perticular process
             TAT = completionTime - arrivalTime[posMinBT];
             waitingTime[posMinBT] =  TAT - burstTime[posMinBT] ;
        }
        // Increment time
        time++;
    }while (processDone != n);

//TAT calculation
for (int i=0; i<n; i++){
    TurnAroundTime[i] = burstTime[i] + waitingTime[i];
}


printf("ProcessNum ||  Burst time || Waiting Time  ||  Turn Around Time\n");

for (int i=0; i<n; i++){
   // printf("-----------------------------------------------------------------\n");
    printf("Process %d  || \t",i+1);
    printf("%d\t  || \t",burstTime[i] );
    printf("%d\t   || \t",waitingTime[i] );
    printf("%d\n",TurnAroundTime[i] );
  //  printf("-----------------------------------------------------------------\n");

    }

//average time calculation
    int total_Waiting_time=0;
    int total_turnaround_time=0;

    for (int i = 0; i < n; i++) {
        total_Waiting_time +=  waitingTime[i];
        total_turnaround_time += TurnAroundTime[i];
    }

    printf("-----------------------------------------------------------------\n");
    printf("Average waiting time  : %.2f", (float) total_Waiting_time / (float)n);
    printf("\nAverage turnaround time  : %.2f", (float) total_turnaround_time / (float)n);
    printf("\n-----------------------------------------------------------------\n");

}

