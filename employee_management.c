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
#include <ctype.h>

#define NAME_LEN 50
#define POSITION_LEN 50
#define DATA_FILE "employees.dat"
#define MAX_EMPLOYEES 1000

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

/* menu core */
static void printMenu(void);
static void addEmployee(void);
static void listEmployees(void);
static void searchEmployeeByID(void);

/* util helpers */
static void clearInputBuffer(void);
static void readLine(char *buffer, size_t size);
static int  getInt(const char *prompt);
static float getFloat(const char *prompt);
static void clearScreen(void);
static void pauseForEnter(void);
static void printEmployee(const Employee *emp);
static int  employeeExists(int employeeID);
static int isStringEmpty(const char *s);
static void importFromFile(void);
static int  loadAllEmployees(Employee employees[], int max);
static int  saveAllEmployees(Employee employees[], int count);
static void insertEmployeeSorted(Employee employees[], int *count, const Employee *emp);
static int nameHasDigit(const char *s);

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
    printf("5. Import Employees from File\n");
    printf("==============================\n");
}

/*========================*/
/*input and help functions*/
/*========================*/
static void clearInputBuffer(void){
    int c;
    while ((c = getchar()) != '\n' && c != EOF){
        // discards the chars
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

static int getInt(const char *prompt)
{
    char buffer[100];
    char *endptr;
    long value;

    for (;;) {
        printf("%s", prompt);
        readLine(buffer, sizeof buffer);

        if (isStringEmpty(buffer)) {
            printf("Input cannot be empty. Please enter a whole number (e.g. 101).\n");
            continue;
        }

        value = strtol(buffer, &endptr, 10);

        /* Skip trailing spaces/tabs */
        while (*endptr == ' ' || *endptr == '\t') {
            endptr++;
        }

        if (*endptr != '\0') {
            printf("Invalid input. Please enter digits only (e.g. 101).\n");
            continue;
        }

        return (int)value;
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

// clears the screen after each operation
static void clearScreen(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// pausing for user to press enter so it increased user interactivity
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
        /* if no file yet = no employees = no duplicates */
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

    /* skip leading spaces/tabs/newlines so no dumb shit */
    while (*s == ' ' || *s == '\t' || *s == '\n') {
        s++;
    }

    /* make sure ending is whitespace only */
    return *s == '\0';
}

static int nameHasDigit(const char *s)
{
    if (s == NULL) {
        return 0;
    }

    while (*s != '\0') {
        if (isdigit((unsigned char)*s)) {
            return 1;
        }
        s++;
    }

    return 0;
}


/* Load all employees from the data file into an array.
 * Returns the number of employees loaded (0 if file does not exist). */
static int loadAllEmployees(Employee employees[], int max)
{
    FILE *fp = fopen(DATA_FILE, "rb");
    int count = 0;

    if (fp == NULL) {
        /* no file no emps. */
        return 0;
    }

    while (count < max && fread(&employees[count], sizeof(Employee), 1, fp) == 1) {
        count++;
    }

    fclose(fp);
    return count;
}

/* save and overwrite employee.dat file. */
static int saveAllEmployees(Employee employees[], int count)
{
    FILE *fp = fopen(DATA_FILE, "wb");
    if (fp == NULL) {
        perror("Error opening data file for writing");
        return 0;
    }

    if ((int)fwrite(employees, sizeof(Employee), count, fp) != count) {
        perror("Error writing employees to data file");
        fclose(fp);
        return 0;
    }

    fclose(fp);
    return 1;
}

/* insert and sort using insertion sort*/
static void insertEmployeeSorted(Employee employees[], int *count, const Employee *emp)
{
    int pos = 0;
    int i;

    /* finding position */
    while (pos < *count && employees[pos].employeeID < emp->employeeID) {
        pos++;
    }

    /* shifting elements in array to insert */
    for (i = *count; i > pos; i--) {
        employees[i] = employees[i - 1];
    }

    employees[pos] = *emp;
    (*count)++;
}



/*========================*/
/*employee management functions*/
/*========================*/

static void addEmployee(void)
{
    Employee emp;
    Employee employees[MAX_EMPLOYEES];
    int count;

    clearScreen();
    printf("========== Add Employee ==========\n\n");

    /* id validating */
    for (;;) {
        emp.employeeID = getInt("Enter employee ID (positive whole number): ");

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

    /* make sure names cant be empty or contain numbers */
    do {
        printf("Enter employee full name (letters only, no numbers): ");
        readLine(emp.name, NAME_LEN);

        if (isStringEmpty(emp.name)) {
            printf("Name cannot be empty. Please enter a valid name.\n");
        } else if (nameHasDigit(emp.name)) {
            printf("Name cannot contain numbers. Please enter letters only (e.g. 'Liam Keats').\n");
        }
    } while (isStringEmpty(emp.name) || nameHasDigit(emp.name));

    /* making sure the position is not empty or negative */
    do {
        printf("Enter position (e.g. 'Manager', 'Technician 2'): ");
        readLine(emp.position, POSITION_LEN);

        if (isStringEmpty(emp.position)) {
            printf("Position cannot be empty. Please enter a valid position.\n");
        }
    } while (isStringEmpty(emp.position));

    /* salary cannot be less than 0 thats illegal */
    do {
        emp.salary = getFloat("Enter monthly salary(positive integers or floats only):");

        if (emp.salary < 0.0f) {
            printf("Salary cannot be negative. Please enter a value >= 0.\n");
        }
    } while (emp.salary < 0.0f);

    /* loading the emps */
    count = loadAllEmployees(employees, MAX_EMPLOYEES);

    if (count >= MAX_EMPLOYEES) {
        printf("Cannot add more employees: maximum capacity reached.\n");
        return;
    }

    /* using insertion sort function */
    insertEmployeeSorted(employees, &count, &emp);

    /* save and overwrite */
    if (!saveAllEmployees(employees, count)) {
        printf("Failed to save employees to data file.\n");
        return;
    }

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

    for (;;) {
        FILE *fp;
        Employee emp;
        int found = 0;

        clearScreen();
        printf("========== Search Employee by ID ==========\n\n");
        printf("Note: Employee IDs are positive whole numbers (e.g. 101).\n");
        printf("Enter -1 to return to the main menu.\n\n");

        targetID = getInt("Enter employee ID to search for: ");

        if (targetID == -1) {
            printf("\nReturning to the main menu.\n");
            break;
        }

        fp = fopen(DATA_FILE, "rb");
        if (fp == NULL) {
            printf("\nNo data file found. Cannot search employees.\n");
        } else {
            while (fread(&emp, sizeof(Employee), 1, fp) == 1) {
                if (emp.employeeID == targetID) {
                    found = 1;
                    break;
                }
            }

            fclose(fp);

            if (found) {
                printf("\nEmployee found:\n");
                printEmployee(&emp);
            } else {
                printf("\nEmployee with ID %d not found.\n", targetID);
            }
        }
        pauseForEnter();
    }
}


static void importFromFile(void)
{
    char filename[100];
    FILE *fp;
    char line[256];
    int lineNumber = 0;
    int imported = 0;
    int skipped = 0;

    /* loading employees for mass merging */
    Employee employees[MAX_EMPLOYEES];
    int count = loadAllEmployees(employees, MAX_EMPLOYEES);

    clearScreen();
    printf("======= Import Employees from File =======\n\n");
    printf("Expected format per line:\n");
    printf("employeeID,name,position,salary\n");
    printf("Example: 101,Liam Keats,Manager,5000.00\n\n");
    printf("Notes: employeeID must be a positive whole number; names should not contain numbers.\n\n");

    printf("Enter import filename: ");
    readLine(filename, sizeof filename);

    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening import file");
        return;
    }

    while (fgets(line, (int)sizeof line, fp) != NULL) {
        Employee emp;
        int scanned;
        int i;
        int duplicate = 0;

        lineNumber++;

        /* remove the newline so no errors */
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        /* parse the information from the line */
        scanned = sscanf(line, "%d,%49[^,],%49[^,],%f",
                         &emp.employeeID,
                         emp.name,
                         emp.position,
                         &emp.salary);

        if (scanned != 4) {
            printf("Line %d: invalid format, skipping.\n", lineNumber);
            skipped++;
            continue;
        }

        /* validating the id */
        if (emp.employeeID <= 0) {
            printf("Line %d: invalid employee ID (%d), skipping.\n",
                   lineNumber, emp.employeeID);
            skipped++;
            continue;
        }

        if (isStringEmpty(emp.name)) {
            printf("Line %d: empty name, skipping.\n", lineNumber);
            skipped++;
            continue;
        }

        if (nameHasDigit(emp.name)) {
            printf("Line %d: name '%s' contains digits, skipping.\n",
                lineNumber, emp.name);
            skipped++;
            continue;
        }

        if (isStringEmpty(emp.position)) {
            printf("Line %d: empty position, skipping.\n", lineNumber);
            skipped++;
            continue;
        }

        if (emp.salary < 0.0f) {
            printf("Line %d: negative salary %.2f, skipping.\n",
                   lineNumber, emp.salary);
            skipped++;
            continue;
        }

        /* checkign for duplicate IDS */
        for (i = 0; i < count; i++) {
            if (employees[i].employeeID == emp.employeeID) {
                duplicate = 1;
                break;
            }
        }

        if (duplicate) {
            printf("Line %d: employee ID %d already exists, skipping.\n",
                   lineNumber, emp.employeeID);
            skipped++;
            continue;
        }

        if (count >= MAX_EMPLOYEES) {
            printf("Maximum employee capacity reached. Remaining lines will be skipped.\n");
            skipped++;
            break;
        }

        /* insertion */
        insertEmployeeSorted(employees, &count, &emp);
        imported++;
    }

    fclose(fp);

    /* save the data  */
    if (!saveAllEmployees(employees, count)) {
        printf("\nError saving imported employees to data file.\n");
        return;
    }

    printf("\nImport complete.\n");
    printf("Lines processed: %d\n", lineNumber);
    printf("Employees imported: %d\n", imported);
    printf("Lines skipped: %d\n", skipped);
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
            addEmployee();      /* draw add screen */
            break;
        case 2:
            listEmployees();    /* draw list screen */
            break;
        case 3:
            searchEmployeeByID();  /* draw the search screen */
            break;
        case 4:
            printf("Exiting the program.\n");
            break;
        case 5:
            importFromFile();  /* this handles importing employees from a file */
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
