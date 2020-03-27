#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <string>
#include <chrono>
#include <list>
#include <iterator>

#include "RPQ.h"

#define MAX_TASK_NUMBER 100
#define MAX_TEST_NUMBER 4

using namespace std;
list<task> sort_r_algorithm(list<task> task_list) {
	list<task> temp, optimal_order;

	temp = task_list;

	
	while (!temp.empty()) {
		int max_r_id = find_max_r(temp);
		task max_r_task;
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
		optimal_order.push_front(max_r_task);
	}

	return optimal_order;
}

list<task> shrage_algorithm(list<task> task_list) {
	list<task> unasigned, optimal_order;
	int c_max = 0;
	int n = task_list.size();
	int t = 0;
	int id = 0;

	unasigned = task_list;



	return optimal_order;
}

list<task> algorithm(list<task> task_list) {
	list<task> temp, sorted_r, sorted_q, optimal_order;
	temp = task_list;

	int temp_size = temp.size();
	int max_r_id = find_max_r(temp);
	int max_q_id = find_max_q(temp);

	task max_r_task, max_q_task;
	task current_task;

	int sum = 0;

	if (max_r_id != max_q_id) {
		for (int i = 0; i < temp_size; i++) {
			task temp_task = temp.front();
			temp.pop_front();
			if (temp_task.id == max_r_id) {
				max_r_task = temp_task;
			}
			else {
				temp.push_back(temp_task);
			}
		}

		for (int i = 0; i < temp_size; i++) {
			task temp_task = temp.front();
			temp.pop_front();
			if (temp_task.id == max_q_id) {
				max_q_task = temp_task;
			}
			else {
				temp.push_back(temp_task);
			}
		}
		optimal_order.push_back(max_r_task);
		optimal_order.push_back(max_q_task);
	}
	else {
		for (int i = 0; i < temp_size; i++) {
			task temp_task = temp.front();
			temp.pop_front();
			if (temp_task.id == max_r_id) {
				max_r_task = temp_task;
			}
			else {
				temp.push_back(temp_task);
			}
		}
		optimal_order.push_back(max_r_task);
	}
	
	sorted_r = sort_list_r(temp);

	while (!sorted_r.empty()) {
		current_task = sorted_r.front();
		sorted_r.pop_front();
		if (sum + current_task.r < max_r_task.r) {
			optimal_order.push_front(current_task);
		}
		else {
			sorted_q.push_back(current_task);
		}
		sum = sum + current_task.p;
	}
	sorted_q = sort_list_q(sorted_q);
	while (!sorted_q.empty()) {
		current_task = sorted_q.front();
		sorted_q.pop_front();
		optimal_order.push_back(current_task);
	}
	return optimal_order;
}

int main() {
	const char* file_name = "Data.txt";
	const char* data_name[MAX_TEST_NUMBER] = { "data.1","data.2","data.3","data.4" };
		
	int Sum = 0;
	string line;

	ifstream data_file;

	data_file.open(file_name);

	auto start = chrono::steady_clock::now();

	if (data_file.fail()) {
		cerr << "Nie udalo sie otworzyc pliku o nazwie: " << file_name << endl;
		system("pause");
		exit(1);
	}
	else {
		cout << "Pomyslnie otwarto plik o nazwie: " << file_name << endl;
		cout << "//---------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < MAX_TEST_NUMBER; i++) {
			list<task> task_list, optimal_order;
			int n = 0; // iloœæ zadañ do wykonania

			while (line != data_name[i]) {
				getline(data_file, line);
			}
			
			cout << "Znaleziono: " << line << endl;

			data_file >> n;

			cout << "Ilosc zadan do wykonania: " << n << endl;

			for (int j = 0; j < n; j++) {
				task temp_task;
				temp_task.id = j + 1;
				data_file >> temp_task.r >> temp_task.p >> temp_task.q;
				task_list.push_back(temp_task);
			}

			//display_task_list(task_list);

			//ALGORYTM
			auto search_start = chrono::steady_clock::now();

			optimal_order = sort_r_algorithm(task_list);

			auto search_end = chrono::steady_clock::now();
			//KONIEC ALGORYTMU

			int optimal_time = calculate_execution_time(optimal_order);

			cout << endl << "Znaleziono optymalne rozwiazanie dla danych " << data_name[i] << " w czasie " << chrono::duration_cast<chrono::nanoseconds>(search_end - search_start).count() << " ns\n";
			cout << "Czas wykonywania sie zadan: " << optimal_time << " jednostek czasu." << endl;
			cout << "Najlepsza znaleziona permutacja:" << endl;
			display_task_order(optimal_order);
			//display_task_list(optimal_order);
			cout << "//---------------------------------------------------------------------------------" << endl;
			
			Sum = Sum + optimal_time;
		}
	}
	auto end = chrono::steady_clock::now();

	cout << "\nUzyskany wynik (suma czasow): " << Sum << endl;
	cout << "\nCzas wykonywania zadania ";
	cout << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns ~ ";
	cout << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us ~ ";
	cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms ~ ";
	cout << chrono::duration_cast<chrono::seconds>(end - start).count() << " s\n";

	data_file.close();

	cout << endl;
	system("pause");
		

	return 0;
}