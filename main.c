/* Name         : Naura Yasmeen 
   Start Date   : 15/10/2025
   End Date     : 20/10/2025
   Project Name : Address Book
   Description  : This project is a simple address book management system where 
                  the user can create, search, edit or delete contact details such as 
                  name, phone number and Email Id. The contacts are stored in a csv file
                  so that the data remains available even after terminating the program.
*/


#include <stdio.h>
#include "contact.h"
#include "validations.h"

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:          
                listContacts(&addressBook);
                break;
            case 6:
                printf(" Exiting...\n");
                saveAndExit(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    
       return 0;
}
