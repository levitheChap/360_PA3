#include "PA3.h"


/* -----------------------------
   Read input file
-------------------------------- */
int read_processes(const char* filename, Process processes[]) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening file");
        return -1;
    }

    int count = 0;
    while (fscanf(fp, "%d %d %d",
        &processes[count].pid,
        &processes[count].arrival_time,
        &processes[count].burst_time) == 3) {

        processes[count].remaining_time = processes[count].burst_time;
        count++;
    }

    fclose(fp);
    return count;
}
