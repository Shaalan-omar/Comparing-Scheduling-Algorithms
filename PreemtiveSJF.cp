#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string.h>
using namespace std;

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int exit_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    int total_idle_time = 0;
    int rem_burst[10000];
    int done[10000];

void PreemtiveSJF(process pr[], int n)
{
  
    memset(done,0,sizeof(done));

    cout << setprecision(2) << fixed;

    int current_time = 0;
    int completed = 0;
    int prev = 0;

    while(completed != n) {
        int proc = -1;
        int minimum = 100000000;
        for(int i = 0; i < n; i++) {
            if(pr[i].arrival_time <= current_time && done[i] == 0) {
                if(rem_burst[i] < minimum) {
                    minimum = rem_burst[i];
                    proc = i;
                }
                if(rem_burst[i] == minimum) {
                    if(pr[i].arrival_time < pr[proc].arrival_time) {
                        minimum = rem_burst[i];
                        proc = i;
                    }
                }
            }
        }

        if(proc != -1) {
            if(rem_burst[proc] == pr[proc].burst_time) {
                pr[proc].start_time = current_time;
                total_idle_time += pr[proc].start_time - prev;
            }
            rem_burst[proc] -= 1;
            current_time++;
            prev = current_time;
            
            if(rem_burst[proc] == 0) {
                pr[proc].exit_time = current_time;
                pr[proc].turnaround_time = pr[proc].exit_time - pr[proc].arrival_time;
                pr[proc].waiting_time = pr[proc].turnaround_time - pr[proc].burst_time;
                pr[proc].response_time = pr[proc].start_time - pr[proc].arrival_time;

                total_turnaround_time += pr[proc].turnaround_time;
                total_waiting_time += pr[proc].waiting_time;
                total_response_time += pr[proc].response_time;

                done[proc] = 1;
                completed++;
            }
        }
        else {
             current_time++;
        }
    }

    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;
    avg_response_time = (float) total_response_time / n;
   
    cout<<endl<<endl;

    cout<<"#P\t"<<"AT\t"<<"BT\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"RT\t"<<"\n"<<endl;

    for(int i = 0; i < n; i++) {
        cout<<pr[i].pid<<"\t"<<pr[i].arrival_time<<"\t"<<pr[i].burst_time<<"\t"<<pr[i].start_time<<"\t"<<pr[i].exit_time<<"\t"<<pr[i].turnaround_time<<"\t"<<pr[i].waiting_time<<"\t"<<pr[i].response_time<<"\t"<<"\n"<<endl;
    }
    cout<<"Average Turnaround Time = "<<avg_turnaround_time<<endl;
    cout<<"Average Waiting Time = "<<avg_waiting_time<<endl;
    cout<<"Average Response Time = "<<avg_response_time<<endl;
   
}

int main() {

    int n;
    struct process pr[10000];


    // cout<<"Enter the number of processes: ";
    // cin>>n;

    // for(int i = 0; i < n; i++) {
    //     cout<<"Enter arrival time of process "<<i+1<<": ";
    //     cin>>pr[i].arrival_time;
    //     cout<<"Enter burst time of process "<<i+1<<": ";
    //     cin>>pr[i].burst_time;
    //     pr[i].pid = i+1;
    //     rem_burst[i] = pr[i].burst_time;
    //     cout<<endl;
    // }

    //generate 50 random processes
    n = 1000;
    for(int i = 0; i < n; i++) {
        pr[i].arrival_time = i+5;
        pr[i].burst_time = i+10;
        pr[i].pid = i+1;
        rem_burst[i] = pr[i].burst_time;
    }

    PreemtiveSJF(pr, n);
   

}

/*
TAT = CT - AT
WT = TAT - BT
RT = ST - AT
*/