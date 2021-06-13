#pragma once

#pragma once
#pragma once
#include <string>
using namespace std;


//this is the user class. Each node in the queue represents a user.
class User {
	int key;
	int id;
	char operationType;

public:
	User() {
		key = id = 0;
		operationType = '\0';
	}
	User(int k, int i, char s)
		:key(k), id(i), operationType(s)
	{};

	User& operator= (const User& obj) {
		key = obj.key;
		id = obj.id;
		operationType = obj.operationType;
		return *this;
	}

	//the operators are overloaded since they are used in reheap up as well as reheap down
	
	bool operator == (const User& obj) {
		return key == obj.key;
	}

	bool operator != (const User& obj) {
		return key != obj.key;
	}

	bool operator < (const User& obj) {
		return (key < obj.key);
	}
	bool operator <= (const User& obj) {
		return (key <= obj.key);
	}
	bool operator > (const User& obj) {
		return (key > obj.key);
	}

	int getKey() {
		return key;
	}

	int getId() {
		return id;
	}

	char getOperation() {
		return operationType;
	}


	~User() {
		//nothing to be deleted
	}
};

