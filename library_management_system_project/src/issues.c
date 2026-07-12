#include <stdio.h>
#include <string.h>

#include "lms.h"

void issueBook(void) {
    IssueRecord issue;
    int bookId;
    int index;

    if (issueCount >= MAX_ISSUES) {
        printf("Issue record storage is full.\n");
        return;
    }

    bookId = readInt("Enter book ID to issue: ", 1);
    index = findBookById(bookId);

    if (index == -1) {
        printf("Book not found.\n");
        return;
    }

    if (books[index].quantity <= 0) {
        printf("Book is not available for issue.\n");
        return;
    }

    issue.issueId = nextIssueId++;
    issue.bookId = books[index].id;
    strncpy(issue.bookTitle, books[index].title, sizeof(issue.bookTitle));
    issue.bookTitle[sizeof(issue.bookTitle) - 1] = '\0';
    issue.userId = readInt("Enter user ID: ", 1);
    readLine("Enter user name: ", issue.userName, sizeof(issue.userName));
    todayString(issue.issueDate, sizeof(issue.issueDate));
    addDaysString(issue.issueDate, ISSUE_DAYS, issue.dueDate, sizeof(issue.dueDate));
    issue.returnDate[0] = '\0';
    issue.fineAmount = 0;
    issue.returned = 0;

    books[index].quantity--;
    issues[issueCount++] = issue;

    printf("Book issued successfully.\n");
    printf("Issue Date: %s\n", issue.issueDate);
    printf("Due Date  : %s\n", issue.dueDate);
}

void returnBook(void) {
    int bookId = readInt("Enter book ID: ", 1);
    int userId = readInt("Enter user ID: ", 1);
    int issueIndex = findIssueByBookAndUser(bookId, userId);
    int bookIndex;
    int lateDays;

    if (issueIndex == -1) {
        printf("Active issue record not found.\n");
        return;
    }

    todayString(issues[issueIndex].returnDate, sizeof(issues[issueIndex].returnDate));
    lateDays = daysBetween(issues[issueIndex].dueDate, issues[issueIndex].returnDate);
    issues[issueIndex].fineAmount = lateDays > 0 ? lateDays * FINE_PER_DAY : 0;
    issues[issueIndex].returned = 1;

    bookIndex = findBookById(bookId);
    if (bookIndex != -1) {
        books[bookIndex].quantity++;
    }

    printf("Book returned successfully.\n");
    printf("Return Date: %s\n", issues[issueIndex].returnDate);
    printf("Fine Amount: Rs. %d\n", issues[issueIndex].fineAmount);
}

void listIssuedBooks(void) {
    if (issueCount == 0) {
        printf("No issue records available.\n");
        return;
    }

    printIssueHeader();
    for (int i = 0; i < issueCount; i++) {
        printIssue(&issues[i]);
    }
}

int findIssueByBookAndUser(int bookId, int userId) {
    for (int i = 0; i < issueCount; i++) {
        if (issues[i].bookId == bookId && issues[i].userId == userId && !issues[i].returned) {
            return i;
        }
    }
    return -1;
}

void printIssueHeader(void) {
    printf("\n%-8s %-8s %-24s %-8s %-18s %-12s %-12s %-12s %-8s %-8s\n",
           "IssueID", "BookID", "Book Title", "UserID", "User Name",
           "Issue", "Due", "Return", "Fine", "Status");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
}

void printIssue(const IssueRecord *issue) {
    printf("%-8d %-8d %-24.24s %-8d %-18.18s %-12s %-12s %-12s %-8d %-8s\n",
           issue->issueId,
           issue->bookId,
           issue->bookTitle,
           issue->userId,
           issue->userName,
           issue->issueDate,
           issue->dueDate,
           issue->returned ? issue->returnDate : "-",
           issue->fineAmount,
           issue->returned ? "Returned" : "Issued");
}
