#include <stdio.h>
#define MAX_PROCESSES 10
#define NO_ARRIVAL_TIME -1  

typedef struct Process {
    int id;
    int burst_time;
    int remaining_time;
    int arrival_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

int main() { 
    int num_processes, time_quantum;
    int show_details = 1;  

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    if (num_processes <= 0 || num_processes > MAX_PROCESSES) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    printf("Enter time quantum for Round Robin: ");
    scanf("%d", &time_quantum);

    Process processes[MAX_PROCESSES];

    for (int i = 0; i < num_processes; i++) {
        printf("\nEnter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);

        printf("Enter arrival time for process %d (or -1 if no arrival time): ", i + 1);
        scanf("%d", &processes[i].arrival_time);

        processes[i].id = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }

    int time = 0;
    int remaining_processes = num_processes;

    while (remaining_processes > 0) {
        for (int i = 0; i < num_processes; i++) {
            if (processes[i].remaining_time > 0) {
                int execute_time = (processes[i].remaining_time < time_quantum) ? processes[i].remaining_time : time_quantum;
                processes[i].remaining_time -= execute_time;
                time += execute_time;

                if (processes[i].remaining_time == 0) {
                    remaining_processes--;
                    processes[i].completion_time = time;
                    processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                }
            }
        }
    }

    float avg_turnaround_time = 0, avg_waiting_time = 0, throughput;
    for (int i = 0; i < num_processes; i++) {
        avg_turnaround_time += processes[i].turnaround_time;
        avg_waiting_time += processes[i].waiting_time;
    }
    avg_turnaround_time /= num_processes;
    avg_waiting_time /= num_processes;

    throughput = (float)num_processes / time;

    printf("\nGantt Chart: ");
    for (int i = 0; i < num_processes; i++) {
        printf("|\t P%d \t", processes[i].id);
    }
    printf("|\n");

    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    printf("Throughput: %.2f processes per unit time\n", throughput);

    return 0;  
}
