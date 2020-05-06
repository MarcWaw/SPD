#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <limits>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono>


#include "Task.h"
#include "MaxHeap.h"
#include "MinHeap.h"

#define MAX_TEST_NUMBER 9

using namespace std;

int calculateC_MAX(vector<task> tasks) {
	int m = 0, c = 0;
	for (int i = 0; i < tasks.size(); i++) {
		m = max(tasks[i].r, m) + tasks[i].p;
		c = max(c, m + tasks[i].q);
	}
	return c;
}


////////////// Algorytm Schrage
void schrage(r_MinHeap* unasignedTasks, q_MaxHeap* awaitingTasks, int time, vector<task> result, int n) {
	r_MinHeap* unasignedTasks_copy = unasignedTasks;
	while (result.size() != n) {
		while (unasignedTasks_copy->isEmpty() == false && unasignedTasks_copy->getMin().r <= time) {
			awaitingTasks->insert(unasignedTasks_copy->extractMin());
		}
		if (awaitingTasks->isEmpty() == false) {
			result.push_back(awaitingTasks->extractMax());
			time = time + result.back().p;
		}
		else {
			time = unasignedTasks_copy->getMin().r;
		}

		// Bledny wynik dla data003 

	}
	int C_max = calculateC_MAX(result);
	cout << "***Algorytm Schrage***" << endl;
	cout << "C_max = " << C_max << endl;
	cout << "Permutacja: ";
	for (int i = 0; i < n; i++) {
		cout << result[i].id << " ";
	}
	cout << endl;
}


/////////////////// Schrage z przerwaniami 
void schrage_interrupt(r_MinHeap* unasignedTasks, q_MaxHeap* awaitingTasks, int time) {
	task now, temp1;
	now.r = 0;
	now.p = 0;
	now.q = 0;
	temp1.r = 0; temp1.p = 0; temp1.q = 0;
	int C_max = 0;

	while (!unasignedTasks->isEmpty() || !awaitingTasks->isEmpty()) {
		while (unasignedTasks->isEmpty() == false && unasignedTasks->getMin().r <= time) {
			temp1 = unasignedTasks->getMin();
			awaitingTasks->insert(temp1);
			unasignedTasks->extractMin();

			if (temp1.q > now.q) {
				now.p = time - temp1.r;
				time = temp1.r;
				if (now.p > 0) {
					awaitingTasks->insert(now);
				}
			}
		}

		if (awaitingTasks->isEmpty() == true) { // jezeli zadne zadanie nie jest obecnie wykonywane to zrób skok time
			time = unasignedTasks->getMin().r;
		}
		else { // jezeli jest cos wykonywane
			temp1 = awaitingTasks->getMax();
			awaitingTasks->extractMax();
			now = temp1;
			time = time + temp1.p;
			C_max = max(C_max, time + temp1.q);
		}

	}
	cout << "---Algorytm Schrage z przerwaniami---" << endl;
	cout << "C_max = " << C_max << endl;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
	ifstream data_file;
	const char* file_name = "Data.txt";
	string data_name[MAX_TEST_NUMBER];

	//GENEROWANIE NAZW TESTOW#######################################################################
	string sdata = "data.";
	for (int i = 0; i < MAX_TEST_NUMBER; i++) {
		if (i < 10) {
			data_name[i] = sdata + "00" + to_string(i) + ":";
		}
		else if (i >= 10 && i < 100) {
			data_name[i] = sdata + "0" + to_string(i) + ":";
		}
		else {
			data_name[i] = sdata + to_string(i) + ":";
		}
	}
	
	//OTWARCIE PLIKU################################################################################
	data_file.open(file_name);
	if (data_file.fail()) {
		cerr << "Nie udalo sie otworzyc pliku o nazwie: " << file_name << endl;
		system("pause");
		exit(1);
	}
	else {
		string line;
		cout << "Pomyslnie otwarto plik o nazwie: " << file_name << endl;
		cout << "-------------------------------------------------------------------------" << endl;
		for (int i = 0; i < MAX_TEST_NUMBER; i++) {
			int n = 0; // iloœæ zadañ do wykonania

			while (line != data_name[i]) {
				getline(data_file, line);
			}

			cout << "Znaleziono: " << line << endl;

			data_file >> n;

			cout << "Ilosc zadan do wykonania: " << n << endl;
			
			q_MaxHeap* awaitingTasks = new q_MaxHeap(n);
			r_MinHeap* unasignedTasks = new r_MinHeap(n);

			for (int j = 0; j < n; j++) {
				task temp_task;
				temp_task.id = j + 1;
				data_file >> temp_task.r >> temp_task.p >> temp_task.q;
				unasignedTasks->insert(temp_task);
				//awaitingTasks->insert(temp_task);
			}

			vector<task> result;

			task task_min = unasignedTasks->getMin();
			int time = task_min.r; // czas startu

			/*auto search_start1 = chrono::steady_clock::now();
			schrage(unasignedTasks, awaitingTasks, time, result, n);
			auto search_end1 = chrono::steady_clock::now();
			cout << endl << "Znaleziono optymalne rozwiazanie dla danych " << data_name[i] << " w czasie: ";
			cout << chrono::duration_cast<chrono::milliseconds>(search_end1 - search_start1).count() << " ms" << endl;

			cout << endl;
			cout << endl;


			time = task_min.r;*/

			auto search_start2 = chrono::steady_clock::now();
			schrage_interrupt(unasignedTasks, awaitingTasks, time);
			auto search_end2 = chrono::steady_clock::now();
			cout << endl << "Znaleziono optymalne rozwiazanie dla danych " << data_name[i] << " w czasie: ";
			cout << chrono::duration_cast<chrono::milliseconds>(search_end2 - search_start2).count() << " ms" << endl;



			result.clear();
			unasignedTasks->~r_MinHeap();
			awaitingTasks->~q_MaxHeap();


			/*cout << "Malejaco" << endl; 
			while(!awaitingTasks->isEmpty())
			cout << awaitingTasks->extractMax().q << endl;
			cout << "Rosnaco: " << endl;
			while (!unasignedTasks->isEmpty())
				cout << unasignedTasks->extractMin().r << endl;*/
			cout << "-------------------------------------------------------------------------" << endl;
		}
	}
	data_file.close();

	system("pause");
	return 0;
}