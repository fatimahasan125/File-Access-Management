#pragma once
#include <vector>
#include <list>
#include <ctime>
#include "File.h"
#include <iomanip>

using namespace std;

//a function to find the next prime 
int NextPrime(int num)
{
	int count = 0;
	int prime;
	bool outer = true;
	bool inner = true;
	for (int i = num; outer; i++)
	{
		inner = true;
		count = 0;
		for (int j = 2; j < i/2 && inner; j++)
		{
			if (i%j == 0)
			{
				count++;					//even if one divisor found, that means the number is not prime
				inner = false; 
			}
		}
		if (count == 0)
		{
			outer = false;
			prime = i;
		}
	}

	return prime;
}

template <class key, class value>
class HashTable {
	int size;
	list<pair<key,value>>* table;					//we keep both key and value so we can search just bby using the key
	int a;
	int b;
	int p;

public:
	HashTable(int tableSize, key maxInput) {
		srand(unsigned(time(0)));

		size = NextPrime(tableSize);

		table = new list<pair<key,value>>[size];
		//these all are used in the hash function
		p = NextPrime(maxInput + 1);
		a = rand() % p/2;
		b = rand() % p/2;						//divided by 2 since p in our case is very huge 
									//and a needs to be multiplied

	}

	bool Insert(key k, value val) {

		int index = ( ((k*a) + b) % p) % size;		//universal hash function used to calculate index based on key
													//which in our case is the file ID
	
			for (auto it = table[index].begin(); it != table[index].end(); it++) {
				if ((*it).first == k)
					return false;
			}

		table[index].push_back(make_pair(k,val));
		return true;
	}

	//the condition of whether of not any user is currently accessing the file is checked in main
	//here the file with ID k is just deleted. This function is only called if no user is currently
	//accessing the file
	bool Delete(key k) {
		int index = (((k*a) + b) % p) % size;	

		for (auto it = table[index].begin(); it != table[index].end(); it++) {
			if ((*it).first == k) {
				table[index].erase(it);
				return true;
			}
		}
		return false;
	}

	//overloading this operator for using release file and request file access functions 
	//it returns the file whose id is given as parameter

	value& operator[](key id) {
		int index = (((id*a) + b) % p) % size;

		for (auto it = table[index].begin(); it != table[index].end(); it++)
			if ((*it).first == id)
				return (*it).second;
	}


	//this functions finds a particular id in the table
	//return true if found, otherwise false

	bool findID(key id) {
		int index = (((id*a) + b) % p) % size;

		for (auto it = table[index].begin(); it != table[index].end(); it++)
			if ((*it).first == id)
				return true;

		return false;
	}

	void Print() {
		for (int i = 0; i < size; i++) {
			if (!table[i].empty()) {

				for (auto it = table[i].begin(); it != table[i].end(); it++) {
					cout << "H" << i + 1;
					cout << setw(8) << " --> ";
					cout << (*it).second;
					cout << endl;
				}
				cout << endl;
			}
		}
	}

	~HashTable() {
		if (table)
			delete[] table;
	}

};