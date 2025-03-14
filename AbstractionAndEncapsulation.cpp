#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

#define RED "\033[1;31m"
#define YELLOW "\033[1;33m"
#define RESET "\033[0m"

class Employee {
protected:
    string id, name;
public:
    Employee(string id, string name) : id(id), name(name) {}
    virtual void displayPayroll() const = 0;
    virtual ~Employee() {}
    string getId() const { return id; }
};

class FullTimeEmployee : public Employee {
    double salary;
public:
    FullTimeEmployee(string id, string name, double salary) 
        : Employee(id, name), salary(salary) {}
    void displayPayroll() const override {
        cout << RED << "Employee: " << RESET << name << " (ID: " << id << ")\n";
        cout << "Fixed Monthly Salary: $" << salary << "\n\n";
    }
};

class PartTimeEmployee : public Employee {
    double hourlyWage;
    int hoursWorked;
public:
    PartTimeEmployee(string id, string name, double hourlyWage, int hoursWorked) 
        : Employee(id, name), hourlyWage(hourlyWage), hoursWorked(hoursWorked) {}
    void displayPayroll() const override {
        cout << RED << "Employee: " << RESET << name << " (ID: " << id << ")\n";
        cout << "Hourly Wage: $" << hourlyWage << "\nHours Worked: " << hoursWorked << "\n";
        cout << YELLOW << "Total " << RESET << "Salary: $" << hourlyWage * hoursWorked << "\n\n";
    }
};

class ContractualEmployee : public Employee {
    double salaryPerProject;
    int numProjects;
public:
    ContractualEmployee(string id, string name, double salaryPerProject, int numProjects) 
        : Employee(id, name), salaryPerProject(salaryPerProject), numProjects(numProjects) {}
    void displayPayroll() const override {
        cout << RED << "Employee: " << RESET << name << " (ID: " << id << ")\n";
        cout << "Contract Payment Per Project: $" << salaryPerProject << "\nProjects Completed: " << numProjects << "\n";
        cout << YELLOW << "Total " << RESET << "Salary: $" << salaryPerProject * numProjects << "\n\n";
    }
};

double getDouble(string prompt) {
    double val;
    cout << prompt; cin >> val;
    while (cin.fail()) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Try again: "; cin >> val;
    }
    return val;
}

int getInt(string prompt) {
    int val;
    cout << prompt; cin >> val;
    while (cin.fail() || val <= 0) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Try again: "; cin >> val;
    }
    return val;
}

int main() {
    vector<Employee*> employees;
    vector<string> ids;
    bool myCondition = true;

    while (myCondition) {
        cout << "\nMenu\n";
        cout << "1 - Full-time Employee\n";
        cout << "2 - Part-time Employee\n";
        cout << "3 - Contractual Employee\n";
        cout << "4 - Display Payroll Report\n";
        cout << "5 - Exit\n";
        cout << "Enter your choice: ";
        int choice; cin >> choice;

        if (choice == 5) break;
        if (choice == 4) {
            cout << "\n------ Employee Payroll Report ------\n";
            if (employees.empty()) cout << "No employees added.\n";
            else for (const auto& emp : employees) emp->displayPayroll();
            continue;
        }
        
        string id, name;
        do {
            cout << "Enter ID: "; cin >> id;
        } while (find(ids.begin(), ids.end(), id) != ids.end() && cout << "Duplicate ID! Try again.\n");
        ids.push_back(id);

        cin.ignore();
        cout << "Enter Name: "; getline(cin, name);

        if (choice == 1) employees.push_back(new FullTimeEmployee(id, name, getDouble("Enter Salary: ")));
        else if (choice == 2) employees.push_back(new PartTimeEmployee(id, name, getDouble("Enter Hourly Wage: "), getInt("Enter Hours: ")));
        else if (choice == 3) employees.push_back(new ContractualEmployee(id, name, getDouble("Enter Salary per Project: "), getInt("Enter Number of Projects: ")));
    }

    for (auto emp : employees) {
        delete emp;
    }

    return 0;
}
