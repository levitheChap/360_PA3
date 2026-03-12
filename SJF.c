#include "PA3.h"

/* -----------------------------
   SJF Scheduling (Non-preemptive)
-------------------------------- */
void sjf(Process processes[], int n) {

    // TODO:
    // 1. While not all processes are completed:
    // 2. Find the available process with the shortest burst time
    // 3. Execute it fully and update completion_time
    // 4. Handle CPU idle time if no process is available

    int completed_A[n]; // Track completed processes
    int completed_count = 0;
    int current_time = 0;
    int B_compare = processes[0].burst_time; // set the burst time to first process 
    int P_index = 0; // set index to first process

    // Loop until all processes are completed
    while (completed_count < n) {
        //find the process with the shortest burst time that has arrived and is not completed
        for (int i = 0; i < n; i++) {
            //check if the current index has been completed
            for (int j = 0; j < completed_count; j++) {
                if (processes[i].pid == completed_A[j]) { //if the current index has been completed
                    continue; //skip to the next index
                }
            }


            if (processes[i].burst_time < B_compare) { // if current index burst time is less than the burst compare
                //set the burst compare to the current index burst time
                B_compare = processes[i].burst_time;
                //set the process index to the current index
                P_index = i;
                    
                }
                // else if(){ //if the current index burst is  

                // }
        
        }




    }


}

