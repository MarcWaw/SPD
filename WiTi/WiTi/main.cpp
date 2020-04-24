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
	int p; // czas trwania zadania
	int w; // waga
	int d; // po¿¹dany termin zakoñczenia
	int id;
};

using namespace std;
int main()
{
	const char* file_name = "data.txt";
	const string data_name[MAX_TEST_NUMBER] = { "data.10","data.11","data.12","data.13","data.14","data.15","data.16","data.17","data.18","data.19","data.20" };

	task tasks[MAX_N];

	double time_tab[MAX_TEST_NUMBER];
	double time = 0;

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
		for (int k = 0; k < 11; k++) {
			int n = 0; // iloœæ zadañ do wykonania

			cout << "Plik: " << data_name[k] << ":" << endl;
			while (line != (data_name[k] + ":")) {
				getline(data_file, line);
			}

			data_file >> n;
			cout << "Ilosc zadan do wykonania: " << n << endl;

			for (int j = 0; j < n; j++) {
				tasks[j].id = j;
				data_file >> tasks[j].p >> tasks[j].w >> tasks[j].d;
			}

			// Algorytm PD zaimplementowany zgodnie ze schematem dzia³ania przedstawionym na wyk³adzie: http://mariusz.makuchowski.staff.iiar.pwr.wroc.pl/download/courses/sterowanie.procesami.dyskretnymi/lab.instrukcje/lab02.witi/witi.literatura/SPD_WiTi.pdf

			number_of_permutations = pow(2.0, n);

			vector<int> set_vector(number_of_permutations); // przechowuje kary optymalnego uszeregowania zadañ - oznaczenie F na wyk³adzie

			set_vector[0] = 0;

			int sum_of_p = 0; // d³ugoœæ uszeregowania zadañ - oznaczenie C na wyk³adzie

			auto search_start = chrono::steady_clock::now();

			for (int set_index = 1; set_index < number_of_permutations; set_index++) {
				sum_of_p = 0;
				for (int i = 0, b = 1; i < n; i++, b *= 2) {
					/*
					i - indeks zadania w tabeli
					b - kolejne potegi liczby 2
					*/

					if (set_index & b) { // iloczyn bitowy
						sum_of_p += tasks[i].p;
					}
				}

				set_vector[set_index] = numeric_limits<int>::max(); // ustawienie aktualnego indeksu w set_vector na bardzo du¿¹ liczbê

				for (int i = 0, b = 1; i < n; i++, b *= 2) {
					if (set_index & b) {
						// algorytm PD

						set_vector[set_index] = min(set_vector[set_index], set_vector[set_index - b] + tasks[i].w * max(0, sum_of_p - tasks[i].d));
					}
				}
			}
			cout << endl;
			auto search_end = chrono::steady_clock::now();
			time_tab[k] = chrono::duration_cast<chrono::milliseconds>(search_end - search_start).count();
			cout << "Optymalny czas wykonywania zadan: " << set_vector.back() << " jednostek czasu." << endl;
			cout << endl << "Znaleziono optymalne rozwiazanie dla danych [" << data_name[k] << "] w czasie: " << time_tab[k] << " ms" << endl;
			set_vector.clear();

			cout << "-------------------------------------------------------------------------" << endl;
		}
	}

	data_file.close();

	cout << endl;
	for (int i = 0; i < MAX_TEST_NUMBER; i++) {
		time = time + time_tab[i];
	}
	cout << "Laczny czas trwania programu: " << time << "ms" << endl;

	system("pause");

	return 0;
}