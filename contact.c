#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "populate.h"
#include "validations.h"



void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);

    if (addressBook->contactCount == 0) {
        populateAddressBook(addressBook);
    }
}


// function to list the contacts
void listContacts(AddressBook *addressBook)
{
	//list all the contacts..
    printf("------------------------------------------------------------------\n");
    printf("Name\t\t\tPhone No.\t\tEmail\n");
    printf("------------------------------------------------------------------\n");
    for (int i = 0; i < addressBook -> contactCount; i++)
    {
        // list the contacts from addressBook
        printf("%s\t\t%s\t\t%s\n", addressBook -> contacts[i].name, addressBook -> contacts[i].phone, addressBook -> contacts[i].email);
    }
}


// function to create a contact
void createContact(AddressBook *addressBook)
{
    // create name and validate
    char str_name[50]; 
    while(1)
    {
        printf("\nEnter the name : ");
        fgets(str_name, 50, stdin); // read a name string
        if (strchr(str_name, '\n') == NULL)     // if user enter >50 char
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);  // flush leftover input/clear buffer
        }

        str_name[strcspn(str_name, "\n")] = '\0'; // removes new line

        if (validate_name(str_name)) // if valid name is entered, store it to the array of structure
        {
            strcpy(addressBook -> contacts[addressBook -> contactCount].name, str_name);
            break;
        }
        else
        {
            printf("Error: Enter a valid name\n");
        }
    }

    // create phone number and validate
    char str_phone[11];
    while(1)
    {
        printf("\nEnter phone number : ");
        fgets(str_phone, 11, stdin); // read a phone number
        if (strchr(str_phone, '\n') == NULL)
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);  // flush leftover input/clear buffer
        }

        str_phone[strcspn(str_phone, "\n")] = '\0'; // removes new line

        if (validate_phone(str_phone, addressBook)) // if valid,, store phone number to the array of structure
        {
            strcpy(addressBook -> contacts[addressBook -> contactCount].phone, str_phone);
            break;
        }
        else
        {
            printf("Error: Enter a valid phone number\n");
        }
    }

    // create email and validate
    while(1)
    {
        char str_email[50];
        printf("\nEnter email : ");
        fgets(str_email, 50, stdin); // read email
        if (strchr(str_email, '\n') == NULL)
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);  // flush leftover input/clear buffer
        }

        str_email[strcspn(str_email, "\n")] = '\0'; // removes new line

        if (validate_email(str_email, addressBook)) // if it is valid, store to the array of structure
        {
            lowercase(str_email);
            strcpy(addressBook -> contacts[addressBook -> contactCount].email, str_email);
            break;
        }
        else
        {
            printf("Error: Enter a valid email id\n");
        }
    }
    addressBook -> contactCount++; // increment the count
    saveContactsToFile(addressBook); // Save contacts to file
}


// funstion to search contacts
void searchContact(AddressBook *addressBook)
{
    char query[50]; // declare a string to store the search item
    printf("\nEnter Name or Phone number to search: ");
    fgets(query, 50, stdin); // read string to search
    if (strchr(query, '\n') == NULL)
    {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);  // flush leftover input/clear buffer
    }

    query[strcspn(query, "\n")] = '\0'; // removes new line

    int indices[MAX_CONTACTS];
    int found = searchstruct(addressBook, query, indices); // function call to search through the structure

    if (found == 0) 
    {
        printf("Contact not found!\n");
        return;
    }
    else
    {
        printf("\n------------------------------------------------------------------\n");
        printf("Sl No.\tName\t\t\tPhone No.\t\tEmail\n");
        printf("------------------------------------------------------------------\n");
        for (int i = 0; i < found; i++)
        {
            printf("%d\t%s\t\t%s\t\t%s\n", i + 1, addressBook -> contacts[indices[i]].name, addressBook -> contacts[indices[i]].phone, addressBook -> contacts[indices[i]].email);
        }
    }
}


// function to edit a contact
void editContact(AddressBook *addressBook)
{
    char query[50]; // declare a string to store the contact to edit
    int choice;
    int indices[MAX_CONTACTS];

    printf("\nEnter the name or phone number to edit :");
    fgets(query, 50, stdin); // read string to edit
    if (strchr(query, '\n') == NULL)
    {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);  // flush leftover input/clear buffer
    }
    query[strcspn(query, "\n")] = '\0'; // removes new line
    
    int found = searchstruct(addressBook, query, indices); // check if string exists
    
    if (found == 0)
    {
        printf("\nNo matches found!\n");
        return;
    }
    else if (found > 0)
    {
        printf("\n------------------------------------------------------------------\n");
        printf("Sl No.\tName\t\t\tPhone No.\t\tEmail\n");
        printf("------------------------------------------------------------------\n");
        for (int i = 0; i < found; i++) // print the contacts found
        {
            printf("%d\t%s\t\t%s\t\t%s\n", i + 1, addressBook -> contacts[indices[i]].name, addressBook -> contacts[indices[i]].phone, addressBook -> contacts[indices[i]].email);
        }

        if (found > 1)
        {
            printf("\nMultiple matches found!\n");
            printf("Select one contact: ");
            
            while(1) // loop till correct choice is entered
            {
                scanf("%d", &choice); // read the choice of contact to edit
                if(choice < 1 || choice > found) // check if the choice exists
                {
                    printf("\nInvalid choice!\nEnter again: ");
                }
                else
                {
                    break;
                }
            }
        }
        else 
        {
            choice = 1;
        }
    }

    int ind = indices[choice - 1]; // find the index of the contact to be editted in the array of structure
    
    printf("\nSelect the item you want to edit:\n");
    printf("1. Name\n2. Phone number\n3. Email\n");

    while (1)
    {
        printf("\nEnter an option : ");
        int opt;
        scanf("%d", &opt); // read the option 
        getchar();  // clear the buffer containing new line

        int flag = 0;
        switch (opt)
        {
            case 1:
                {

                    char new_name[50];
                    printf("\nEnter new name: ");
                    fgets(new_name, 50, stdin); // read new name
                    if (strchr(new_name, '\n') == NULL)
                    {
                        int ch;
                        while ((ch = getchar()) != '\n' && ch != EOF);  // flush leftover input/clear buffer
                    }
                    new_name[strcspn(new_name, "\n")] = '\0'; // removes new line

                    if (validate_name(new_name)) // validate new name
                    {
                        strcpy(addressBook -> contacts[ind].name, new_name); // update the new name
                        printf("\nName successfully updated!\n");
                    }
                    else
                    {
                        printf("\nEnter a valid name\n");
                    }
                    flag = 1;
                    break;
                }
            case 2:
                {
                    char new_phone[11];
                    printf("\nEnter new phone number: ");
                    fgets(new_phone, 11, stdin); // read new phone number
                    if (strchr(new_phone, '\n') == NULL)
                    {
                        int ch;
                        while ((ch = getchar()) != '\n' && ch != EOF);  // flush leftover input/clear buffer
                    }
                    new_phone[strcspn(new_phone, "\n")] = '\0'; // removes new line

                    if (validate_phone(new_phone, addressBook)) // validate new phone number
                    {
                        strcpy(addressBook -> contacts[ind].phone, new_phone); // update the new phone number
                        printf("\nPhone number successfully updated!\n");
                    }
                    else
                    {
                        printf("\nEnter a valid Phone number\n");
                    }
                    flag = 1;
                    break;
                }
            case 3:
                {
                    char new_email[50];
                    printf("\nEnter new email id: ");
                    fgets(new_email, 50, stdin); // read new email
                    if (strchr(new_email, '\n') == NULL)
                    {
                        int ch;
                        while ((ch = getchar()) != '\n' && ch != EOF);  // flush leftover input/clear buffer
                    }
                    new_email[strcspn(new_email, "\n")] = '\0'; // removes new line

                    if (validate_email(new_email, addressBook)) // validate new email
                    {
                        strcpy(addressBook -> contacts[ind].email, new_email); // update new email
                        printf("\nEmail id successfully updated!\n");
                    }
                    flag = 1;
                    break;

                }
        }
        if (flag == 1) // check if valid option is entered
        {
            break;
        }
        else
        {
            printf("\nInvalid item entered!\nEnter again: \n");
        }
    }
    saveContactsToFile(addressBook); // Save contacts to file
}

// function to delete contact
void deleteContact(AddressBook *addressBook)
{
    char query[50];
    int indices[50];

    printf("\nEnter contact name of number to delete: ");
    fgets(query, 50, stdin); 
    if (strchr(query, '\n') == NULL)
    {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);  // flush leftover input/clear buffer
    }
    query[strcspn(query, "\n")] = '\0'; 

    int found = searchstruct(addressBook, query, indices);
    if (found == 0)
    {
        printf("No matches found!\n");
        return;
    }

    int choice;
    if (found > 0)
    {
        printf("\n----------------------------------------------------------------------------\n");
        printf("Sl No.\tName\t\t\tPhone No.\t\tEmail\n");
        printf("----------------------------------------------------------------------------\n");

        for (int i = 0; i < found; i++) // print the contacts found
        {
            printf("%d\t%s\t\t%s\t\t%s\n", i + 1, addressBook -> contacts[indices[i]].name, addressBook -> contacts[indices[i]].phone, addressBook -> contacts[indices[i]].email);
        }

        if (found > 1)
        {
            printf("\nMulitple matches found!\n");
            printf("Select one contact: ");
            while (1)
            {
                scanf("%d", &choice);
                if (choice < 1 || choice > found)
                {
                    printf("\nInvalid choice\nEnter again: ");
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            choice = 1;
        }
    }

    int ind = indices[choice - 1];
    char confirm;
    printf("\nAre you sure you want to delete? (y/n): ");
    scanf(" %c", &confirm);
    
    if (confirm == 'y' || confirm == 'Y')
    {
        for (int i = ind; i < addressBook -> contactCount - 1; i++)
        {
            addressBook -> contacts[i] = addressBook -> contacts[i + 1];
        }
        addressBook -> contactCount--;
        printf("\nDeleted contact successfully!\n");
    }
    else
    {
        printf("\nDelete action terminated!\n");
    }
    saveContactsToFile(addressBook); // Save contacts to file
}


void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(0);              // Exit the program
} 




