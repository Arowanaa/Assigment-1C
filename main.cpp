//**************************************************
// main.cpp : This file contains the 'main' function at the end. 
// Program execution starts with the main function.
//**************************************************


//Include libraries for strings and writing/reading from console and text files 
#include <iostream>
#include <string>
#include <fstream>

#include <vector>     //Included for the support of vector
#include <algorithm>  //Included for the support of the generic "find" algorithm

#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
using namespace std;


//**************************************************
// Define a structure type for holding date information
//**************************************************
struct Date 
{
	int day;
	int month;
	int year;
}; 
//Note that you need the semicolon above at the end of the type declaration 


//**************************************************
// The main data structure (a vector as a data container):
// 
//**************************************************
// Declare a vector (of Date) for holding dates as data.
// Note that a vector can change its maximal storage capacity 
//		  during the execution time, and it keeps track of
//        its own size (the current number of records) and capacity.
// So there is 
//    NO need to have a fixed maximal capacity constant (such as CapacityLimitOfArray in 1A)
//    NOR a variable about the current maximal capacity limit (such as capacityLimitOfArray as in 1B)
//    NOR a separate variable (such as numOfRecords in both 1A and 1B) for holding the information of
//    the number of records in it.
// Consequently, we have carefully revised program below
//    such that (without CapacityLimitOfArray and numOfRecords)
//    the vector as a container can still provide all the servicesvect.
//**************************************************
vector< Date > dataContainer;


//In the partially completed project given to you here,
//  dataContainer is a vector of double below
//  for handling a single piece of numerical information in each data record
//  just like Programming #1A and 1B.
//In your complete implementation, 
//  you need to revise dataContaine as a vector of Date as shown above
//  for handling a date (i.e. 3 numbers for day, month, year) in each data record.
//Consequently, you also need to revise many code segments below accordingly 
//  to properly handle dates (instead of doube values) when processing a data record.
//
//vector< double > dataContainer;


//**************************************************
// The following is a collection of functions
//   implementing the data processing services provided 
//   by the main function.
//**************************************************

//print the menu options so the user knows what to enter.
void displayMenu()
{	
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "-      A vector as a data container (data structure) in the main memory        -" << endl;
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "Enter one of the following options: " << endl;
	cout << endl;
	cout << '\t' << "*****  Basic data management options already implemented  *****" << endl;
	cout << '\t' << "K: Resize the container and manually enter a batch of data records into the container." << endl;
	cout << '\t' << "W: Write the data records in the container to a file." << endl;
	cout << '\t' << "R: Read data records from a file into the container." << endl;
	cout << '\t' << "D: Display the current data records in the container." << endl;
	cout << '\t' << "M: Modify one of the records in the container." << endl;
	cout << '\t' << "Q: Quit the program." << endl;
	cout << endl;

	cout << '\t' << "C: Clear and make it an empty container of no records." << endl;
	cout << '\t' << "F: Resize the container and fill random data records into the container." << endl;
	cout << endl;

	cout << '\t' << "*****  Additional operational options to implement  *****" << endl;
	cout << '\t' << "A: Append a new record at the end of the container." << endl;
	cout << '\t' << "I: Insert a new record at a specific location in the container." << endl;
	cout << '\t' << "P: Pop (remove) the record at the end of the container." << endl;
	cout << '\t' << "E: Erase (delete) a record at a specific location in the container." << endl;
	cout << '\t' << "L: Locate (find) a record with a specific value in the container." << endl;
	cout << '\t' << "S: Bubble-Sort the records in the container." << endl;
	cout << endl;

	cout << '\t' << "***** Testing options already implemented *****" << endl;
	cout << '\t' << "O: Test writing data beyond the vector boundary." << endl;
	cout << '\t' << "T: Test the operational performance of the container." << endl;
	cout << "------------------------------------------------------------" << endl;
	
}


//get the input for the menu options.
char getOptionInputFromUser()
{
	char input;
	cout << "Your input: ";
	cin >> input;
	cout << endl; // for spacing
	return input;
}


//get and return a valid number of records.
//==> We have adjusted this function since there is no specific capacity limit any more.
int getNumOfRecordsFromUser()
{
	int n;
	cout << "How many records are you going to have in the container?: ";
	cin >> n;
	while (n < 1 ) //No explicit upper limit, just must be a postive number, 
	{
		cout << "Invalid number, try again (must be a postive number): ";
		cin >> n;
	}
	return n;
}


//A helper function to get a valid index. 
//You should think about how to enhance the implementation below such that 
// it can check whether it is a valid index 
// and keep asking for a new input until a valid index is entered.
//
//!!!==> Write your code to enhance the function e accordingly
int getValidIndexFromUser()
{
	int index = 0;
    bool valid = false;

    while (!valid) {
        cout << '\t' << "What is the index? ";
        cin >> index;

        // Check if the index is out of bounds
        if (index < 0) {
            cout << '\t' << "Please enter a valid index" << endl;
        } else {
            valid = true; // Index is valid, exit the loop
        }
    }

    return index;
}

//get and return a valid file name.
string getFileName()
{
	string name;
	cout << "Enter file name (include .txt): ";
	cin >> name;
	while (name.length() > 20) //verifies that the name is within length limit
	{
		cout << "Your file is " << name.length() << " characters long, please make it less than or equal to 20. Enter a new file name (include .txt): ";
		cin >> name;
	}
	return name;
}

//option K, set the number of records and then 
//  have the user use the keyboard to enter the data into the container. 
//==> We have modified the code here such that
//    (i) it resizes the dataContainer vector properly before storing data records, and
//    (ii) uses the size member function of the vector class to control the loop
//    for getting the specified number of data records from the user. 
//Note: In your complete implementation, each data record is about a date (month, day, year),
//         not a single number in Programming 1A and 1B.
//      Consequently, you need to change the line 
//         cin >> dataContainer[index];
//      to read the informaton of month, day, year seperately and store them properly in
//         dataContainer[index].month, dataContainer[index].day, dataContainer[index].year, 
//      respectively.
// 
//!!!==> Write your code to enhance the function accordingly
void getBatchOfDataFromKeyboard()
{
	//get the number of records, verifies that the number is valid.
	int numOfRecordsInBatch;
	numOfRecordsInBatch = getNumOfRecordsFromUser();
	dataContainer.resize(numOfRecordsInBatch);
    
	for (int index = 0; index < dataContainer.size(); index++)
	{
		cout << "Enter record " << index << " value (month, day, year): ";
		cin >> dataContainer[index].month >> dataContainer[index].day >> dataContainer[index].year;
	}

}


//option W, write the dataContainer contents to the file.
//==> We have modified the code here such that
//    it uses the size member function of the vector class to 
//    (i) determine the number of records in dataContainer, and
//    (ii) control the loop to write the every data records to the file. 
//Note: In your complete implementation, each data record is about a date (month, day, year),
//         not a single number in Programming 1A.
//      Consequently, you need to change the line 
//         fout << endl << dataContainer[index];
//      to write the informaton of month, day, year seperately from
//      dataContainer[index].month, dataContainer[index].day, dataContainer[index].year
//      to the file through fout.
// 
//!!!==> Write your code to enhance the function accordingly
void writeDataRecordsToFile( )
{
	ofstream fout;
	fout.open( getFileName() );
	fout << dataContainer.size();

	for (int index = 0; index < dataContainer.size(); index++)
	{
		fout << endl << dataContainer[index].month << "/" << dataContainer[index].day << "/" << dataContainer[index].year;
	}
	fout.close(); //close the file
	cout << "Data in dataContainer have been written to the file" << endl;
}

//option R, read contents from a file into the dataContainer vector 
//  and update numOfRecords
//==> We have modified the code here such that
//    (i) it resizes the dataContainer vector properly before storing data records, and
//    (ii) uses the size member function of the vector class to control the loop
//    for getting the specified number of data records from the user. 
//Note: In your complete implementation, each data record is about a date (month, day, year),
//         not a single number in Programming 1A.
//      Consequently, you need to change the line 
//         fin >> dataContainer[index];
//      to read the informaton of month, day, year seperately from fin and store them in
//         dataContainer[index].month, dataContainer[index].day, dataContainer[index].year
//     respectively.
// 
//!!!==> Write your code to enhance the function accordingly
void readDataRecordsFromFile( )
{
	ifstream fin;
	fin.open(getFileName()); //open the file
	
	//get the number of records, verifies that the number is valid.
	int numOfRecordsInBatch;
	fin >> numOfRecordsInBatch; //the first line is the number of students
	dataContainer.resize(numOfRecordsInBatch);

	for (int index = 0; index < dataContainer.size(); index++) //get each students scores
	{
		fin >> dataContainer[index].month >> dataContainer[index].day >> dataContainer[index].year;
	}

	fin.close(); //close the file
	cout << "Data have been read from te file into dataContainer" << endl;
}

//Option D, display to the user 
//    the capacity, the number of records, and the records of dataContainer.
//==> We have modified the code here such that
//    it uses the size member function of the vector class to 
//    (i) determine the number of data records in dataContainer, and
//    (ii) control the loop for displaying all the data records in the container. 
//==> In your complete implementation, you need to deal with Date instead of double below.
//    Consequently, you also need to carefully compare the years, months, and days of the dates 
//        to sort them out since you cannot directly compare two Date structures
//		  to determine their order (not until we define relational operators for Date 
//        as we will do later in a future programming assignment).
// 
//!!!==> Write your code to enhance the function accordingly
void displayDataRecords( )
{
	// Display the capacity and size of the container
    cout << "Current vector container capacity: " << dataContainer.capacity() << endl;
    cout << "Number of Records: " << dataContainer.size() << endl;

    // If no records, return early
    if (dataContainer.size() == 0) {
        return;
    }

    // Initialize minIndex and maxIndex to the first record
    int minIndex = 0;
    int maxIndex = 0;

    // Loop through the dataContainer to display all records
    for (int index = 0; index < dataContainer.size(); index++) {
        // Display the current record in "dd/mm/yyyy" format
        cout << "Record " << index << ": "
             << dataContainer[index].day << "/"
             << dataContainer[index].month << "/"
             << dataContainer[index].year << endl;

        // Compare dates to find the minimum and maximum
        // Compare year, then month, then day
        if ((dataContainer[index].year > dataContainer[maxIndex].year) ||
            (dataContainer[index].year == dataContainer[maxIndex].year &&
             dataContainer[index].month > dataContainer[maxIndex].month) ||
            (dataContainer[index].year == dataContainer[maxIndex].year &&
             dataContainer[index].month == dataContainer[maxIndex].month &&
             dataContainer[index].day > dataContainer[maxIndex].day)) 
        {
            maxIndex = index; // Found a newer (later) date
        }
        
        if ((dataContainer[index].year < dataContainer[minIndex].year) ||
            (dataContainer[index].year == dataContainer[minIndex].year &&
             dataContainer[index].month < dataContainer[minIndex].month) ||
            (dataContainer[index].year == dataContainer[minIndex].year &&
             dataContainer[index].month == dataContainer[minIndex].month &&
             dataContainer[index].day < dataContainer[minIndex].day)) 
        {
            minIndex = index; // Found an older (earlier) date
        }
    }

    // Display the minimum (earliest) and maximum (latest) dates
    cout << endl; // For spacing
    cout << "Maximum value (latest date in the container): "
         << dataContainer[maxIndex].day << "/"
         << dataContainer[maxIndex].month << "/"
         << dataContainer[maxIndex].year << endl;

    cout << "Minimum value (earliest date in the container): "
         << dataContainer[minIndex].day << "/"
         << dataContainer[minIndex].month << "/"
         << dataContainer[minIndex].year << endl;
}

//option m, manually change one of the records in the container
//==> We have modified the code here such that
//    it uses the size member function of the vector class to 
//    (i) determine the proper range of the index of a data record in dataContainer.
// 
//!!!==> Write your code to enhance the function accordingly
void modifyRecord( )
{
	//get the index
	int indexNumber;
	cout << "Tell us the index of the data record to modify?  (The first indexe is 0): ";
	cin >> indexNumber;
	
	//Make sure the index is within the proper range. 
	//Repeat the loop for input again if the given index is negative or bigger than it can be.
	while (indexNumber < 0 || indexNumber >= dataContainer.size() ) 
	{
		cout << "Not within the valid index range, please enter a number between 0 and " 
			 << dataContainer.size() - 1 << ": ";
		cin >> indexNumber;
	}

	//get the new data
	//Note: In your completeimplementation you need to change the type 
	//         of newData below to Date, and properly 
	//         read the informaton of month, day, year into newData.
// Get the new date data from the user
    Date newData;
    cout << "Enter new data for this record (day, month, year): ";
    cin >> newData.day >> newData.month >> newData.year;

    // Modify the record at the given index
    dataContainer[indexNumber] = newData;

    // Confirmation of modification
    cout << "Record " << indexNumber << " has been updated to: "
         << newData.day << "/" << newData.month << "/" << newData.year << endl;
}

// Clear and make it an empty container of no records
//==> We have modified the code here such that
//    it uses the clear member function of the vector class to make it an empty class.
void clear()
{
	dataContainer.clear();
}

//option F, set the number of records and fill the container with random records. 
//==> We have modified the code here such that
//    (i) it resizes the dataContainer vector properly before storing data records, and
//    (ii) uses the size member function of the vector class to control the loop
//    for filling random data records into the container. 
//Note: In your complete implementation, each data record is about a date (month, day, year),
//         not a single number in Programming 1A.
//      Consequently, you need to change the line 
//         dataContainer[index] = rand();
//      to properly store a random month, a random day, and a random year in 
//         dataContainer[index].month, dataContainer[index].day, dataContainer[index].year
//     respectively.
// 
//!!!==> Write your code to enhance the function accordingly
void fillBatchOfRandomData(int n)
{
	dataContainer.resize(n);
	srand(time(0));

    for (int index = 0; index < dataContainer.size(); index++) {
        dataContainer[index].month = rand() % 12 + 1;         
        dataContainer[index].day = rand() % 28 + 1;          
        dataContainer[index].year = rand() % (2023 - 1900 + 1) + 1900; 
    }
}


//We no longer need to define our own functions:  push_back, insert, pop_back, and erase
//   
//**************************************************
// Unlike Programming 1A and 1B,
// we don't need to implement the following 4 global functions in 1A
//       push_back, insert, pop_back, erase
//   for managing dataContainer.
// This is because dataContainer is a vector and
//   the vector class already provide member functions for such functionality.
// 
//  push_back ==> Append a new record at the end of the vector
//  insert ==> Insert a new record at (before) a specific place in the vector
//  pop_back ==> Remove the record at the end of the vector
//  erase ==> Erase (remove) a specific record given its index in the vector.
//**************************************************


//Option L: 
//Find a record with a specific value in the vector:
//Return the index of record if it is in the vector,
//Otherwise, return -1 to indicates it is not found
//==> We have modified the code here such that
//    it uses the size member function of the vector class to control the loop
//    for conducting a linear search over the container. 
//Note: In your complete implementation, 
//         change the type of dataToLocate from double to Date since
//         now each data record is about a date (month, day, year),
//         not a single number in Programming 1A and 1B.
//      Consequently, you also need to change the if statement in the for loop 
//      to properly compare the month, day, and year in dataToLocate with
//         the month, day, and year in dataContainer[index]
//      respectively.
//!!!==> Write your code to enhance the function accordingly
int find(Date dataToLocate)
{   //check records one by one;
	//Return the index of the first matching record if found.
	for (int i = 0; i < dataContainer.size(); i++) {
        if (dataContainer[i].day == dataToLocate.day &&
            dataContainer[i].month == dataToLocate.month &&
            dataContainer[i].year == dataToLocate.year) {
            return i;  // Return the index of the first matching record
        }
    }

	//Reach this point only if the record is not found ==> Return -1
	return -1;
}


//Bubble sort the records in dataContainer (a vector now)
//==> In your complete implementation,
//    you reuse and adjust your bubble sort function from Programming 1A
//        to make it work with the vector container of dates.
//    In particular, you need to compare the elements years, months, and days in the dates 
//        to sort them out since you cannot directly compare two Date structures
//		  to determine their order (not until we define relational operators for Date 
//        as we will do later in a future programming assignment).
//
//!!!==> Write your code to enhance the function accordingly
void bubbleSort()
{
	int maxElement; //For holding the info of the maximal number of elements examined on each iteration
	int index;      //For holding the info of the index of an element to be examined 
	Date temp;    //For holding information when swpping the values of two elements

	for (maxElement = dataContainer.size() - 1; maxElement > 0; maxElement--) {
        for (index = 0; index < maxElement; index++) {
            // Compare the years
            if (dataContainer[index].year > dataContainer[index + 1].year) {
                temp = dataContainer[index];
                dataContainer[index] = dataContainer[index + 1];
                dataContainer[index + 1] = temp;
            }
            // compare the months
            else if (dataContainer[index].year == dataContainer[index + 1].year &&
                     dataContainer[index].month > dataContainer[index + 1].month) {
                temp = dataContainer[index];
                dataContainer[index] = dataContainer[index + 1];
                dataContainer[index + 1] = temp;
            }
            // compare the days
            else if (dataContainer[index].year == dataContainer[index + 1].year &&
                     dataContainer[index].month == dataContainer[index + 1].month &&
                     dataContainer[index].day > dataContainer[index + 1].day) {
                temp = dataContainer[index];
                dataContainer[index] = dataContainer[index + 1];
                dataContainer[index + 1] = temp;
            }
        }
    }
}



//Option O: Test writing data beyond the boundary of the vetor as a container.
//==> We have modified the code here such that
//    it uses the size member function of the vector class to 
//    (i) determine the boundary of dataContainer.
//!!!==> In your implementation, 
//       change the type of arbitraryDataRecord deom double to Date.
//       See the "!!!==>" comments embedded in the code below.
void testWritingOutOfBound(int extentOfTesting)
{
	//!!!==> Change the type of arbitraryDataRecord to Date.
	Date arbitraryDataRecord;

	//!!!==> Change the code to properly store some random month, day, year in arbitraryDataRecord.
	arbitraryDataRecord.day = 10;
	arbitraryDataRecord.month = 10;
	arbitraryDataRecord.year = 2020;
	//Write an arbitrary date to the memory outside the boundary of the vector
	for (int index = 0; index < extentOfTesting; index++)
		dataContainer[dataContainer.size() + index] = arbitraryDataRecord;

	cout << '\t' << "Task testWritingOutOfBound finished!" << endl << endl;

}

//******************************************************************
//Option T: Test the running time of each of the following tasks:
// clear the container and then do n random push (append) operations
// clear the container and then do n random insertion operations
// clear the container, fill in n random records and then do n pop operations
// clear the container, fill in n random records and then do n random erase operations
// clear the container, fill in n random records and then do n random find operations
// clear the container, fill in n random records and then bublb sort the records
// 
//This function is already implemented.
//******************************************************************
//==> We have modified the code here such that
//       the function will properly call the member functions of the vector class
//       and the generic sorting algorithm implemted in STL 
//       to test the performace of dataContainer as a vector
//
//!!!==> Write your code to enhance the function for processing dates instead of numbers
//       See the "!!!==>" comments embedded in the code below.
void testPerformance()
{
	cout << endl
		<< '\t' << "Test the operational performance." << endl << endl;

	//Set the size od the container for testing purpose
	int n = getNumOfRecordsFromUser();
    Date randomData;
	char yesOrNo;
	cout << '\t' << "clear the container and then do " << n << " random push_back(append) operations, ready(y / n) ? " << endl;
	cin >> yesOrNo;
	if (yesOrNo == 'y')
	{
		clear();

		//Randomly set up the contents for a data record
		//Note: In your completeimplementation you need to change type 
		//           of your randomData to Date, and properly set up 
		//           a random date in randomData.
		//!!!==> Write your code to enhance the code segment accordingly
		
        randomData.day = rand() % 31 + 1;   // Days between 1 and 31
        randomData.month = rand() % 12 + 1; // Months between 1 and 12
        randomData.year = rand() % 100 + 1920; // Years between 1920 and 2019

        
        dataContainer.push_back(randomData);
    }


	cout << '\t' << "cout << clear the container and then do " << n << " random insertion, ready (y/n)?" << endl;
	cin >> yesOrNo;
	if (yesOrNo == 'y')
	{
		clear();
		for (int i = 0; i < n; i++)
		{
			//Randomly pick an insertion point
			int insertionPoint;
			insertionPoint = rand() % (dataContainer.size() + 1) ;

			//Set up the corresponding iterator
			//Note: In your complete implementation, 
			//      you need to change the line below to
			//      vector< Date >::iterator insertIterator;
		    //!!!==> Write your code to enhance the code segment accordingly
			vector< Date >::iterator insertIterator;
			insertIterator = dataContainer.begin() + insertionPoint;

			//Randomly set up the contents for a data record
			//Note: In your complete implementation, you need to change the type 
			//         of your randomData to Date, and properly store 
			//         random numbers into month, day, year in dataRecord.
			//!!!==> Write your code to enhance the code segment accordingly
			Date dataRecord;
			dataRecord.day = rand() % 31 + 1;   // Days between 1 and 31
            dataRecord.month = rand() % 12 + 1; // Months between 1 and 12
            dataRecord.year = rand() % 100 + 1920; // Years between 1920 and 2019

			//Insert a random data record at the insertion point
			dataContainer.insert(insertIterator, dataRecord);
		}
		cout << '\t' << "Task finished!" << endl << endl;
	}

	cout << '\t' << "clear the container, fill in " << n << " random records and then do " << n << " pop operations, ready (y/n)?" << endl;
	cin >> yesOrNo;
	if (yesOrNo == 'y')
	{
		fillBatchOfRandomData(n);
		for (int i = 0; i < n; i++)
			dataContainer.pop_back();
		cout << '\t' << "Task finished!" << endl << endl;

	}

	cout << '\t' << "clear the container, fill in " << n << " random records and then do " << n << " random erase operations, ready (y/n)?" << endl;
	cin >> yesOrNo;
	if (yesOrNo == 'y')
	{
		fillBatchOfRandomData(n);

		for (int i = 0; i < n; i++)
		{
			int deletionPoint;
			//Randomly pick a deletion point
			deletionPoint = rand() % dataContainer.size();

			//Set up the corresponding iterator
			//Note: In your complete implementation, 
			//      you need to change the line below to
			//      vector< Date >::iterator deleteIterator;
			//!!!==> Write your code to enhance the code segment accordingly
			vector< double >::iterator deleteIterator;
			deleteIterator = dataContainer.begin() + deletionPoint;

			dataContainer.erase(deleteIterator);
		}
		cout << '\t' << "Task finished!" << endl << endl;
	}

	cout << '\t' << "clear the container, fill in " << n << " random records and then do " << n << " random find operations, ready (y/n)" << endl;
	cin >> yesOrNo;
	if (yesOrNo == 'y')
	{
		fillBatchOfRandomData(n);

		for (int i = 0; i < dataContainer.size(); i++)
		{
			//Pick a random record to locate
			int randomIndex;
			randomIndex = rand() % dataContainer.size();

			//Note: In your complete implementation, you need to change the type 
			//         of randomRecordToLocate to Date.
			//!!!==> Write your code to enhance the code segment accordingly
			double randomRecordToLocate;
			randomRecordToLocate = dataContainer[randomIndex];

			//Try to locate the record 
			int indexOfLocatedRecord;
			indexOfLocatedRecord = find(randomRecordToLocate);
		}
		cout << '\t' << "Task finished!" << endl << endl;
	}

	cout << '\t' << "clear the container, fill in " << n << " random records and then bubble sort the records, ready (y/n)" << endl;
	cin >> yesOrNo;
	if (yesOrNo == 'y')
	{
		clear();
		fillBatchOfRandomData(n);
		bubbleSort();
		cout << '\t' << "Task finished!" << endl << endl;
	}
}


//**************************************************
// The following is the main function that 
//	 (i) uses vector for holding data and
//   (ii) manages the data processing services  
//   by calling the service functions defined above.
//**************************************************
//!!!==> Write your code to enhance the function for processing dates instead of numbers
//       See the "!!!==>" comments embedded in the code below.
int main()
{   
	//**************************************************
	// Use a loop to repeatedly display the menu
	//  and provide the services until the user hits 'q'/'Q'
	//**************************************************
	bool isInServiceMode = true;
	while (isInServiceMode)
	{
		int n;

		displayMenu();
		switch (getOptionInputFromUser())
		{
			//K: resize and manually enter data case
		case 'k':
		case 'K':
			getBatchOfDataFromKeyboard();
			break;

			//W: write to file case
		case 'w':
		case 'W':
			writeDataRecordsToFile();
			break;

			//R: read from file case
		case 'r':
		case 'R':
			readDataRecordsFromFile();
			break;

			//D: display current data records in the dataContainer
		case 'd':
		case 'D':
			displayDataRecords();
			break;

			//M: modify a single data record in the container
		case 'm':
		case 'M':
			modifyRecord();
			break;

			//Q: quit case: Please fix a minor bug below
		case 'q':
		case 'Q':
			//Something wrong in the code below when the user does Not want to quit.
			//Please add some code or modify the code below to fix the minor bug. 
			cout << "Are you sure to quit and end the program? (y/n)" << endl;
			// if (getOptionInputFromUser() == 'y'); //==> Just remove the ending seicolon
			if (getOptionInputFromUser() == 'y')
			isInServiceMode = false;
			break;

			//C: Clear and make it an empty container of no records.
		case 'c':
		case 'C':
			cout << "Are you sure to clear (empty) the data container? (y/n)" << endl;
			if (getOptionInputFromUser() == 'y')
			{
				clear();
				cout << '\t' << "clear operation finished" << endl;
			}
			break;

			//F: resize and fill in random data records into the vector dataContainer
		case 'f':
		case 'F':
			//get the number of records, verifies that the number is valid.
			fillBatchOfRandomData( getNumOfRecordsFromUser() );
			cout << '\t' << "filled with random records now" << endl;
			break;

			//A: Append a new record at the end of the container
		case 'a':
		case 'A':
			{	//Note: In your complete implementation you need to change the type 
				//      of dataRecord to Date, and then properly read 
			    //      the information of month, day, year into 
			    //		dataRecord.month, dataRecord.day, dataRecord.year .

				double dataRecord;
				//!!!==> Write your code to enhance the code segment accordingly
				cout << '\t' << "Append: Enter the data of the new record: ";
				cin >> dataRecord;
				dataContainer.push_back(dataRecord);
			}
			break;
			//Insert a new record at a specific location in the container.
		case 'i':
		case 'I':
			{	int insertionPoint;
				cout << '\t' << "Please provide the insertion point:" << endl;
				insertionPoint = getValidIndexFromUser();

				//Set up the corresponding iterator
				//Note: In your complete implementation, 
				//      you need to change the line below to
				//      vector< Date >::iterator insertIterator;
			    //!!!==> Write your code to enhance the code segment accordingly
				vector< double >::iterator insertIterator;
				insertIterator = dataContainer.begin() + insertionPoint;

				//Note: In your complete implementation you need to change the type 
			    //      of dataRecord to Date, and then properly read 
				//      the information of month, day, year into 
				//		dataRecord.month, dataRecord.day, dataRecord.year .
				//!!!==> Write your code to enhance the code segment accordingly
				double dataRecord;
				cout << '\t' << "Insert: Enter the data of the new record: ";
				cin >> dataRecord;

				dataContainer.insert(insertIterator, dataRecord); 
			}
			break;

			//P: Pop (remove) the record at the end of the container.
		case 'p':
		case 'P':
			{
				dataContainer.pop_back();
				cout << '\t' << "pop operation finished" << endl;
			}
			break;	

		//E: Erase (delete) a record at a specific location in the container.
		case 'e':
		case 'E':
			{
				int deletionPoint;
				cout << '\t' << "Please povide the deletion point:" << endl;
				deletionPoint = getValidIndexFromUser();

				//Set up the corresponding iterator
				//Note: In your complete implementation, 
				//      you need to change the line below to
				//      vector< Date >::iterator deleteIterator;
				//!!!==> Write your code to enhance the code segment accordingly
				vector< double >::iterator deleteIterator;
				deleteIterator = dataContainer.begin() + deletionPoint;

				dataContainer.erase(deleteIterator);
			}
			break;

		//L: Locate (find) a record with a specific value in the container.
		case 'l':
		case 'L':
			{
				//Note: In your complete implementation you need to change the type 
				//      of dataToLocate to Date, and then properly read 
				//      the information of month, day, year into 
				//		dataToLocate.month, dataToLocate.day, dataToLocate.year .
			    //!!!==> Write your code to enhance the code segment accordingly
				double dataToLocate;
				cout << '\t' << "Locate: Enter the data to search for: ";
				cin >> dataToLocate;

				//For recording the index of the first record found
				int locationIndex;
				
				//Try to locate the record RecordToLocate in the container
				locationIndex = find( dataToLocate);
				if (locationIndex == -1 )
					cout << '\t' << "Not found" << endl;
				else
					cout << '\t' << "Found: Record " 
					<< locationIndex << " contains the data" << endl;
			}
			break;

		//S: STL quick-sort the records in the container.
		case 's':
		case 'S':
			bubbleSort();
			cout << '\t' << "bubble sort finished" << endl;
			break;


		//O: Test overwriting n records beyond the vector boundary
		case 'o':
		case 'O':
			cout << '\t' << "Test writing n records beyond the data container: n=?";
			cin >> n;
			testWritingOutOfBound(n);
		break;

		//T: Test the performance of individual performance
		case 't':
		case 'T':
			testPerformance();
		break;

		default:
			cout << '\t' << "That is not a valid input, please enter an input from the options listed. " << endl;
			break;
		}

		cout << endl << "Enter any key to continue:"; 
		//Pause before displaying the menu again
		char bufferChar;
		cin >> bufferChar;

		cout << endl; //for spacing
	}

	//display exit message, only shown shortly before the program terminates
	cout << "Thank you, exiting... " << endl; 	
	return 0; //End of the program

}



