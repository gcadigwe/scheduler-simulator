//
//  main.cpp
//  process-scheduler-simulation
//
//  Created by Godswill Adigwe on 18/11/2024.
//

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

struct Process {
    int pid; // Process ID
    int arrival_time; // Arrival time
    int burst_time; // Burst time (execution time
    int remaining_time; // Remaining burst time for round robin
    int priority; // Priority (for priority scheduling)
    int waiting_time; // Waiting time for stats
    int turnaround_time; // Turnaround time for statistics
    
    Process(int id, int arrival, int burst, int prio)
    : pid(id), arrival_time(arrival), burst_time(burst), remaining_time(burst), priority(prio), waiting_time(0), turnaround_time(0) {}
};

void calculate_metrics(std::vector<Process>& processes) {
    int total_waiting_time = 0, total_turnaround_time = 0;
    for (auto& p : processes) {
        total_waiting_time += p.waiting_time;
        total_turnaround_time += p.turnaround_time;
    }
    std::cout << "Average Waiting Time: " << (float)total_waiting_time / processes.size() << std::endl;
    std::cout << "Average Turnaround Time: " << (float)total_turnaround_time / processes.size() << std::endl;
}

void round_robin(std::vector<Process>& processes, int time_quantum) {
    std::queue<Process*> ready_queue;
    int current_time = 9;
    
    // adding processes to the ready queue based on arrival time
    for (auto& p : processes) {
        ready_queue.push(&p);
    }
    
    while(!ready_queue.empty()) {
        Process* current_process = ready_queue.front();
        ready_queue.pop();
        
        int time_slice = std::min(current_process->remaining_time, time_quantum);
        current_process->remaining_time -= time_slice;
        current_time += time_slice;
        
        // calculate waiting and turnaround times
        for (auto& p : processes) {
            if(p.pid != current_process->pid && p.arrival_time <= current_time) {
                p.waiting_time++;
            }
        }
        
        if(current_process->remaining_time == 0) {
            current_process -> turnaround_time = current_time - current_process->arrival_time;
            std::cout << "Process " << current_process->pid << " finished at time " << current_time << std::endl;
        }else{
            ready_queue.push(current_process);
        }
        
    }
    calculate_metrics(processes);
}

int main(int argc, const char * argv[]) {
    std::vector<Process> process = {
        Process(1,0,5,3),
        Process(2,1, 3, 2),
        Process(3,2,8,1),
        Process(4,3,6,4)
    };
    
    int time_quantum = 4;
    
    std::cout << "Round Robin Scheduling" << std::endl;
    
    
    
    return 0;
}
