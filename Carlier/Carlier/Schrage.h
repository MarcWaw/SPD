#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

#include "Task.h"
#include "MaxHeap.h"
#include "MinHeap.h"


int calculateC_MAX(vector<task> tasks) {
	int m = 0, c = 0;
	for (int i = 0; i < tasks.size(); i++) {
		m = max(tasks[i].r, m) + tasks[i].p;
		c = max(c, m + tasks[i].q);
	}
	return c;
}

////////////// Algorytm Schrage
int schrage(r_MinHeap* unasignedTasks, q_MaxHeap* awaitingTasks, int t, vector<task> &result, int n) {
	r_MinHeap* unasignedTasks_copy = new r_MinHeap(n);
	unasignedTasks_copy = unasignedTasks;
	q_MaxHeap* awaitingTasks_copy = new q_MaxHeap(n);
	awaitingTasks_copy = awaitingTasks;
	int time = 0;
	time = t;


	while (result.size() != n) {
		while (unasignedTasks_copy->isEmpty() == false && unasignedTasks_copy->getMin().r <= time) {
			awaitingTasks_copy->insert(unasignedTasks_copy->extractMin());
		}
		if (awaitingTasks_copy->isEmpty() == false) {
			result.push_back(awaitingTasks_copy->extractMax());
			time = time + result.back().p;
		}
		else { // jesli nie ma dostepnych zadan to przeskocz z czasem
			time = unasignedTasks_copy->getMin().r;
		}

		// Bledny wynik dla data003 

	}
	int C_max = calculateC_MAX(result);

	return C_max;
}

/////////////////// Schrage z przerwaniami 
int schrage_interrupt(r_MinHeap* unasignedTasks, q_MaxHeap* awaitingTasks, int time) {
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

			if (temp1.q > now.q) { // jezeli nowe zadanie ma wieksze q niz obecnie wykonywane
				now.p = time - temp1.r; // zmiana wielkosci p wykonywanego zadania
				time = temp1.r;
				if (now.p > 0) { // jezeli jeszcze cos jest to zrobienia w tym zadaniu to dodaj do kopca oczekujacych
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
	return C_max;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////