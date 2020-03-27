#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <chrono>

#define MAX_TEST_NUMBER 121

using namespace std;

int main() {
	ifstream data_file;
	stringstream ss;
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

		for (int i = 0; i < MAX_TEST_NUMBER; i++) {
			int machines = 0;
			int tasks = 0;
			int** time_matrix;

			//WCZYTANIE ZESTAWU DANYCH######################################################################
			cout << "Zestaw danych: " << data_name[i] << endl;
			while (line != (data_name[i] + ":")) {
				getline(data_file, line);
			}

			data_file >> tasks >> machines;
			cout << "Ilosc zadan: " << tasks << endl;
			cout << "Ilosc maszyn: " << machines << endl;

			// Alokacja dynamicznej macierzy
			time_matrix = new int* [tasks];
			for (int j = 0; j < tasks; j++)
				time_matrix[j] = new int[machines];
			//Zapis danych z pliku do macierzy
			for (int a = 0; a < tasks; a++)
				for (int b = 0; b < machines; b++)
					data_file >> time_matrix[a][b]; // a - wiersz b - kolumna
			
			//Wyswietl macierz
			/*for (int a = 0; a < tasks; a++) {
				for (int b = 0; b < machines; b++)
					cout << time_matrix[a][b] << " ";
				cout << endl;
			}*/
			//##############################################################################################

			//ALGORYTM NEH##################################################################################
			auto search_start = chrono::steady_clock::now();

			auto search_end = chrono::steady_clock::now();
			//##############################################################################################

			cout << endl << "Znaleziono optymalne rozwiazanie dla danych [" << data_name[i] << "] w czasie: ";
			cout << chrono::duration_cast<chrono::milliseconds>(search_end - search_start).count() << " ms" << endl;
			cout << "-------------------------------------------------------------------------" << endl;

			//Zwalnianie pamieci macierzy dynamicznej
			for (int i = 0; i < tasks; ++i)
				delete[] time_matrix[i];
			delete[] time_matrix;
		}
	}
	data_file.close();

	system("pause");

	return 0;
}