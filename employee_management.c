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
static void addEmployee(void){
    printf("TODO: addEmployee() not implemented yet.\n");
}
static void listEmployees(void){
    printf("TODO: listEmployees() not implemented yet.\n");
}
static void searchEmployeeByID(void){
    printf("TODO: searchEmployeeByID() not implemented yet.\n");
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

static void clearScreen(void){
#ifdef _WIN32
    system("cls");
#else
    /*escape codes*/
    printf("\033[2J\033[H");
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


/*========================*/
/*main*/
/*===============*/
int main(void)
{
    int choice;
    do {
        clearScreen();          /* wipe the old stuff */
        printMenu();            /* draw the main menu */

        choice = getInt("Enter your choice: ");

        switch (choice) {
        case 1:
            addEmployee();
            break;
        case 2:
            listEmployees();
            break;
        case 3:
            searchEmployeeByID();
            break;
        case 4:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
        if (choice != 4) {
            pauseForEnter();    /* “Press Enter to go back to menu” */
        }
    } while (choice != 4);

    return 0;
}
