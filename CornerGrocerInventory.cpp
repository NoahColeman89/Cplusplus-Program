#include <Python.h>     // Include python header file
#include <iostream>     // Include input/output stream
#include <Windows.h>    // Include standard Windows operations
#include <string>       // Include string functionality
#include <vector>       // Include vector functinoality
#include <fstream>      // Include file stream
#include <iomanip>      // Include formatting
#include "CornerGrocerInventory.h"      // Include class header file

using namespace std;    // Incldue stadard namesapce


// Function provided for pyhton integration
void CornerGrocerInventory::callProcedure(string pName){
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("myFirstProgram");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}  

// Function provided for pyhton integration
int CornerGrocerInventory::callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"myFirstProgram");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

// Function provided for pyhton integration
int  CornerGrocerInventory::callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"myFirstProgram");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
} 

// Function to output starting menu
int CornerGrocerInventory::menuDisplayFunc() {
	
	cout << "Corner Grocer Inventory Application" << endl;
	cout << "Choose from the following options:" << endl << endl;
	cout << "1: Show all daily pruchased items and frequency" << endl;
	cout << "2: Search for a specific item to show frequency" << endl;
	cout << "3: Show a daily item histogram" << endl;
	cout << "4: EXIT" << endl << endl;

	return 0;
}

// Function to read file and output a histogram
void CornerGrocerInventory::displayHistogram() {

	vector<string> itemNames;  // Declare a vector to hold all item names
	vector<int> itemFreq;      // Declare a vector to hold all itewm frequencies
	string names;
	int freq;
	int n;

	// Open frequency file and declare a variable for it
	std::fstream itemFreqFileFS("frequency.dat");

	// Check that file opens correctly
	if (!itemFreqFileFS.is_open()) {
		cout << "Could not open file numFile.txt." << endl;
	}

	// While loop iterates through end of file, adds item names and frequencies to the appropriate vectors
	while (!itemFreqFileFS.eof()) {
		string holdString;
		int holdInt;
		itemFreqFileFS >> holdString;
		itemFreqFileFS >> holdInt;
		itemNames.push_back(holdString);
		itemFreq.push_back(holdInt);
	}

	// For loop iterates through itemNames vector and outputs each item on a new line
	for (int i = 0; i < itemNames.size()-1; ++i) {
		std::cout << left << setw(15) << itemNames.at(i);
		n = itemFreq.at(i);
		// While loop prints the number of * associated with the item frequency
		while (n > 0) {
			cout << "*";
			n = n - 1;
		}
		cout << endl;
	}
		

}

// Function to run the menu choices
void CornerGrocerInventory::menuExecuteFunc() {
	string userInput;
	string userItem;

	// While loop to execute the menu until the user chooses to exit
	while (userInput[0] != '4') { // Use a string to only take the first character of the input
		cout << endl;
		menuDisplayFunc();        // Display the menu
		cout << "Enter choice: ";
		cin >> userInput;         // Get user input
		if (userInput[1]) {       // Validate input, only accept a single character
			cout << "Please enter a single character.";
			cout << endl;
		}
		else {
			switch (userInput[0]) { // Use a string to only take the first character of the input
			case '1':               // Case 1 displays all items and thier frequency
				cout << endl;
				callProcedure("ToatlDailyItemFrequency");  // Call the python function to display all items and thier frequencies
				break;
			case '2':              // Case 2 displays a single items frequency
				cout << endl;
				cout << "Enter item name to see number sold." << endl;
				cin >> userItem;   // Get user input for the item to search
				cout << endl;
				//callIntFunc("SingleItemSearch", userItem);
				//callIntFunc("SingleItemFreq", userItem);
				
				callIntFunc("SingleItemFrequency", userItem);  // Call pyhton function to search and output single item frequency
				break;
			case '3':              // Case 3 displays a histogram of all items
				cout << endl;
				callProcedure("CreateFreqFile"); // Call python function to create the file with the appropriate list of frequencies
				displayHistogram();              // Call C++ function to display histogram from file
				break;
			case '4':              // Case 4 exits the program
				cout << endl;
				cout << "Thank you have a nice day!" << endl << endl << endl;
				break;
			default:               // Default case to check user input
				cout << "Please enter a valid menu selection";
				cout << endl;
				break;

			}
		}
	}
}