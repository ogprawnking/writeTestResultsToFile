#define _CRT_SECURE_NO_WARNINGS // so that ctime works instead of ctime_S
#include <iostream>
#include <cstring>
#include "String.h" // my header file
#include <string>
#include <fstream> //inp/outp operations for files
#include <ctime> // access date and time
using namespace std;


// Function Prototypes
String systemDateTime();
void runTestsAndLogResults();

/*
    Expected/Wanted result
    date/time Sun Mar 17 23:07:00 2024
    Test name   Results

    Length      Successful
    CharAt      Successful
    EqualTo     Successful
    Append      Successful
*/

//function to allow operator overloading;
// allows: cout << string;  INSTEAD OF: cout << string.Cstr();
std::ostream& operator<<(std::ostream& os, const String& str) {
    // Assuming you have a method CStr() that returns a const char* to the internal string data
    os << str.CStr();
    return os;
}

int main() {
    
    runTestsAndLogResults();
    cout << "Results printed to .txt file\n -- PRESS ANY KEY TO EXIT -- " << endl;
    system("pause>0");
}

// Get current date/time from system
String systemDateTime()
{
time_t currentTime = time(nullptr); // current time since last epoch (1970)
//write date & time to testFile.txt
String currentDateTime = ctime(&currentTime); // convert current time to readable time
return currentDateTime;
}


void runTestsAndLogResults()
{
    // ----- Create/Open file -----
    fstream testFile; // create file
    testFile.open("test_file.txt", ios::app); // open in append mode
    if (!testFile.is_open()) {
        cerr << "Error: Failed to open" << endl; // Print error message
        return; // exit program.
    }

    
    int totalTests = 0; //Total Test counter (should be 8 Currently)
    int successfulTests = 0; //successful tests counter
    String exampleString = "Hello, world"; //string to test functions on
    String exampleString2 = "Hello, world"; // string to compare to
    String logResults(""); // text space to log everything

    logResults.Append("\nTestName : Results");
    
    totalTests++;
    logResults.Append("\nLength\t");
    if (exampleString.Length() == 12){
        successfulTests++;
        logResults.Append("Successful");
    }
    else logResults.Append("failed");
    
    totalTests++;
    logResults.Append("\nCharAt\t");
    if (exampleString.CharacterAt(4) == 'o'){
        successfulTests++;
        logResults.Append("Successful");
    }
    else logResults.Append("failed");


    totalTests++;
    logResults.Append("\nEqualTo\t");
    if (exampleString.EqualTo(exampleString2) == 1) {
        successfulTests++;
        logResults.Append("Successful");
    }
    else logResults.Append("failed");

    totalTests++;
    String prependString("\nPrepend\t");
    String testName("Successful");
    testName.Prepend(prependString);
    logResults.Append(testName);
    if (testName.EqualTo("\nPrepend\tSuccessful")) {
        successfulTests++;
    }
    else logResults.Append("failed");


    totalTests++;
    exampleString.ToLower();
    logResults.Append("\nToLower\t");
    if (exampleString.EqualTo(exampleString.ToLower())) {
        successfulTests++;
        logResults.Append("Successful");
    }
    else logResults.Append("failed");


    totalTests++;
    exampleString.ToUpper();
    logResults.Append("\nToUpper\t");
    if (exampleString.EqualTo(exampleString.ToUpper())) {
        successfulTests++;
        logResults.Append("Successful");
    }
    else logResults.Append("failed");

    //find(string&)
    totalTests++;
    exampleString = "Hello, world"; // resets any changes i.e. uppercasing etc.
    logResults.Append("\nFind\t");
    String stringToFind("world");
    size_t findPos = exampleString.Find(stringToFind);
    if (findPos != std::string::npos) {
        successfulTests++;
        logResults.Append("Successful");
    }
    else logResults.Append("failed");
    cout << findPos << endl;


    //replace(string& _find, string& _other)
    totalTests++;
    String imposterString("failed >:)");
    String successfulString("Successful");
    logResults.Append("\nReplace\t");
    if (imposterString.Replace(imposterString, successfulString) == "Successful") {
        successfulTests++;
        logResults.Append(imposterString);
        logResults.Append("\n\n");
    }
    else logResults.Append("failed\n\n");


    // ----- Date/Time & SuccessPercentage are printed before everything else -----
    // ----- logResults haven't been printed to txt file yet -----
    // print date / time top of page
    String dateTime = systemDateTime();
    cout << dateTime;
    testFile << ("TimeStamp: ") << dateTime;
    

    // getting success percentages and printing to file.
    double successPercentage = static_cast<double>(successfulTests) / totalTests * 100;
    testFile << "Total Tests Ran: " << totalTests << "\n";
    testFile << "Success Rate: " << successPercentage << "%\n";
    testFile << logResults; // print logResults to .txt
    testFile << "\n\n";


    testFile.close(); //close the file (MUST)
    

}





























/* STRING CLASS PRIOR TESTING

// constructor with NO ARGUMENTS
// class nameOfInstance;
String string1;


// covert a "string" to char array for input as variable(temp)
cout << "----- STRING USING CHAR[] -----" << endl;
char temp[] = "written through char[]";
String string2a(temp);
cout << temp << endl;
// ALTERNATE WAY
String string2b("written through overloaded");


cout << "----- STRING CLASS OVERLOADED -----" << endl;
String string3(string2b);
cout << string3.CStr() << endl;


cout << "----- NON CONST CHARACTER AT FUNCTION -----" << endl;
// doesn't include 'SPACE' as a character
size_t index = 9;
String string4aNonConst = "4.written Non Const";

char& character = string4aNonConst.CharacterAt(index);
cout << "Character " << character << " is at position " << index << " of the string: " << string4aNonConst.CStr() << endl;

// ALTERNATE WAY (const version)
cout << "----- CONST CHARACTER AT FUNCTION -----" << endl;
const String constString("4.written as Const");
const char& character1 = constString.CharacterAt(index);
cout << "Character " << character1 << " is at position " << index << " of the string: " << constString.CStr() << endl;
cout << "\n\n";


cout << "----- LENGTH FUNCTION -----" << endl;
String stringL = "Hello";
size_t StrLength = stringL.Length();
cout << "The length of " << stringL.CStr() << " is: " << StrLength << endl;
cout << "\n\n";


cout << "----- EQUAL TO FUNCTION -----" << endl;
String compare1 = "Hello there!";
String compare2 = "Hello there!"; //change one of these strings to change outcome

if (compare1.EqualTo(compare2) == 1)
    cout << "The strings are the same" << endl;
else cout << "The strings are NOT the same" << endl;
cout << "\n\n";


cout << "----- APPEND FUNCTION -----" << endl;
String str1("Hello ");
String str2("World");
cout << "Source string: " << str1.CStr() << endl;
cout << "String to append: " << str2.CStr() << endl;
str1.Append(str2).Append("!");
cout << str1.CStr() << endl;

cout << "----- PREPEND FUNCTION -----" << endl;
String ogVar = "world";
String PrependVar = ("Hello ");
cout << "Source string: " << ogVar.CStr() << endl;
cout << "String to Prepend: " << PrependVar.CStr() << endl;
ogVar.Prepend(PrependVar);
cout << ogVar.CStr() << endl;
cout << "\n\n";


cout << "----- CSTR FUNCTION -----" << endl;
// this allows you to use the 'cout <<' on your string (as per below)
String str3("can 'cout << string.CStr()' to console now!");
cout << str3.CStr() << endl;
// cout << str3 << endl; // <------This is a problem without it. Value is a char** (pointer to a pointer) not char* (just a pointer)
cout << "\n\n";


cout << "----- TO LOWER FUNCTION -----" << endl;
String str4 = "TO LOWER CASE\n";
str4.ToLower();
cout << str4.CStr();


cout << "----- TO UPPER FUNCTION -----" << endl;
String str5 = "to uppercase\n";
str5.ToUpper();
cout << str5.CStr();
cout << "\n\n";


cout << "----- FIND FUNCTION FOR SUBSTRING -----" << endl;
String str11("Hello, world");
cout << "Total string: " << str11.CStr() << "\n";

String substr11("world");


size_t pos = str11.Find(substr11);
if (pos != std::string::npos)
{
    cout << "Substring found at position: " << pos << endl;
}
else
{
    cout << "Substring not found." << endl;
}


cout << "----- FIND W/ INDEX FUNCTION -----" << endl;
String str12("Hello, world");
String substr12("llo");
size_t posi = str11.Find(1, substr12); // .Find(index to start search, substr to find)
if (posi != -1)
{
    cout << "Substring found at position: " << posi << endl;
}
else
{
    cout << "Substring not found." << endl;
}
cout << "\n\n";


cout << "----- REPLACE FUNCTION -----" << endl;

String str13("Hello, world");
String substr13("everyone");
cout << "Original string: " << str13.CStr() << endl;
cout << "Replacement string: " << substr13.CStr() << endl;

str13.Replace("world", substr13);
cout << "Final string (replaced): " << str13.CStr() << endl;
cout << "\n\n";


cout << "----- READ FROM CONSOLE FUNCTION -----" << endl;
String fromConsole;
fromConsole.ReadFromConsole();
//cout << "String: " << fromConsole.CStr() << endl;


cout << "----- WRITE TO CONSOLE FUCNTION -----" << endl;
cout << "write to console: ";
fromConsole.WriteToConsole();
cout << "\n\n";


cout << "----- OPERATOR == OVERLOAD -----" << endl;
String equal1("Hello");
String equal2("World");
String equal3("Hello");

if (equal1 == equal2)
{
    cout << "'equal1' is equal to 'equal2'" << endl;
}
else {
    cout << "'equal1' is NOT equal to 'equal2'" << endl;
}

if (equal1 == equal3)
{
    cout << "'equal1' is equal to 'equal3'" << endl;
}
else {
    cout << "'equal1' is NOT equal to 'equal3'" << endl;
}


cout << "----- OPERATOR != OVERLOAD -----" << endl;
if (equal1 != equal2)
{
    cout << "'equal1' is not equal to 'equal2'" << endl;
}
else {
    cout << "'equal1' is equal to 'equal2'" << endl;
}

if (equal1 != equal3)
{
    cout << "'equal1' is not equal to 'equal3'" << endl;
}
else {
    cout << "'equal1' is equal to 'equal3'" << endl;
}
cout << "\n\n";


cout << "----- OPERATOR = OVERLOAD -----" << endl;
String str18("Hello");
String otherstr18("World");

cout << "source string: " << str18.CStr() << endl;
cout << "other string: " << otherstr18.CStr() << endl;
str18 = otherstr18;
cout << "string result: " << str18.CStr() << endl;


cout << "----- OPERATOR [] OVERLOAD -----" << endl;
String accessarray("Hello world");
cout << "Original string: " << accessarray.CStr() << endl;
accessarray[0] = 'J';
cout << "Change array via element [0]: " << accessarray.CStr() << endl;


cout << "----- CONST OPERATOR [] OVERLOAD -----" << endl;
cout << accessarray.CStr() << endl;
cout << "Accessed element at position [2] is: " << accessarray[2] << endl; // change [number] to access different elements


cout << "----- OPERATOR += OVERLOAD -----" << endl;
String finalString("Hello ");
String finalSubString("Cliff :)");
cout << "Original string    " << finalString.CStr() << "\n" << "Substring:  " << finalSubString.CStr() << endl;
finalString += finalSubString;
cout << "String += together:    " << finalString.CStr() << endl;

// ----- END OF PROGRAM -----


String end("\n\n\n----- end of program -----\n\n\n");
cout << end.ToUpper().CStr();
return 0;
}
*/