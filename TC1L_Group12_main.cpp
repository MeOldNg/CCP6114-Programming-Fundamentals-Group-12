#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <windows.h> //prosess accesss
#include <limits>  //limit input

using namespace std;

void writeSheet(string filename) {
    int ids[10];
    string names[20];
    string status[10];
    int count = 0;

    do {
        cout << "How many students do you want to add? (Max 10): ";
        if (!(cin >> count)) {
            cin.clear();
            cin.ignore(10000, '\n');
            count = 11;
        } else {
            if (count > 10) {
                cout << "The max is 10" << endl;
            }
        }
    } while (count > 10 || count <= 0);

    cin.ignore();

    for (int i = 0; i < count; i++) {
        cout << "----------------------" << endl;
        cout << "Student " << i + 1 << endl;

        while (true) {
            cout << "Enter StudentID (Max 10 Digits): ";
            if (cin >> ids[i]) {
                cin.ignore();
                break;
            } else {
                cout << "Error: Invalid INT value. Please enter a number." << endl; //input checking message
                cin.clear();
                cin.ignore(10000, '\n');  //minor fix
            }
        }

        do {
            cout << "Enter Name: ";
            getline(cin, names[i]);
            // null checker
            if (names[i].empty()) {
                cout << "Input cannot be empty. Please try again." << endl;
            }
        } while (names[i].empty());

        do {
            cout << "Enter Status (Present/Absent): ";
            getline(cin, status[i]);
            if (status[i].empty()) { //null checker
                cout << "Input cannot be empty. Please try again." << endl;
            }
        } while (status[i].empty());
    }

    ofstream file(filename.c_str()); //file create handle
    if (!file) {
        cout << "Error creating file." << endl;
    } else {
        file << "ID,Name,Status" << endl;
        for (int i = 0; i < count; i++) {
            file << ids[i] << "," << names[i] << "," << status[i] << endl;
        }
        file.close();
        cout << "Data saved to " << filename << endl;
    }
}

void viewSheet(string filename) {
    string line;
    ifstream file(filename.c_str());

    if (!file) {
        cout << "Error opening file." << endl;
    } else {
        cout << "--- CSV VIEW MODE ---" << endl;
        getline(file, line);

        cout << left << setw(10) << "ID"
             << left << setw(20) << "Name"
             << left << setw(10) << "Status" << endl;

        string id, name, stat;

        while (file.good()) {
            getline(file, id, ',');
            getline(file, name, ',');
            getline(file, stat, '\n');

            if(!id.empty()) {
                 cout << left << setw(10) << id
                      << left << setw(20) << name
                      << left << setw(10) << stat << endl;
            }
        }
        file.close();
    }
}

int main() {
    SetConsoleOutputCP(65001);

    string sheet_name;
    string filename;

    cout << "=============================================" << endl;
    cout << " STUDENT ATTENDANCE TRACKER - MILESTONE 1" << endl;
    cout << "=============================================" << endl;

    cout << "Enter attendance sheet name: ";
    getline(cin, sheet_name);

    while (sheet_name.empty()) {
        cout << "Input cannot be empty. Enter attendance sheet name: ";
        getline(cin, sheet_name);
    }

    filename = sheet_name + ".csv";

    writeSheet(filename);
    viewSheet(filename);

    return 0;
}
