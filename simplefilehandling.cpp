#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Student {
    int id;
    string name;   // full name
    int grade;
    double fee;
};

string getFilename(int grade) {
    return "grade_" + to_string(grade) + ".txt";
}

// Add new student
void addStudent() {
    Student s;
    cout << "Enter Student ID: "; cin >> s.id;
    cin.ignore();
    cout << "Enter Full Name: "; getline(cin, s.name);
    cout << "Enter Grade (1,2,3...): "; cin >> s.grade;
    s.fee = 0;

    ofstream file(getFilename(s.grade), ios::app);
    file << s.id << "\n";
    file << s.name << "\n";
    file << s.grade << " " << s.fee << "\n";
    file.close();

    cout << "Student Added Successfully!\n";
}

// Remove student
void removeStudent() {
    int grade, searchId;
    cout << "Enter Grade of Student: "; cin >> grade;
    cout << "Enter Student ID to remove: "; cin >> searchId;

    string filename = getFilename(grade);
    ifstream infile(filename);
    if (!infile) { cout << "No such grade exists!\n"; return; }

    vector<Student> students;
    Student temp;

    while (infile >> temp.id) {
        infile.ignore();
        getline(infile, temp.name);
        infile >> temp.grade >> temp.fee;
        infile.ignore();
        students.push_back(temp);
    }
    infile.close();

    bool found = false;
    ofstream outfile(filename);
    for (auto &st : students) {
        if (st.id == searchId) { found = true; continue; }
        outfile << st.id << "\n" << st.name << "\n" << st.grade << " " << st.fee << "\n";
    }
    outfile.close();

    if (found) cout << "Student Removed Successfully!\n";
    else cout << "Student not found!\n";
}

// Add or clear student fee
void feeMenu() {
    int choice, grade, id;
    cout << "1. Add Fee\n2. Clear Fee\nEnter choice: "; cin >> choice;

    cout << "Enter Grade: "; cin >> grade;
    cout << "Enter Student ID: "; cin >> id;

    string filename = getFilename(grade);
    ifstream infile(filename);
    if (!infile) { cout << "No such grade found!\n"; return; }

    vector<Student> stList;
    Student temp;

    while (infile >> temp.id) {
        infile.ignore();
        getline(infile, temp.name);
        infile >> temp.grade >> temp.fee;
        infile.ignore();
        stList.push_back(temp);
    }
    infile.close();

    bool found = false;
    for (auto &st : stList) {
        if (st.id == id) {
            found = true;
            if (choice == 1) {
                double amount;
                cout << "Enter amount to add: "; cin >> amount;
                st.fee += amount;
            } else if (choice == 2) {
                st.fee = 0;
            }
            break;
        }
    }

    if (!found) { cout << "Student not found!\n"; return; }

    ofstream outfile(filename);
    for (auto &st : stList)
        outfile << st.id << "\n" << st.name << "\n" << st.grade << " " << st.fee << "\n";
    outfile.close();

    cout << "Fee Updated Successfully!\n";
}

// Display students of a grade
void displayGrade() {
    int grade;
    cout << "Enter Grade: "; cin >> grade;
    string filename = getFilename(grade);

    ifstream file(filename);
    if (!file) { cout << "No students in this grade!\n"; return; }

    Student s;
    cout << "\n--- Students of Grade " << grade << " ---\n";

    while (file >> s.id) {
        file.ignore();
        getline(file, s.name);
        file >> s.grade >> s.fee;
        file.ignore();
        cout << "ID: " << s.id << "  Name: " << s.name << "  Fee: " << s.fee << "\n";
    }
    file.close();
}

// Display all students
void displayAll() {
    cout << "\n====== ALL STUDENTS ======\n";

    for (int g = 1; g <= 12; g++) {
        string filename = getFilename(g);
        ifstream file(filename);
        if (!file) continue;

        cout << "\n--- Grade " << g << " Students ---\n";
        Student s;

        while (file >> s.id) {
            file.ignore();
            getline(file, s.name);
            file >> s.grade >> s.fee;
            file.ignore();
            cout << "ID: " << s.id << "  Name: " << s.name << "  Fee: " << s.fee << "\n";
        }
        file.close();
    }
}

int main() {
    int choice;
    while (true) {
        cout << "\n===== STUDENT MANAGEMENT SYSTEM =====\n";
        cout << "1. New Student Options\n";
        cout << "2. Fee of Student\n";
        cout << "3. Display Students of a Grade\n";
        cout << "4. Display All Students\n";
        cout << "5. Exit\n";
        cout << "Enter Choice: "; cin >> choice;

        switch (choice) {
        case 1: {
            int c;
            cout << "1. Add Student\n2. Remove Student\nEnter choice: "; cin >> c;
            if (c == 1) addStudent();
            else if (c == 2) removeStudent();
            else cout << "Invalid!\n";
            break;
        }
        case 2: feeMenu(); break;
        case 3: displayGrade(); break;
        case 4: displayAll(); break;
        case 5: return 0;
        default: cout << "Invalid choice!\n";
        }
    }
}