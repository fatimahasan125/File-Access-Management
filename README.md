# File-Access-Management
A simple project implementing file access management in C++ using hashing 

We use a priority queue to maintain the list of users who want to access a file for reading or writing. We have developed a template-based Priority Queue implemented as Max heap using STL vectors.
Each node in the queue maintains the following information

- Key (to maintains Priority)
- Id of the user
- Operation type (read or write)

Functions in the priority Queue class

• BuildQueue: Takes in an unsorted array and convert in to a priority queue
• ExtractMax: Removes and returns the maximum element
• FindMax: Returns the maximum value in O(1) time
• FindMin: Returns the minimum value in O(1) time
• Insert: Insert a value with given priority
• size
• empty

A generic template-based Hash Table is built to maintain a repository of the files. The hash table uses chaining to
resolve collision. STL (standard template library) linked lists are used for chaining. In the hash table file id is used as hashing index.
Each node in the linked list has a pointer to a priority queue of the users who wants to access the file, called the waiting
queue. If a user requests an access to a file. We will check the file’s waiting priority queue. If queue is empty the user will be granted
access otherwise, he will be inserted in the particular file’s waiting queue with given priority.


Following are the functionalities of the Hash Table:

Insert a file in the hash table using a hash function based on file id
• Request File Access
      o Get User Id and File Id as input
      o Get priority as input
              ▪ user can either give a number for priority or
              ▪ specify priority is high or low
              • If priority is high, then we will assign the user a number(priority) that is maximum in the given
              file’s waiting queue. (using FindMax function in the priority queue)
              • If priority is low, then we will assign the user a number(priority) that is minimum value in the
              given file’s current waiting queue. (using FindMin function in the priority queue)

      o Insert a user with given id in the file’s waiting queue with given priority. If waiting queue is empty and no user is
      currently accessing the file, we give the user immediate access to the file.
      o If file does not exist print error message
      
• Release File
      o If a user no longer needs to access a file, we provide access to the next user with highest priority.
              ▪ If the next highest priority user in waiting queue wants a write access, then he got exclusive access to the
              file.
              ▪ However, if the next user with highest priority wants a read access then we grant access to all the top
              priority users in the queue that want read access till we find a user with write access.
                    • For example: if there are 5 users in the waiting queue with following priorities and access requests
                    o UserID 14, read access, priority = 10
                    o UserID 55, read access, priority = 7
                    o UserID 10, read access, priority = 7
                    o UserID 12, write access, priority = 6
                    o UserID 1, read access, priority = 5
                    • We will grant read access to top 3 users. We will remove first three users from waiting priority
                    queue, grant them access to the file and keep track of their IDs.

• Print the Hash table:

      o Print the list of the files in Hash table along with the user’s ids who are currently accessing the file and the next user
      to get the access.
      
 Example output is shown below:
 
 
 
 
 
 
