#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <chrono>

#define MAX_TEST_NUMBER 121

using namespace std;

struct taskp{
	int id;
	int priority;
};

//WYLICZANIE CZAS�W#############################################################################
int** caclculate_left(int** matrix, int m, int n) {
	int** temp_matrix;
	// Alokacja dynamicznej macierzy
	temp_matrix = new int* [n];
	for (int j = 0; j < n; j++)
		temp_matrix[j] = new int[m];
	//Zapis danych z pliku do macierzy
	for (int a = 1; a < n; a++)
		for (int b = 1; b < m; b++)
			temp_matrix[a][b] = NULL; // a - wiersz b - kolumna

	return temp_matrix;

	for (int i = 0; i < n; ++i)
		delete[] temp_matrix[i];
	delete[] temp_matrix;
}

int** caclculate_right(int** matrix, int m, int n) {
	int** temp_matrix;
	// Alokacja dynamicznej macierzy
	temp_matrix = new int* [n];
	for (int j = 0; j < n; j++)
		temp_matrix[j] = new int[m];
	//Zapis danych z pliku do macierzy
	for (int a = 1; a < n; a++)
		for (int b = 1; b < m; b++)
			temp_matrix[a][b] = NULL; // a - wiersz b - kolumna

	return temp_matrix;

	for (int i = 0; i < n; ++i)
		delete[] temp_matrix[i];
	delete[] temp_matrix;
}
//##############################################################################################

//WYLICZANIE CMAX###############################################################################
int calculate_c_max(int** matrix, int* permutation, int m, int n) {
	int c_max = 0;

	int *m_time = new int[m];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (m_time[j] < matrix[permutation[i]][j])
				m_time[j] = m_time[j] + matrix[permutation[i]][j];
		}
	}

	delete[] m_time;
	return c_max;
}
//##############################################################################################

int main() {
	ifstream data_file;
	const char* file_name = "Data.txt";
	string data_name[MAX_TEST_NUMBER];
	
	//GENEROWANIE NAZW TESTOW#######################################################################
	string sdata = "data.";
	for (int i = 0; i < MAX_TEST_NUMBER; i++) {
		if (i < 10) {
			data_name[i] = sdata + "00" + to_string(i);
		}
		else if (i >= 10 && i < 100) {
			data_name[i] = sdata + "0" + to_string(i);
		}
		else {
			data_name[i] = sdata + to_string(i);
		}
	}
	//##############################################################################################

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
		auto experiment_start = chrono::steady_clock::now();
		for (int i = 0; i < MAX_TEST_NUMBER; i++) {
			int m = 0;          // maszyny
			int n = 0;          // zadania

			taskp* priority_array;// tablica priorytetow zadan
			int** time_matrix;  // macierz czasow

			//WCZYTANIE ZESTAWU DANYCH######################################################################
			cout << "Zestaw danych: " << data_name[i] << endl << endl;
			while (line != (data_name[i] + ":")) {
				getline(data_file, line);
			}

			data_file >> n >> m;
			cout << "Ilosc zadan: " << n << endl;
			cout << "Ilosc maszyn: " << m << endl;

			// Alokacja dynamicznej macierzy
			time_matrix = new int* [n];
			for (int j = 0; j < n; j++)
				time_matrix[j] = new int[m];
			//Zapis danych z pliku do macierzy
			for (int a = 0; a < n; a++)
				for (int b = 0; b < m; b++)
					data_file >> time_matrix[a][b]; // a - wiersz b - kolumna
			
			
			//Wyswietl macierz
			/*
			cout << endl <<  "Macierz czasow wykonywania: " << endl;
			for (int a = 0; a < n; a++) {
				for (int b = 0; b < m; b++)
					cout << time_matrix[a][b] << " ";
				cout << endl;
			}
			*/
			//##############################################################################################

			//WYZNACZANIE PRIORYTETOW ZADAN#################################################################
			priority_array = new taskp[n];

			for (int a = 0; a < n; a++) {
				int priority_sum = 0;
				for (int b = 0; b < m; b++) {
					priority_sum = priority_sum + time_matrix[a][b];
				}
				priority_array[a].id = a + 1;;
				priority_array[a].priority = priority_sum;
			}

			
			//Wyswietl priorytety zadan
			/*
			cout << endl << "Priorytety zadan: " << endl;
			for (int a = 0; a < n; a++) {
				cout << "Zadanie " << priority_array[a].id << ": " << priority_array[a].priority << endl;
			}
			*/
			//TODO
			//Sortowanie QuickSortem
			
			//##############################################################################################

			//ALGORYTM NEH##################################################################################
			auto search_start = chrono::steady_clock::now();
			
			for (int j = 0; j < n; j++) {
				int* permutation = new int[j + 1];
				for (int k = 0; k < j + 1; k++) {
					permutation[k] = k;
				}
			}


			auto search_end = chrono::steady_clock::now();
			//##############################################################################################

			cout << endl << "Znaleziono optymalne rozwiazanie dla danych " << data_name[i] << " w czasie: ";
			cout << chrono::duration_cast<chrono::milliseconds>(search_end - search_start).count() << " ms" << endl;
			cout << "-------------------------------------------------------------------------" << endl;

			//Zwalnianie pamieci macierzy dynamicznej
			for (int i = 0; i < n; ++i)
				delete[] time_matrix[i];
			delete[] time_matrix;
			delete[] priority_array;
		}
		auto experiment_end = chrono::steady_clock::now();
		cout << endl << "Obliczenia calosci zadanie trwaly: ";
		cout << chrono::duration_cast<chrono::milliseconds>(experiment_end - experiment_start).count() << " ms" << endl;
	}
	data_file.close();

	system("pause");

	return 0;
}