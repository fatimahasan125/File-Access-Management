#pragma once


#pragma once
#include "Queue.h"
#include "User.h"


class File {
	friend ostream& operator<<(ostream& fout, File& obj);
	int fileId;
	PriorityQueue<User>* waitingQueue;
	vector<User> currentUsers;

public:
	File() {
		fileId = 0;
		waitingQueue = nullptr;
	}
	File(int id) {
		fileId = id;
		waitingQueue = nullptr;
	}
	File(int f, const PriorityQueue<User> &q) {	
		fileId = f;
		waitingQueue = new PriorityQueue<User>(q);
	}

	int getId() {
		return fileId;
	}

	//this operator is overloaded with int as parameter since if the id is same, that means the file is the same
	bool operator == (int element) {
		return fileId == element;
	}


	//this is the variant of request access that takes an int as priority
	void RequestFileAccess(User user) {

		//if a user is currently accessing the file and the same user requests to access it, then we simply return
		for (int i = 0; i < currentUsers.size(); i++)
			if (currentUsers[i].getId() == user.getId())
				return;

		
		//if there is no waiting queue and no current users then immediate access is given to the user 
		if ((!waitingQueue || waitingQueue->Size() == 0) && currentUsers.size()== 0)
			currentUsers.push_back(user);

		//if the operation of the user is to read
		//and currently some users are accessing the file, then the operation of current
		//users is checked. If any of them is writing, then the user on hand is added to the 
		//waiting queue. Otherwise the priority of this user is checked. If it is greater than the
		//max priority of the waiting queue then he is given immediate access
		else if (currentUsers.size()> 0 && user.getOperation() == 'R') {

			if (currentUsers[0].getOperation() != 'W') {
				if (waitingQueue&& waitingQueue->Size() > 0) {
					User p = waitingQueue->FindMax();
					if (p < user)
						currentUsers.push_back(user);
					else
						waitingQueue->Insert(user);
				}
				else
					currentUsers.push_back(user);

			}
			else {
				if(!waitingQueue)
					waitingQueue = new PriorityQueue<User>();
				waitingQueue->Insert(user);
			}
		}

		//if there is no waiting queue and the operation of the user is to write
		//he is given access only if no user is currently accessing the file
		else if ((!waitingQueue || waitingQueue->Size() == 0) && user.getOperation() == 'W') {
			if (currentUsers.size() != 0) {
				if(!waitingQueue)
					waitingQueue = new PriorityQueue<User>();
				waitingQueue->Insert(user);
			}
			else
				currentUsers.push_back(user);
		}

		else if (waitingQueue) 
			waitingQueue->Insert(user);

	}

	//this is the variant of request access that takes a char as priority
	void RequestFileAccess(int user_id, char priority, char operation_type) {

		//if a user is currently accessing the file and the same user requests to access it, then we simply return
		for (int i = 0; i < currentUsers.size(); i++)
			if (currentUsers[i].getId() == user_id)
				return;

		//if there is a waiting queue, (that means currently some users are accessing the file), and 
		//the user has requested to write, then that user is added to the waiting queue. The priority is calculated
		//based on whether the user has entered high or low
		//But if the user wants to read it, then we check the current user's operation and
		//the new user's priority. If the current user is writing, or the new user's priority is low
		//then the new user has to wait, otherwise immediate access is given since more than one user can 
		//read the file at a time
		if (waitingQueue && waitingQueue->Size()>0) {
			if (operation_type == 'W' || currentUsers[0].getOperation() == 'W' || priority=='l' || priority=='L' ) {
				int p;
				if (priority == 'h' || priority == 'H')
					p = waitingQueue->FindMax().getKey() + 1;

				else if (priority == 'l' || priority == 'L')
					p = waitingQueue->FindMin().getKey() - 1;

				User user(p, user_id, operation_type);
				waitingQueue->Insert(user);
			}
			else {
				User user(1, user_id, operation_type);
				currentUsers.push_back(user);
			}
		}


		else {
			User user(1, user_id, operation_type);		//1 is just a random priority

			if ((!waitingQueue ||waitingQueue->Size()==0) && currentUsers.size() == 0) {
				currentUsers.push_back(user);
			}

			else if (currentUsers.size() > 0 && user.getOperation() == 'R') {

				if (currentUsers[0].getOperation()=='R')
					currentUsers.push_back(user);
				else {
					if(!waitingQueue)
						waitingQueue = new PriorityQueue<User>();
					waitingQueue->Insert(user);
				}
			}

			else if ((!waitingQueue || waitingQueue->Size() == 0) && operation_type == 'W') {
				if (currentUsers.size() != 0) {
					if(!waitingQueue)
						waitingQueue = new PriorityQueue<User>();
					waitingQueue->Insert(user);
				}
				else
					currentUsers.push_back(user);
			}
		
		}
	}

	bool releaseAccess(int user_id) {

		//if there is just one user currently accessing the file, and that user wants to release access
		//then he is simply removed from the current users vector
		if (currentUsers.size() == 1 && currentUsers[0].getId() == user_id) {
			currentUsers.pop_back();

			//these are the conditions if there is a waiting queue
			//if the next user's operation is to write, then he is given EXCLUSIVE access
			if (waitingQueue && waitingQueue->Size()>0) {
				User temp = waitingQueue->ExtractMax();
				if (temp.getOperation() == 'W')
					currentUsers.push_back(temp);

				else {
					//otherwise all the users whose operation is to read are given access
					while (temp.getOperation() == 'R') {
						currentUsers.push_back(temp);
						if (waitingQueue && waitingQueue->Size() > 0) {
							temp = waitingQueue->FindMax();
							if (temp.getOperation() == 'R')
								temp = waitingQueue->ExtractMax();
						}
						else
							break;
					}
				}
			}

			return true;
		}

		//if more than one users are currently accessing the file
		else if (currentUsers.size() > 1) {
			bool flag = false;
			//we search for the user who asked to release the file
			//move all current users one place to the left when we find the user
			//then simply remove the last entry from the vector
			for (int i = 0; i < currentUsers.size(); i++) {
				if (currentUsers[i].getId() == user_id) {
					flag = true;
					for (int j = i + 1; j < currentUsers.size(); j++)
						currentUsers[i++] = currentUsers[j];			//shift each element one place to the left
				}
			}
			if (flag == true)
				currentUsers.pop_back();
			else
				return false;			//this is in case the user isnt found

			return true;
		}
		else
			return false;

	}

	//in order to delete a file,
	//this function will be used to check whether no user is currently accessing it
	int getSizeOfCurrentUsers() {
		return currentUsers.size();
	}

	~File() {
		if (waitingQueue != nullptr && waitingQueue->Size()>0)
			delete waitingQueue;
		
	}
};


ostream& operator<<(ostream& cout, File& obj) {
	
	if (obj.currentUsers.size() > 0) {
		cout << " File " << obj.fileId << "...Access granted to the following user(s): " << endl;
		for (int i = 0; i < obj.currentUsers.size(); i++) {
			cout << "	User " << obj.currentUsers[i].getId() << " , ";
			if (obj.currentUsers[i].getOperation() == 'R')
				cout << "read" << endl;
			else
				cout << "write" << endl;

		}
	}
	else
		cout << " File " << obj.fileId << "...Access granted to none" << endl;

	if (obj.waitingQueue && obj.waitingQueue->Size()>0) {
		cout << endl;
		cout << "	Next User " << obj.waitingQueue->FindMax().getId() << " , ";
		if (obj.waitingQueue->FindMax().getOperation() == 'R')
			cout << "Read" << endl;
		else
			cout << "Write" << endl;

		if (obj.waitingQueue->Size() >= 1) {
			cout << "	Waiting " << obj.waitingQueue->Size() << " users" << endl;
		}
	}
	else {
		cout << endl;
		cout << "	Next none" << endl;
		cout << "	Waiting none" << endl;
	}

	return cout;

}