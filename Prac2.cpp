#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const char* FILENAME = "StudentRecord.xlsx";

class Student {
public:
    int rollNo;
    char name[20];
    char div;
    char address[50];

    void accept() {
        cout << "\nEnter Roll Number: ";
        cin >> rollNo;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Division: ";
        cin >> div;
        cout << "Enter Address: ";
        cin.ignore(); // Clear input buffer
        cin.getline(address, 50);
    }

    void display() {
        cout << "\nRoll No: " << rollNo << "\nName: " << name << "\nDivision: " << div << "\nAddress: " << address << endl;
    }

    void writeToFile(ofstream& file) {
        file << rollNo << " " << name << " " << div << " " << address << endl;
    }

    void readFromFile(ifstream& file) {
        file >> rollNo >> name >> div;
        file.ignore(); // Clear input buffer
        file.getline(address, 50);
    }
};

void addRecord() {
    ofstream file(FILENAME, ios::app);
    if (!file) {
        cerr << "Error opening file for writing." << endl;
        return;
    }
    Student s;
    s.accept();
    s.writeToFile(file);
    file.close();
    cout << "Record added successfully." << endl;
}

void displayAllRecords() {
    ifstream file(FILENAME);
    if (!file) {
        cerr << "Error opening file for reading." << endl;
        return;
    }
    Student s;
    while (!file.eof()) {
        s.readFromFile(file);
        if (file.eof()) break; // To avoid displaying an extra empty record at the end
        s.display();
    }
    file.close();
}

void searchByRollNo() {
    int rollNo;
    cout << "Enter Roll No. to search: ";
    cin >> rollNo;

    ifstream file(FILENAME);
    if (!file) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    Student s;
    bool found = false;
    while (!file.eof()) {
        s.readFromFile(file);
        if (file.eof()) break; // To avoid an infinite loop when reaching the end of the file
        if (s.rollNo == rollNo) {
            s.display();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Record not found." << endl;
    }

    file.close();
}

void deleteRecord() {
    int rollNo;
    cout << "Enter Roll No. to delete: ";
    cin >> rollNo;

    ifstream inFile(FILENAME);
    if (!inFile) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    ofstream outFile("temp.txt");
    if (!outFile) {
        cerr << "Error opening temporary file." << endl;
        inFile.close();
        return;
    }

    Student s;
    bool found = false;
    while (!inFile.eof()) {
        s.readFromFile(inFile);
        if (inFile.eof()) break; // To avoid an infinite loop when reaching the end of the file
        if (s.rollNo != rollNo) {
            s.writeToFile(outFile);
        } else {
            found = true;
        }
    }
    inFile.close();
    outFile.close();

    if (found) {
        remove(FILENAME);
        rename("temp.txt", FILENAME);
        cout << "Record with Roll No. " << rollNo << " deleted successfully." << endl;
    } else {
        cout << "Record not found." << endl;
        remove("temp.txt");
    }
}

int main() {
    int choice;
    do {
        cout << "\n<<<<<<<<<<<< MENU >>>>>>>>>>>>\n"
             << "1. Add Record\n"
             << "2. Display All Records\n"
             << "3. Search by Roll No.\n"
             << "4. Delete Record\n"
             << "5. Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addRecord();
                break;
            case 2:
                displayAllRecords();
                break;
            case 3:
                searchByRollNo();
                break;
            case 4:
                deleteRecord();
                break;
            case 5:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}

