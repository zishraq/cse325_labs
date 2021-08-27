#include <stdio.h>

typedef struct Process {
    int arrival_time;
    int burst_time;
    int starting_time;
    int finishing_time;
    int has_finished;
} Process;

int getShortestJob(Process processes[], int n) {
    int shortest = 0;

    for (int i = 0; i < n; i++) {
        if (processes[i].burst_time < processes[shortest].burst_time && processes[i].has_finished == 0) {
            shortest = i;
        }

        if (processes[i].burst_time > processes[shortest].burst_time && processes[shortest].has_finished == 1) {
            shortest = i;
        }

        if (processes[i].burst_time == processes[shortest].burst_time) {
            if (processes[shortest].has_finished) {
                shortest = i;
            }
        }
    }

    return shortest;
}

int getEarlyArrivedJob(Process processes[], int n) {
    int earliest = 0;

    for (int i = 0; i < n; i++) {

        if (processes[i].arrival_time < processes[earliest].arrival_time && processes[i].has_finished == 0) {
            earliest = i;
        }

        if (processes[i].arrival_time > processes[earliest].arrival_time && processes[earliest].has_finished == 1) {
            earliest = i;
        }

        if (processes[i].arrival_time == processes[earliest].arrival_time) {
            if (processes[earliest].has_finished) {
                earliest = i;
            }
        }
    }

    return earliest;
}

int main() {
    int n = 4;
    Process processes[4] = {
            {5, 6, 0, 0, 0},
            {3, 7, 0, 0, 0},
            {7, 5, 0, 0, 0},
            {8, 7, 0, 0, 0},
    };
    
    int progressed_time = 0;

    for (int i = 0; i < n; i++) {
        int shortest_job = getShortestJob(processes, n);
        int early_arrived_job = getEarlyArrivedJob(processes, n);

        int current_job = shortest_job;

        if (processes[current_job].arrival_time > progressed_time) {
            current_job = early_arrived_job;

            if (progressed_time < processes[current_job].arrival_time) {
                progressed_time = processes[current_job].arrival_time;
            }
        }

        processes[current_job].starting_time = progressed_time;
        progressed_time += processes[current_job].burst_time;

        processes[current_job].finishing_time = progressed_time;
        processes[current_job].has_finished = 1;
    }

    printf("Processes\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t\t%d\t\t\t%d\n", i + 1, processes[i].starting_time - processes[i].arrival_time, processes[i].finishing_time - processes[i].arrival_time);
    }

    return 0;
}
