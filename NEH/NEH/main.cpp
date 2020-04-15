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
#include <list>

#define MAX_TEST_NUMBER 1

using namespace std;

struct taskp{
	int id;
	int priority;
};

//WYLICZANIE CMAX###############################################################################
int calculate_from_left_top(int** matrix, int* permutation, int m, int n) {
	int c_max = 0;
	int** m_time;
	m_time = new int* [n];
	for (int i = 0; i < n; i++)
		m_time[i] = new int[m];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			m_time[i][j] = 0;
		}
		
	}

	for (int i = 0; i < n; i++) { //zadania
		if (i == 0) {
			for (int j = 0; j < m; j++) {
				if (j == 0) {
					m_time[i][j] = matrix[permutation[i]][j];
				}
				else {
					m_time[i][j] = m_time[i][j-1] + matrix[permutation[i]][j];
				}				
			}
		}
		else {
			for (int j = 0; j < m; j++) { //maszyny
				if (j == 0) {
					m_time[i][j] = m_time[i - 1][j] + matrix[permutation[i]][j];
				}
				else {
					if (m_time[i - 1][j] < m_time[i][j - 1]) {
						m_time[i][j] = m_time[i][j - 1] + matrix[permutation[i]][j];
					}
					else {
						m_time[i][j] = m_time[i - 1][j] + matrix[permutation[i]][j];
					}
				}
			}
		}
	}
	c_max = m_time[n-1][m-1];
	for (int i = 0; i < n; ++i)
		delete[] m_time[i];
	delete[] m_time;
	return c_max;
}

int calculate_from_right_bottom(int** matrix, int* permutation, int m, int n) {
	int c_max = 0;
	int** m_time;
	m_time = new int* [n];
	for (int i = 0; i < n; i++)
		m_time[i] = new int[m];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			m_time[i][j] = 0;
		}

	}

	for (int i = n - 1; i >= 0; i--) { //zadania
		if (i == n - 1) {
			for (int j = m - 1; j >= 0; j--) {
				if (j == m - 1) {
					m_time[i][j] = matrix[permutation[i]][j];
				}
				else {
					m_time[i][j] = m_time[i][j + 1] + matrix[permutation[i]][j];
				}
			}
		}
		else {
			for (int j = m - 1; j >= 0; j--) { //maszyny
				if (j == m - 1) {
					m_time[i][j] = m_time[i + 1][j] + matrix[permutation[i]][j];
				}
				else {
					if (m_time[i + 1][j] < m_time[i][j + 1]) {
						m_time[i][j] = m_time[i][j + 1] + matrix[permutation[i]][j];
					}
					else {
						m_time[i][j] = m_time[i + 1][j] + matrix[permutation[i]][j];
					}
				}
			}
		}
	}
	c_max = m_time[0][0];
	for (int i = 0; i < n; ++i)
		delete[] m_time[i];
	delete[] m_time;
	return c_max;
}
//##############################################################################################

int main() {
	ifstream data_file;
	const char* file_name = "Data.txt";
	string data_name[MAX_TEST_NUMBER];
	int time_sum = 0;
	
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
		for (int i = 0; i < MAX_TEST_NUMBER; i++) {
			int m = 0;          // maszyny
			int n = 0;          // zadania

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
			taskp* sorted_priority_array = new taskp[n];

			for (int a = 0; a < n; a++) {
				sorted_priority_array[a].id = 0;
				sorted_priority_array[a].priority = 0;
			}

			for (int a = 0; a < n; a++) {
				taskp* priority_array = new taskp[n];

				int priority_sum = 0;
				for (int b = 0; b < m; b++) {
					priority_sum = priority_sum + time_matrix[a][b];
				}
				priority_array[a].id = a + 1;;
				priority_array[a].priority = priority_sum;

				



				delete[] priority_array;
			}
			
			
			//Wyswietl priorytety zadan
			
			cout << endl << "Priorytety zadan: " << endl;
			for (int a = 0; a < n; a++) {
				cout << "Zadanie " << sorted_priority_array[a].id << ": " << sorted_priority_array[a].priority << endl;
			}
			
			//TODO
			//Sortowanie QuickSortem
			
			//##############################################################################################

			//ALGORYTM NEH##################################################################################
			auto search_start = chrono::steady_clock::now();
			int* permutation = new int[n];
			for (int j = 0; j < n; j++) {
				permutation[j] = j;
			}
			/*
			cout << "Permutacja: ";
			for (int j = 0; j < n; j++) {
				cout << permutation[j] << " ";
			}
			cout << endl;
			*/
			auto search_end = chrono::steady_clock::now();
			//##############################################################################################
			int c_max_left_top = calculate_from_left_top(time_matrix, permutation, m, n);
			int c_max_right_bottom = calculate_from_right_bottom(time_matrix, permutation, m, n);
			int c_max = 0;
			if(c_max_left_top == c_max_right_bottom)
				c_max = c_max_left_top;

			cout << "C_max = " << c_max << endl;

			cout << endl << "Znaleziono optymalne rozwiazanie dla danych " << data_name[i] << " w czasie: ";
			cout << chrono::duration_cast<chrono::nanoseconds>(search_end - search_start).count() / 1000 << " ms" << endl;
			cout << "-------------------------------------------------------------------------" << endl;

			time_sum = time_sum + chrono::duration_cast<chrono::nanoseconds>(search_end - search_start).count();

			//Zwalnianie pamieci macierzy dynamicznej
			for (int i = 0; i < n; ++i)
				delete[] time_matrix[i];
			delete[] time_matrix;
			delete[]sorted_priority_array;
		}
		cout << endl << "Obliczenia calosci zadanie trwaly (bez alokacji pamiêci): ";
		cout << time_sum / 1000 << " ms" << endl;
	}
	data_file.close();

	system("pause");

	return 0;
}