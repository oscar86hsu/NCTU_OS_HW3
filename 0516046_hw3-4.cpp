#include <iostream>
#include <fstream>
#include <climits>
#include <queue>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdio.h>
using namespace std;

struct process
{
  int arrival;
  int burst;
  int remain;
  int waiting;
};
queue<process*> que_h,que_m;
vector<process*> vec_l;

bool sortFunction (process* i,process* j) { return (i->remain>j->remain); }

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
	output.open("ans4.txt");
	int n,quantum_h,quantum_m,complete=0,time=0,last_time=-1,finish_time;
	input >> n;
	float sum_waiting=0, sum_turnaround=0;
	process proc[n];
	for(int i=0;i<n;i++)
	{
		input >> proc[i].arrival;
	}
	for(int i=0;i<n;i++)
	{
		input >> proc[i].burst;
		proc[i].remain=proc[i].burst;
		que_h.push(&proc[i]);
	}
	input >> quantum_h >> quantum_m;
	input.close();
	while(complete<n)
	{
		if(!que_h.empty() && que_h.front()->arrival<=time)
		{
			if(que_h.front()->remain>=quantum_h)
			{
				time+=quantum_h;
				que_h.front()->remain-=quantum_h;
				if(que_h.front()->remain<=0)
				{
					complete++;
					finish_time=time;
					que_h.front()->waiting=finish_time-que_h.front()->arrival-que_h.front()->burst;
				}
				else
				{
					que_m.push(que_h.front());
				}
			}
			else
			{
				time+=que_h.front()->remain;
				complete++;
				finish_time=time;
				que_h.front()->waiting=finish_time-que_h.front()->arrival-que_h.front()->burst;
				que_h.front()->remain=0;
			}
			que_h.pop();
		}
		else if(!que_m.empty())
		{
			if(que_m.front()->remain>=quantum_m)
			{
				time+=quantum_m;
				que_m.front()->remain-=quantum_m;
				if(que_m.front()->remain<=0)
				{
					complete++;
					finish_time=time;
					que_m.front()->waiting=finish_time-que_m.front()->arrival-que_m.front()->burst;
				}
				else
				{
					vec_l.push_back(que_m.front());
				}
			}
			else
			{
				time+=que_m.front()->remain;
				complete++;
				finish_time=time;
				que_m.front()->waiting=finish_time-que_m.front()->arrival-que_m.front()->burst;
				que_m.front()->remain=0;
			}
			que_m.pop();
		}
		else if(!vec_l.empty())
		{
			sort(vec_l.begin(), vec_l.end(), sortFunction);
			time+=vec_l.back()->remain;
			complete++;
			finish_time=time;
			vec_l.back()->waiting=finish_time-vec_l.back()->arrival-vec_l.back()->burst;
			vec_l.back()->remain=0;
			vec_l.pop_back();
		}
		else
		{
			time++;
		}
	}
	int turnaround_time[n];
	for(int i=0;i<n;i++)
	{
		turnaround_time[i]=proc[i].burst+proc[i].waiting;
		output << outputFormat(proc[i].waiting) << " " << outputFormat(turnaround_time[i]) << endl;
		sum_waiting+=proc[i].waiting;
		sum_turnaround+=turnaround_time[i];
	}
	output << outputFormat(sum_waiting/n) << endl;
	output << outputFormat(sum_turnaround/n) << endl;
	output.close();

}