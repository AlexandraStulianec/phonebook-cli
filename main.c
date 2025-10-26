#include<stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct
{
    char firstname[100];
    char lastname[100];
    char address[100];
    char email[100];
    char gender[8];
    long int phoneNumber;
} Contact;

void got(char *name)
{
    int i = 0, j;
    char c, ch;
    int prev_space = 0;

    do
    {
        c = getch();

        if (c != 8 && c != 13)
        {
            *(name + i) = c;
            putch(c);
            i++;
            prev_space = (c == ' ');
        }

        if (c == 8)
        {
            if (i > 0)
            {
                i--;
                prev_space = (*(name + i) == ' ');
            }
            system("cls");
            for (j = 0; j < i; j++)
            {
                ch = *(name + j);
                putch(ch);
                prev_space = (ch == ' ');
            }
        }

        /// Allow spaces only if previous character is not a space
        if (c == ' ' && !prev_space && i > 0)
        {
            *(name + i) = c;
            putch(c);
            i++;
        }
    }
    while (c != 13);

    *(name + i) = '\0';
}

void addcontact()
{
    FILE *fp;
    Contact newContact;

    /// Open the phone book file for appending
    fp = fopen("phonebook.txt", "ab+");
    printf("\n");
    if (fp == NULL)
    {
        printf("Cannot create phonebook.txt. Please check permissions.");
        fclose(fp); /// Closing the file
    }
    else
    {
        /// Get the information for the new contact
        printf("Enter firstname: ");
        got(newContact.firstname);
        printf("\n");

        printf("Enter lastname: ");
        got(newContact.lastname);
        printf("\n");

        printf("Enter address: ");
        got(newContact.address);
        printf("\n");

        printf("Enter email: ");
        got(newContact.email);
        printf("\n");

        printf("Enter gender: ");
        scanf("%s",&newContact.gender);
        printf("\n");

        printf("Enter phone number: ");
        scanf("%ld",&newContact.phoneNumber);

        /// Write the new contact to the phone book file
        fprintf(fp, "%s,%s,%s,%s,%s,0%ld\n", newContact.firstname,newContact.lastname,newContact.address, newContact.email, newContact.gender, newContact.phoneNumber);
    }
    /// Close the file
    fclose(fp);

    printf("\nContact added successfully.\n");
}

void updatecontact()
{
    FILE *f,*ft;
    Contact p;
    int flag=0,option,again;
    char lastname[100],firstname[100];
    char gender[100],address[100],email[100];
    long int phone;
    f=fopen("phonebook.txt","r");
    if(f==NULL)
    {

        printf("Contact's data not added yet.");

    }
    else
    {
        ft=fopen("temp.txt","w+");
        if(ft==NULL)

            printf("File Opening Error");
        else

        {
            printf("\nEnter contact's lastname: ");
            got(lastname);

            printf("\nEnter contact's firstname: ");
            got(firstname);
            printf("\n");

            while (fscanf(f, "%[^,],%[^,],%[^,],%[^,],%[^,],0%ld\n", p.firstname, p.lastname, p.address, p.email, p.gender, &p.phoneNumber) != EOF)
            {
                if (strcmp(p.lastname, lastname) == 0 && strcmp(p.firstname, firstname) == 0)
                {
                    do {
                        printf("\nSelect the field you want to update:\n");
                        printf("1. Firstname\n");
                        printf("2. Lastname\n");
                        printf("3. Address\n");
                        printf("4. Email\n");
                        printf("5. Gender\n");
                        printf("6. Phone number\n");
                        printf("Enter your choice: ");
                        scanf("%d", &option);

                        switch (option)
                        {
                            case 1:
                                printf("Enter new firstname: ");
                                got(p.firstname);
                                break;
                            case 2:
                                printf("Enter new lastname: ");
                                got(p.lastname);
                                break;
                            case 3:
                                printf("Enter new address: ");
                                got(p.address);
                                break;
                            case 4:
                                printf("Enter new email: ");
                                scanf("%s", p.email);
                                break;
                            case 5:
                                printf("Enter new gender: ");
                                scanf("%s", p.gender);
                                break;
                            case 6:
                                printf("Enter new phone number: ");
                                scanf("%ld", &p.phoneNumber);
                                break;
                            default:
                                printf("\nInvalid choice.\n");
                                break;
                        }
                        printf("\nDo you want to change anything else(0 or 1):");
                        scanf("%d",&again);
                    } while (again == 1);
                    fprintf(ft, "%s,%s,%s,%s,%s,0%ld\n", p.firstname, p.lastname, p.address, p.email, p.gender, p.phoneNumber);
                    flag = 1;
                }
                else {
                    fprintf(ft, "%s,%s,%s,%s,%s,0%ld\n", p.firstname, p.lastname, p.address, p.email, p.gender, p.phoneNumber);
                }
            }
            fclose(f);
            fclose(ft);
            if(flag!=1)
            {
                printf("\nNO CONACT'S RECORD TO UPDATE.");
                remove("temp.txt");
            }
            else
            {
                remove("phonebook.txt");
                rename("temp.txt","phonebook.txt");
                printf("\nRECORD UPDATED SUCCESSFULLY.");

            }
        }
    }
}
void deletecontact()
{
    FILE *f,*ft;
    Contact p;
    int flag;
    char lastname[100],firstname[100];
    f=fopen("phonebook.txt","r");
    if(f==NULL)
    {

        printf("\nContact's data not added yet.");

    }
    else
    {
        ft=fopen("temp.txt","w+");
        if(ft==NULL)

            printf("File Opening Error");
        else

        {
            printf("\nEnter contact's lastname: ");
            got(lastname);

            printf("\nEnter contact's firstname: ");
            got(firstname);

            while(fscanf(f, "%[^,],%[^,],%[^,],%[^,],%[^,],0%ld\n", p.firstname, p.lastname, p.address, p.email, p.gender, &p.phoneNumber) != EOF)
            {

                if(strcmp(p.lastname,lastname)==0)
                {
                    if(strcmp(p.firstname,firstname)==0)
                        flag=1;
                }

                else
                    ///fprintf function to write formatted data to a file
                    fprintf(ft, "%s,%s,%s,%s,%s,0%ld\n", p.firstname, p.lastname, p.address, p.email, p.gender, p.phoneNumber);
            }
            fclose(f);
            fclose(ft);
            if(flag!=1)
            {
                printf("\nNO CONACT'S RECORD TO DELETE.");
                remove("temp.txt");
            }
            else
            {
                remove("phonebook.txt");
                rename("temp.txt","phonebook.txt");
                printf("\nRECORD DELETED SUCCESSFULLY.");

            }
        }
    }
}

void viewcontact()
{
    FILE *fptr; /// Creating file pointer
    Contact p;
    fptr = fopen("phonebook.txt", "r"); /// Opening in read mode
    printf("\n");
    while (fscanf(fptr, "%[^,],%[^,],%[^,],%[^,],%[^,],0%ld\n", p.firstname, p.lastname, p.address, p.email, p.gender, &p.phoneNumber) != EOF)
    {
        printf("Firstname: %s\n", p.firstname);
        printf("Lastname: %s\n", p.lastname);
        printf("Address: %s\n", p.address);
        printf("Email: %s\n", p.email);
        printf("Gender: %s\n", p.gender);
        printf("Phone number: 0%ld\n", p.phoneNumber);
        printf("\n");
    }
}

void searchcontact()
{
    FILE *fptr; /// Creating file pointer
    int found = 0, result;
    char searchName[100],firstname[100];
    Contact p;

    printf("\nEnter contact's lastname you want to search: ");
    got(searchName);

    printf("\nEnter contact's firstname: ");
    got(firstname);

    fptr = fopen("phonebook.txt", "r"); /// Opening in read mode

    while (fscanf(fptr, "%[^,],%[^,],%[^,],%[^,],%[^,],0%ld\n", p.firstname, p.lastname, p.address, p.email, p.gender, &p.phoneNumber) != EOF)
    {
        /// Comparing strings, if 0 means equal
        if (strcmp(p.lastname, searchName) == 0)
        {
            if(strcmp(p.firstname,firstname)==0)
            {
                found = 1;
                printf("Firstame: %s\n", p.firstname);
                printf("Lastname: %s\n", p.lastname);
                printf("Address: %s\n", p.address);
                printf("Email: %s\n", p.email);
                printf("Gender: %s\n", p.gender);
                printf("Phone number: 0%ld\n", p.phoneNumber);
                printf("\n");
            }
        }
    }
    if (found == 0)
    {
        printf("Person does not exist.\n");
    }
}
void menu()
{
    int choice;
    do
    {
        printf("\n\t\t\t  MENU\t\t\n\n");
        printf("\t1.Add New   \t2.Update   \t3.Delete  \n\t4.View   \t5.Search\t6.Exit\n\n");
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);

        switch(choice)
        {

        case 1:
            printf("\nEnter 0 to exit, 1 to go back to the main menu and 2 to stay: ");
            scanf("%d", &choice);
            if (choice == 0)
            {
                printf("Exiting program.\n");
                exit(0);
            }
            else if(choice==2)
            {
                addcontact();

            }
            break;
        case 2:
            printf("\nEnter 0 to exit, 1 to go back to the main menu and 2 to stay: ");
            scanf("%d", &choice);
            if (choice == 0)
            {
                printf("Exiting program.\n");
                exit(0);
            }
            else if(choice==2)
            {

                updatecontact();
            }
            break;
        case 3:
            printf("\nEnter 0 to exit, 1 to go back to the main menu and 2 to stay: ");
            scanf("%d", &choice);
            if (choice == 0)
            {
                printf("Exiting program.\n");
                exit(0);
            }
            else if(choice==2)
            {

                deletecontact();

            }
            break;
        case 4:
            printf("\nEnter 0 to exit, 1 to go back to the main menu and 2 to stay: ");
            scanf("%d", &choice);
            if (choice == 0)
            {
                printf("Exiting program.\n");
                exit(0);
            }
            else if(choice==2)
            {

                viewcontact();
            }
            break;
        case 5:
            printf("\nEnter 0 to exit, 1 to go back to the main menu and 2 to stay: ");
            scanf("%d", &choice);
            if (choice == 0)
            {
                printf("Exiting program.\n");
                exit(0);
            }
            else if(choice==2)
            {

                searchcontact();
            }
            break;
        case 6:
            exit(0);
        default:
            printf("\nInvalid choice.Please try again.\n");
            break;

        }

        printf("\n\n");

    }
    while(choice!=6);

}
int main()
{
    menu();
    return 0;
}


