#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

void writeSheet(string filename) {
    string ids[10];
    string names[20];
    string status[10];
    int count = 0;

    do {
        cout << "How many students do you want to add? (Max 10): ";
        if (!(cin >> count)) {
            cin.clear();
            cin.ignore(10000, '\n'); //debug dont delete idk why but it work
            count = 11;
        } else {
            if (count > 10) {
                cout << "The max is 10" << endl;
            }
        }
    } while (count > 10 || count <= 0);

    cin.ignore(); //debug for leak input

// student number output as Student "n"
    for (int i = 0; i < count; i++) {
        cout << "----------------------" << endl;
        cout << "Student " << i + 1 << endl;

        // ID input null checker
        do {
            cout << "Enter ID (Number): ";
            getline(cin, ids[i]);
            if (ids[i].empty()) {
                cout << "Input cannot be empty. Please try again." << endl;
            }
        } while (ids[i].empty());

        // Name input null checker
        do {
            cout << "Enter Name: ";
            getline(cin, names[i]);
            if (names[i].empty()) {
                cout << "Input cannot be empty. Please try again." << endl;
            }
        } while (names[i].empty());

        // Attandance input null checker
        do {
            cout << "Enter Status (Present/Absent): ";
            getline(cin, status[i]);
            if (status[i].empty()) {
                cout << "Input cannot be empty. Please try again." << endl;
            }
        } while (status[i].empty());
    }

//file create function
    ofstream file(filename.c_str());
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
        while (getline(file, line)) {
            cout << line << endl;
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

    // input null checker
    while (sheet_name.empty()) {
        cout << "Input cannot be empty. Enter attendance sheet name: ";
        getline(cin, sheet_name);
    }

    filename = sheet_name + ".csv";

    writeSheet(filename);
    viewSheet(filename);

    return 0;
}
