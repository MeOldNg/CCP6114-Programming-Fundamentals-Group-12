# Student Attendance Tracker - Milestone 1

A C++ console-based application designed to track student attendance. This program allows users to create attendance sheets, input student data (ID, Name, Status), and save the information directly to a CSV file for easy viewing in Excel or spreadsheet software.

## 📋 Features

* **Create Attendance Sheets:** user-defined naming for attendance files.
* **Data Entry:** Supports input for up to **10 students** per session.
* **Input Validation:**
    * Prevents entering more than the maximum allowed students.
    * Supports spaces in filenames (e.g., "Class A").
* **Data Types:**
    * **IDs:** Stored as strings to preserve leading zeros (e.g., `0010` stays `0010`).
    * **Names & Status:** Text-based input.
* **File Handling:** Automatically creates and saves data to `.csv` format.
* **View Mode:** Reads the generated CSV file and displays the content within the console.
* **UTF-8 Support:** optimized for Windows consoles to ensure clean text output.

## 🛠️ Technologies Used

* **Language:** C++
* **Libraries:** `<iostream>`, `<fstream>`, `<string>`, `<windows.h>`

## 🚀 How to Run

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/YourUsername/YourRepo.git](https://github.com/YourUsername/YourRepo.git)
    ```

2.  **Compile the code:**
    You can use g++ or any C++ IDE (like Visual Studio or Code::Blocks).
    ```bash
    g++ TC1L_Group12_main.cpp -o attendance_tracker
    ```

3.  **Run the application:**
    ```bash
    ./attendance_tracker
    ```

## 📖 Usage Example

```text
=============================================
 STUDENT ATTENDANCE TRACKER - MILESTONE 1
=============================================
Enter attendance sheet name: Class A
How many students do you want to add? (Max 10): 2

----------------------
Student 1
Enter ID (Number): 0010
Enter Name: Ali
Enter Status (Present/Absent): Present
----------------------
Student 2
Enter ID (Number): 0020
Enter Name: Abu
Enter Status (Present/Absent): Absent

Data saved to Class A.csv
--- CSV VIEW MODE ---
ID,Name,Status
0010,Ali,Present
0020,Abu,Absent
