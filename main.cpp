// OS_project 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>
#include <time.h>
#include <iomanip>
using namespace std;
#pragma warning(disable : 4996)


string help()
{
	string help = " RUN  <PROGRAM NAME> \n KILL <PROCESS ID/PROCESS NAME> \n LIST \n ADD  # # #... \n SUB  # # #... \n MULT # # #... \n DIV  # # #... \n EXIT  \n";
	return help;
}


int add(string data)
{
	int total = 0;
	char char_array[100 + 1];
	strcpy(char_array, data.c_str());

	char *token = strtok(char_array, " ");
	while (token != NULL)
	{
		int value;
		std::stringstream ss(token);
		ss >> value;
		total = total + value;
		token = strtok(NULL, " ");
	}
	return total;
}

int sub(string data)
{
	int total;
	int value;
	int n = data.length();
	char char_array[50 + 1];
	strcpy(char_array, data.c_str());
	char *token = strtok(char_array, " ");
	stringstream ss(token);
	ss >> value;
	total = value;
	token = strtok(NULL, " ");
	while (token != NULL)
	{
		int value;
		std::stringstream ss(token);
		ss >> value;
		total = total - value;
		token = strtok(NULL, " ");
	}
	return total;
}

int mult(string data)
{
	int total = 1;
	int n = data.length();
	char char_array[50 + 1];
	strcpy(char_array, data.c_str());
	char *token = strtok(char_array, " ");
	while (token != NULL)
	{
		int value;
		std::stringstream ss(token);
		ss >> value;
		total = total * value;
		token = strtok(NULL, " ");
	}
	return total;
}

int div(string data)
{
	int total;
	int value;
	int n = data.length();
	char char_array[50 + 1];
	strcpy(char_array, data.c_str());
	char *token = strtok(char_array, " ");
	stringstream ss(token);
	ss >> value;
	total = value;
	token = strtok(NULL, " ");
	while (token != NULL)
	{
		int value;
		stringstream ss(token);
		ss >> value;
		if (value == 0)
		{
			cout << "Division by 0 not allowed" << endl; 
			token = strtok(NULL, " ");
			total = 0;
		}
		else
		{
			total = total / value;
			token = strtok(NULL, " ");
		}
	}
	return total;
}


struct Processes
{
	int p_id;
	HANDLE p_handle;
	string p_name;
	string p_status;
	string s_time;
	string e_time;
	time_t el_time;
};


int main()
{
	Processes p[50];
	string input;
	string data;
	int p_total = 0;
	auto ins= input.substr(0, input.find(' '));	
	while (ins != "EXIT")
	{
		getline(cin, input);
		auto ins = input.substr(0, input.find(' '));
		if (ins == "EXIT")
		{
			exit(0);
		}
		else if (ins == "HELP")
		{
			cout << help() << endl;
		}
		else if (ins == "RUN")
		{
				data = input.substr(input.find(' ') + 1);
				
				//CONVERTING STRING TO LPSTR
				size_t len = data.length();
				LPSTR path = new char[len + 1];
				data._Copy_s(path, len, len);
				path[len] = '\0';
	
				//PARAMETERS FOR CREATEPROCESS()
				
				
				HANDLE p_handle = NULL;
				HANDLE t_handle = NULL;

				DWORD p_id = 0;
				DWORD t_id = 0;

				STARTUPINFO p_start = { 0 };
				PROCESS_INFORMATION p_info = { 0 };
				
				ZeroMemory(&p_start, sizeof(p_start));
				ZeroMemory(&p_info, sizeof(p_info));
				

				BOOLEAN p_running = CreateProcess
				(
					NULL,  
					path,              
					NULL,
					NULL,
					FALSE,
					0,
					NULL,
					NULL,
					&p_start,
					&p_info     // gets populated with handle info
				);
				if (p_running == TRUE)
				{
					time_t start = time(NULL);
					p[p_total].p_status = "active";
					p[p_total].p_name = data;
					p[p_total].p_id = p_info.dwProcessId;
					p[p_total].p_handle = p_info.hProcess;
					p[p_total].s_time = ctime(&start);
					cout << "-->> Process Created" << endl;
					p_total = p_total + 1;
				}
				else
				{
					cerr << "-->> Create Process Failed" << endl;
				}
		}
		else if (ins == "KILL")
		{
			int i;
			int id;
			data = input.substr(input.find(' ') + 1);
			istringstream ss(data);
			ss >> id;
			for (i = 0; i < p_total; i++)
			{
				if (id == p[i].p_id	|| data == p[i].p_name)
				{
					BOOLEAN p_ending = TerminateProcess(p[i].p_handle, 0);
					if (p_ending == TRUE)
					{
						time_t end = time(NULL);
						p[i].e_time = ctime(&end);
						p[i].p_status = "inactive";
						cout << "-->> Process Terminated" << endl;
					}
					else
					{
						cerr << "-->> Terminate Process Failed" << endl;
					}
				}	
			}
		}
		else if (ins == "LIST")
		{
			int i;
			for (i = 0; i < p_total; i++)
			{
				cout << " " << endl;
				cout << "Process ID:" << setw(10) << p[i].p_id << endl;
				cout << "Process Name:" << setw(10) << p[i].p_name << endl;
				cout << "Status:" << setw(15) << p[i].p_status << endl;
				cout << "Starting Time:" << setw(25) << p[i].s_time;
				cout << "Ending Time:" << setw(25) << p[i].e_time << endl;
			}
		}
		else if (ins == "ADD")
		{
			data = input.substr(input.find(' ') + 1);
			cout << add(data) << endl;
		}
		else if (ins == "SUB")
		{
			data = input.substr(input.find(' ') + 1);
			cout << sub(data) << endl;
		}
		else if (ins == "MULT")
		{
			data = input.substr(input.find(' ') + 1);
			cout << mult(data) << endl;
		}
		else if (ins == "DIV")
		{
			data = input.substr(input.find(' ') + 1);
			cout << div(data) << endl;
		}
		else 
		{
			cout << "-->> Invalid Instruction" << endl;
		}
	}

} 
