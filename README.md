Facebook Database Program
This repository contains a C-language program that functions as a simple Facebook database. It allows users to manage member information, including personal details and group affiliations, with data persistence through file handling.

Table of Contents
Features

How to Use

Developer Guide

Setup

File Structure

Features
The program offers the following functionalities:

Enter a new member: Add new user profiles to the database.

Search a member: Find members by family name or nickname.

Delete a member: Remove existing members from the database by their nickname.

Add a member to a group: Assign an existing member to a specified group.

Remove a group member: Delete a member from a particular group.

List all group members: Display all members belonging to a specific group.

List all members: Show details of all users currently in the database.

Exit the program: Save all current data to a file and terminate the application.

How to Use
Upon running the program, you will be presented with a menu of tasks:

    Application started succesfully
    Welcome to Facebook database

    please select the task:

    1. Enter a new member in the data.
    2. search a member in the data.
    3. delete a member in the data.
    4. add a member in a group
    5. remove a group member.
    6. list all group members.
    7. list all the members in the data.
    8. Exit the program
Entering a new member (Option 1):

You will be prompted to enter the member's nickname, family name, given name, and birthplace. Input validation ensures that names contain only letters and nicknames are unique.

Next, enter the date of birth (year, month, day). The program validates the date for correctness, including leap years.

You will then be asked if you want to add the member to any groups (Y/N). If 'Y', specify the number of groups and their names.

Searching a member (Option 2):

Choose to search by family name or nickname.

Enter the requested name, and the program will display details of matching members.

Deleting a member (Option 3):

Enter the nickname of the member you wish to delete. The program will remove the member and their associated data.

Adding/Removing Group Members (Options 4 & 5):

Specify the user's nickname and the group name to add or remove them from a group.

Listing Group Members (Option 6):

Enter a group name to see all members associated with that group.

Listing All Members (Option 7):

Displays a comprehensive list of all members, including their personal information and group affiliations.

Exit (Option 8):

The program will save all current data to Facebook.txt and then exit.

Developer Guide
The program is implemented in C and uses dynamic memory allocation for efficient data management.

Structures
date: Stores the year, month, and day for a member's date of birth.

member: Holds individual user data, including dynamically allocated strings for nick_name, family_name, given_name, place, and an array of dynamically allocated group names (group). Also includes group_total for the number of groups and birth (a date structure).

statistics: Manages the entire collection of users, containing total (the count of members) and users (a dynamically allocated array of member structures).

Key Functions
read_from_file(statistics * data): Loads member data from Facebook.txt into the statistics structure. It uses strtok for string tokenization and strdup for dynamic string allocation. Integer values are converted using strtol.

print_in_file(statistics *data): Saves the current statistics data back to Facebook.txt.

add_new(statistics * data): Handles user input to create a new member structure, including nickname uniqueness and name/date validation.

add_name(): Dynamically allocates memory for string inputs (e.g., names).

add_date(): Prompts for and validates date input.

invalid_date(date tmp): Checks the validity of a given date.

leap_year(int year): Determines if a year is a leap year.

improper_name(char * check): Validates if a string contains only alphabetic characters.

add_in_list(member * to_add, statistics old): Adds a new member to the statistics array, reallocating memory as needed.

delete_member(statistics data): Removes a member by nickname, freeing associated memory and reorganizing the users array.

search_member(statistics data): Implements search functionality by family name or nickname.

add_group(int *total, char*** group): Manages the dynamic allocation and input for groups when a new member is created.

adding_in_group(char * group_to_add, char*** group_array, int * total): Adds a new group name to a member's group array, handling reallocation.

add_member_in_group(statistics * data): Adds an existing member to a specific group.

delete_member_in_group(statistics * data): Removes a member from a specific group.

deleting_in_group(int index, char*** group_array, int * total): Removes a group name at a specified index from a member's group list.

print_single_user(member profile): Displays the details of a single member.

print_all_members(statistics data): Iterates through and prints details of all members.

main(): The entry point of the program, which initializes data, loads from file, presents the main menu, processes user choices, and manages memory deallocation upon exit.

Setup
To compile and run this program:

Save the source code: Save the provided C code as a .c file (e.g., facebook_db.c).

Compile: Use a C compiler (like GCC) to compile the source code.

Bash

gcc facebook_db.c -o facebook_db
Run: Execute the compiled program.

Bash

./facebook_db
The program will automatically create or load data from a file named Facebook.txt in the same directory.

File Structure
facebook_db.c: The main source code file for the Facebook Database Program.

Facebook.txt: A text file used for storing and retrieving member data. This file is created and managed by the program.
