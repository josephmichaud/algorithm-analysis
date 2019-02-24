#include <iostream>
#include <fstream>
#include <vector> 
#include <cstdlib> 
#include <cmath>
#include <chrono> 
#include <algorithm>

using namespace std;
using namespace chrono;

void maxHeapify(vector<int>& heap, int heapSize, int i);
void quickSort(vector<int>& quick, int left, int right);

int main() {
	int n;
	ofstream insertionFile("insertionResults.csv", ios::out | ios::trunc);
	ofstream heapFile("heapResults.csv", ios::out | ios::trunc);
	ofstream quickFile("quickResults.csv", ios::out | ios::trunc);
	double insertionConstant, heapConstant, quickConstant;
	for (n = 1000; n <= 50000; n += 1000) {
		double insertionTotal = 0, insertionAvg, heapTotal = 0, heapAvg, quickTotal = 0, quickAvg;
		for (int trial = 1; trial <= 5; trial++) {
			vector<int> elements;
			for (int i = 0; i < n; i++) {
				elements.push_back(rand()); //GENERATE ELEMENTS
			}
			time_point<high_resolution_clock> start, end;
			duration<double> elapsed;
			//INSERTION SORT
			vector<int> insertion = elements;
			start = high_resolution_clock::now();
			for (int i = 1; i < n; i++) {
				int current = insertion[i];
				for (int j = i - 1; j >= 0; j--) {
					if (insertion[j] > current) {
						int temp = insertion[j];
						insertion[j] = current;
						insertion[j + 1] = temp;
					}
				}
			}
			end = high_resolution_clock::now();
			elapsed = end - start;
			insertionTotal += elapsed.count();
			//HEAP SORT
			vector<int> heap = elements;
			start = high_resolution_clock::now();
			for (int i = n / 2 - 1; i >= 0; i--) {
				maxHeapify(heap, n, i);
			}
			for (int i = n-1; i >= 0; i--) {
				int temp = heap[0];
				heap[0] = heap[i];
				heap[i] = temp;
				maxHeapify(heap, i, 0);
			}
			end = high_resolution_clock::now();
			elapsed = end - start;
			heapTotal += elapsed.count();
			//QUICK SORT
			start = high_resolution_clock::now();
			quickSort(elements, 0, n-1);
			end = high_resolution_clock::now();
			elapsed = end - start;
			quickTotal += elapsed.count();
		}
		cout << "n = " << n << endl;
		//INSERTION SORT RESULTS
		insertionAvg = insertionTotal / 5;
		insertionConstant = max(insertionConstant, insertionAvg / (n*n));
		insertionAvg = insertionAvg * pow(10, 3); //convert to ms
		insertionFile << n << "," << insertionAvg << endl;
		cout << "I Sort: " << insertionAvg << "ms" << endl;
		//HEAP SORT RESULTS
		heapAvg = heapTotal / 5;
		heapConstant = max(heapConstant, heapAvg / (n*log2(n)));
		heapAvg = heapAvg * pow(10, 3); //convert to ms
		heapFile << n << "," << heapAvg << endl;
		cout << "H Sort: " << heapAvg << "ms" << endl;
		//QUICK SORT RESULTS
		quickAvg = quickTotal / 5;
		quickConstant = max(quickConstant, quickAvg / (n*log2(n)));
		quickAvg = quickAvg * pow(10, 3); //convert to ms
		quickFile << n << "," << quickAvg << endl;
		cout << "Q Sort: " << quickAvg << "ms" << endl;
		cout << endl;
	}
	//INSERTION SORT FINISH
	cout << "Insertion Sort Constant: " << insertionConstant << endl;
	insertionFile << insertionConstant << endl;
	insertionFile.close();
	//HEAP SORT FINISH
	cout << "Heap Sort Constant: " << heapConstant << endl;
	heapFile << heapConstant << endl;
	heapFile.close();
	//QUICK SORT FINISH
	cout << "Quick Sort Constant: " << quickConstant << endl;
	quickFile << quickConstant << endl;
	quickFile.close();
}

void maxHeapify(vector<int>& heap, int heapSize, int i) {
	int leftChildIndex = 2*i + 1;
	int rightChildIndex = 2*(i + 1);
	int indexOfLargest;
	if (leftChildIndex < heapSize && heap[leftChildIndex] > heap[i]) {
		indexOfLargest = leftChildIndex;
	}
	else {
		indexOfLargest = i;
	}
	if (rightChildIndex < heapSize && heap[rightChildIndex] > heap[indexOfLargest]) {
		indexOfLargest = rightChildIndex;
	}
	if (indexOfLargest != i) {
		int temp = heap[i];
		heap[i] = heap[indexOfLargest];
		heap[indexOfLargest] = temp;
		maxHeapify(heap, heapSize, indexOfLargest);
	}
}

void quickSort(vector<int>& array, int left, int right) {
	int i = left;
	int j = right;
	int pivot = array[(left + right) / 2];
	while (i <= j) {
		while (array[i] < pivot) i++;
		while (array[j] > pivot) j--;
		if (i <= j) {
			int temp = array[i];
			array[i] = array[j];
			array[j] = temp;
			i++;
			j--;
		}
	}
	if (left < i - 1) {
		quickSort(array, left, i - 1);
	}
	if (i < right) {
		quickSort(array, i, right);
	}
}