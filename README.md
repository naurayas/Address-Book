# Address-Book in C

## Overview
This project is a command-line based Address Book application written in C.
It allows users to manage contacts with features like create, search, edit, delete, and persistent storage.

---

## Features
- Add new contacts with proper input validation
- Prevent duplicate phone numbers and email IDs
- Search contacts using partial name match or exact phone number
- Edit existing contact details
- Delete contacts with confirmation
- Display all stored contacts
- Persistent storage using `contacts.csv`

---

## Concepts Demonstrated
- Structures and arrays
- Modular programming in C
- File handling (CSV read/write)
- Input validation and error handling
- String manipulation

---

## Project Structure
```bash
- main.c
- contact.c / contact.h
- validations.c / validations.h
- populate.c / populate.h
- contacts.csv
```
---

## Build Instructions
### Using Makefile
```bash
make
./addressbook
```
### clean build files
```bash
make clean
```
### Manual Compilation
```bash
gcc main.c contact.c validations.c populate.c -o addressbook
./addressbook
```
