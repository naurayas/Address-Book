# Address-Book in C

This project is a command-line based Address Book application written in C.
It allows users to manage contacts with features like create, search, edit, delete, and persistent storage.

# Features
* Add new contacts with validation
* Search contacts by name or phone number
* Edit existing contact details
* Delete contacts with confirmation
* List all saved contacts
* Persistent storage using CSV file

# Technologies Used
* C Programming
* File Handling (CSV)
* Modular Programming
* String Manipulation

# Project Structure
- main.c
- contact.c / contact.h
- validations.c / validations.h
- populate.c / populate.h
- contacts.csv

# Manual Compilation
gcc main.c contact.c validations.c populate.c -o addressbook
./addressbook

## Build Instructions
### Using makefile
```bash
make
./addressbook

* Clean build files
make clean

