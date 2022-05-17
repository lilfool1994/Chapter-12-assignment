// Names of Group:
// Julian Espinoza
// Wesley Goo
// Hamza Patel
// Arturo Islas Mejia
// Eduardo Garcia Ortiz
// Date: 5/11/2022

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include <list>
#include "input.h"
#include "applicationOfHashing.h"
#include "sortedString.h"
#include "unsortedString.h"


using namespace std;
int mainMenuOption();

int main()
{
    do
    {
        switch (mainMenuOption())
        {
        case 0: exit(1); break;
        case 1: unsortedString(); break;
        case 2: sortedString(); break;
        case 3: applicationOfHashing(); break;
        default: cout << "\t\tERROR - Invalid option. Please re-enter."; break;
        }
        cout << "\n";
        system("pause");

    } while (true);
}

//Precondition:none
//PostCondition:displays the main menu
int mainMenuOption()
{
    cout << endl << "Chapter 12 Assignment by by Julian Espinoza, Wesley Goo, Hamza Patel, Arturo Islas Mejia, and Eduardo Garcia Ortiz";
    cout << endl << "==========================================";
    cout << endl << "1> Searching from an unsorted dynamic array";
    cout << endl << "2> Searching from a sorted dynamic array";
    cout << endl << "3> Application using hashing";
    cout << endl << "==========================================";
    cout << endl << "Exit 0";
    cout << endl << "==========================================" << endl;
    int options = inputInteger("Options: ", 0, 3);
    cout << endl << endl << endl;
    return options;
}