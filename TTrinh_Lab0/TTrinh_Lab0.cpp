// Program written by Tommy Trinh
// February 2, 2024
// This program simulates a database to store animal types, count, and 
// endangered status
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <cctype>
using namespace std;

// declare constants
const int
MIN_COUNT = 0,			// minimum number of animals
ADD_CHOICE = 1,			// choice to add an animal
DISPLAY_CHOICE = 2,		// choice to display animals
QUIT_CHOICE = 3,		// choice to quit program
MENU_CHOICE_SIZE = 1,	// size of menu choice field
MIN_RECORD = 2,			// minimum number of animal records
MAX_RECORD = 5,			// maximum number of animal records
ENDANGERED_POP = 100,	// population considered endangered
TYPE_SIZE = 20;			// size of the animal type field


// define structures
struct species
{
	char typeAnimal[TYPE_SIZE] = "none";	// stores type of animal
	int numAnimal = 0;						// stores number of animals
	bool endangered = false;				// flag for endangered
};


// define function prototypes
void header();					// display program info to user
void dataEntry(species[], int);	// allows data entry of animals
void dataDisplay(const species[], const int);// displays data to user
bool positiveValid(int);		// validates a number is positive
bool recordValidation(int);		// validates records is between min and max
bool menuValid(int);			// validates menu is between first and quit option
bool noneValid(const char[]);	// validates user input is not none
bool exitProgram();				// ask user if they really want to quit

int main()
{
	// define variables
	string input;					// temporary string for user input
	species* animalPen = nullptr;	// initialize a new struct array 
	int 
		numAnimal,					// number of animal types
		menuChoice;					// user entered menu choice

	// call header
	header();

	// ask user for number of records
	do
	{
		cout << "How many animal records would you like to store? ("
			<< MAX_RECORD << " max): ";
		getline(cin, input);
	} while (recordValidation(stoi(input)));
	numAnimal = stoi(input);
	cout << endl;

	// dynamically allocate a new array
	animalPen = new species[numAnimal];


	do
	{
		// display a menu and  ask user for a menu choice
		do
		{
			cout << ADD_CHOICE << ". Add animal(s)\n";
			cout << DISPLAY_CHOICE << ". Display animals\n";
			cout << QUIT_CHOICE << ". Quit\n\n";
			cout << "Enter the menu choice: ";
			getline(cin, input);
		} while (menuValid(stoi(input)));
		menuChoice = stoi(input);

		// switch statement based on user choice
		switch (menuChoice)
		{
		case ADD_CHOICE:
		{
			dataEntry(animalPen, numAnimal);
			break;
		}
		case DISPLAY_CHOICE:
		{
			dataDisplay(animalPen, numAnimal);
			break;
		}
		case QUIT_CHOICE:
		{
			if (exitProgram())
				menuChoice = ADD_CHOICE;
			break;
		}
		default:
		{
			cout << "Something went wrong\n\n";
			break;
		}
		}
	} while (menuChoice != QUIT_CHOICE);


	// delete dynamically allocated array
	delete[]animalPen;
	animalPen = nullptr;

	// goodbye message
	cout << "\nThank you for using the CMSY 171 Animal Count Program\n\n";

	// end of main
	system("pause");
	return 0;
}

// shows program title, copyright, and program info to user
void header()
{
	cout << "\t\t\t\tCMSY 171 Lab 0\n"
		<< "Copyright 2024 - Howard Community College All rights reserved;"
		<< "Unauthorized duplication prohibited.\n\n"
		<< "\t\t\tWelcome to CMSY-171 Animal Count Program\n\n";
}

// validates animal records is between min and max. returns true if invalid and keeps
// looping, returns false if valid and exits loop.
bool recordValidation(int input)
{
	if (MIN_RECORD > input || input > MAX_RECORD)
	{
		cout << "Invalid entry! Try Again\n";
		return true;
	}
	return false;
}

// validates menu choice, returns true if invalid and keeps looping, returns false if
// valid and exits loop
bool menuValid(int choice)
{
	if (ADD_CHOICE > choice || choice > QUIT_CHOICE)
	{
		cout << "Invalid choice! Try again: \n\n";
		return true;
	}
	return false;
}

// tests if animal count is positive, returns true if invalid and keeps looping,
// returns false if valid and exits loop
bool positiveValid(int num)
{
	if (num <= MIN_COUNT)
	{
		cout << "Invalid count! Try again\n";
		return true;
	}
	return false;
}

// tests if user entered none. If user entered none, return true and stop loop
// if not none, return false and ask for more info
bool noneValid(const char name[])
{
	char temp[TYPE_SIZE];	// temp cstring to test none
	for (int index = 0; index < TYPE_SIZE; index++)
		temp[index] = toupper(name[index]);
	if (!strcmp(temp, "NONE"))
		return true;
	return false;
}

// ask user if they really want to quit, return true if they do not and keep
// looping, return false if they want to quit and leave loop
bool exitProgram()
{
	char temp[TYPE_SIZE];	// holds user's choice to quit
	cout << "\nDo you wish to exit the program (Y or N): ";
	cin.getline(temp, TYPE_SIZE);
	while (toupper(temp[0]) != 'Y' && toupper(temp[0]) != 'N')
	{
		cout << "Please enter Y or N: ";
		cin.getline(temp, TYPE_SIZE);
	}
	if (toupper(temp[0]) == 'Y')
		return false;
	else
		return true;
}

// lets user enter data on the animal types, if user enters none, quit out
void dataEntry(species animalPen[], int numTypes)
{
	string input;				// temporary input string
	static int counter = 0;		// initialize static counter variable
	bool noneFlag = true;		// flag for none 

	// error message if too many types, redisplay menu
	if (counter == numTypes)
		cout << "Cannot enter any more animals\n";

	// loop until none input or max types
	while (noneFlag && counter < numTypes)
	{
		cout << "Please enter an animal type (none to stop): ";
		cin.getline(animalPen[counter].typeAnimal, TYPE_SIZE);
		// if user types none, stop looping, do not increment count
		if (noneValid(animalPen[counter].typeAnimal))
			noneFlag = false;
		// if not none, ask for the rest of info
		if (noneFlag)
		{
			do
			{
				cout << "Enter the animal type's count: ";
				getline(cin, input);
			} while (positiveValid(stoi(input)));
			animalPen[counter].numAnimal = stoi(input);
			if (animalPen[counter].numAnimal < ENDANGERED_POP)
				animalPen[counter].endangered = true;
			counter++;
			// if counter is greater than array size, stop loop
			if (counter >= numTypes)
				noneFlag = false;
		}
	}
	// set noneFlag back to true for next time Add menu is selected
	noneFlag = true;
	cout << endl;
}

// display contents of animal array to user, if an entry has 0 number of
// animals, end the loop and redisplay menu
void dataDisplay(const species animals[], const int numAnimals)
{
	int count = 0;	// temporary counter variable
	
	// if the first animal has a name of none, give an error 
	if (noneValid(animals[0].typeAnimal))
		cout << "You have not entered any data, returning to menu.\n\n";

	while (!noneValid(animals[count].typeAnimal) && count < numAnimals)
	{
		cout << "\nAnimal: " << animals[count].typeAnimal << endl;
		cout << "Has a count of: " << animals[count].numAnimal << endl;
		if (animals[count].endangered)
			cout << "This animal is endangered!!\n\n";
		else
			cout << "This animal is not endangered!!\n\n";
		count++;
	}
}