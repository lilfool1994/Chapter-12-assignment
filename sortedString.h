#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "input.h"
using namespace std;

template <class T>
class SortedArray {
private:
    vector<T> sorted = vector<T>();
    int operationCount;

public:
    //default constructor
    SortedArray() {
        operationCount = 0;
    }

    //precondition: NA
    //postcondition: will return the operation count
    int getOperationCount() {
        return operationCount;
    }

    //precondition: NA
    //postcondition: will return the size
    int getSize() {
        return sorted.size();
    }


    //precondition: NA
    //postcondition: will clear the array
    void clearArray() {
        sorted.clear();
        cout << "\nThe array has been cleared" << endl;
    }

    //precondition: NA
    //postcondition: will sort the array
    void sortArray() {
        sort(sorted.begin(), sorted.end());
    }

    //precondition: NA
    //postcondition: will add an element to the array
    void addElement(string value) {
        sorted.push_back(value);
    }

    //precondition: NA
    //postcondition: will display all the elements in the array
    void displayAll() {
        for (int i = 0; i < sorted.size(); i++) {
            cout << "\n\t" << sorted[i];
        }//end for
    }

    //precondition: NA
    //postcondition: will recursively binary search for the ID given
    bool binarySearch(string value, size_t first, size_t pSize, size_t& pos, int depth, int opCount = 0) {
        bool found = false;
        operationCount = opCount;
        size_t middle = size_t();
        if (depth < 0 || pSize == 0)
            return false;
        else {
            middle = first + pSize / 2;
            if (value == sorted[middle]) {
                pos = middle;
                operationCount++;
                return true;
            }
            else if (value < sorted[middle])
            {
                return binarySearch(value, first, pSize / 2, pos, depth / 2, opCount + 1);
            }
            else {
                return binarySearch(value, middle + 1, (pSize - 1) / 2, pos, depth / 2, opCount + 1);
            }
        }
    }
    //precondition: NA
    //postcondition: Recursive serial search
    bool searchElement(string searchValue, int index) {
        //linear search
        if (index == 0) {
            operationCount = 0; //resets the operation count every time it calls the function
        }
        operationCount++;

        if (sorted[index] == searchValue) { // once found returns true
            return true;
        }

        if (index == sorted.size() - 1 && sorted[index] != searchValue) { //if at the last index and not found return false

            return false;
        }
        else
            return searchElement(searchValue, ++index); //calls recursively
    }

};

//precondition: user input 1
//postcondition: will allocate the size of the array
void option1(SortedArray<string>& arr) {//populate array with random elements
    system("cls");
    int elements = inputInteger("Enter the size of the dynamic array: ", true);
    arr.clearArray();
    for (int i = 0; i < elements; i++) {
        int randomNum = (rand() % 100);//0-99
        arr.addElement(("String#" + to_string(randomNum)));
    }
    arr.sortArray();
}

//precondition: user input 2
//postcondition: will add an element to the array
void option2(SortedArray<string>& arr) {//add element
    system("cls");
    size_t pos = size_t();
    int operations = int();
    bool found = false;
    string elem = "String#" + to_string(rand() % 100);//0-99//comment out next line to add random string element
    elem = inputString("\n\tEnter a string element: ", false);
    arr.sortArray();
    found = arr.binarySearch(elem, 0, arr.getSize(), pos, arr.getSize());
    if (found) {
        std::cout << "\n\tNumber of comparisons: " << arr.getOperationCount() << "\n";
        std::cout << "\n\tAlready exists ";
    }
    else {
        arr.addElement(elem);
        arr.sortArray();
        arr.binarySearch(elem, 0, arr.getSize(), pos, arr.getSize());
        std::cout << "\n\tNumber of comparisons: " << arr.getOperationCount() << "\n";
    }
}

//precondition: user input 3
//postcondition: will display all the elements of the array
void option3(SortedArray<string>& arr) {//Display all elements in the array
    system("cls");
    if (arr.getSize() <= 0) {
        std::cout << "\n\tThe array is empty\n";
    }
    else
    {
        std::cout << "\n\tElements of sorted array:\n";
        arr.sortArray();
        arr.displayAll();
    }
}

//precondition: user input 4
//postcondition: will search the array for a given value  either binary or serial
void option4(SortedArray<string>& arr) {
    system("cls");
    if (arr.getSize() <= 0) {
        std::cout << "\n\tThe array is empty\n";
    }
    else
    {
        size_t position;
        char serOrBin = inputChar("Choose search type (S)erial or (B)inary: ", string("sb"));
        string searchValue = inputString("\n\tPlease enter a string element to search for: ", false);
        bool found = bool(false);
        switch (serOrBin)
        {
        case 'S':found = arr.searchElement(searchValue, 0); break;
        case 'B': {
            arr.sortArray();
            found = arr.binarySearch(searchValue, 0, arr.getSize(), position, arr.getSize()); break;
        }
        }

        if (found) {
            std::cout << "\n\tFound the element: " << searchValue << " within the array";
        }
        else
            std::cout << "\n\tElement " << searchValue << " not found in the array";
        std::cout << "\n\tNumber of comparisons: " << arr.getOperationCount() << "\n";
    }

}

//precondition: N/A
//postcondition: will output the menu options
int sortedArrayOption()
{
    cout << endl << "2> Searching from a sorted dynamic array";
    cout << endl << "==========================================";
    cout << endl << "1> Read random string data and store into the dynamic array";
    cout << endl << "2> Add an element to the dynamic array";
    cout << endl << "3> Display elements from the array";
    cout << endl << "4> Search for an element from the array";
    cout << endl << "5> Clear the array";
    cout << endl << "==========================================";
    cout << endl << "Exit 0";
    cout << endl << "==========================================" << endl;
    int options = inputInteger("Options: ", 0, 5);
      
    return options;
 
}

void main()
{
    SortedArray<string> sArray = SortedArray<string>();
    system("cls");

    do
    {
        switch (sortedArrayOption())
        {
        case 0 : return; break;
        case 1 :option1(sArray); break;
        case 2 :option2(sArray); break;
        case 3 :option3(sArray); break;
        case 4 :option4(sArray); break;
        case 5 :sArray.clearArray(); break;
        default: cout << "\t\tERROR - Invalid option. Please re-enter."; break;
        }
        std::cout << "\n";
        system("pause");        
    } while (true);   
    
}
