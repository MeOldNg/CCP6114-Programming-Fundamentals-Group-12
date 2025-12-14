#include<iostream>
#include<fstream>
using namespace std;

int main() {
    string sheet_name;
    string filename;

    cout << "=============================================" << endl;
    cout << "  STUDENT ATTENDANCE TRACKER - MILESTONE 1" << endl;
    cout << "=============================================" << endl;

    cout << "Enter attendance sheet name: " << endl;
    cin >> sheet_name;
    filename = sheet_name + ".csv";
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Error";
    }
    return 0;
}