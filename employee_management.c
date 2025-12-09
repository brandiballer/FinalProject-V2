/*
* File: employee_management.c
* Author: Liam Keats 0307334k@acadiau.ca and Brandi Johnson (email here)
* Date: November 29th 2025
* Purpose: Skeleton for employee management system
* Notes: Contains struct, macros, and function
*        prototypes for managing employee data.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 50
#define POSITION_LEN 50
#define DATA_FILE "employees.dat"

// struct for employee data
typedef struct {
    int employeeID;
    char name[NAME_LEN];
    char position[POSITION_LEN];
    float salary;
} Employee;


/*========================*/
/*function declarations*/
/*========================*/

/* -------- Function declarations (prototypes) -------- */

/* Menu + core features */
static void printMenu(void);
static void addEmployee(void);
static void listEmployees(void);
static void searchEmployeeByID(void);

/* Input / utility helpers */
static void clearInputBuffer(void);
static void readLine(char *buffer, size_t size);
static int  getInt(const char *prompt);
static float getFloat(const char *prompt);
static void clearScreen(void);
static void pauseForEnter(void);
static void printEmployee(const Employee *emp);
static int  employeeExists(int employeeID);
static int isStringEmpty(const char *s);

/*========================*/
/*menu features*/
/*========================*/
static void printMenu(void){
    printf("==============================\n");
    printf("Employee Management System\n");
    printf("==============================\n");
    printf("1. Add Employee\n");
    printf("2. List Employees\n");
    printf("3. Search Employee by ID\n");
    printf("4. Exit\n");
    printf("==============================\n");
}

/*========================*/
/*input and help functions*/
/*========================*/
static void clearInputBuffer(void){
    int c;
    while ((c = getchar()) != '\n' && c != EOF){
        // discard characters
    }
}

static void readLine(char *buffer, size_t size){
    if (fgets(buffer, size, stdin) != NULL){
        size_t len = strlen(buffer);

        if (len > 0 && buffer[len - 1] == '\n'){
            buffer[len - 1] = '\0'; // remove newline

        } else {
            /*line too long flushing*/
            clearInputBuffer(); // clear remaining input
        }
    } else {
        /*failed fget this makes the buffer empty*/
        if (size > 0){
            buffer[0] = '\0';
        }
    }
}

static int getInt(const char *prompt){
    int value;
    int result;

    for (;;) {
        printf("%s", prompt);
        result = scanf("%d", &value);

        if (result == 1) {
            clearInputBuffer();
            return value;
        }

        printf("Invalid input. Please enter an integer.\n");
        clearInputBuffer();
    }
}

static float getFloat(const char *prompt){
    float value;
    int result;

    for (;;){
        printf("%s", prompt);
        result = scanf("%f", &value);
        if (result == 1){
            clearInputBuffer();
            return value;
        } else {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
        }
    }
}

static void clearScreen(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

static void pauseForEnter(void){
    printf("\nPress Enter to continue...");
    fflush(stdout);

    int c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

static void printEmployee(const Employee *emp)
{
    if (emp == NULL) {
        return;
    }

    printf("Employee ID : %d\n", emp->employeeID);
    printf("Name        : %s\n", emp->name);
    printf("Position    : %s\n", emp->position);
    printf("Salary      : %.2f\n", emp->salary);
    printf("----------------------------------\n");
}

static int employeeExists(int employeeID)
{
    FILE *fp = fopen(DATA_FILE, "rb");
    Employee emp;
    int found = 0;

    if (fp == NULL) {
        /* No file yet = no employees = no duplicates */
        return 0;
    }

    while (fread(&emp, sizeof(Employee), 1, fp) == 1) {
        if (emp.employeeID == employeeID) {
            found = 1;
            break;
        }
    }

    fclose(fp);
    return found;
}

static int isStringEmpty(const char *s)
{
    if (s == NULL) {
        return 1;
    }

    /* Skip leading spaces/tabs/newlines */
    while (*s == ' ' || *s == '\t' || *s == '\n') {
        s++;
    }

    /* If we hit the end of the string, it's empty/whitespace only */
    return *s == '\0';
}


/*========================*/
/*employee management functions*/
/*========================*/

static void addEmployee(void)
{
    Employee emp;
    FILE *fp;

    clearScreen();
    printf("========== Add Employee ==========\n\n");

    for (;;) {
        emp.employeeID = getInt("Enter employee ID: ");

        if (emp.employeeID <= 0) {
            printf("Employee ID must be a positive integer. Please try again.\n");
        } else if (employeeExists(emp.employeeID)) {
            printf("An employee with ID %d already exists. "
                "Please enter a different ID.\n",
                emp.employeeID);
        } else {
            break;
        }
    }

    do {
        printf("Enter name: ");
        readLine(emp.name, NAME_LEN);

        if (isStringEmpty(emp.name)) {
            printf("Name cannot be empty. Please enter a valid name.\n");
        }
    } while (isStringEmpty(emp.name));

    do {
        printf("Enter position: ");
        readLine(emp.position, POSITION_LEN);

        if (isStringEmpty(emp.position)) {
            printf("Position cannot be empty. Please enter a valid position.\n");
        }
    } while (isStringEmpty(emp.position));

    do {
        emp.salary = getFloat("Enter monthly salary: ");

        if (emp.salary < 0.0f) {
            printf("Salary cannot be negative. Please enter a value >= 0.\n");
        }
    } while (emp.salary < 0.0f);

    fp = fopen(DATA_FILE, "ab");
    if (fp == NULL) {
        perror("Error opening data file");
        return;
    }

    if (fwrite(&emp, sizeof(Employee), 1, fp) != 1) {
        perror("Error writing to data file");
        fclose(fp);
        return;
    }

    fclose(fp);

    printf("\nEmployee added successfully.\n");
}

static void listEmployees(void)
{
    Employee emp;
    FILE *fp;
    int count = 0;

    clearScreen();
    printf("========== Employee List ==========\n\n");

    fp = fopen(DATA_FILE, "rb");
    if (fp == NULL) {
        printf("No data file found. No employees to display.\n");
        return;
    }

    while (fread(&emp, sizeof(Employee), 1, fp) == 1) {
        printEmployee(&emp);
        count++;
    }

    if (count == 0) {
        printf("No employee records found.\n");
    }

    fclose(fp);
}

static void searchEmployeeByID(void)
{
    int targetID;
    Employee emp;
    FILE *fp;
    int found = 0;

    clearScreen();
    printf("====== Search Employee by ID ======\n\n");

    targetID = getInt("Enter employee ID to search for: ");

    fp = fopen(DATA_FILE, "rb");
    if (fp == NULL) {
        printf("No data file found. Cannot search.\n");
        return;
    }

    while (fread(&emp, sizeof(Employee), 1, fp) == 1) {
        if (emp.employeeID == targetID) {
            printf("\nEmployee found:\n");
            printEmployee(&emp);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nEmployee with ID %d not found.\n", targetID);
    }

    fclose(fp);
}

/*========================*/
/*main*/
/*===============*/
int main(void)
{
    int choice;

    do {
        clearScreen();          /* wipe whatever was there before */
        printMenu();            /* draw the main menu */

        choice = getInt("Enter your choice: ");

        switch (choice) {
        case 1:
            addEmployee();      /* this draws the Add screen */
            break;
        case 2:
            listEmployees();    /* this draws the List screen */
            break;
        case 3:
            searchEmployeeByID();  /* this draws the Search screen */
            break;
        case 4:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }

        if (choice != 4) {
            pauseForEnter();    /* wait so you can read that screen */
        }

    } while (choice != 4);

    return 0;
}
