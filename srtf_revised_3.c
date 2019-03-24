#include<unistd.h>
#include<stdio.h>
#include<limits.h>

//Akshar Kashyap
//srtf - shortest remaining time first
//revised_3(completionTime display of each process)

void srt();

bool flag = false;

int arrivalTime[50],burstTime[50],waitingTime[50],TurnAroundTime[50];
int totalBT=0,remainingBT[50],completionTime[50];
int posSmallestBT = 0, process= 0, time = 0,TAT=0;
int smallestBT = INT_MAX; // max value taken so that loop can run at-least once in order to search the smallest burstTime (>0).
int n;

//---------------main---------------------
int main(){

//enter the num of processes
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
// calling srt function to calculate WT,TAT,CT
srt();
//-------------

printf("-----------------------------------------------------------------------------------------------\n");
printf("ProcessNum ||  Arrival Time ||  Burst Time || CompletionTime || Waiting Time || TurnaroundTime\n");

for (int i=0; i<n; i++){
   // printf("-----------------------------------------------------------------\n");
    printf("Process %d  || \t",i+1);
    printf("%d\t    || \t",arrivalTime[i] );
    printf("%d\t   || \t",burstTime[i] );
    printf("%d\t     ||\t",completionTime[i] );
    printf("%d\t     ||\t",waitingTime[i] );
    printf("%d\n",TurnAroundTime[i] );

    }

//average time calculation
    int total_Waiting_time=0;
    int total_turnaround_time=0;

    for (int i = 0; i < n; i++) {
        total_Waiting_time +=  waitingTime[i];
        total_turnaround_time += TurnAroundTime[i];
    }

printf("-----------------------------------------------------------------------------------------------\n");
printf("Average waiting time  : %.2f", (float) total_Waiting_time / (float) n);
printf("\nAverage turnaround time  : %.2f", (float) total_turnaround_time / (float) n);
printf("\n---------------------------------------------------------------------------------------------\n");

}
//------end of main-----------


//--------------srt function------------
void srt(){

do {
    condn:
        for (int i = 0; i < n; i++) {

            if (remainingBT[i] > 0 && (arrivalTime[i] <= time) && (remainingBT[i] < smallestBT)){
                posSmallestBT = i;
                smallestBT = remainingBT[i];
                flag = true;
            }
        }

        if (flag == false) {
            time++;
            goto condn; // again iterate through the - for loop
        }

        //--------condition satisfied - we found the smallest Burst Time Process.
        //increase running time
        time++;
        // Reduce remainingBT time
        remainingBT[posSmallestBT]--;
        //update smallest burst time
        smallestBT = remainingBT[posSmallestBT];

        // If a process gets completely executed (burst time ==0)
        if (remainingBT[posSmallestBT] == 0) {

            // Increment process
            process++;
            flag = false;
            // completion time calculation
            completionTime[posSmallestBT] = time;
            // WT  & TAT calculation of perticular process
            TurnAroundTime[posSmallestBT] = completionTime[posSmallestBT] - arrivalTime[posSmallestBT];
            waitingTime[posSmallestBT] =  TurnAroundTime[posSmallestBT] - burstTime[posSmallestBT] ;

            //update smallest burst time to INT_MAX
            smallestBT = INT_MAX;

        }

}while (process != n); //if all processes are done then break the loop. i.e.(remainingBT[i]==0)


}
