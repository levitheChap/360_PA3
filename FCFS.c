
#include "PA3.h"

/* -----------------------------
   FCFS Scheduling
-------------------------------- */
void fcfs(Process processes[], int n) {
    
	
	int current_time = 0;

    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }

        int start = current_time;
        current_time += processes[i].burst_time;
        int end = current_time;

        print_gantt(processes[i].pid, start, end);
        processes[i].completion_time = end;
    }
}
