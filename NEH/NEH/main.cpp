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

#define MAX_TEST_NUMBER 121

using namespace std;

struct taskp{
	int id;
	int priority;
};

void Swap(int* &tab, int a, int b) {
	int temp = 0;

	temp = tab[a];
	tab[a] = tab[b];
	tab[b] = temp;
}

///////////////////////////////////////////////////////////////////////////////////

// sortowanie malej¹co ze wzglêdu na id
void Quick_Sort(taskp* tab, int left, int right)
{
	int i = left;
	int j = right;

	taskp x = tab[(left + right) / 2];
	do
	{
		while (tab[i].id > x.id)
		i++;

		while (tab[j].id < x.id)
			j--;

		if (i <= j)
		{
			swap(tab[i], tab[j]);

			i++;
			j--;
		}
	} while (i <= j);

	if (left < j) Quick_Sort(tab, left, j);

	if (right > i) Quick_Sort(tab, i, right);

}


//////////////////////////////////////////////////////////////////////////////////////

// sortowanie rosn¹co ze wzglêdu na priorytety
void QuickSort(taskp *tab, int left, int right)
{
	int i = left;
	int j = right;

	taskp x = tab[(left + right) / 2];
	do
	{
		while (tab[i].priority < x.priority)// || (tab[i].priority == x.priority && tab[i].id > x.id))
			i++;

		while (tab[j].priority > x.priority)
			j--;

		if (i <= j )
		{
			swap(tab[i], tab[j]);

			i++;
			j--;
		}
	} while (i <= j);

	if (left < j) QuickSort(tab, left, j);

	if (right > i) QuickSort(tab, i, right);

}

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
			taskp* priority_array = new taskp[n];

			for (int a = 0; a < n; a++) {
				int priority_sum = 0;
				for (int b = 0; b < m; b++) {
					priority_sum = priority_sum + time_matrix[a][b];
				}
				priority_array[a].id = a;
				priority_array[a].priority = priority_sum;
			}
			QuickSort(priority_array, 0, n - 1);


			// Znalezienie obszaru tablicy, gdzie priorytety s¹ równe
			int first_index = 0;
			int last_index = 0;
			for (int i = 0; i < n - 1; i++) {
				if (priority_array[i].priority == priority_array[i + 1].priority) {
					first_index = i;
					while (priority_array[i].priority == priority_array[i + 1].priority) {
						i++;
					}
					last_index = i;
				}
				// Posortowanie tego miejsca ze wzgledu na nr zadania
				Quick_Sort(priority_array, first_index, last_index);
				//sort(priority_array + firstIndexOfSameValue, priority_array + lastIndexOfSameValue + 1, [](const taskp& first, const taskp& second) { return first.id > second.id; });
			}
			

			//Wyswietl priorytety zadan
			/*
			cout << endl << "priorytety zadan: " << endl;
			for (int a = 0; a < n; a++) {
				cout << "zadanie " << priority_array[a].id + 1 << ": " << priority_array[a].priority << endl;
			}*/
			

			//##############################################################################################

			//ALGORYTM NEH ##################################################################################
			auto search_start = chrono::steady_clock::now();
			int* permutation = new int[n];
			int* better_permutation = new int[n];

			for (int q = 0; q < n; q++)
				permutation[q] = 0;
			for (int q = 0; q < n; q++)
				better_permutation[q] = 0;

			for (int j = 0; j < n; j++) {
				int best_c_max = INT_MAX;
				permutation[j] = priority_array[n - 1 - j].id;

				for (int q = 0; q < n; q++)
					better_permutation[q] = permutation[q];
				best_c_max = calculate_from_left_top(time_matrix, better_permutation, m, j + 1);
				
				for (int x = 0; x < j; x++) {
					int new_c_max = INT_MAX;

					Swap(permutation, j - x, j - x - 1);

					new_c_max = calculate_from_left_top(time_matrix, permutation, m, j + 1);

					if (new_c_max <= best_c_max) {
						for (int q = 0; q < n; q++)
							better_permutation[q] = permutation[q];
						best_c_max = new_c_max;
					}
				}
				for (int q = 0; q < n; q++)
					permutation[q] = better_permutation[q];
			}
			
			cout << endl << "Permutacja: " << "[ ";
			for (int j = 0; j < n; j++) {
				cout << better_permutation[j] + 1 << " ";
			}
			cout << "] <---- Najlepsza" << endl;

			/*
			cout << "Permutacja: [ ";
			for (int j = 0; j < n; j++) {
				cout << permutation[j] << " ";
			}
			cout << "]" << endl;
			*/

			auto search_end = chrono::steady_clock::now();
			//##############################################################################################
			int c_max_left_top = calculate_from_left_top(time_matrix, better_permutation, m, n);
			int c_max_right_bottom = calculate_from_right_bottom(time_matrix, better_permutation, m, n);
			int c_max = 0;
			if (c_max_left_top == c_max_right_bottom)
				c_max = c_max_left_top;
				

			cout << "C_max = " << c_max << endl;

			cout << endl << "Znaleziono optymalne rozwiazanie dla danych " << data_name[i] << " w czasie: ";
			cout << chrono::duration_cast<chrono::milliseconds>(search_end - search_start).count() << " ms" << endl;
			cout << "-------------------------------------------------------------------------" << endl;

			//Zwalnianie pamieci macierzy dynamicznej
			for (int i = 0; i < n; ++i)
				delete[] time_matrix[i];
			delete[] time_matrix;
			delete[] priority_array;
			delete[] better_permutation;
			delete[] permutation;
		}

	}
	data_file.close();

	system("pause");

	return 0;
}