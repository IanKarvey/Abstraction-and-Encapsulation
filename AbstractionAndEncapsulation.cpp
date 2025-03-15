#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

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
    FullTimeEmployee(string id, string name, double salary) : Employee(id, name), salary(salary) {}
    void displayPayroll() const override {
        cout << "Employee: " << name << " (ID: " << id << ")\n";
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
        cout << "Employee: " << name << " (ID: " << id << ")\n";
        cout << "Hourly Wage: $" << hourlyWage << "\n";
        cout << "Hours Worked: " << hoursWorked << "\n";
        cout << "Total Salary: $" << hourlyWage * hoursWorked << "\n\n";
    }
};

class ContractualEmployee : public Employee {
    double salaryPerProject;
    int numProjects;
public:
    ContractualEmployee(string id, string name, double salaryPerProject, int numProjects)
        : Employee(id, name), salaryPerProject(salaryPerProject), numProjects(numProjects) {}
    void displayPayroll() const override {
        cout << "Employee: " << name << " (ID: " << id << ")\n";
        cout << "Contract Payment Per Project: $" << salaryPerProject << "\n";
        cout << "Projects Completed: " << numProjects << "\n";
        cout << "Total Salary: $" << salaryPerProject * numProjects << "\n\n";
    }
};

double getDouble(string prompt) {
    double val;
    cout << prompt;
    while (!(cin >> val)) {
        cout << "Invalid input! Enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return val;
}

int getInt(string prompt) {
    string input;
    int val;
    bool myCondition = true;
    while (myCondition) {
        cout << prompt;
        cin >> input;
        if (input.find_first_not_of("0123456789") == string::npos) {
            val = stoi(input);
            if (val > 0) {
                myCondition = false;
            } else {
                cout << "Invalid input! Enter a positive whole number: ";
            }
        } else {
            cout << "Invalid input! Enter a positive whole number: ";
        }
    }
    return val;
}

string getNumericID(string prompt) {
    string id;
    bool myCondition = true;
    while (myCondition) {
        cout << prompt;
        cin >> id;
        if (id.find_first_not_of("0123456789") == string::npos) {
            myCondition = false;
        } else {
            cout << "Invalid input! ID must contain only numbers.\n";
        }
    }
    return id;
}

int getChoice() {
    return getInt("\n1 - Full-time\n2 - Part-time\n3 - Contractual\n4 - Show Payroll\n5 - Exit\nEnter choice: ");
}

int main() {
    vector<Employee*> employees;
    vector<string> ids;
    bool running = true;

    while (running) {
        int choice = getChoice();
        if (choice == 4) {
            cout << "\n------ Employee Payroll Report ------\n";
            if (employees.empty()) {
                cout << "No employees yet.\n";
            } else {
                for (const auto& emp : employees) {
                    emp->displayPayroll();
                }
            }
        } else if (choice == 5) {
            running = false;
        } else if (choice >= 1 && choice <= 3) {
            string id, name;
            bool duplicateFound = true;
            while (duplicateFound) {
                id = getNumericID("Enter ID: ");
                duplicateFound = (find(ids.begin(), ids.end(), id) != ids.end());
                if (duplicateFound) {
                    cout << "Duplicate ID!\n";
                }
            }
            
            ids.push_back(id);
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, name);
            
            if (choice == 1) {
                employees.push_back(new FullTimeEmployee(id, name, getDouble("Enter Salary: ")));
            } else if (choice == 2) {
                employees.push_back(new PartTimeEmployee(id, name, getDouble("Enter Hourly Wage: "), getInt("Enter Hours Worked: ")));
            } else {
                employees.push_back(new ContractualEmployee(id, name, getDouble("Enter Per Project Salary: "), getInt("Enter No. of Projects: ")));
            }
        }
    }

    for (auto emp : employees) {
        delete emp;
    }
    return 0;
}