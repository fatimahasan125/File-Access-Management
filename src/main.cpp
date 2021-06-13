#include <iostream>
using namespace std;
#include <vector>
#include "Queue.h"
#include "HashTable.h"
#include <fstream>
#include <string>


void Load(string filename, HashTable<int, File> &table) {
	ifstream fin(filename.c_str());
	if (fin) {
		string firstLine;
		//ignoring the first line of the file
		getline(fin, firstLine);
		int user_id, file_id, priority;
		char operation_type;
		char ch;

		fin >> file_id;
		while (!fin.eof()) {
			
			fin.get(ch);
			fin >> user_id;
			fin.get(ch);
			fin >> priority;
			fin.get(ch);
			fin >> operation_type;

			File file(file_id);
			User user(priority, user_id, operation_type);
			table.Insert(file_id, file);
			table[file_id].RequestFileAccess(user);
			fin >> file_id;
		}

	}
	else
		cout << "Error opening file" << endl;
}


int main() {

	int choice = 0;

	int tableSize;
	cout << "Enter the maximum number of entries that you wish to test" << endl;
	cin >> tableSize;
	
	HashTable<int, File> table(tableSize, 99999);

	while (choice != -1) {
		cout << "1. Print Hash Table with File Information" << endl;
		cout << "2. Load data from file" << endl;
		cout << "3. Insert a file" << endl;
		cout << "4. Delete a file" << endl;
		cout << "5. Request Access to a file by a user" << endl;
		cout << "6. Release a file by a user" << endl<<endl;
		cout << "Enter -1 to QUIT" << endl << endl;
		cin >> choice;


		if (choice == 1) {
			table.Print();
		}
		else if (choice == 2) {
			string name;
			cout << endl << endl << "Enter File Name to Load data from" << endl;
			cin >> name;
			Load(name, table);
			cout << endl << endl << "Here is all the information stored in the table" << endl << endl;
			table.Print();
		}
		else if (choice == 3) {
			int file_id;
			cout << "Enter file id" << endl;
			cin >> file_id;
			File file(file_id);

			cout << endl << endl;
			if (table.Insert(file_id, file)) {
				cout << endl<<endl<<"File Inserted successfully" << endl<<endl;
				cout << endl<<endl<<"Here is the complete data of all the files" << endl << endl;
				table.Print();
			}
			else
				cout << endl<<endl<<"This file already exists" << endl<<endl;

		}
		else if (choice == 4) {
			cout << "The file will only be deleted if no user is currently accessing it" << endl;
			cout << "Enter the id of file to delete" << endl;
			int id;
			cin >> id;
			if (table.findID(id)) {
				if (table[id].getSizeOfCurrentUsers() == 0) {
					table.Delete(id);
					cout <<endl<<endl<< "File deleted successfully" << endl<<endl;
					cout << "Here is the current complete data of all the files" << endl << endl;
					table.Print();
				}
				else
					cout <<endl<<endl<< "Could not delete file. Some users were currently accessing it" << endl<<endl;
			}
			else
				cout <<endl<<endl<< "File not found" << endl<<endl;

		}
		else if (choice == 5) {
			int user_id, file_id, priority;
			char operation_type;
			cout << "Enter the ID of the user" << endl;
			cin >> user_id;
			cout << "Enter the ID of the file" << endl;
			cin >> file_id;
			cout << "Enter the operation type" << endl;
			cout << "R. Read" << endl;
			cout << "W. Write" << endl;
			cin >> operation_type;
			cout << "Enter the priority (Max 100)" << endl;
			cin >> priority;
			if (operation_type == 'r')
				operation_type = 'R';
			else if (operation_type == 'w')
				operation_type = 'W';

			User user(priority, user_id, operation_type);
			if (table.findID(file_id)) {
				table[file_id].RequestFileAccess(user);
				cout << endl << endl;
				table.Print();
			}
			else
				cout << endl << endl << "No such file could be found" << endl << endl;

			

		}
		else if (choice == 6) {
			int user_id, file_id;
			cout << "Enter the ID of the user" << endl;
			cin >> user_id;
			cout << "Enter the ID of the file" << endl;
			cin >> file_id;
			if (table.findID(file_id)) {
				if (table[file_id].releaseAccess(user_id))
					cout << endl<<endl<<"Successful Operation" << endl<<endl;
				else
					cout << "Unsuccessful Operation: User not found" << endl;
			}
			else
				cout << endl<<endl<<"Unsuccessful Operation: File Not Found!" << endl<<endl;
		}
		else if (choice != -1)
			cout << "Invalid choice" << endl;

	}
	

	
}