#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

void writeSheet(string filename) {
    string ids[10];
    string names[20];
    string status[2];
    int count = 0;

    do {
        cout << "How many students do you want to add? (Max 10): ";
        cin >> count;

        if (count > 10) {
            cout << "The max is 10" << endl;
        }
    } while (count > 10);

    for (int i = 0; i < count; i++) {
        cout << "----------------------" << endl;
        cout << "Student " << i + 1 << endl;
        cout << "Enter ID (Number): ";
        cin >> ids[i];
        cout << "Enter Name: ";
        cin >> names[i];
        cout << "Enter Status P/A (Present/Absent): ";
        cin >> status[i];
    }

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
    // Using getline allows names with spaces like "Class A"
    getline(cin, sheet_name);
    filename = sheet_name + ".csv";

    writeSheet(filename);
    viewSheet(filename);

    return 0;
}
