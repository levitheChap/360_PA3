#include "PA3.h"

/* -----------------------------
   SJF Scheduling (Non-preemptive)
-------------------------------- */
void sjf(Process processes[], int n) {

    int completed_A[n]; // Track completed processes
    int completed_count = 0;
    int current_time = 0;

    // Loop until all processes are completed
    while (completed_count < n) {
        int shortestindex = -1; // set the index to first process
        int is_completed = 0; // flag to check if the process is completed

        //find the process with the shortest burst time that has arrived and is not completed
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time > current_time) { //if the process has not arrived yet
                continue; //skip to the next index
            }

            
            //check if the current index has been completed
            
            
            int is_completed = 0; // flag to check if the process is completed
            for (int j = 0; j < completed_count; j++) {
                if (processes[i].pid == completed_A[j]) { //if the current index has been completed
                    is_completed = 1; //skip to the next index
                }
            }
            if(is_completed == 1) {
                continue; //skip to the next index
            }

            // First valid candidate
            if (shortestindex == -1) {
                shortestindex = i;
            }

            // if current index burst time is less than the burst compare
            if (processes[i].burst_time < processes[shortestindex].burst_time) { 
                //set the burst compare to the current index burst time
                shortestindex = i;
            }
            else if (processes[i].burst_time == processes[shortestindex].burst_time) { //if the burst time is the same
                 if (processes[i].arrival_time < processes[shortestindex].arrival_time) { //if the arrival time is less than the compare
                    shortestindex = i; //set the compare to the current index
                }
                //implide else 
            }
            
        }

        // If no process is ready, CPU is idle
        if (shortestindex == -1) {
            current_time++;
            continue;
        }


        //Run process to completion
        int start = current_time;
        current_time += processes[shortestindex].burst_time;
        int end = current_time;

        // Mark the process as completed
        completed_A[completed_count] = processes[shortestindex].pid;
        completed_count++;

        // Update metrics
        processes[shortestindex].completion_time = end;
        processes[shortestindex].turnaround_time =
            processes[shortestindex].completion_time - processes[shortestindex].arrival_time;
        processes[shortestindex].waiting_time =
            processes[shortestindex].turnaround_time - processes[shortestindex].burst_time;
        processes[shortestindex].remaining_time = 0;


        print_gantt(processes[shortestindex].pid, start, end);
    }

}