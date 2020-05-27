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
#include "Schrage.h"

#define MAX_TEST_NUMBER 9

using namespace std;

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
			cout << endl;

			q_MaxHeap* awaitingTasks = new q_MaxHeap(n);
			r_MinHeap* unasignedTasks = new r_MinHeap(n);
			r_MinHeap* unasignedTasks2 = new r_MinHeap(n);

			for (int j = 0; j < n; j++) {
				task temp_task;
				temp_task.id = j + 1;
				data_file >> temp_task.r >> temp_task.p >> temp_task.q;
				unasignedTasks->insert(temp_task);
				unasignedTasks2->insert(temp_task);
			}

			vector<task> result; // tablica zadan uszeregowanych

			task task_min = unasignedTasks->getMin();
			int time = task_min.r; // czas startu

			auto search_start1 = chrono::steady_clock::now();
			cout << "***Algorytm Schrage***" << endl;
			cout << "C_max = " << schrage(unasignedTasks2, awaitingTasks, time, result, n) << endl;
			cout << "Permutacja: ";
			for (int i = 0; i < n; i++) {
				cout << result[i].id << " ";
			}
			cout << endl;

			auto search_end1 = chrono::steady_clock::now();
			cout << endl << "Znaleziono optymalne rozwiazanie dla danych " << data_name[i] << " w czasie: ";
			cout << chrono::duration_cast<chrono::milliseconds>(search_end1 - search_start1).count() << " ms" << endl;

			cout << endl;
			cout << endl;

			//time = task_min.r;

			auto search_start2 = chrono::steady_clock::now();
			cout << "***Algorytm Schrage z przerwaniami***" << endl;
			cout << "C_max = " << schrage_interrupt(unasignedTasks, awaitingTasks, time) << endl;
			auto search_end2 = chrono::steady_clock::now();
			cout << endl << "Znaleziono optymalne rozwiazanie dla danych " << data_name[i] << " w czasie: ";
			cout << chrono::duration_cast<chrono::milliseconds>(search_end2 - search_start2).count() << " ms" << endl;



			result.clear();
			unasignedTasks->~r_MinHeap();
			awaitingTasks->~q_MaxHeap();


			// Test kopcow
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