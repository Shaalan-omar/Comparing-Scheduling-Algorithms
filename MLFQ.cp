#include<iostream>
#include<fstream>
#include <ctime>
#include <cstdlib>
#include<time.h>
#include<iomanip>
#include <vector>

using namespace std;



struct process
{
    double burst_time;
    double arrival_time;
    double time_quant = 2;
    double waiting_time;
    double TAT;
    double response_time;
    double start_time;
    double end_time;
    bool status_done = false;
    double remaining = burst_time;
};

vector<process> MLFQ(vector<process> p);
vector<process> sort_arrival(vector<process> PT);

int main()
{

    /*srand(time(0));

   ofstream outfile;
    outfile.open("Text.txt");

    for (int i = 0; i < 100; i++) // generating random data, arrival time and burst time
    {
        outfile << (rand() % 100) + 1 << " " << (rand() % 100) << endl;
    }


    outfile.close();

    exit(0);
    */

    vector<process> Vector;

    ifstream readingfile;
    readingfile.open("Text.txt");
    if (readingfile.is_open())
        cout << "File Opened";
    double bt, at;
    int gen_num;
    cout << "Enter the number of processes you want to generate. Please note that the maximum is 10000 : ";
    cin >> gen_num;
    cout << endl;
    while (gen_num < 0 || gen_num>10000)
    {
        cout << "Invalid range. Please reenter : ";
        cin >> gen_num;
        cout << endl;
    }

    for (int i = 0; i < gen_num; i++) // generating random data, arrival time and burst time
    {
        readingfile >> bt;
        readingfile >> at;
        process p{};
        p.arrival_time = at;
        p.burst_time = bt;
        p.remaining = bt;
        Vector.push_back(p);
    }

    //Vector = { {5, 0}, {4, 1}, {2, 2}, {1, 3} };

    Vector = MLFQ(Vector);
    cout << "Array size is : " << Vector.size() << endl;

    double waiting_T = 0;
    double response_T = 0;
    double turnaround_T = 0;

    for (int i = 0; i < Vector.size(); i++)
    {
        waiting_T += (Vector[i].waiting_time);
        response_T += (Vector[i].response_time);
        turnaround_T += (Vector[i].TAT);
    }
    cout << "Average waiting time is : " << waiting_T / Vector.size()<<endl;
    cout << "Average response time is : " << response_T / Vector.size()<<endl;
    cout << "Average trunaround time is : " << turnaround_T / Vector.size()<<endl;
    
    return 0;
}



vector<process> MLFQ(vector<process> p)
{

    vector <process> q1, q2, q3;
    vector <process> Finished_Processes;
    int clock = 0;

    //q1 will use RR, n = 8 - High Priority
    //q2 will use RR, n = 16 - Medium Priority
    //q3 will use FCFS - Low Priority

    for (int i = 0; i < p.size(); i++)
    {
        q1.push_back(p[i]);
    }

    q1 = sort_arrival(q1);
    clock = q1[0].arrival_time;
    while ((!q1.empty()) || (!q2.empty()) || (!q3.empty()))
    {
        while (!q1.empty())
        {
            
            if (q1[0].arrival_time <= clock) {
                if (q1[0].remaining <= 8)
                {
                    if (q1[0].remaining == q1[0].burst_time)
                        q1[0].start_time = clock;

                    q1[0].end_time = clock + q1[0].remaining;
                    clock += q1[0].remaining;
                    q1[0].remaining = 0;
                    q1[0].TAT = q1[0].end_time - q1[0].arrival_time;
                    q1[0].waiting_time = q1[0].TAT - q1[0].burst_time;
                    q1[0].response_time = q1[0].start_time - q1[0].arrival_time;
                    Finished_Processes.push_back(q1[0]);
                    q1.erase(q1.begin() + 0);
                    //cout << q1[0].start_time << setw(20) << q1[0].arrival_time;
                }
                else if (q1[0].remaining > 8)
                {
                    q1[0].start_time = clock;
                    clock += 8;
                    q1[0].remaining -= 8;
                    q1[0].response_time = q1[0].start_time - q1[0].arrival_time;

                    q2.push_back(q1[0]);
                    q1.erase(q1.begin() + 0);
                }
            }
            else
                clock++;
        }

        while (!q2.empty())
        {
            /* for (int i = 0; i < q2.size(); i++)
             {
                 if (q2[i].waiting_time >= 30)
                 {
                     q1.push_back(q2[i]);
                     q2.erase(q2.begin() + i);
                 }
             }*/

            if (q2[0].remaining <= 16)
            {
                q2[0].end_time = clock + q2[0].remaining;
                clock += q2[0].remaining;
                q2[0].remaining = 0;
                q2[0].TAT = q2[0].end_time - q2[0].arrival_time;
                q2[0].waiting_time = q2[0].TAT - q2[0].burst_time;
                //q2[0].response_time = q2[0].start_time - q2[0].arrival_time;
                Finished_Processes.push_back(q2[0]);
                q2.erase(q2.begin() + 0);
            }
            else if (q2[0].remaining > 16)
            {
                clock += 16;
                q2[0].remaining -= 16;

                q3.push_back(q2[0]);
                q2.erase(q2.begin() + 0);
            }

        }

        while (!q3.empty())
        {
            q3[0].end_time = clock + q3[0].remaining;
            clock += q3[0].remaining;

            q3[0].TAT = q3[0].end_time - q3[0].arrival_time;
            q3[0].waiting_time = q3[0].TAT - q3[0].burst_time;

            Finished_Processes.push_back(q3[0]);
            q3.erase(q3.begin() + 0);
        }
    }
    return Finished_Processes;
}


vector<process> sort_arrival(vector<process> PT) {

    vector<process> result;
    int index = 0;
    int smallest = 1000;
    process chosen;
    for (int i = 0; i < PT.size(); i++)
    {

        for (int j = 0; j < PT.size(); j++)
        {
            if ((PT[j].arrival_time < smallest) && (PT[j].status_done == false)) {
                smallest = PT[j].arrival_time;
                chosen = PT[j];
                index = j;
                //temp[j].done = true;

            }
        }
        result.push_back(chosen);
        PT[index].status_done = true;
        smallest = 1000;
    }
    return result;
}