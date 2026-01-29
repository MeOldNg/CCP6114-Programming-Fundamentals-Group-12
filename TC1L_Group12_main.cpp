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
    // Member_1:Coder, Partial Documentation
    // Member_2:Coder, Documentation
    // Member_3:Flowchart
    // Member_4:Coder
    // *********************************************************

    #include <iostream>
    #include <iomanip>
    #include <fstream>
    #include <string>
    #include <windows.h> //prosess accesss
    #include <limits>  //limit input
    #include <sstream>
    using namespace std;

    void term(string term_name) {
        cout << "Create School Term (Database)" << endl;
        cout << "----------------------" << endl;
        cout << "Enter term name: " << endl;
        cin >> term_name;
        cout << "Database \"" << term_name << "\" created and loaded. " << endl << "Reading attendance data from file..." << endl;
    }


    // count student total
void countRows(string filename) {
    ifstream file(filename.c_str());
    if (!file) {
        return;
    }

    int rows = 0;
    string line;

    getline(file, line); // Skip the first line because it's just the header

    // take alll input
    while (getline(file, line)) {
        //check input
        if (!line.empty()) {
            rows++;
        }
    }
    file.close();

    // output
    cout << "------------------------------------------" << endl;
    cout << "Count Rows" << endl;
    cout << "------------------------------------------" << endl;
    cout << "Number of rows: " << rows << endl;
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

void advancedErrorUpdate(string filename) {
    cout << endl;
    cout << "------------------------------------------" << endl;
    cout << "Advanced Error Handling" << endl;
    cout << "------------------------------------------" << endl;

    int updateID;
    bool validID = false;


    while (!validID) {
        cout << "Enter StudentID to update: ";

        // Check input
        if (!(cin >> updateID)) {
            cout << "Error: Invalid integer. Try again." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        } else {
            // Check valid
            ifstream checkFile(filename.c_str());
            string line, idCheck;
            bool exists = false;

            while (getline(checkFile, line)) {
                stringstream ss(line);
                getline(ss, idCheck, ',');
                // Try to convert ID to number to compare
                try {
                    if (stoi(idCheck) == updateID) {
                        exists = true;
                        break;
                    }
                } catch (...) {}
            }
            checkFile.close();

            if (exists) {
                validID = true;
            } else {
                cout << "Error: StudentID does not exist." << endl;
            }
        }
    }


    ifstream src(filename.c_str());
    ofstream dst("updated.csv");
    string line;

    while (getline(src, line)) {
        stringstream ss(line);
        string idStr, name, status;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, status);

        try {
            // If this is the student we want to update
            if (stoi(idStr) == updateID) {
                cout << "Current Status: " << status << endl;
                cout << "Enter new status: ";
                string newStatus;
                cin.ignore();
                getline(cin, newStatus);

                // Write the updated details to the temp file
                dst << idStr << "," << name << "," << newStatus << endl;
                cout << "Row updated successfully." << endl;
            } else {
                // Keep the other students exactly as they are
                dst << line << endl;
            }
        } catch (...) {
            // Keep the header row or empty lines
            dst << line << endl;
        }
    }

    src.close();
    dst.close();

    // output
    remove(filename.c_str());
    rename("updated.csv", filename.c_str());
}



    void deleteStudent(string filename) {
        ifstream file(filename.c_str());

        if (!file) {
            cout << "Error opening file." << endl;
            return;
        }

        int deleteID;

        cout << "Enter Student ID to delete: ";
        cin >> deleteID;

        ofstream temp("temp.txt", ios::app);

        if (!temp) {
            cout << "Error creating temp file." << endl;
            file.close();
            return;
        }

        string line;
        bool found = false;


        getline(file, line);
        temp << line << endl;


        while (getline(file, line)) {
            string id, name, status;
            stringstream ss(line);

            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, status);

            if (stoi(id) == deleteID) {
                found = true;
                continue;
            }

            temp << id << "," << name << "," << status << endl;
        }

        file.close();
        temp.close();

        remove(filename.c_str());
        rename("temp.txt", filename.c_str());

        if (found) {
            cout << "Student ID " << deleteID << " deleted successfully." << endl;
        } else {
            cout << "Student ID not found." << endl;
        }
    }


    void deletestudentchoice(string filename) {
    char choice;
    cout << "Do you want to delete a student? (y/n): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
            deleteStudent(filename);
            viewSheet(filename); // Show list to verify deletion
            deletestudentchoice(filename); // Ask again
    }
    else if (choice == 'n' || choice == 'N') {
        viewSheet(filename);
        // [CHANGED] Removed exit(0) so the program can continue to countRows
    }
    else {
        cout << "The input is not valid, please try again!" << endl;
        deletestudentchoice(filename);
    }
}


    int main() {
    SetConsoleOutputCP(65001); // Fixes special characters

    string term_name;
    string sheet_name;
    string filename;
    string sheet_option;

    cout << "=============================================" << endl;
    cout << " STUDENT ATTENDANCE TRACKER - MILESTONE 2" << endl;
    cout << "=============================================" << endl;

    term(term_name);

    cout << "Create or Load: ";
    cin >> sheet_option;

    if (sheet_option == "create") {
        cout << "Enter attendance sheet name: ";
        cin.ignore(); // Need to clear the buffer before reading a string with spaces
        getline(cin, sheet_name);

        while (sheet_name.empty()) {
            cout << "Input cannot be empty. Enter attendance sheet name: ";
            getline(cin, sheet_name);
        }

        filename = sheet_name + ".csv";
        writeSheet(filename);

        viewSheet(filename);

        // Call the new update function
        advancedErrorUpdate(filename);
        viewSheet(filename);

        deletestudentchoice(filename);

        // Call the new count function
        countRows(filename);
    }
    else {
        cout << "Enter the filename you want to load (without .csv): ";
        cin.ignore();
        getline(cin, sheet_name);
        filename = sheet_name + ".csv";

        viewSheet(filename);

        // Call the new update function on loaded files too
        advancedErrorUpdate(filename);
        viewSheet(filename);

        deletestudentchoice(filename);

        // Call the new count function
        countRows(filename);
    }

    return 0;
}
