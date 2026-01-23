// *********************************************************
// Program: TC1L_Group12_main.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC1L
// Tutorial Class: TT1L
// Trimester: 2530
// Member_1: 252UC24001 | Zul Fadhli Bin Zaiman | ZUL.FADHLI.ZAIMAN1@student.mmu.edu.my | 01133310455
// Member_2: 252UC24071 | NG JUN WEI | NG.JUN.WEI1@student.mmu.edu.my | 0182994163
// Member_3: 252UC2551C | SHAZARUL MUHAMMAD HAFIZ BIN SHAARI | SHAZARUL.MUHAMMAD.HAFIZ@student.mmu.edu.my | 0142122488
// Member_4: 252UC243K7 | WOON YU HERN | WOON.YU.HERN1@student.mmu.edu.my | 0109376813
// *********************************************************
// Task Distribution
// Member_1:Partial Documentation
// Member_2:Coder
// Member_3:flowchart 
// Member_4:Coder
// *********************************************************

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <windows.h> //prosess accesss
#include <limits>  //limit input

using namespace std;


void term(string term_name) {
    cout << "Create School Term (Database)" << endl;
    cout << "----------------------" << endl;
    cout << "Enter term name: " << endl;
    cin >> term_name;
    cout << "Database \"" << term_name << "\" created and loaded. " << endl << "Reading attendance data from file..." << endl;

}

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

    string term_name;
    string sheet_name;
    string filename;
    string sheet_option;

    cout << "=============================================" << endl;
    cout << " STUDENT ATTENDANCE TRACKER - MILESTONE 2" << endl;
    cout << "=============================================" << endl;

    term(term_name);

    cout << "Create or Load: " << endl;
    cin >> sheet_option;
    if (sheet_option == "create") {
        cout << "Enter attendance sheet name: ";
        getline(cin, sheet_name);

        while (sheet_name.empty()) {
            cout << "Input cannot be empty. Enter attendance sheet name: ";
            getline(cin, sheet_name);
        }

    filename = sheet_name + ".csv";
    viewSheet(filename);
    }
    else {
        viewSheet(filename);
    }

    

    writeSheet(filename);
    viewSheet(filename);

    return 0;
}
