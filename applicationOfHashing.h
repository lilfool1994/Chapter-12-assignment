#pragma once
//Class that holds the student info
class studentInfo
{
private:
    int id;
    string name;
    string major;
    double GPA;
public:
    studentInfo()
    {
        id = 0;
        name = "unknown";
        major = "unknown";
        GPA = 0;
    }

    studentInfo(int newId, string newName, string newMajor, double newGPA)
    {
        id = newId;
        name = newName;
        major = newMajor;
        GPA = newGPA;
    }

    //setter
    void setID(int newID)
    {
        id = newID;
    }

    void setName(string newName)
    {
        name = newName;
    }

    void setMajor(string newMajor)
    {
        major = newMajor;
    }

    void setGPA(double newGPA)
    {
        GPA = newGPA;
    }

    //getters
    int getID()
    {
        return id;
    }

    string getName()
    {
        return name;
    }

    string getMajor()
    {
        return major;
    }

    double getGPA()
    {
        return GPA;
    }

    friend ostream& operator <<(ostream& out, const studentInfo& obj);
};
//overloaded cout operator
ostream& operator <<(ostream& out, const studentInfo& obj)
{
    out << setw(40) << obj.name << setw(20) << obj.major
        << setw(15) << obj.GPA;
    return out;
}

//class for the hashing
class hashtable {
private:
    static const int hashGroups = 10;
    list<pair<int, studentInfo>> table[hashGroups];
public:
    //precondition: none
    //postcondition: returns true if the data type is empty, else false
    const bool isEmpty()
    {
        int sum=0;
        for (int i = 0; i < hashGroups; i++)
        {
            sum += table[i].size();
        }

        if (!sum)
            return true;
        else
            return false;
    }

    //precondition: takes in a int
    //postcondition: returns the hash key
    int hashFunction(int key)
    {
        return key % hashGroups;
    }

    //precondition: takes in a key and student indo data type
    //postcondition: adds a element to the data type
    void insertItem(int key, studentInfo value)
    {
        int hashValue = hashFunction(key);
        auto& cell = table[hashValue];
        auto itr = begin(cell);
        bool keyExists = false;
        for (; itr != end(cell); itr++)
        {
            if (itr->first == key)
            {
                keyExists = true;
                //itr->second = value;
                cout << "Key exist. " << endl;
                break;
            }
        }

        if (!keyExists)
        {
            cell.emplace_back(key, value);
        }
    }

    //precondition: takes in a key
    //postcondition: removes an element at index
    void removeItem(int key)
    {
        int hashValue = hashFunction(key);
        auto& cell = table[hashValue];
        auto itr = begin(cell);
        bool keyExists = false;
        for (; itr != end(cell); itr++)
        {
            if (itr->first == key)
            {
                keyExists = true;
                cout << setw(6) << "ID" << setw(40) << "Name" << setw(20) << "Major" << setw(15) << "GPA" << endl;
                cout << setw(6) << itr->first << itr->second << endl;
                itr = cell.erase(itr);
                cout << "ID exist. Value is being erased." << endl;
                break;
            }
        }

        if (!keyExists)
        {
            cout << "ID not found" << endl;
        }
    }

    //precondition: takes in a key
    //postcondition: displays weather the student has ben found or not
    void searchTable(int key)
    {
        int hashValue = hashFunction(key);
        auto& cell = table[hashValue];
        auto itr = begin(cell);
        bool keyExists = false;
        for (; itr != end(cell); itr++)
        {
            if (itr->first == key)
            {
                keyExists = true;
                cout << setw(6) << "ID" << setw(40) << "Name" << setw(20) << "Major" << setw(15) << "GPA" << endl;
                cout << setw(6) << itr->first << itr->second << endl;
                break;
            }
        }

        if (!keyExists)
        {
            cout << "ID not found" << endl;
        }
    }

    //precondition: takes in a key
    //postcondition: returns false if the id is found false if not found. 
    bool checkID(int key)
    {
        int hashValue = hashFunction(key);
        auto& cell = table[hashValue];
        auto itr = begin(cell);
        bool keyExists = false;
        for (; itr != end(cell); itr++)
        {
            if (itr->first == key)
            {
                return true;
            }
        }

        return false;
    }

    //precondition: none
    //postcondition: prints the whole table. 
    void PrintTable()
    {
        for (int i = 0; i < hashGroups; i++)
        {
            if (table[i].size() != 0)
            {
                auto itr = table[i].begin();
               
                for (; itr != table[i].end(); itr++)
                {
                    cout << setw(6) << itr->first << itr->second << endl;
                }
            }
        }
    }
};

//precondition: takes in the hashtable
//postcondition: adds elements from a file to the hashtable
void readData(hashtable& ht)
{
    string fileName = inputString("Enter the name of the file: ", false);
    int newEmployeeIDIncrment = 0;
    string correctFile = "Students.dat";

    cout << "loading file..." << endl;

    ifstream file1;
    file1.open(fileName, ios::in);
    if (file1.fail())
    {
        cout << "ERROR: file cannot be read, try " << correctFile << endl;
        return;
    }

    studentInfo buffer;
    string temp;
    int tempInt = 0;
    while (!file1.eof())
    {
        getline(file1, temp, ','); // this gets student ID
        buffer.setID(stoi(temp));
        getline(file1, temp, ','); // This gets student name
        buffer.setName(temp);
        getline(file1, temp, ','); // this gets student Major
        buffer.setMajor(temp);
        getline(file1, temp, '\n'); //this gets GPA
        buffer.setGPA(stod(temp));

        
        ht.insertItem(buffer.getID(), buffer);
        //studentList.push_back(buffer);
    }
    cout << "file loaded and data downloaded" << endl;
    file1.close();
}

//precondition: takes in a hashtable
//postcondition: displays if the element exist or not based on index
void searchElement(hashtable ht)
{
    if (ht.isEmpty())
    {
        cout << "There is no data." << endl;
        return;
    }

    ht.searchTable(inputInteger("Enter a the student Id of the student you'd like to remove:", 0, 100));
}

//precondition: takes in a hashtable
//postcondition: insert element into the hashtable
void insertElement(hashtable& ht)
{
    studentInfo buffer;
    int newID = inputInteger("Enter the student ID of the student you'd like to add:", 0, 100);

    if (ht.checkID(newID))
    {
        cout << "ID already exist... enter a new one." << endl;
        return;
    }

    buffer.setID(newID);
    buffer.setName(inputString("Enter the full name of the new student: ", true));
    buffer.setMajor(inputString("Enter the major of the new student: ", true));
    buffer.setGPA(inputDouble("Enter the GPA of the new student: ", 0, 4.0));

    ht.insertItem(newID, buffer);
}

//precondition: takes in a hashtable
//postcondition: remove an element at the specfied key
void removeElement(hashtable &ht)
{
    if (ht.isEmpty())
    {
        cout << "There is no data." << endl;
        return;
    }

    ht.removeItem(inputInteger("Enter a the student Id of the student you'd like to remove:", 0, 100));
}

//precondition: takes in a has table
//postcondition: displays all elements
void DisplayAll(hashtable ht)
{
    if (ht.isEmpty())
    {
        cout << "There is no data." << endl;
        return;
    }
    cout << setw(6) << "ID" << setw(40) << "Name" << setw(20) << "Major" << setw(15) << "GPA" << endl;
    ht.PrintTable();

}

//Precondition:none
//PostCondition:displays the main menu
int applicationOfHashingMenuOption()
{
    cout << endl << "Chapter 12 Assignment by by Julian Espinoza, Wesley Goo, Hamza Patel, Arturo Islas Mejia, and Eduardo Garcia Ortiz";
    cout << endl << "==========================================";
    cout << endl << "1> Read data file, hash and insert into the dynamic array";
    cout << endl << "2> Search an element from the dynamic array";
    cout << endl << "3> Insert an element into the dynamic array";
    cout << endl << "4> Remove an element from the dynamic array";
    cout << endl << "5> Display all records from the array";
    cout << endl << "==========================================";
    cout << endl << "Exit 0";
    cout << endl << "==========================================" << endl;
    int options = inputInteger("Options: ", 0, 5);
    cout << endl << endl << endl;
    return options;
}

//main dirver function
void applicationOfHashing()
{
    hashtable ht;
    do
    {
        switch (applicationOfHashingMenuOption())
        {
        case 0: return; break;
        case 1: readData(ht); break;
        case 2: searchElement(ht); break;
        case 3: insertElement(ht); break;
        case 4: removeElement(ht); break;
        case 5: DisplayAll(ht); break;
        default: cout << "\t\tERROR - Invalid option. Please re-enter."; break;
        }
        cout << "\n";
        system("pause");

    } while (true);
}