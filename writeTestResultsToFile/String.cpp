#define _CRT_SECURE_NO_WARNINGS
#include "String.h"
#include <iostream>
//#include <string>
#include <cstring> // gives access to 'str' functions (i.e. strlen, strcmp etc.)

using namespace std;

// Default  constructor. string = '\0'
String::String()
{
	mystring = new char[1];
	mystring[0] = '\0';
	//cout << "PART1		++ default constructor called" << endl;
}

// constructor w/ 1 argument
// allocates space for inputted _str to mystring
// then copies _str into the space of mystring
String::String(const char* _str) // overloaded or parameterized
{
	if (_str != nullptr) // if string is inputted
	{
		mystring = new char[strlen(_str) + 1]; // +1 makes space for nullchar
		strcpy(mystring, _str);
		mystring[strlen(_str)] = '\0'; // adds nullchar to the end of array.
		//cout << "PART 2		++ Parameterized constructor called" << endl;
		//cout << "The string entered is: " << mystring << endl;
	}
	else // make empty string
	{
		mystring = new char[1];
		mystring[0] = '\0';
		//cout << "PART 2		++ Overlaoded constructor called" << endl;
		//cout << "Invalid input. Empty string created.\n" << endl;
	}
}

// copy constructor (deep copy)
// enter reference to another class and object
String::String(const String& _other)
{
	// make space for the inputted object
	mystring = new char[strlen(_other.mystring) + 1];
	// copy _other.mystring(existing string) to mystring of this new class made.
	strcpy(mystring, _other.mystring);
	mystring[strlen(_other.mystring)] = '\0'; // --good practice--

	//cout << "PART 3		++ copy constructor called" << endl;
	//cout << "String copied is: " << mystring << endl;
}

String::~String()
{
	delete[] mystring;
	mystring = nullptr;

	//cout << "-- string DESTRUCTOR called" << endl;
}

char& String::CharacterAt(size_t _index)
{
	if (_index >= strlen(mystring) || _index < 0)
	{
		// Return '\0' if index is out of range... Ensures empty string.
		char nullChar = '\0';
		//cout << "PART 4		++characterAt constructor called" << endl;
		//cout << "Index out of range. Empty string created";
		return nullChar;
	}
	else
		//cout << "PART 4		++CharacterAt Constructor called" << endl; 
		//cout << "character at index " << _index << " is: " << mystring[_index] << "\n" << endl;
		return mystring[_index]; // character at index inputted
}

// The return type is a reference to a const char, which means that the caller cannot modify the character retrieved through this function.
//body is the same as the one before... just uses const instead of non-const.
const char& String::CharacterAt(size_t _index) const // const after means it won't change what was inputted.
{
	if (_index >= strlen(mystring) || _index < 0)
	{
		// Return '\0' if index is out of range... Ensures empty string.
		char nullChar = '\0';
		//cout << "PART 4		++CONSTcharacterAt constructor called" << endl;
		//cout << "Index out of range. Empty string created";
		return nullChar;
	}
	else
		//cout << "PART 4 ALT	++CONSTcharacterAt Constructor called" << endl;
		//cout << "const character at index " << _index << " is: " << mystring[_index] << "\n" << endl;
		return mystring[_index]; // character at index inputted
}

// Returns an integer representing the count of characters up to the null termination character
size_t String::Length() const
{
	// store length of (mystring) in length variable.
	size_t length = strlen(mystring);

	// if length > 0 then -1 (for nullChar). Else return 0;
	//cout << "PART 5		++Length constructor called" << endl;
	//cout << "Length of string is: " << length << "\n" << endl;
	return (length > 0) ? (length) : 0;
}

//				OR use below method.

//size_t String::Length() const
//{
//	// store length of (mystring) in length variable.
//	size_t length = 0;
//	while (mystring[length] != '\0')
//		length++;
//		return length;
//}




// Returns true if str contains the same characters.
bool String::EqualTo(const String& _other) const
{
	// Are both strings same length?
	if (Length() == _other.Length())
	{
		// compare each character from input string and  known string.
		for (size_t i = 0; i < Length(); i++)
		{
			// If char's are equal return true.
			if (mystring[i] == _other.mystring[i])
				//cout << "PART 6		++EqualTo constructor called" << endl;
				//cout << "The strings ARE equal. \n" << endl;
				return true;
		}
		// else false
		return false;
	}
	else
		//cout << "PART 6		++EqualTo constrcutor called" << endl;
		//cout << "The strings are NOT equal. \n" << endl;
		return false;
}
// Adds _str to end of string
String& String::Append(const String& _str)
{
	// add sizes of strings together
	size_t sizeNewString = Length() + _str.Length();

	// allocate memory for full string(newstring)
	char* newString = new char[sizeNewString + 1]; // +1 for nullchar

	// copy current string to newString
	//	newstring = mystring
	strcpy(newString, mystring);

	// concatenate newinput data (_str) to newString
	strcat(newString, _str.mystring);

	// delete old memory from old string
	delete[] mystring;

	// update to point to new string
	mystring = newString;

	//cout << "PART 7		++Append constructor called" << endl;
	//cout << "Appended string is: " << mystring << "\n" << endl;

	// return reference to modified object
	return *this;

}
// Adds _str to the beginning of the string
String& String::Prepend(const String& _str)
{
	// add size of both strings together
	size_t sizeOfNewString = Length() + _str.Length();
	// allocate memory for full string
	char* newString = new char[sizeOfNewString + 1];
	// copy current string to newString
	// newstring = mystring
	strcpy(newString, _str.mystring);
	// concatenate newinput data (_str) to newstring)
	strcat(newString, mystring);
	// delete old memory from old string
	delete[] mystring;
	// update old string to point to new string
	mystring = newString;
	//cout << "PART 8		++Prepend constructor called" << endl;
	//cout << "Prepended string is: " << mystring << "\n" << endl;

	return *this;
}

// retrieves underlying C-style string from Strin object.
// Use with std::cout to print string.
const char* String::CStr() const
{
	return mystring;
}

String& String::ToLower()
{
	for (int i = 0; i < Length(); i++)
	{
		mystring[i] = tolower(mystring[i]);
	}
	return *this;
}


String& String::ToUpper()
{
	for (int i = 0; i < Length(); i++)
	{
		mystring[i] = toupper(mystring[i]);
	}
	return *this;
}

size_t String::Find(const String& _str)
{
	// Get pointers to sourcec string and substring to be found.
	//	OR 'converts to c_style strings for easier use with arrays.
	const char* substr = _str.mystring;
	const char* source = mystring;
	size_t sourceLen = Length();
	size_t substrLen = _str.Length();

	// if the to find string is larger than source. Then return error.
	if (substrLen > sourceLen) return std::string::npos;

	for (size_t i = 0; i <= sourceLen - substrLen; i++)
	{
		// create j outside inner loop so that we can have it as a statement for a return value.
		size_t j;

		// Check if substr matches the portion o the source string
		for (j = 0; j < substrLen; j++)
		{
			if (source[i + j] != substr[j])
				break;
		}
		// If substr is found, return its position in the sourceStr
		if (j == substrLen)
			return i;
	}
	// if substr is not found, return value for failure.
	return std::string::npos;
}


// Return location of strToFind. Beginning search from startIndex. If not found return -1
size_t String::Find(size_t _startIndex, const String& _str)
{
	// If index isn't in range, return -1
	if (_startIndex >= Length()) return -1;

	// get position from finding string inside a string
	// strstr finds first occurence of nullchar to then point to the next character-
	// this is then the position pointed to.
	const char* startPos = strstr(mystring + _startIndex, _str.mystring);
	if (startPos != nullptr) return startPos - mystring; // substring position - mystring position?
	else return -1;
}

String& String::Replace(const String& _find, const String& _replace)
{
	size_t startPos = 0;
	while ((startPos = Find(startPos, _find)) != -1)
	{
		// create new string to hold the replaced content
		string replacedContent = string(mystring, mystring + startPos) + _replace.CStr() + string(mystring + startPos + _find.Length());

		// allocate memory for the new string data
		char* buffer = new char[replacedContent.length() + 1]; // +1 for nullchar

		// copy replaced content to the buffer
		strcpy(buffer, replacedContent.c_str());

		delete[] mystring;

		mystring = buffer;

		startPos += _replace.Length(); //move start pos past the replaced substr
	}
	return *this; // a reference to itself
}

// Wait for input in the console window and store the result
String& String::ReadFromConsole()
{
	// TODO: insert return statement here
	cout << "Enter a string: "; // Prompt user for a string
	char input[1024]; // temp buffer for input
	cin.getline(input, 1024); // read input into temp buffer
	size_t inputLen = strlen(input); // length of the user's input
	mystring = new char[inputLen + 1]; // allocate memory for string
	strcpy(mystring, input); // copy input to allocated memory in mystring
	return *this;
}

// Write the string to the console window
String& String::WriteToConsole()
{
	// TODO: insert return statement here
	cout << mystring; //print whatever was read and stored in console
	return *this; // return ref to current string object
}

// returns true if lhs == rhs
bool String::operator==(const String& _other)
{
	// if two strings are the same then it will return 0. Else false(1)
	return strcmp(mystring, _other.mystring) == 0;
}

// returns true if lhs is NOT equal to rhs
bool String::operator!=(const String& _other)
{
	// if two trings AREN'T the same then it will return 0;
	return strcmp(mystring, _other.mystring) != 0;
}

// replaces the characters in lhs with the characters in the rhs
String& String::operator=(const String& _str)
{
	// TODO: insert return statement here
	if (this != &_str) // if 'this' isn't equal to otherString (_str)
	{
		delete[] mystring; // Deallocate any previous data in mystring
		mystring = new char[_str.Length() + 1]; //Allocate memory.. Len of new string + nullchar
		strcpy(mystring, _str.mystring); // copy data
	}
	return *this; //return ref to mystring new value
}


// can read and write to data inside index accessed
char& String::operator[](size_t _index)
{
	// Returns the position the array based on the _index inputed
	return mystring[_index];
}

// can only read from data at specific index. Thus cannot alter the data inside.(CONST)
const char& String::operator[](size_t _index) const
{
	// Same as previous but string cannot be changed.
	return mystring[_index];
}

// is lhs first or second?
bool String::operator<(const String& _other)
{
	return strcmp(mystring, _other.mystring) < 0; // if mystring less than _other.mystring.. return true
}

String& String::operator+=(const String& _other)
{
	// calc new length of string after appending
	size_t newLength = Length() + _other.Length();

	// Allocate memory for new string
	char* newString = new char[newLength + 1]; // +1 for nullchar

	// copy current string to empty 'newString'
	strcpy(newString, mystring);

	// copy input data and place onto end of newString
	strcat(newString, _other.mystring);

	// Deallocate old mystring data
	delete[] mystring;

	//update mystring to have complete string
	mystring = newString;

	return *this; // return completed 'mystring' string
}

