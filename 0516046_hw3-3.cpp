#include <iostream>
#include <fstream>
#include <climits>
#include <queue>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdio.h>

using namespace std;

template <typename T>
string outputFormat(const T a_value, const int n = 5)
{
    ostringstream out;
    string result;
    out.precision(n);
    out << fixed << a_value;
    result=out.str();
    while((result.back()=='0' || result.back()=='.') && result.find('.')<result.size())
    {
    	result.pop_back();
    }
    return result;
}

int main(int argc, char *argv[])
{

	ifstream input;
	ofstream output;
	input.open(argv[1]);
	output.open("ans3.txt");
	int n,quantum;
	input >> n;
	int proc_a[n],proc_b[n];
	int remain_time[n], complete=0, time=0, min=INT_MAX, shortest=0, finish_time;
	int waiting_time[n], turnaround_time[n];
	float sum_waiting=0, sum_turnaround=0;
	queue<int> que;
	for(int i=0;i<n;i++)
	{
		input >> proc_a[i];
	}
	for(int i=0;i<n;i++)
	{
		input >> proc_b[i];
		remain_time[i]=proc_b[i];
	}
	input >> quantum;
	input.close();
	que.push(0);
	while(complete<n)
	{
		if(remain_time[que.front()]>=quantum)
		{
			time+=quantum;
			remain_time[que.front()]-=quantum;
			for(int i=0;i<n;i++)
			{
				if((proc_a[i]<=time) && (proc_a[i]>time-quantum) && (remain_time[i]>0))
					que.push(i);
			}
			if(remain_time[que.front()]<=0)
			{
				complete++;
				finish_time=time;
				waiting_time[que.front()]=finish_time-proc_a[que.front()]-proc_b[que.front()];
				que.pop();
			}
			else
			{
				que.push(que.front());
				que.pop();
			}
		}
		else
		{
			time+=remain_time[que.front()];
			for(int i=0;i<n;i++)
			{
				if((proc_a[i]<=time) && (proc_a[i]>time-remain_time[que.front()]) && (remain_time[i]>0))
					que.push(i);
			}
			complete++;
			finish_time=time;
			waiting_time[que.front()]=finish_time-proc_a[que.front()]-proc_b[que.front()];
			remain_time[que.front()]=0;
			que.pop();
		}
	}
	for(int i=0;i<n;i++)
	{
		turnaround_time[i]=proc_b[i]+waiting_time[i];
		output << outputFormat(waiting_time[i]) << " " << outputFormat(turnaround_time[i]) << endl;
		sum_waiting+=waiting_time[i];
		sum_turnaround+=turnaround_time[i];
	}
	output << outputFormat(sum_waiting/n) << endl;
	output << outputFormat(sum_turnaround/n) << endl;
	output.close();
}