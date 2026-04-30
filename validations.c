#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"

// function to search contact through the array of structure
int searchstruct(AddressBook* addressBook, char* query, int* indices)
{
    int found = 0;
    for (int i = 0; i < addressBook -> contactCount; i++) // search the query in the array of structure
    {
        if (strstr(addressBook -> contacts[i].name, query) != NULL || strcmp(addressBook -> contacts[i].phone, query) == 0)
        {
            indices[found] = i; // store the index of contact found into the array
            found++; // count the number of contacts found
        }
    }
    return found;
}

// function definition to validate the name
int validate_name(char* str_name)
{
    if (strlen(str_name) == 0) // no name entered
    {
        return 0;
    }

    while (*str_name != '\0') // loop through the characters of string
    {
        if (*str_name == ' ') // increment the pointer if there is a space
        {
            str_name++;
        }
        if (!isalpha(*str_name)) // invalid if there is a digit
        {
            return 0;
        }
        str_name++;
    }
    return 1; // valid name
}


// function definition for phone number validation
int validate_phone(char* str_phone, AddressBook* addressBook)
{
    if (strlen(str_phone) != 10) // check if the length of phone is 10 digits
    {
        return 0;
    }

    char* ptr = str_phone;
    while (*ptr != '\0')
    {
        if (isalpha(*ptr)) // invalid if there is an alphabet
        {
            return 0;
        }
        ptr++;
    }

    for (int i = 0; i < addressBook -> contactCount; i++)
    {
        if (strcmp(str_phone, addressBook -> contacts[i].phone) == 0) // check if the number is unique
        {
            return 0;
        }
    }
    return 1; // valid phone number
}


// funciton definition for email validation
int validate_email(char* str_email, AddressBook* addressBook)
{
    if (strstr(str_email, ".com") == NULL || strchr(str_email, '@') == NULL) // check if @ and .com is present
    {
        return 0;
    }
    char* at = strchr(str_email, '@');
    char* dot = strchr(str_email, '.');

    if (at > dot) // check if @ comes after dot
    {
        return 0;
    }
    
    if (at == str_email) // check if email starts with atleast a character
    {
        return 0;
    }

    if (dot - at < 2) // check if atleast one character is in between @ and .
    {
        return 0;
    }

    for (int i = 0; str_email[i] != '\0'; i++)
    {
        if (str_email[i] == ' ') // check if there is a space
        {
            return 0;
        }
    }

    for (int i = 0; i < addressBook -> contactCount; i++)
    {
        if (strcmp(str_email, addressBook -> contacts[i].email) == 0) // check if the email is unique
        {
            return 0;
        }
    }
    return 1;
}


// save the contacts to file contacts.csv
void saveContactsToFile(AddressBook* addressBook)
{
    FILE* fp = fopen("contacts.csv", "w"); // open file in write mode
    if (fp == NULL) 
    {
        printf("\nError: Unable to open the file to write!\n");
        return;
    }

    fprintf(fp, "Name,Phone No.,Email\n");
    for (int i = 0; i < addressBook -> contactCount; i++) // save structure content to file contact.csv
    {
        fprintf(fp, "%s,%s,%s\n", addressBook -> contacts[i].name, addressBook -> contacts[i].phone, addressBook -> contacts[i].email);
    }
    fclose(fp); // close file
}

// load the contact details from the contact.csv file
void loadContactsFromFile(AddressBook* addressBook)
{
    FILE * fp = fopen("contacts.csv", "r");
    if (fp == NULL)
    {
        printf("\nError: Cannot find the file!\n");
        return;
    }

    char csv[100];
    addressBook -> contactCount = 0;
    fgets(csv, sizeof(csv), fp); // read the header line

    while (fgets(csv, sizeof(csv), fp) != NULL)
    {
        csv[strcspn(csv, "\n")] = '\0';
        if (addressBook -> contactCount >= MAX_CONTACTS)
        {
            printf("\nMaximum contact limit reached!\n");
            break;
        }

        char* token = strtok(csv, ",");
        if (token != NULL)
        {
            strcpy(addressBook -> contacts[addressBook -> contactCount].name, token);
        }

        token = strtok(NULL, ",");
        if (token != NULL)
        {
            strcpy(addressBook -> contacts[addressBook -> contactCount].phone, token);
        }

        token = strtok(NULL, ",");
        if (token != NULL)
        {
            strcpy(addressBook -> contacts[addressBook -> contactCount].email, token);
        }
        
        addressBook -> contactCount++;
    }
    fclose(fp);
} 

// convert uppercase characters in email to lowercase
void lowercase(char* str_email)
{
    for (int i = 0; str_email[i] != '\0'; i++)
    {
        str_email[i] = tolower(str_email[i]);
    }
}