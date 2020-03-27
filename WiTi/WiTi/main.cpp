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

#define MAX_TEST_NUMBER 11
#define MAX_N 20

struct task {
	int p;
	int w;
	int d;
	int id;
};

using namespace std;
int main()
{
	const char* file_name = "data.txt";
	const string data_name[MAX_TEST_NUMBER] = { "data.10","data.11","data.12","data.13","data.14","data.15","data.16","data.17","data.18","data.19","data.20" };

	task tasks[MAX_N];

	double number_of_permutations = 0;

	string line;

	ifstream data_file;

	data_file.open(file_name);

	if (data_file.fail()) {
		cerr << "Nie udalo sie otworzyc pliku o nazwie: " << file_name << endl;
		system("pause");
		exit(1);
	}
	else {
		cout << "Pomyslnie otwarto plik o nazwie: " << file_name << endl;
		cout << "-------------------------------------------------------------------------" << endl;
		for (int k = 0; k <1; k++) {
			int n = 0; // iloœæ zadañ do wykonania

			cout << "Plik: " << data_name[k] << ":" << endl;
			while (line != (data_name[k] + ":")) {
				getline(data_file, line);
			}

			data_file >> n;
			cout << "Ilosc zadan do wykonania: " << n << endl;

			for (int j = 0; j < n; j++) {
				//data_file >> p[j] >> w[j] >> d[j];
				tasks[j].id = j;
				data_file >> tasks[j].p >> tasks[j].w >> tasks[j].d;
			}

			// Wyœwietlenie
			/*for (int j = 0; j < n; j++) {
				cout << p[j] << " " << w[j] << " " << d[j] << endl;
			}*/

			number_of_permutations = pow(2.0, n);

			vector<int> sub_set_vector(number_of_permutations);

			sub_set_vector[0] = 0;

			int sum_of_p_InSubSet = 0; // suma czasów wykonania zadañ

			auto search_start = chrono::steady_clock::now();

			for (int sub_set_index = 1; sub_set_index < number_of_permutations; sub_set_index++) {
				sum_of_p_InSubSet = 0;
				for (int i = 0, b = 1; i < n; i++, b *= 2) {
					/*
					i - indeks zadania w tabeli
					b - kolejne potegi liczby 2
					*/

					if (sub_set_index & b) { // iloczyn bitowy
						sum_of_p_InSubSet += tasks[i].p;
						//cout << "Zaszedl iloczyn bitowy" << endl;
					}
				}

				sub_set_vector[sub_set_index] = numeric_limits<int>::max();
				
				for (int i = 0, b = 1; i < n; i++, b *= 2) {
					if (sub_set_index & b) {
						// algorytm PD
						
						sub_set_vector[sub_set_index] = min(sub_set_vector[sub_set_index], sub_set_vector[sub_set_index - b] + tasks[i].w * max(0, sum_of_p_InSubSet - tasks[i].d));
					}
				}
			}
			cout << endl;
			auto search_end = chrono::steady_clock::now();
			cout << "Optymalny czas wykonywania zadan: " << sub_set_vector.back() << " jednostek czasu." << endl;
			cout << endl << "Znaleziono optymalne rozwiazanie dla danych [" << data_name[k] << "] w czasie: " << chrono::duration_cast<chrono::milliseconds>(search_end - search_start).count() << " ms" << endl;
			sub_set_vector.clear();

			cout << "-------------------------------------------------------------------------" << endl;
		}
	}

	data_file.close();

	cout << endl;
	system("pause");

	return 0;
}