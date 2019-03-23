#include<stdio.h>
#include<limits.h>

//round robin
//1st iteration TQ=3
//2nd iteration TQ=6 (waiting processes)
//3rd iteration SJF (waiting processes)

int arrivalTime[50],burstTime[50],waitingTime[50],remainingBT[50],TurnAroundTime[50],compltnTime[50];
int time = 0; // Current time
int timeQauntum =3;int check=0,checkBT=0;

int smallestBT=0, totalBT=0,completionTime;
int posMinBT = 0, processDone = 0, minimumBT = INT_MAX,TAT=0;

bool flag = false;
//enter the num of processes
int n;

void calcWait();
void srtf();

int main(){
printf("Please enter number of processes: ");
scanf("%d",&n);

// ask for arrival and burst time
for (int i=0;i<n;i++){
printf("Arrival Time for Process: %d\n",i+1);
scanf("%d",&arrivalTime[i]);

printf("Burst Time for Process: %d\n",i+1);
scanf("%d",&burstTime[i]);
printf("-------------------------------------------------\n");
}

for (int i = 0 ; i < n ; i++){ // Make a copy of burst times bt[] to store remaining // burst times.
        remainingBT[i] =  burstTime[i];
 }

calcWait();

if(checkBT>0){
timeQauntum=6;
calcWait();
}

if(checkBT>0){
    srtf();
}

checkBT=0;
for(int i=0;i<n;i++){
    checkBT += remainingBT[i];
}


//TAT calculation
for (int i=0; i<n; i++){
    TurnAroundTime[i] = burstTime[i] + waitingTime[i];
    compltnTime[i] = TurnAroundTime[i] + arrivalTime[i];
}

printf("Current Time %d\n",time);
printf("TotalRemainingBT %d\n",checkBT);
printf("ProcessNum ||  Arrival time ||  Burst time || Waiting Time || TurnaroundTime || completionTime ||remaining\n");

for (int i=0; i<n; i++){
   // printf("-----------------------------------------------------------------\n");
    printf("Process %d  || \t",i+1);
    printf("%d\t    || \t",arrivalTime[i] );
    printf("%d\t   || \t",burstTime[i] );
    printf("%d\t    || \t",waitingTime[i] );
    printf("%d\t    || \t",TurnAroundTime[i] );
    printf("%d\t    || \t",compltnTime[i] );
    printf("%d\t    || \n",remainingBT[i] );

  //  printf("-----------------------------------------------------------------\n");

}
}


void calcWait(){

    bool flag = false;

//while(flag!=true){
condnCheck:
    for(int i=0;i<n;i++){
        if(remainingBT[i]>timeQauntum && arrivalTime[i]<=time && remainingBT[i]>0){
            remainingBT[i] -= timeQauntum;
            time += timeQauntum;
            flag = true;

        }
        else if(remainingBT[i] <timeQauntum && arrivalTime[i] <= time && remainingBT[i]>0){
          //  while(remainingBT[i] !=0){
          //      time = time +1;
          //      remainingBT[i]--;
          //  }
            time = time + remainingBT[i];
            remainingBT[i] = 0;
             waitingTime[i] = time - arrivalTime[i] - burstTime[i];
             flag = true;

        }
        if(remainingBT[i] ==0){
            waitingTime[i] = time - arrivalTime[i] - burstTime[i];
            flag =true;
         }
        if(flag == false){
            time++;
            goto condnCheck;
        }


}

checkBT=0;
for(int i=0;i<n;i++){
    checkBT += remainingBT[i];
}
}


void srtf(){
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

         //   completion time calculation
            completionTime = time + 1;
          //   WT calculation of perticular process
             TAT = completionTime - arrivalTime[posMinBT];
             waitingTime[posMinBT] =  TAT - burstTime[posMinBT] ;

        }
        // Increment time
        time++;
    }while (processDone != n);

    checkBT=0;
    for(int i=0;i<n;i++){
    checkBT += remainingBT[i];
}
}
