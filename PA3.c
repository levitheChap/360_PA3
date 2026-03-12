#include "FCFS.c"
#include "SJF.c"
#include "Round_robin.c"
#include "readProcesses.c"
#include "resetProcceses.c"
#include "print_metrics.c"


/* -----------------------------
   Utility: sort by arrival time
-------------------------------- */
    // TODO:
    // 1. Sort processes by arrival time (if needed)
    // 2. For each process:
    //    - Advance current_time if CPU is idle
    //    - Run process to completion
    //    - Set completion_time


/* -----------------------------
   Main
-------------------------------- */
int main(int argc, char* argv[]) {
    Process processes[MAX_PROCESSES];
    int n;

    if (argc < 3) {
        printf("Usage: %s <input_file> <time_quantum>\n", argv[0]);
        return 1;
    }

    int quantum = atoi(argv[2]);

    n = read_processes(argv[1], processes);
    if (n <= 0) {
        printf("No processes loaded.\n");
        return 1;
    }

    printf("before sort\n");

    for(int i = 0; i < n; i++) {
        printf("\n%d\t%d\t%d\n\n\n",
            processes[i].pid,
            processes[i].arrival_time,
            processes[i].burst_time);
    }


    //sort processes by arrival time
    for (int i = 0; i < n - 1; i++) {
        if (processes[i].arrival_time > processes[i + 1].arrival_time) {
            //swaping step
            printf("swapping %d and %d\n", processes[i].pid, processes[i + 1].pid);
            Process temp;//create temp to hold <er arrival time
            temp = processes[i + 1];//temp holds <er arrival time
            processes[i + 1] = processes[i];//move >er arrival time to next index
            processes[i] = temp;//move <er arrival time to current index
            
            
            // for (int j = 0; j < n - 1 - i; j++) {
            //     if (processes[j].arrival_time > processes[j + 1].arrival_time) {
            //         Process temp = processes[j];
            //         processes[j] = processes[j + 1];
            //         processes[j + 1] = temp;
            //     }
            // }
        }
        
    }

    printf("after sort\n");

    for(int i = 0; i < n; i++) {
        printf("\n%d\t%d\t%d\n",
            processes[i].pid,
            processes[i].arrival_time,
            processes[i].burst_time);
    }

    printf("\n===== First-Come, First-Serve =====\n");
    reset_processes(processes, n);
    fcfs(processes, n);
    print_metrics(processes, n);

    return 0;

    printf("\n===== Shortest Job First =====\n");
    reset_processes(processes, n);
    sjf(processes, n);
    print_metrics(processes, n);

    printf("\n===== Round Robin (q = %d) =====\n", quantum);
    reset_processes(processes, n);
    round_robin(processes, n, quantum);
    print_metrics(processes, n);

    
}


/* -----------------------------
   Gantt Chart Helper
-------------------------------- */
void print_gantt(int pid, int start, int end) {
    printf("P%d [%d -> %d]\n", pid, start, end);
}
