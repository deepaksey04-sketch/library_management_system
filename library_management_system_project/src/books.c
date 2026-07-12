#include <ctype.h>
#include <stdio.h>

#include "lms.h"

void addBook(void) {
    Book book;

    if (bookCount >= MAX_BOOKS) {
        printf("Book storage is full.\n");
        return;
    }

    book.id = nextBookId++;
    readLine("Enter book title: ", book.title, sizeof(book.title));
    readLine("Enter author name: ", book.author, sizeof(book.author));
    book.quantity = readInt("Enter available quantity: ", 0);

    books[bookCount++] = book;
    printf("Book added successfully. Book ID: %d\n", book.id);
}

void updateBookMenu(void) {
    char choice[8];
    int index;

    do {
        index = -1;
        printf("\nUpdate Book Details\n");
        printf("A. By Book ID\n");
        printf("B. By Book Name\n");
        printf("C. Back to Main Menu\n");
        readLine("Enter your choice: ", choice, sizeof(choice));

        switch (toupper((unsigned char)choice[0])) {
            case 'A': {
                int id = readInt("Enter book ID: ", 1);
                index = findBookById(id);
                break;
            }
            case 'B': {
                char title[TITLE_LEN];
                readLine("Enter book name: ", title, sizeof(title));
                for (int i = 0; i < bookCount; i++) {
                    if (containsIgnoreCase(books[i].title, title)) {
                        index = i;
                        break;
                    }
                }
                break;
            }
            case 'C':
                return;
            default:
                printf("Invalid choice.\n");
                continue;
        }

        if (index == -1) {
            printf("Book not found.\n");
            continue;
        }

        printf("Current details:\n");
        printBookHeader();
        printBook(&books[index]);

        readLine("Enter new title: ", books[index].title, sizeof(books[index].title));
        readLine("Enter new author: ", books[index].author, sizeof(books[index].author));
        books[index].quantity = readInt("Enter new quantity: ", 0);
        printf("Book updated successfully.\n");
    } while (1);
}

void removeBookMenu(void) {
    char choice[8];
    int index;

    do {
        index = -1;
        printf("\nRemove Book\n");
        printf("A. By Book ID\n");
        printf("B. By Book Name\n");
        printf("C. Back to Main Menu\n");
        readLine("Enter your choice: ", choice, sizeof(choice));

        switch (toupper((unsigned char)choice[0])) {
            case 'A': {
                int id = readInt("Enter book ID: ", 1);
                index = findBookById(id);
                break;
            }
            case 'B': {
                char title[TITLE_LEN];
                readLine("Enter book name: ", title, sizeof(title));
                for (int i = 0; i < bookCount; i++) {
                    if (containsIgnoreCase(books[i].title, title)) {
                        index = i;
                        break;
                    }
                }
                break;
            }
            case 'C':
                return;
            default:
                printf("Invalid choice.\n");
                continue;
        }

        if (index == -1) {
            printf("Book not found.\n");
            continue;
        }

        for (int i = 0; i < issueCount; i++) {
            if (issues[i].bookId == books[index].id && !issues[i].returned) {
                printf("Cannot remove this book because it is currently issued.\n");
                return;
            }
        }

        for (int i = index; i < bookCount - 1; i++) {
            books[i] = books[i + 1];
        }
        bookCount--;
        printf("Book removed successfully.\n");
    } while (1);
}

void searchBookMenu(void) {
    char choice[8];
    char query[AUTHOR_LEN];
    int found;

    do {
        found = 0;
        printf("\nSearch Book\n");
        printf("A. By Book ID\n");
        printf("B. By Book Name\n");
        printf("C. By Author Name\n");
        printf("D. Back to Main Menu\n");
        readLine("Enter your choice: ", choice, sizeof(choice));

        switch (toupper((unsigned char)choice[0])) {
            case 'A': {
                int id = readInt("Enter book ID: ", 1);
                int index = findBookById(id);
                if (index != -1) {
                    printBookHeader();
                    printBook(&books[index]);
                    found = 1;
                }
                break;
            }
            case 'B':
                readLine("Enter book name or part of name: ", query, sizeof(query));
                printBookHeader();
                for (int i = 0; i < bookCount; i++) {
                    if (containsIgnoreCase(books[i].title, query)) {
                        printBook(&books[i]);
                        found = 1;
                    }
                }
                break;
            case 'C':
                readLine("Enter author name or part of name: ", query, sizeof(query));
                printBookHeader();
                for (int i = 0; i < bookCount; i++) {
                    if (containsIgnoreCase(books[i].author, query)) {
                        printBook(&books[i]);
                        found = 1;
                    }
                }
                break;
            case 'D':
                return;
            default:
                printf("Invalid choice.\n");
                continue;
        }

        if (!found) {
            printf("No matching book found.\n");
        }
    } while (1);
}

void viewAllBooks(void) {
    if (bookCount == 0) {
        printf("No books available.\n");
        return;
    }

    printBookHeader();
    for (int i = 0; i < bookCount; i++) {
        printBook(&books[i]);
    }
}

int findBookById(int id) {
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            return i;
        }
    }
    return -1;
}

void printBookHeader(void) {
    printf("\n%-8s %-30s %-25s %-8s\n", "Book ID", "Title", "Author", "Qty");
    printf("------------------------------------------------------------------------\n");
}

void printBook(const Book *book) {
    printf("%-8d %-30.30s %-25.25s %-8d\n",
           book->id, book->title, book->author, book->quantity);
}
