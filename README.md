# Employee Management System

This project is a simple **Employee Management System** written in C for COMP 2103.

It allows you to:

- Add new employees
- List all employees
- Search for an employee by ID
- (Optional) View basic statistics about employees (if you’ve enabled that menu option)
- Exit cleanly

Employee data is stored in a binary file (`employees.dat`) so it persists between runs.

Along the way, the program also enforces some realistic rules:

- Employee ID must be a **positive integer**
- Employee ID must be **unique** (no duplicate IDs allowed)
- Salary must be **non-negative** (≥ 0)
- Name and position **cannot be empty**

---

## 1. Open your project folder

First open your terminal and move into the project folder

```bash
cd /path/to/your/project
```

## 2. Make the file
Since I created a makefile to compile just do

```bash
make
```
## 3. Run the file
This compiles employee_management.c and creates employee_management. Then run

```bash
./employee_management
```
## 4. Using the executable
You will see a menu popup.

```text
==============================
Employee Management System
==============================
1. Add Employee
2. List Employees
3. Search Employee by ID
4. Exit
==============================
Enter your choice:
```

To use it
- Type a number (1-4) and press **Enter**
- The program will do that action
- After each action you will see

```bash
Press enter to continue...
```
Then you can press enter to go back to the main menu


## 5. Cleaning up

If you want to delete the compiled program and start fresh run

```bash
make clean
```

This will remove the employee_management executable but not delete any data files created. 

If you want to completely reset the project

```bash
make superclean
```

This will run `make clean` and will also delete `employees.dat`

