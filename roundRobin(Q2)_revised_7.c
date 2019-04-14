#include<stdio.h>
#include<limits.h>
#include<unistd.h>
#include <stdbool.h>

//round robin
//1st iteration TQ=3
//2nd iteration TQ=6 (waiting processes)
//3rd iteration SJF (waiting processes)
//revision 6 - improved process numbering & minor bug fixes .
//revised 7 - constrain added BT>0

int arrivalTime[50],burstTime[50],waitingTime[50],remainingBT[50],TurnAroundTime[50],compltnTime[50],process_number[50];
int time = 0; // Current time
int timeQauntum =3;int check=0,checkBT=0,TAT;
int posMinBT = 0;

bool flag = false;
int n;

void calcWait();
void sjf();



//------main-----------------
int main(){

//enter the num of processes
printf("Please enter number of processes: ");
scanf("%d",&n);

// ask for arrival and burst time
for (int i=0;i<n;i++){
printf("Arrival Time for Process: %d\n",i+1);
scanf("%d",&arrivalTime[i]);

bt:
printf("Burst Time for Process: %d\n",i+1);
scanf("%d",&burstTime[i]);
printf("-------------------------------------------------\n");
if(burstTime[i] <=0){
    printf("BurstTime should be greater than 0\n");
    goto bt;
}



process_number[i] = i+1;
}

int temp;
//arranging them according to arrival time
for(int i=0;i<n;i++){
    for(int j=i+1;j<n;j++){
        if(arrivalTime[i] > arrivalTime[j]){
            //arrival time
            temp = arrivalTime[i];
            arrivalTime[i] = arrivalTime[j];
            arrivalTime[j] = temp;
            //burst time
            temp = burstTime[i];
            burstTime[i] = burstTime[j];
            burstTime[j] = temp;
            //process_number
            temp = process_number[i];
            process_number[i] = process_number[j];
            process_number[j] = temp;

        }
    }
}
//---------------------------------------------

for (int i = 0 ; i < n ; i++){ // Make a copy of burst times
        remainingBT[i] =  burstTime[i];
 }

calcWait();

if(checkBT>0){
timeQauntum=6;
calcWait();
}

if(checkBT>0){
    sjf();
}

checkBT=0;// set to 0(because it contains old Sum of RBT) to again calculate the sum of remainingBT
for(int i=0;i<n;i++){
    checkBT += remainingBT[i];
}


//TAT & CT calculation
for (int i=0; i<n; i++){
    TurnAroundTime[i] = burstTime[i] + waitingTime[i];
    compltnTime[i] = TurnAroundTime[i] + arrivalTime[i];
}

printf("Finish Time(All Process) : %d\n",time);
printf("TotalRemainingBT : %d\n",checkBT);
printf("--------------------------------------------------------------------------------------------------------------\n");
printf("ProcessNum ||  Arrival Time ||  Burst Time || CompletionTime || Waiting Time || TurnaroundTime  || RemainingBT\n");

for (int i=0; i<n; i++){
   // printf("-----------------------------------------------------------------\n");
    printf("Process %d  || \t",process_number[i]);
    printf("%d\t    || \t",arrivalTime[i] );
    printf("%d\t   || \t",burstTime[i] );
    printf("%d\t     ||\t",compltnTime[i] );
    printf("%d\t     ||\t",waitingTime[i] );
    printf("%d\t        ||\t",TurnAroundTime[i] );
    printf("%d\n",remainingBT[i] );


  //  printf("-----------------------------------------------------------------\n");

}

//average time calculation
    int total_Waiting_time=0;
    int total_turnaround_time=0;

    for (int i = 0; i < n; i++) {
        total_Waiting_time +=  waitingTime[i];
        total_turnaround_time += TurnAroundTime[i];
    }

    printf("------------------------------------------------------------------------------------------------------\n");
    printf("Average waiting time  : %.2f", (float) total_Waiting_time / (float)n);
    printf("\nAverage turnaround time  : %.2f", (float) total_turnaround_time / (float)n);
    printf("\n----------------------------------------------------------------------------------------------------\n");


}//end of main


void calcWait(){

    bool flag = false;

condnCheck:
    for(int i=0;i<n;i++){
        if(remainingBT[i]>timeQauntum && arrivalTime[i]<=time && remainingBT[i]>0){
            remainingBT[i] -= timeQauntum;
            time += timeQauntum;
            flag = true;

            if(remainingBT[i] == 0){
            waitingTime[i] = time - arrivalTime[i] - burstTime[i];
            flag =true;
         }

        }
        else if(remainingBT[i]<=timeQauntum && arrivalTime[i]<=time && remainingBT[i]>0){
           // while(remainingBT[i] !=0){
            //    time = time +1;
            //    remainingBT[i]--;}
            time = time + remainingBT[i];
            remainingBT[i] = 0;
            flag = true;

            if(remainingBT[i] == 0){
            waitingTime[i] = time - arrivalTime[i] - burstTime[i];
            flag =true;
         }
          }

          else if(remainingBT[i] ==0){ //if process has finished earlier then continue through the loop for another processes
            continue;
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

int smallestBT = INT_MAX;

void sjf(){

while (1)
 {
        flag = false;
        for (int i = 0; i < n; i++) {

            if (remainingBT[i] > 0 && (remainingBT[i] < smallestBT)){

                posMinBT = i;
                smallestBT = remainingBT[i];
                flag = true;
            }

        if (flag == false) {
            continue; // again iterate through the for loop
        }
    }

        time += remainingBT[posMinBT];
        remainingBT[posMinBT]=0; //finish the process
        TAT = time - arrivalTime[posMinBT];
        waitingTime[posMinBT] = TAT - burstTime[posMinBT];
        smallestBT = INT_MAX;



if (flag==false)
    break;
}
}
