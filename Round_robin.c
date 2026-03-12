#include "PA3.h"


/* -----------------------------
   Round Robin Scheduling
-------------------------------- */
void round_robin(Process processes[], int n, int quantum) {
    int current_time = 0;
    int completed = 0;

    // TODO:
    // 1. Implement a ready queue (array-based is fine)
    // 2. Add processes to queue when arrival_time <= current_time
    // 3. Execute each process for min(quantum, remaining_time)
    // 4. Re-queue unfinished processes
    // 5. Track completion_time correctly

    while (completed < n) {
        int did_work = 0;

        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0 &&
                processes[i].arrival_time <= current_time) {

                int exec = (processes[i].remaining_time > quantum)
                    ? quantum
                    : processes[i].remaining_time;

                int start = current_time;
                current_time += exec;
                int end = current_time;

                print_gantt(processes[i].pid, start, end);

                processes[i].remaining_time -= exec;
                did_work = 1;

                if (processes[i].remaining_time == 0) {
                    processes[i].completion_time = current_time;
                    completed++;
                }
            }
        }

        if (!did_work) {
            current_time++; // CPU idle
        }
    }
}
