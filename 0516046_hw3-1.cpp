#include <iostream>
#include <fstream>
#include <climits>
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
	output.open("ans1.txt");
	int n;
	input >> n;
	int proc[2][n];
	int remain_time[n], complete=0, time=0, min=INT_MAX, shortest=0, finish_time;
	bool check=false;
	int waiting_time[n], turnaround_time[n];
	float sum_waiting=0, sum_turnaround=0;
	for(int i=0;i<n;i++)
	{
		input >> proc[0][i];
	}
	for(int i=0;i<n;i++)
	{
		input >> proc[1][i];
		remain_time[i]=proc[1][i];
	}
	input.close();
	while(complete<n)
	{
		for(int i=0;i<n;i++)
		{
			if((proc[0][i]<=time) && (remain_time[i]<min) && (remain_time[i]>0))
			{
				min=remain_time[i];
				shortest=i;
				check=true;
			}
		}
		if(!check)
		{
			time++;
			continue;
		}
		time+=remain_time[shortest];
		remain_time[shortest]=0;
		min=INT_MAX;

		if(remain_time[shortest]<=0)
		{
			complete++;
			check=false;
			finish_time=time;
			waiting_time[shortest]=finish_time-proc[1][shortest]-proc[0][shortest];
			if(waiting_time[shortest]<0)
				waiting_time[shortest]=0;
		}
	}

	for(int i=0;i<n;i++)
	{
		turnaround_time[i]=proc[1][i]+waiting_time[i];
		output << outputFormat(waiting_time[i]) << " " << outputFormat(turnaround_time[i]) << endl;
		sum_waiting+=waiting_time[i];
		sum_turnaround+=turnaround_time[i];
	}
	output << outputFormat(sum_waiting/n) << endl;
	output << outputFormat(sum_turnaround/n) << endl;
	output.close();

}