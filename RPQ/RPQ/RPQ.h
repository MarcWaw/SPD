#pragma once

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <string>
#include <chrono>
#include <list>
#include <iterator>

using namespace std;

struct task {
	int q;   // czas stygniêcia zadania 
	int r;   // czas dostarczania zadania
	int p;   // czas trwania zadania
	int id;  // numer zadania
};

void display_task_list(list<task> task_list);
void display_task_order(list<task> task_list);

int calculate_execution_time(list<task>task_list);

task find_task_with_id(list<task> task_list, int id);

int find_max_r(list<task> task_list);
int find_max_q(list<task> task_list);
int find_max_p(list<task> task_list);
int find_max_rpq(list<task> task_list);

list<task> sort_list_p(list<task> task_list);
list<task> sort_list_q(list<task> task_list);
list<task> sort_list_r(list<task> task_list);

