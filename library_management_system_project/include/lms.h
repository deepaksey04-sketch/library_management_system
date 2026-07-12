#ifndef LMS_H
#define LMS_H

#include <stddef.h>

#define MAX_BOOKS 500
#define MAX_ISSUES 1000
#define TITLE_LEN 80
#define AUTHOR_LEN 80
#define NAME_LEN 80
#define DATE_LEN 11
#define BOOKS_FILE "books.dat"
#define ISSUES_FILE "issues.dat"
#define ISSUE_DAYS 7
#define FINE_PER_DAY 5

typedef struct {
    int id;
    char title[TITLE_LEN];
    char author[AUTHOR_LEN];
    int quantity;
} Book;

typedef struct {
    int issueId;
    int bookId;
    char bookTitle[TITLE_LEN];
    int userId;
    char userName[NAME_LEN];
    char issueDate[DATE_LEN];
    char dueDate[DATE_LEN];
    char returnDate[DATE_LEN];
    int fineAmount;
    int returned;
} IssueRecord;

extern Book books[MAX_BOOKS];
extern IssueRecord issues[MAX_ISSUES];
extern int bookCount;
extern int issueCount;
extern int nextBookId;
extern int nextIssueId;

void bookMenu(void);

void addBook(void);
void updateBookMenu(void);
void removeBookMenu(void);
void searchBookMenu(void);
void viewAllBooks(void);
int findBookById(int id);
void printBookHeader(void);
void printBook(const Book *book);

void issueBook(void);
void returnBook(void);
void listIssuedBooks(void);
int findIssueByBookAndUser(int bookId, int userId);
void printIssueHeader(void);
void printIssue(const IssueRecord *issue);

void loadData(void);
void saveData(void);
void recomputeNextIds(void);

int readInt(const char *prompt, int minValue);
void readLine(const char *prompt, char *buffer, size_t size);
int containsIgnoreCase(const char *text, const char *pattern);
void todayString(char *buffer, size_t size);
void addDaysString(const char *dateText, int days, char *buffer, size_t size);
int daysBetween(const char *fromDate, const char *toDate);

#endif
