#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Process {
private:
    int arrival_time;
    int burst_time;
    int starting_time;
    int finishing_time;
    bool has_finished;

public:
    Process(int arrivalTime, int burstTime) : arrival_time(arrivalTime), burst_time(burstTime), starting_time(0), finishing_time(0), has_finished(false) {}

    void setStartingTime(int startingTime) {
        starting_time = startingTime;
    }

    void setFinishingTime(int finishingTime) {
        finishing_time = finishingTime;
    }

    int getWaitingTime() const {
        return starting_time - arrival_time;
    }

    int getTurnaroundTime() const {
        return finishing_time - arrival_time;
    }

    int getArrivalTime() const {
        return arrival_time;
    }

    int getBurstTime() const {
        return burst_time;
    }

    bool hasFinished() const {
        return has_finished;
    }

    void setHasFinished(bool hasFinished) {
        has_finished = hasFinished;
    }

};

int getShortestJob(const vector <Process> &processes) {
    int shortest = 0;

    for (int i = 0; i < processes.size(); i++) {
        if (processes[i].getBurstTime() < processes[shortest].getBurstTime() && processes[i].hasFinished() == false) {
            shortest = i;
        }

        if (processes[i].getBurstTime() > processes[shortest].getBurstTime() && processes[shortest].hasFinished() == true) {
            shortest = i;
        }

        if (processes[i].getBurstTime() == processes[shortest].getBurstTime()) {
            if (processes[shortest].hasFinished()) {
                shortest = i;
            }
        }
    }

    return shortest;
}

int getEarlyArrivedJob(const vector <Process> &processes) {
    int earliest = 0;

    for (int i = 0; i < processes.size(); i++) {

        if (processes[i].getArrivalTime() < processes[earliest].getArrivalTime() && processes[i].hasFinished() == false) {
            earliest = i;
        }

        if (processes[i].getArrivalTime() > processes[earliest].getArrivalTime() && processes[earliest].hasFinished() == true) {
            earliest = i;
        }

        if (processes[i].getArrivalTime() == processes[earliest].getArrivalTime()) {
            if (processes[earliest].hasFinished()) {
                earliest = i;
            }
        }
    }

    return earliest;
}

int main() {
    vector <Process> processes = {
            Process(5, 6),
            Process(3, 7),
            Process(7, 5),
            Process(8, 7)
    };

    int progressed_time = 0;
    int processes_count = (int) processes.size();

    for (int i = 0; i < processes_count; i++) {
        int shortest_job = getShortestJob(processes);      // 2
        int early_arrived_job = getEarlyArrivedJob(processes);      // 1

        int current_job = shortest_job;

        if (processes[current_job].getArrivalTime() > progressed_time) {
            current_job = early_arrived_job;

            if (progressed_time < processes[current_job].getArrivalTime()) {
                progressed_time = processes[current_job].getArrivalTime();
            }
        }

        processes[current_job].setStartingTime(progressed_time);
        progressed_time += processes[current_job].getBurstTime();

        processes[current_job].setFinishingTime(progressed_time);
        processes[current_job].setHasFinished(true);
    }

    cout << "Processes\tWaiting Time\tTurnaround Time" << endl;
    for (int i = 0; i < processes.size(); i++) {
        cout << "P" << (i + 1) << "\t\t\t" << processes[i].getWaitingTime() << "\t\t\t" << processes[i].getTurnaroundTime() << endl;
    }

    return 0;
}
