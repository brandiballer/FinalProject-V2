# TO DO LIST

## Core setup

- [x] project setup
- [x] creating struct `Employee`
- [x] define header and macros
- [x] declare functions
- [x] renamed main.c to employee_management.c
- [x] removed test.c
- [x] write the main menu loop
- [x] implement helper functions (`printMenu`, `clearInputBuffer`, `readLine`, `getInt`, `getFloat`)

## Core features (file I/O)

- [x] create `addEmployee` using `readLine`, salary, etc.
- [x] implement file I/O in `addEmployee` (append to `employees.dat` with `fopen` / `fwrite`)
- [x] create `listEmployees`
- [x] implement file I/O in `listEmployees` (read all employees with `fopen` / `fread`)
- [x] create `searchEmployeeByID`
- [x] implement file I/O in `searchEmployeeByID` (scan file for matching ID)

## UI / UX polish

- [x] add `clearScreen` function for “one screen at a time” game-style UI
- [x] add `pauseForEnter` to pause after each action
- [x] ensure main menu redraws cleanly after each operation

## Validation & realism

- [x] add `employeeExists(int employeeID)` to prevent duplicate IDs
- [x] require employee ID to be a **positive** integer
- [x] disallow negative salaries (salary must be ≥ 0)
- [x] add `isStringEmpty` helper
- [x] enforce non-empty `name` and `position` fields
- [x] add `printEmployee(const Employee *emp)` helper and use it in list/search

## Extra features

- [x] add statistics screen (`showStatistics`): total employees, average salary, highest salary
- [x] integrate statistics option into main menu (if enabled)

## Build & tooling

- [x] create `Makefile` with build + `clean` target
- [x] add `superclean` target to also remove `employees.dat`
- [x] verify clean build with `-Wall -Wextra -Wpedantic -std=c11`

## Documentation & collaboration

- [x] write `README.md` with:
  - how to build (`make`)
  - how to run (`./employee_management`)
  - explanation of menu options
  - notes about validations (ID, salary, name/position)
- [x] add Git usage instructions section for Brandi (pull → add → commit → push)

## Final tasks

- [x] do a final testing pass:
  - start with no `employees.dat`
  - add multiple employees
  - list employees
  - search existing and non-existing IDs
  - test invalid inputs (negative salary, duplicate ID, empty name/position)
- [ ] create `EmployeeManagementSystem_Project.zip` with:
  - `employee_management.c`
  - `README.md`
  - `employees.dat` (if including sample data)
- [ ] write/update COMP 2103 diary / notes (if required by assignment)
