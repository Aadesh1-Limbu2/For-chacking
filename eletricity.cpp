#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // For formatting output
#include <limits>  // For input validation

using namespace std;

// Customer class
class Customer {
public:
    int id;
    string name;
    string address;
    string contact;

    Customer(int id, string name, string address, string contact)
        : id(id), name(name), address(address), contact(contact) {}

    void display() const {
        cout << "ID: " << id << "\nName: " << name << "\nAddress: " << address << "\nContact: " << contact << endl;
    }
};

// Bill class
class Bill {
public:
    int billId;
    int customerId;
    double consumption; // in kWh
    double ratePerKwh;  // rate per kWh
    double totalAmount;
    string dueDate;

    Bill(int billId, int customerId, double consumption, double ratePerKwh, string dueDate)
        : billId(billId), customerId(customerId), consumption(consumption), ratePerKwh(ratePerKwh), dueDate(dueDate) {
        totalAmount = consumption * ratePerKwh;
    }

    void display() const {
        cout << "Bill ID: " << billId << "\nCustomer ID: " << customerId << "\nConsumption: " << consumption << " kWh\nRate: $" << ratePerKwh << "/kWh\nTotal: $" << fixed << setprecision(2) << totalAmount << "\nDue Date: " << dueDate << endl;
    }
};

// Electricity Management System class
class ElectricityManagementSystem {
private:
    vector<Customer> customers;
    vector<Bill> bills;
    int nextCustomerId = 1;
    int nextBillId = 1;

public:
    // Create Customer
    void createCustomer() {
        string name, address, contact;
        cout << "Enter Name: ";
        getline(cin >> ws, name); // ws to handle spaces
        cout << "Enter Address: ";
        getline(cin, address);
        cout << "Enter Contact: ";
        getline(cin, contact);

        customers.push_back(Customer(nextCustomerId++, name, address, contact));
        cout << "Customer created successfully!\n";
    }

    // Read Customer
    void readCustomer() {
        int id;
        cout << "Enter Customer ID: ";
        cin >> id;
        for (const auto& cust : customers) {
            if (cust.id == id) {
                cust.display();
                return;
            }
        }
        cout << "Customer not found.\n";
    }

    // Update Customer
    void updateCustomer() {
        int id;
        cout << "Enter Customer ID to update: ";
        cin >> id;
        for (auto& cust : customers) {
            if (cust.id == id) {
                string name, address, contact;
                cout << "Enter new Name: ";
                getline(cin >> ws, name);
                cout << "Enter new Address: ";
                getline(cin, address);
                cout << "Enter new Contact: ";
                getline(cin, contact);

                cust.name = name;
                cust.address = address;
                cust.contact = contact;
                cout << "Customer updated successfully!\n";
                return;
            }
        }
        cout << "Customer not found.\n";
    }

    // Delete Customer
    void deleteCustomer() {
        int id;
        cout << "Enter Customer ID to delete: ";
        cin >> id;
        for (auto it = customers.begin(); it != customers.end(); ++it) {
            if (it->id == id) {
                customers.erase(it);
                cout << "Customer deleted successfully!\n";
                return;
            }
        }
        cout << "Customer not found.\n";
    }

    // Create Bill
    void createBill() {
        int customerId;
        double consumption, rate;
        string dueDate;
        cout << "Enter Customer ID: ";
        cin >> customerId;
        // Check if customer exists
        bool exists = false;
        for (const auto& cust : customers) {
            if (cust.id == customerId) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            cout << "Customer not found. Cannot create bill.\n";
            return;
        }

        cout << "Enter Consumption (kWh): ";
        cin >> consumption;
        cout << "Enter Rate per kWh: ";
        cin >> rate;
        cout << "Enter Due Date (e.g., 2023-12-31): ";
        cin >> dueDate;

        bills.push_back(Bill(nextBillId++, customerId, consumption, rate, dueDate));
        cout << "Bill created successfully!\n";
    }

    // Read Bill
    void readBill() {
        int billId;
        cout << "Enter Bill ID: ";
        cin >> billId;
        for (const auto& bill : bills) {
            if (bill.billId == billId) {
                bill.display();
                return;
            }
        }
        cout << "Bill not found.\n";
    }

    // Update Bill
    void updateBill() {
        int billId;
        cout << "Enter Bill ID to update: ";
        cin >> billId;
        for (auto& bill : bills) {
            if (bill.billId == billId) {
                double consumption, rate;
                string dueDate;
                cout << "Enter new Consumption (kWh): ";
                cin >> consumption;
                cout << "Enter new Rate per kWh: ";
                cin >> rate;
                cout << "Enter new Due Date: ";
                cin >> dueDate;

                bill.consumption = consumption;
                bill.ratePerKwh = rate;
                bill.dueDate = dueDate;
                bill.totalAmount = consumption * rate;
                cout << "Bill updated successfully!\n";
                return;
            }
        }
        cout << "Bill not found.\n";
    }

    // Delete Bill
    void deleteBill() {
        int billId;
        cout << "Enter Bill ID to delete: ";
        cin >> billId;
        for (auto it = bills.begin(); it != bills.end(); ++it) {
            if (it->billId == billId) {
                bills.erase(it);
                cout << "Bill deleted successfully!\n";
                return;
            }
        }
        cout << "Bill not found.\n";
    }

    // Display Menu
    void menu() {
        int choice;
        do {
            cout << "\n--- Electricity Management System ---\n";
            cout << "1. Create Customer\n";
            cout << "2. Read Customer\n";
            cout << "3. Update Customer\n";
            cout << "4. Delete Customer\n";
            cout << "5. Create Bill\n";
            cout << "6. Read Bill\n";
            cout << "7. Update Bill\n";
            cout << "8. Delete Bill\n";
            cout << "9. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1: createCustomer(); break;
                case 2: readCustomer(); break;
                case 3: updateCustomer(); break;
                case 4: deleteCustomer(); break;
                case 5: createBill(); break;
                case 6: readBill(); break;
                case 7: updateBill(); break;
                case 8: deleteBill(); break;
                case 9: cout << "Exiting...\n"; break;
                default: cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 9);
    }
};

int main() {
    ElectricityManagementSystem ems;
    ems.menu();
    return 0;
}