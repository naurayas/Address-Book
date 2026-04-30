int validate_name(char* str_name);
int validate_phone(char* str_phone, AddressBook* addressBook);
int validate_email(char* str_email, AddressBook* addressBook);
int searchstruct(AddressBook* addressBook, char* , int*);
void saveContactsToFile(AddressBook *AddressBook);
void loadContactsFromFile(AddressBook* addressBook);
void lowercase(char* str_email);