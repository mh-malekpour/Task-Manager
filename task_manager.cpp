#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include<fstream>

using namespace std;

class Time {
public:
	void currenTime() {
		time_t t = time(0);
		tm* now = localtime(&t);
		cout << now->tm_mday << "-" << now->tm_mon + 1 << " ";
		cout << now->tm_hour << ":" << now->tm_min << endl;
	}
	int currentMonth() {
		time_t t = time(0);
		tm* now = localtime(&t);
		return now->tm_mon + 1;
	}
	int currentDay() {
		time_t t = time(0);
		tm* now = localtime(&t);
		return now->tm_mday;
	}
	int currentHour() {
		time_t t = time(0);
		tm* now = localtime(&t);
		return now->tm_hour;
	}
	int currentMinute() {
		time_t t = time(0);
		tm* now = localtime(&t);
		return now->tm_min;
	}
};

class Task {
public:
	friend class Year;

	void set_title(string title) {
		this->title = title;
	}
	void set_start_hour(int start_hour) {
		this->start_hour = start_hour;
	}
	void set_end_hour(int end_hour) {
		this->end_hour = end_hour;
	}
	void set_start_minute(int start_minute) {
		this->start_minute = start_minute;
	}
	void set_end_minute(int end_minute) {
		this->end_minute = end_minute;
	}
	void set_start_day(int start_day) {
		this->start_day = start_day;
	}
	void set_end_day(int end_day) {
		this->end_day = end_day;
	}
	void set_start_month(int start_month) {
		this->start_month = start_month;
	}
	void set_end_month(int end_month) {
		this->end_month = end_month;
	}
	string get_title() {
		return title;
	}
	int get_start_hour() {
		return start_hour;
	}
	int get_end_hour() {
		return end_hour;
	}
	int get_start_minute() {
		return start_minute;
	}
	int get_end_minute() {
		return end_minute;
	}
	int get_start_day() {
		return start_day;
	}
	int get_end_day() {
		return end_day;
	}
	int get_start_month() {
		return start_month;
	}
	int get_end_month() {
		return end_month;
	}

private:
	string title;
	int start_hour, end_hour;
	int start_minute, end_minute;
	int start_day, end_day;
	int start_month, end_month;
};

class Day {
public:
	friend class Year;

	vector<Task> get_tasklist() {
		return tasklist;
	}

	void bubbleSort() {
		for (int i = 0; i < tasklist.size() - 1; i++) {
			for (int j = i; j < tasklist.size(); j++) {
				if (tasklist[j].get_start_hour() > tasklist[j + 1].get_start_hour()) {
					Task temp = tasklist[j];
					tasklist[j] = tasklist[j + 1];
					tasklist[j + 1] = temp;
				}
				if (tasklist[j].get_start_hour() == tasklist[j + 1].get_start_hour()) {
					if (tasklist[j].get_start_minute() >= tasklist[j + 1].get_start_minute()) {
						Task temp = tasklist[j];
						tasklist[j] = tasklist[j + 1];
						tasklist[j + 1] = temp;
					}
				}
			}
		}
	}

	void displayTasksDay() {
		for (int i = 0; i < tasklist.size(); i++) {
			cout << "\t(" << i + 1 << ") \"" << tasklist[i].get_title() << "\" ";
			cout << "[" << tasklist[i].get_start_hour() << ":" << tasklist[i].get_start_minute() << " - " << tasklist[i].get_end_hour() << ":" << tasklist[i].get_end_minute() << "]" << endl;
		}
	}
	void free_T(int hour, int minute)
	{
		for (int i = 0; i<tasklist.size(); i++)
		{
			if (tasklist[i].get_start_hour() <= hour)
			{
				if (tasklist[i].get_end_hour()>hour)
					tasklist.erase(tasklist.begin() + i);
				else if (tasklist[i].get_start_minute() <= minute)
				{
					tasklist.erase(tasklist.begin() + i);
				}
			}

		}
	}
private:

	vector<Task> tasklist;
};

class Month {
public:
	friend class Year;

	void displayTasksMonth() {
		for (int i = 1; i <= 31; i++) {
			day[i].displayTasksDay();
		}
	}
	void free_day(int day, int hour, int minute)
	{
		this->day[day].free_T(hour, minute);
	}
private:
	Day day[32];
};


class Year {
private:
	Month month[13];
public:
	void free()
	{

		int day, month, hour, minute;
		string free_time;
		cin >> free_time;
		this->month[month].free_day(day, hour, minute);
	}
	void month_display()
	{
		Time now;
		month[now.currentMonth()].displayTasksMonth();

	}

	void print_all()
	{
		for (int i = 1; i <= 12; i++)
			for (int j = 1; j <= 31; j++)
				month[i].day[j].displayTasksDay();
	}

	void day_display()
	{
		Time now;
		month[now.currentMonth()].day[now.currentDay()].displayTasksDay();
	}

	void add()
	{
		int c = 0;
		string command, title, s_month, s_day, s_hour, s_minute, e_month, e_day, e_hour, e_minute;
		while (true) {
			getline(cin, command);
			string syllab;
			stringstream input(command);
			getline(input, syllab, ' ');
			if (syllab == "title" && c == 0) {
				c++;
				getline(input, syllab, ' ');
				getline(input, title, '\n');
			}
			else if (syllab == "starts" && c == 1) {
				c++;
				getline(input, syllab, ' ');
				getline(input, s_day, '-');
				getline(input, s_month, ' ');
				getline(input, s_hour, ':');
				getline(input, s_minute, '\n');
			}
			else if (syllab == "ends" && c == 2) {
				c++;
				getline(input, syllab, ' ');
				getline(input, e_day, '-');
				getline(input, e_month, ' ');
				getline(input, e_hour, ':');
				getline(input, e_minute, '\n');
			}
			else if (syllab == "done") {
				break;
			}
			if (c == 3) {
				int sd = atoi(s_day.c_str());
				int smo = atoi(s_month.c_str());
				int sh = atoi(s_hour.c_str());
				int smi = atoi(s_minute.c_str());
				int ed = atoi(e_day.c_str());
				int emo = atoi(e_month.c_str());
				int eh = atoi(e_hour.c_str());
				int emi = atoi(e_minute.c_str());
				Task temp;
				temp.set_title(title);
				temp.set_start_day(sd);
				temp.set_start_month(smo);
				temp.set_start_hour(sh);
				temp.set_start_minute(smi);
				temp.set_end_day(ed);
				temp.set_end_month(emo);
				temp.set_end_hour(eh);
				temp.set_end_minute(emi);
				month[smo].day[sd].tasklist.push_back(temp);
				c = 0;
			}
		}
	}

	void find(string command)
	{
		string mm, hh;
		getline(cin, command);
		string syllab;
		stringstream input(command);
		getline(input, syllab, ' ');
		getline(input, syllab, ' ');
		getline(input, hh, ':');
		getline(input, mm, '\n');
		int h = atoi(hh.c_str());
		int m = atoi(mm.c_str());
		int lenghth = h * 60 + m;
		Time c;
		vector<Task> temp;
		for (int i = c.currentDay(); i <= 31; i++) {
			month[c.currentMonth()].day[i].bubbleSort();
			for (Task t : month[c.currentMonth()].day[i].get_tasklist()) {
				temp.push_back(t);
			}
		}

		int counter[31] = { 0 };
		int hour_now = Time().currentHour(), minute_now = Time().currentMinute();
		for (int i = 0; i < month[c.currentMonth()].day[c.currentDay()].tasklist.size(); i++) {
			if (hour_now > month[c.currentMonth()].day[c.currentDay()].tasklist[i].get_start_hour()) {
				counter[c.currentDay()] = i + 1;
			}
			if (hour_now == month[c.currentMonth()].day[c.currentDay()].tasklist[i].get_start_hour())
				if (minute_now > month[c.currentMonth()].day[c.currentDay()].tasklist[i].get_start_minute()) {
					counter[c.currentDay()] = i + 1;
				}
		}
		int min[31] = { 0 }, st_h[31], st_m[31];
		for (int i = 0; i < 31; i++)
			min[i] = 10000;
		for (int start_hour = 0; start_hour < 24; start_hour++)
			for (int start_minute = 0; start_minute < 60; start_minute++)
			{
				int end_hour = start_hour + h, end_minute = start_minute + m;
				int count = 0;
				for (int d = c.currentDay(); d <= 31; d++) {
					for (int t = counter[d]; t < month[c.currentMonth()].day[d].tasklist.size(); t++) {
						int current_task_start = month[c.currentMonth()].day[d].tasklist[t].get_start_hour() * 60 + month[c.currentMonth()].day[d].tasklist[t].get_start_minute();
						int current_task_end = month[c.currentMonth()].day[d].tasklist[t].get_end_hour() * 60 + month[c.currentMonth()].day[d].tasklist[t].get_end_minute();
						int x_start = start_hour * 60 + start_minute, x_end = end_hour * 60 + end_minute;
						if (current_task_start < x_start && x_start < current_task_end)
							count++;
						else if (current_task_start < x_end && x_end < current_task_end)
							count++;
					}
					if (count < min[d])
					{
						st_h[d] = start_hour;
						st_m[d] = start_minute;
						min[d] = count;
					}
				}
			}
		int mini = 0;
		for (int i = 0; i < 31; i++)
			if (min[i] < min[mini])
				mini = i;
		cout << mini << "-" << c.currentMonth() << "[" << st_h[mini] << ":" << st_m[mini] << " - " << (st_h[mini] + h) << ":" << (st_m[mini] + m) << "]" << endl;
	}

	void free()
	{

	}


};

int main() {
	Time now;
	Year y;
	while (true) {
		string command;
		getline(cin, command);
		string order;
		stringstream input(command);
		getline(input, order, ' ');
		if (order == "today") {
			y.day_display();
		}
		else if (order == "month") {
			y.month_display();
		}
		else if (order == "add") {
			y.add();
		}
		else if (order == "find") {
			y.find(command);
		}
		else if (order == "now") {
			now.currenTime();
		}
		else if (order == "schedule") {
			//y.schedule();
		}
		else if (order == "free") {
			y.free();
		}
		else
			break;
		ofstream file("data.dat", ios::binary);
		file.write(reinterpret_cast<char*>(&y), sizeof(y));
	}
}
