#include <stdio.h>

#include "lms.h"

void bookMenu(void) {
    int choice;

    do {
        printf("\n+----------------------------------------+\n");
        printf("|         Book Management Menu           |\n");
        printf("|----------------------------------------|\n");
        printf("| 1. Add New Book                        |\n");
        printf("| 2. Update Book Details                 |\n");
        printf("| 3. Remove Book                         |\n");
        printf("| 4. Search Book                         |\n");
        printf("| 5. View All Books                      |\n");
        printf("| 6. Issue Book                          |\n");
        printf("| 7. Return Book                         |\n");
        printf("| 8. List Issued Books                   |\n");
        printf("| 9. Save                                |\n");
        printf("| 10. Exit                               |\n");
        printf("+----------------------------------------+\n");

        choice = readInt("Enter your choice: ", 1);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                updateBookMenu();
                break;
            case 3:
                removeBookMenu();
                break;
            case 4:
                searchBookMenu();
                break;
            case 5:
                viewAllBooks();
                break;
            case 6:
                issueBook();
                break;
            case 7:
                returnBook();
                break;
            case 8:
                listIssuedBooks();
                break;
            case 9:
                saveData();
                printf("Data saved successfully.\n");
                break;
            case 10:
                saveData();
                printf("Data saved. Exiting Library Management System.\n");
                break;
            default:
                printf("Invalid choice. Please select 1 to 10.\n");
        }
    } while (choice != 10);
}
