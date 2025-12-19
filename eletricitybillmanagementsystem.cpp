#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Consumer {
    int id;
    string name;
    int units;
    float bill;
};

float calculateBill(int units) {
    float amount = 0;
    if (units <= 100)
        amount = units * 5;
    else if (units <= 300)
        amount = (100 * 5) + (units - 100) * 7;
    else
        amount = (100 * 5) + (200 * 7) + (units - 300) * 10;
    return amount;
}

void addConsumer() {
    Consumer c;
    ofstream file("electricity.txt", ios::app);

    cout << "Enter Consumer ID: ";
    cin >> c.id;
    cin.ignore();
    cout << "Enter Consumer Name: ";
    getline(cin, c.name);
    cout << "Enter Units Consumed: ";
    cin >> c.units;

    c.bill = calculateBill(c.units);

    file << c.id << " | " << c.name << " | " << c.units << " | " << c.bill << endl;
    file.close();

    cout << "Consumer added successfully!\n";
}

void displayConsumers() {
    ifstream file("electricity.txt");
    string line;

    cout << "\n--- Consumer Records ---\n";
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

int main() {
    int choice;

    do {
        cout << "\n===== Electricity Bill Management System =====\n";
        cout << "1. Add Consumer\n";
        cout << "2. Display All Consumers\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addConsumer();
                break;
            case 2:
                displayConsumers();
                break;
            case 3:
                cout << "Exiting program...";
                break;
            default:
                cout << "Invalid choice!";
        }
    } while (choice != 3);

    return 0;
}
