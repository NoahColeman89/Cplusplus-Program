#ifndef CORNERGROCERINVENTORY_H  // Ensure that the class file is only included once
#define CORNERGROCERINVENTORY_H

#include <Python.h>     // Include python header file
#include <iostream>     // Include input/output stream
#include <Windows.h>    // Include standard Windows operations
#include <string>       // Include string functions

using namespace std;    // Incldue stadard namesapce

class CornerGrocerInventory  // Declare class to process inventory
{
	public:
		int menuDisplayFunc();                         // Declare function to display menu
		void menuExecuteFunc();                        // Declare function to execute menu
		void callProcedure(string pName);              // Declare function to send procedure to python
		int callIntFunc(string proc, string param);    // Declare function to send info to python function with string input
		int callIntFunc(string proc, int param);       // Declare function to send info to python function with integer input
		void displayHistogram();                       // Declare function to display histogram

};

#endif

