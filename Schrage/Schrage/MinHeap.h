#pragma once

#include <iostream>

using namespace std;

struct task {
	int q;   // czas stygniêcia zadania 
	int r;   // czas dostarczania zadania
	int p;   // czas trwania zadania
	int id;  // numer zadania
};

class r_MinHeap
{
public:
	r_MinHeap(int _size);
	~r_MinHeap();

private:
	task* heap_array;
	int _size{};

	int parent(int id) { return id / 2; };
	int left_child(int id) { return 2 * id; };
	int right_child(int id) { return 2 * id + 1; };
	void swap(int id_1, int id_2);
public:
	bool isEmpty() { return _size == 0; };
	task getMax() { return heap_array[1]; };
	void insert(task t);
	void ShiftUp(int id);
	task extractMax();
	void ShiftDown(int id);
	void Display();

};

r_MinHeap::r_MinHeap(int _size)
{
	heap_array = new task[_size + 1];
	heap_array[0].id = -1;
	heap_array[0].r = -1;
	heap_array[0].p = -1;
	heap_array[0].q = -1;
}

r_MinHeap::~r_MinHeap()
{
	delete[] heap_array;
}

void r_MinHeap::swap(int id_1, int id_2)
{
	task temp = heap_array[id_1];
	heap_array[id_1] = heap_array[id_2];
	heap_array[id_2] = temp;
}

void r_MinHeap::insert(task t)
{
	heap_array[++_size] = t;
	ShiftUp(_size);
	return;
}

void r_MinHeap::ShiftUp(int id)
{
	if (id > _size) return;
	if (id == 1) return;
	if (heap_array[id].q > heap_array[parent(id)].q) {
		swap(parent(id), id);
	}
	ShiftUp(parent(id));
}

task r_MinHeap::extractMax()
{
	task qMaxTask = heap_array[1];
	swap(1, _size--);
	ShiftDown(1);
	return qMaxTask;
}

void r_MinHeap::ShiftDown(int id)
{
	if (id > _size) return;

	int swapId = id;

	if (left_child(id) <= _size && heap_array[id].q < heap_array[left_child(id)].q)
		swapId = left_child(id);

	if (right_child(id) <= _size && heap_array[swapId].q < heap_array[right_child(id)].q)
		swapId = right_child(id);

	if (swapId != id) {
		swap(id, swapId);
	}

	return;
}

inline void r_MinHeap::Display()
{
	cout << endl << endl << endl;
	cout << "Tablica Kopca:" << endl;
	for (int i = 1; i <= _size; i++) {
		cout << heap_array[i].q << " ";
	}
	cout << endl;
	return;
}
