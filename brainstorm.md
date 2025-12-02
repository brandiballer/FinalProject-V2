# Employee Mangement System - Brainstoming and Ntoes

## i created a todo.md file where you can add things in a todo list
- to use add something with double brackets [ ]
- if the task is completed put an x inside the brackets to check it off
[x] our first task is complete
- we can keep work organized this way

## Project goals

- building a **simple but real** employee management system in c
- use:
    -`struct` for the records
    - file handling `fopen`, `fwrite`, `fread`, `fclose`
    - pointers
- keeping it clean
    - clear functions
    - good naming and comments
    - compile with strict flags for no variance when compiling
    - flags will be -Wall -Wextra -Wpedantic -std=c11

## Project planning
- set up project
- folder with employee_management.c
- in employee_management.c add header comments and add include and macros
- define struct Employee
- declare functions we will use and helpers
- write the main menu loop
- implement the helper functions before the main
    - examples:
    - print menu
    - clear input
    - read line
    - get int
    - get float
- implement add employee func which writes employees.dat
- implement list employees to read all employees
- implement search by ID func using the get int func
- cleaning and style check and extra ideas for fun
- create README.md so the basic mom could run the program with ease.
    - how to compile, what the program does, how to run, and explanation of each menu option. 
