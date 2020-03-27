#pragma once

#include "RPQ.h"

void display_task_list(list<task> task_list) {
	list<task> temp;
	temp = task_list;
	int temp_size = temp.size();
	for (int i = 0; i < temp_size; i++) {
		task temp_task;
		temp_task = temp.front();
		temp.pop_front();
		cout << "Id " << temp_task.id << ": " << temp_task.r << " " << temp_task.p << " " << temp_task.q << endl;
	}
	cout << endl;
}

void display_task_order(list<task> task_list) {
	list<task> temp;
	temp = task_list;
	int temp_size = temp.size();
	cout << "Permutacja: [";
	for (int i = 0; i < temp_size; i++) {
		task temp_task;
		temp_task = temp.front();
		temp.pop_front();
		cout << temp_task.id;
		if (i != temp_size - 1)
			cout << " ";
	}
	cout << "]." << endl;
}

int calculate_execution_time(list<task>task_list) {
	list<task> temp;
	int m = 0;
	int c = 0;
	temp = task_list;
	int temp_size = temp.size();

	for (int i = 0; i < temp_size; i++) {
		task temp_task = temp.front();
		temp.pop_front();
		m = max(temp_task.r, m) + temp_task.p;
		c = max(m + temp_task.q, c);
	}
	return c;
}

task find_task_with_id(list<task> task_list, int id) {
	list<task> temp;
	temp = task_list;

	task searched_task;

	int temp_size = temp.size();
	for (int i = 0; i < temp_size; i++) {
		task temp_task = temp.front();
		temp.pop_front();
		if (temp_task.id == id) {
			searched_task = temp_task;
		}
	}
	return searched_task;
}

int find_max_r(list<task> task_list) {
	list<task> temp;
	temp = task_list;
	int temp_size = temp.size();
	int task_id = 0;

	int max_r = 0;
	for (int i = 0; i < temp_size; i++) {
		task temp_task = temp.front();
		temp.pop_front();

		if (temp_task.r >= max_r) {
			max_r = temp_task.r;
			task_id = temp_task.id;
		}
	}

	return task_id;
}

int find_max_q(list<task> task_list) {
	list<task> temp;
	temp = task_list;
	int temp_size = temp.size();
	int task_id = 0;

	int max_q = 0;
	for (int i = 0; i < temp_size; i++) {
		task temp_task = temp.front();
		temp.pop_front();

		if (temp_task.q >= max_q) {
			max_q = temp_task.q;
			task_id = temp_task.id;
		}
	}

	return task_id;
}

int find_max_p(list<task> task_list) {
	list<task> temp;
	temp = task_list;
	int temp_size = temp.size();
	int task_id = 0;

	int max_p = 0;
	for (int i = 0; i < temp_size; i++) {
		task temp_task = temp.front();
		temp.pop_front();

		if (temp_task.p >= max_p) {
			max_p = temp_task.p;
			task_id = temp_task.id;
		}
	}

	return task_id;
}

int find_max_rpq(list<task> task_list) {
	list<task> temp;
	temp = task_list;
	int temp_size = temp.size();
	int task_id = 0;

	int sum = 0;
	for (int i = 0; i < temp_size; i++) {
		task temp_task = temp.front();
		temp.pop_front();

		int temp_sum = temp_task.r + temp_task.p + temp_task.q;
		if (temp_sum >= sum) {
			sum = temp_sum;
			task_id = temp_task.id;
		}
	}

	return task_id;
}

list<task> sort_list_p(list<task> task_list) {
	list<task> temp, sorted;
	task max_p_task;
	int max_p_id = 0;
	temp = task_list;

	while (!temp.empty()) {
		max_p_id = find_max_p(temp);

		for (int i = 0; i < temp.size(); i++) {
			task temp_task = temp.front();
			temp.pop_front();
			if (temp_task.id == max_p_id) {
				max_p_task = temp_task;
			}
			else {
				temp.push_back(temp_task);
			}
		}
		sorted.push_front(max_p_task);
	}
	return sorted;
}

list<task> sort_list_q(list<task> task_list) {
	list<task> temp, sorted;
	task max_q_task;
	int max_q_id = 0;
	temp = task_list;

	while (!temp.empty()) {
		max_q_id = find_max_q(temp);

		for (int i = 0; i < temp.size(); i++) {
			task temp_task = temp.front();
			temp.pop_front();
			if (temp_task.id == max_q_id) {
				max_q_task = temp_task;
			}
			else {
				temp.push_back(temp_task);
			}
		}
		sorted.push_front(max_q_task);
	}
	return sorted;
}

list<task> sort_list_r(list<task> task_list) {
	list<task> temp, sorted;
	task max_r_task;
	int max_r_id = 0;
	temp = task_list;

	while (!temp.empty()) {
		max_r_id = find_max_r(temp);

		for (int i = 0; i < temp.size(); i++) {
			task temp_task = temp.front();
			temp.pop_front();
			if (temp_task.id == max_r_id) {
				max_r_task = temp_task;
			}
			else {
				temp.push_back(temp_task);
			}
		}
		sorted.push_front(max_r_task);
	}
	return sorted;
}

