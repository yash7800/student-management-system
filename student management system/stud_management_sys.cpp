#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Struct to store student details
struct Student {
    string name;
    int id;
    float grade;
};

// Function prototypes
void createStudent(vector<Student>& records);
void viewStudents(const vector<Student>& records);
void modifyStudent(vector<Student>& records);
void removeStudent(vector<Student>& records);
void saveData(const vector<Student>& records, const string& filepath);
void loadData(vector<Student>& records, const string& filepath);

int main() {
    vector<Student> students;  // Container to hold student data
    string filepath = "student_records.txt";

    // Load existing data from file at the start
    loadData(students, filepath);

    int option;
    do {
        cout << "\n--- Student Management System ---\n";
        cout << "1. Add New Student\n";
        cout << "2. View All Students\n";
        cout << "3. Update Student Information\n";
        cout << "4. Delete Student Record\n";
        cout << "5. Save and Exit\n";
        cout << "Select an option: ";
        cin >> option;

        switch (option) {
            case 1:
                createStudent(students);
                break;
            case 2:
                viewStudents(students);
                break;
            case 3:
                modifyStudent(students);
                break;
            case 4:
                removeStudent(students);
                break;
            case 5:
                saveData(students, filepath);
                cout << "Data saved successfully. Exiting...\n";
                break;
            default:
                cout << "Invalid selection. Please try again.\n";
        }
    } while (option != 5);

    return 0;
}

// Function to add a new student
void createStudent(vector<Student>& records) {
    Student newStudent;
    cout << "Enter student name: ";
    cin.ignore();
    getline(cin, newStudent.name);
    cout << "Enter student ID: ";
    cin >> newStudent.id;
    cout << "Enter student grade: ";
    cin >> newStudent.grade;

    records.push_back(newStudent);
    cout << "Student added successfully.\n";
}

// Function to display all student records
void viewStudents(const vector<Student>& records) {
    if (records.empty()) {
        cout << "No student records found.\n";
        return;
    }

    cout << "\n--- Student Records ---\n";
    for (const auto& student : records) {
        cout << "Name: " << student.name << ", ID: " << student.id << ", Grade: " << student.grade << endl;
    }
}

// Function to update a student's details
void modifyStudent(vector<Student>& records) {
    int searchId;
    cout << "Enter the ID of the student to update: ";
    cin >> searchId;

    for (auto& student : records) {
        if (student.id == searchId) {
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, student.name);
            cout << "Enter new grade: ";
            cin >> student.grade;
            cout << "Student information updated successfully.\n";
            return;
        }
    }

    cout << "Student with ID " << searchId << " not found.\n";
}

// Function to delete a student's record
void removeStudent(vector<Student>& records) {
    int searchId;
    cout << "Enter the ID of the student to delete: ";
    cin >> searchId;

    for (auto it = records.begin(); it != records.end(); ++it) {
        if (it->id == searchId) {
            records.erase(it);
            cout << "Student record deleted successfully.\n";
            return;
        }
    }

    cout << "Student with ID " << searchId << " not found.\n";
}

// Function to save records to a file
void saveData(const vector<Student>& records, const string& filepath) {
    ofstream outFile(filepath);

    if (!outFile) {
        cout << "Error: Unable to save data to file.\n";
        return;
    }

    for (const auto& student : records) {
        outFile << student.name << endl;
        outFile << student.id << endl;
        outFile << student.grade << endl;
    }

    outFile.close();
}

// Function to load records from a file
void loadData(vector<Student>& records, const string& filepath) {
    ifstream inFile(filepath);

    if (!inFile) {
        cout << "No existing records found. Starting fresh.\n";
        return;
    }

    Student student;
    while (getline(inFile, student.name)) {
        inFile >> student.id >> student.grade;
        inFile.ignore();
        records.push_back(student);
    }

    inFile.close();
    cout << "Records loaded successfully.\n";
}
