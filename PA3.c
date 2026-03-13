#include "FCFS.c"
#include "SJF.c"
#include "Round_robin.c"
#include "readProcesses.c"
#include "resetProcceses.c"
#include "print_metrics.c"


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


    printf("\n===== Shortest Job First =====\n");
    reset_processes(processes, n);
    sjf(processes, n);
    print_metrics(processes, n);


    printf("\n===== Round Robin (q = %d) =====\n", quantum);
    reset_processes(processes, n);
    round_robin(processes, n, quantum);
    print_metrics(processes, n);

    
    return 0;

    
}


/* -----------------------------
   Gantt Chart Helper
-------------------------------- */
void print_gantt(int pid, int start, int end) {
    printf("P%d [%d -> %d]\n", pid, start, end);
}
