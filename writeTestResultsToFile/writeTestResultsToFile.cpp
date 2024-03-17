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