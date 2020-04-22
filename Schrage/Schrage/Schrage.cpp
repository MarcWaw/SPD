#include <iostream>
#include <fstream>
#include <string>

#define MAX_TEST_NUMBER 9

using namespace std;

struct task {
	int q;   // czas stygniêcia zadania 
	int r;   // czas dostarczania zadania
	int p;   // czas trwania zadania
	int id;  // numer zadania
};

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
			task* task_array;

			while (line != data_name[i]) {
				getline(data_file, line);
			}

			cout << "Znaleziono: " << line << endl;

			data_file >> n;

			cout << "Ilosc zadan do wykonania: " << n << endl;
			task_array = new task[n];

			for (int j = 0; j < n; j++) {
				task temp_task;
				temp_task.id = j + 1;
				data_file >> temp_task.r >> temp_task.p >> temp_task.q;
				task_array[j] = temp_task;
			}

			delete[] task_array;
			cout << "-------------------------------------------------------------------------" << endl;
		}
	}
	data_file.close();

	system("pause");
	return 0;
}