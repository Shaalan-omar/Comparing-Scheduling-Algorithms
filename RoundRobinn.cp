
#include<stdio.h>
#include <time.h>

struct proc{
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
    bool isCompleted;
};

 
int main()
{

    int waiting_time=0;
    int turnaround_time=0;
    int response_time=0;
    
    
      int i, n, total = 0, x, counter = 0, timeQuantum;
      int temp[10000];
      float averageWT, averageTAT,averageRT;
      printf("Please enter the numeber of processes here: ");
      scanf("%d", &n);
      x = n;
      proc p[n];
      //generate random arrival time and burst time for each process
        for(i = 0; i < n; i++)
        {
            p[i].pid = i+1;
            p[i].arrival_time = i+5;
            p[i].burst_time = i+10;
            p[i].isCompleted = false;
            temp[i] = p[i].burst_time;
        }
    //   for(i = 0; i < n; i++)
    //   {
    //         // printf("Arrival Time of process %d: ", i + 1);
    //         // scanf("%d", &p[i].arrival_time);
    //         // printf("Burst Time: ");
    //         // scanf("%d", &p[i].burst_time);
    //         // temp[i] = p[i].burst_time;
    //     p[i].pid = i + 1;
    //     p[i].arrival_time = i+5;
    //     p[i].burst_time = i+10;
    //   }
 
      printf("Enter Time Quantum:");
      scanf("%d", &timeQuantum);
      printf("Process ID   Burst Time    Turnaround Time    Waiting Time\n");
      for(total = 0, i = 0; x != 0;)
      {
            if(temp[i] <= timeQuantum && temp[i] > 0)
            {
                  total = total + temp[i];
                  temp[i] = 0;
                  counter = 1;
            }
            else if(temp[i] > 0)
            {
                  temp[i] = temp[i] - timeQuantum;
                  total = total + timeQuantum;
            }
            if(temp[i] == 0 && counter == 1)
            {
                  x--;
                  waiting_time = waiting_time + total + 1 - p[i].arrival_time - p[i].burst_time;
                  turnaround_time = turnaround_time + total + 1 - p[i].arrival_time;
                    response_time = response_time + total + 1 - p[i].arrival_time;
                  counter = 0;
                  printf("Process %d, burst time: %d, turnaround time: %d, waiting time: %d\n", i + 1, p[i].burst_time, total + 1 - p[i].arrival_time, total  + 1 - p[i].arrival_time - p[i].burst_time);

            }
            if(i == n - 1)
            {
                  i = 0;
            }
            else if(p[i+1].arrival_time <= total)
            {
                  i++;
            }
            else
            {
                  i = 0;
            }
      }
 
      averageWT = waiting_time * 1.0 / n;
      averageTAT = turnaround_time * 1.0 / n;
      averageRT = response_time * 1.0 / n;

      printf("Average Waiting Time: %f\n", averageWT);
      printf("Average Turnaround Time: %f\n", averageTAT);
        printf("Average Response Time: %f", averageRT);

      return 0;
}
