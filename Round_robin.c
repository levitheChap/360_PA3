#include "PA3.h"


/* -----------------------------
   Round Robin Scheduling
-------------------------------- */
void round_robin(Process processes[], int n, int quantum) {
    int current_time = 0;
    int completed = 0;


    //ready queue implementation using an array
    int ready_queue[MAX_PROCESSES];
    int front = 0;
    int rear = 0;

    // Track which processes are in the ready queue
    int in_queue[MAX_PROCESSES] = {0};


    while (completed < n) {

        for (int i = 0; i < n; i++) {
            //check if the process is not completed and has arrived
                        
            if (processes[i].arrival_time <= current_time &&
                processes[i].remaining_time > 0 &&
                !in_queue[i]) {
                ready_queue[rear++] = i;
                in_queue[i] = 1;
            }
        }


        // If queue is empty, CPU is idle 
        if (front == rear) {
            current_time++;
            continue;
        }

        // Dequeue next process 
        int idx = ready_queue[front++];
        in_queue[idx] = 0;

        // Execute for min(quantum, remaining_time) 
        int exec = (processes[idx].remaining_time > quantum)
            ? quantum
            : processes[idx].remaining_time;

        int start = current_time;
        current_time += exec;
        int end = current_time;

        print_gantt(processes[idx].pid, start, end);
        processes[idx].remaining_time -= exec;

        /*
         * Add processes that arrived strictly during this time slice
         * before re-queueing the current process.
         */
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time > start &&
                processes[i].arrival_time < end &&
                processes[i].remaining_time > 0 &&
                !in_queue[i]) {
                ready_queue[rear++] = i;
                in_queue[i] = 1;
            }
        }


        // Re-queue unfinished process 
        if (processes[idx].remaining_time > 0) {
            ready_queue[rear++] = idx;
            in_queue[idx] = 1;
        } 
        // Mark process as completed if finished
        else {
            processes[idx].completion_time = current_time;
            completed++;
        }

        /*
         * Add processes that arrive exactly at the end of the time slice
         * after re-queueing the current process.
         */
        for (int i = 0; i < n; i++) {
            //check if the process arrives at the end of the time slice and is not completed
            if (processes[i].arrival_time == end &&
                processes[i].remaining_time > 0 &&
                !in_queue[i]) {
                ready_queue[rear++] = i;
                in_queue[i] = 1;
            }
        }


    }
}