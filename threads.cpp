#include<iostream>
#include<bits/stdc++.h>
#include <thread>
#include <algorithm>
using namespace std;
void findWaitingTime(int processes[], int n,
						int bt[], int wt[])
{
	wt[0] = 0;
	for (int i = 1; i < n ; i++ )
		wt[i] = bt[i-1] + wt[i-1] ;
}

void findTurnAroundTime( int processes[], int n,
				int bt[], int wt[], int tat[])
{
	for (int i = 0; i < n ; i++)
		tat[i] = bt[i] + wt[i];
}

void findavgTime( int processes[], int n, int bt[])
{
	int wt[n], tat[n], total_wt = 0, total_tat = 0;

	findWaitingTime(processes, n, bt, wt);

	findTurnAroundTime(processes, n, bt, wt, tat);

	cout << "Processes "<< " Burst time "
		<< " Waiting time " << " Turn around time\n";

	string cosa = "";
	for (int i=0; i<n; i++)
	{
		total_wt = total_wt + wt[i];
		total_tat = total_tat + tat[i];
		cout << " " << i+1 << "\t\t" << bt[i] <<"\t "
			<< wt[i] <<"\t\t " << tat[i] <<endl;
	}
	for (int i=0; i<n; i++)
	{
		cosa = cosa + "Process " + to_string(processes[i]) + ":\t";
		for (int j = 0; j<wt[i]; j++)
		{
			cosa = cosa + " ";
		}
		for (int j = 0; j<bt[i]; j++)
		{
			cosa = cosa + "-";
		}
		cosa = cosa + "\n";
	}
	cout << cosa;

	cout << "Average waiting time = "
		<< (float)total_wt / (float)n;
	cout << "\nAverage turn around time = "
		<< (float)total_tat / (float)n;
}

int main1()
{
	int processes[] = { 1, 2, 3};
	int n = sizeof processes / sizeof processes[0];

	int burst_time[] = {10, 5, 8};

	findavgTime(processes, n, burst_time);
	return 0;
}

struct Process
{
	int pid;
	int bt; 
	int priority;
};


bool comparison(Process a, Process b)
{
	return (a.priority > b.priority);
}

void findWaitingTim(Process proc[], int n,
					int wt[])
{
	wt[0] = 0;

	for (int i = 1; i < n ; i++ )
		wt[i] = proc[i-1].bt + wt[i-1] ;
}

void findTurnAroundTim( Process proc[], int n,
						int wt[], int tat[])
{
	for (int i = 0; i < n ; i++)
		tat[i] = proc[i].bt + wt[i];
}

void findavgTim(Process proc[], int n)
{
	int wt[n], tat[n], total_wt = 0, total_tat = 0;

	findWaitingTim(proc, n, wt);

	findTurnAroundTim(proc, n, wt, tat);

	cout << "\nProcesses "<< " Burst time "
		<< " Waiting time " << " Turn around time\n";

	for (int i=0; i<n; i++)
	{
		total_wt = total_wt + wt[i];
		total_tat = total_tat + tat[i];
		cout << " " << proc[i].pid << "\t\t"
			<< proc[i].bt << "\t " << wt[i]
			<< "\t\t " << tat[i] <<endl;
	}
	string cosa = "";
	for (int i=0; i<n; i++)
	{
		cosa = cosa + "Process " + to_string(proc[i].pid) + ":\t";
		for (int j = 0; j<wt[i]; j++)
		{
			cosa = cosa + " ";
		}
		for (int j = 0; j<proc[i].bt; j++)
		{
			cosa = cosa + "-";
		}
		cosa = cosa + "\n";
	}
	cout << cosa;
	cout << "\nAverage waiting time = "
		<< (float)total_wt / (float)n;
	cout << "\nAverage turn around time = "
		<< (float)total_tat / (float)n;
}

void priorityScheduling(Process proc[], int n)
{
	sort(proc, proc + n, comparison);

	cout<< "Order in which processes gets executed \n";
	for (int i = 0 ; i < n; i++)
		cout << proc[i].pid <<" " ;

	findavgTim(proc, n);
}

void main2()
{
	Process proc[] = {{1, 10, 2}, {2, 5, 0}, {3, 8, 1}};
	int n = sizeof proc / sizeof proc[0];
	priorityScheduling(proc, n);
}

int mat[10][6];
  
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
  
void arrangeArrival(int num, int mat[][6])
{
    for(int i=0; i<num; i++)
    {
        for(int j=0; j<num-i-1; j++)
        {
            if(mat[j][1] > mat[j+1][1])
            {
                for(int k=0; k<5; k++)
                {
                    swap(mat[j][k], mat[j+1][k]);
                }
            }
        }
    }
}
  
void completionTime(int num, int mat[][6])
{
    int temp, val;
    mat[0][3] = mat[0][1] + mat[0][2];
    mat[0][5] = mat[0][3] - mat[0][1];
    mat[0][4] = mat[0][5] - mat[0][2];
      
    for(int i=1; i<num; i++)
    {
        temp = mat[i-1][3];
        int low = mat[i][2];
        for(int j=i; j<num; j++)
        {
            if(temp >= mat[j][1] && low >= mat[j][2])
            {
                low = mat[j][2];
                val = j;
            }
        }
        mat[val][3] = temp + mat[val][2];
        mat[val][5] = mat[val][3] - mat[val][1];
        mat[val][4] = mat[val][5] - mat[val][2];
        for(int k=0; k<6; k++)
        {
            swap(mat[val][k], mat[i][k]);
        }
    }
}
  
int main3()
{
    int num, temp;
      
    num = 3;
    int mat[10][6] {{2, 0,5},{1,2,10}, {3, 1,8}};
    cout<<"Before Arrange...\n";
    cout<<"Process ID\tArrival Time\tBurst Time\n";
    for(int i=0; i<num; i++)
    {
        cout<<mat[i][0]<<"\t\t"<<mat[i][1]<<"\t\t"<<mat[i][2]<<"\n";
    }
      
    arrangeArrival(num, mat);
    completionTime(num, mat);
    cout<<"Final Result...\n";
    cout<<"Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    string cosa;
    for(int i=0; i<num; i++)
    {
        cout<<mat[i][0]<<"\t\t"<<mat[i][1]<<"\t\t"<<mat[i][2]<<"\t\t"<<mat[i][4]<<"\t\t"<<mat[i][5]<<"\n";
        cosa = cosa + "Process: " + to_string(mat[i][0]) + "\t";
        for(int j = 0; j < mat[i][1]; j++){
            cosa = cosa + " ";
        }
        for(int j = 0; j < mat[i][4]; j++){
            cosa = cosa + "*";
        }
        for(int j = 0; j < mat[i][2]; j++){
            cosa = cosa + "-";
        }
        cosa = cosa + "\n";
    }
    cout << cosa;

}

int main(){
	thread t1 (main1);
	thread t2 (main2);
	thread t3 (main3);
	t1.join();
	t2.join();
	t3.join();
	return 0;
}
