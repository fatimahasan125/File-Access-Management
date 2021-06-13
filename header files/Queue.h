#pragma once
#include <vector>
using namespace std;

template <class T>
class PriorityQueue {
private:
	vector<T> data;
	T min;
public:
	PriorityQueue() {
		//no default values to assign
	}
	PriorityQueue(const PriorityQueue& obj) {
		data = obj.data;
		min = obj.min;
	}
	void BuildQueue(vector<T> A) {
		int size = A.size();

		data = A;									//we do not need to push each element separately since the operator = performs deep copy


		for (int i = size / 2 - 1; i >= 0; i--)
			ReHeapDown(i);

		min = data[0];
		for (int i = size / 2; i < size; i++)
			if (data[i] < min)
				min = data[i];

	}

	void ReHeapDown(int index) {
		int size = data.size();
		if (index < size - 1) {
			int leftChild = 2 * index + 1;
			int rightChild = 2 * index + 2;
			int maxChild;
			if (rightChild < size && leftChild < size) {			//if two children exist
				maxChild = rightChild;
				if (data[leftChild] > data[rightChild]) {
					maxChild = leftChild;
				}
			}
			else if (rightChild < size)								//if only right child exists
				maxChild = rightChild;
			else if (leftChild < size)								//if only left child exists
				maxChild = leftChild;
			else
				return;												//if no children exist

			if (data[maxChild] > data[index]) {
				swap(data[maxChild], data[index]);
				ReHeapDown(maxChild);
			}
		}
	}

	T ExtractMax() {
		int size = data.size();
		if (size>1) {
			T max = data[0];
			int flag = 0;
			data[0] = data[size - 1];

			data.pop_back();
			ReHeapDown(0);

			return max;
		}
		else if (size == 1) {
			T max = data[0];
			data.pop_back();
			return max;
		}

	}

	T FindMax() {
		
		if (data.size() >= 1) {
			T max = data[0];
			return max;
		}
	}

	T FindMin() {
	
		if (data.size() > 0)
			return min;
	}

	void Insert(T val) {
		data.push_back(val);
		
		if (data.size() == 1)								//if only one element has been inserted, it means this element is the max as well as the min
			min = val;

		else if (val < min)
			min = val;

		ReHeapUp(0, data.size() - 1);

	}

	void ReHeapUp(int start, int end) {				//start is sent as parameter just to make it generic
		if (end > start) {
			int parent = (end - 1) / 2;
			if (data[parent] < data[end]) {
				swap(data[parent], data[end]);
				ReHeapUp(start, parent);
			}
		}
	}

	bool isEmpty() {
		return data.size() == 0;
	}
	void empty() {
		for (int i = 0; i < data.size(); i++)
			data.pop_back();
	}
	int Size() {
		return data.size();
	}

	void print() {
		int size = data.size();
		for (int i = 0; i < size; i++)
			cout << data[i] << " ";
	}
	~PriorityQueue() {
		//nothing to delete since the vector deallocates itself
	}
};
