#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Employee {
    int id;
    char name[50];
    int age;
    char department[50];
    float salary;
    struct Employee* next;
} Employee;

Employee* head = NULL;

Employee* createEmployee(int id, char name[], int age, char department[], float salary) {
    Employee* newEmployee = (Employee*)malloc(sizeof(Employee));
    if(newEmployee == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newEmployee->id = id;
    strcpy(newEmployee->name, name);
    newEmployee->age = age;
    strcpy(newEmployee->department, department);
    newEmployee->salary = salary;
    newEmployee->next = NULL;
    return newEmployee;
}

void addEmployee() {
    int id, age;
    char name[50], department[50];
    float salary;
    
    printf("Enter Employee ID: ");
    scanf("%d", &id);
    printf("Enter Employee Name: ");
    scanf(" %[^\n]s", name);
    printf("Enter Age: ");
    scanf("%d", &age);
    printf("Enter Department: ");
    scanf(" %[^\n]s", department);
    printf("Enter Salary: ");
    scanf("%f", &salary);
    
    Employee* newEmp = createEmployee(id, name, age, department, salary);
    
    newEmp->next = head;
    head = newEmp;
    
    printf("Employee added successfully!\n");
}

void displayEmployees() {
    if (head == NULL) {
        printf("No employees found.\n");
        return;
    }
    
    Employee* temp = head;
    printf("\nEmployee Records:\n");
    printf("ID\tName\t\tAge\tDepartment\tSalary\n");
    printf("-----------------------------------------------------------\n");
    while(temp != NULL) {
        printf("%d\t%-15s\t%d\t%-15s\t%.2f\n", 
               temp->id, temp->name, temp->age, temp->department, temp->salary);
        temp = temp->next;
    }
}

Employee* searchEmployee(int id) {
    Employee* temp = head;
    while(temp != NULL) {
        if(temp->id == id)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void deleteEmployee() {
    int id;
    printf("Enter Employee ID to delete: ");
    scanf("%d", &id);
    
    Employee *temp = head, *prev = NULL;
    
    if(temp != NULL && temp->id == id) {
        head = temp->next;
        free(temp);
        printf("Employee deleted successfully!\n");
        return;
    }
    
    while(temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    
    if(temp == NULL) {
        printf("Employee with ID %d not found.\n", id);
        return;
    }
    
    prev->next = temp->next;
    free(temp);
    printf("Employee deleted successfully!\n");
}

void menu() {
    int choice;
    do {
        printf("\n=== Employee Record System ===\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Delete Employee\n");
        printf("4. Search Employee\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                displayEmployees();
                break;
            case 3:
                deleteEmployee();
                break;
            case 4: {
                int id;
                printf("Enter Employee ID to search: ");
                scanf("%d", &id);
                Employee* emp = searchEmployee(id);
                if(emp != NULL)
                    printf("Employee Found: ID: %d, Name: %s, Age: %d, Department: %s, Salary: %.2f\n", 
                           emp->id, emp->name, emp->age, emp->department, emp->salary);
                else
                    printf("Employee with ID %d not found.\n", id);
                break;
            }
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 5);
}

int main() {
    menu();
    return 0;
}
